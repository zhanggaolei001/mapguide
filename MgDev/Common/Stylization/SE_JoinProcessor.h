//
//  Copyright (C) 2007 by Autodesk, Inc.
//
//  This library is free software; you can redistribute it and/or
//  modify it under the terms of version 2.1 of the GNU Lesser
//  General Public License as published by the Free Software Foundation.
//
//  This library is distributed in the hope that it will be useful,
//  but WITHOUT ANY WARRANTY; without even the implied warranty of
//  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
//  Lesser General Public License for more details.
//
//  You should have received a copy of the GNU Lesser General Public
//  License along with this library; if not, write to the Free Software
//  Foundation, Inc., 51 Franklin St, Fifth Floor, Boston, MA  02110-1301  USA
//

#ifndef SE_JOINPROCESSOR_H
#define SE_JOINPROCESSOR_H

#include "SE_RenderProxies.h"
#include "SE_JoinTransform.h"
#include "SE_Join.h"
#include "SE_Cap.h"
#include "SE_Matrix.h"
#include <algorithm>
#include <cstring>

#define MAX_STACK_ALLOC 2048

class SE_IJoinProcessor
{
public:
    virtual LineBuffer* Transform(LineBuffer* data, LineBufferPool* lbp) = 0;
    virtual void Transform(const SE_Tuple outline[4],
                           std::vector<SE_Tuple>& uvquads,
                           std::vector<SE_Tuple>& txquads) = 0;
};

template<class USER_DATA> class SE_JoinProcessor : public SE_IJoinProcessor
{
protected:
    typedef SE_Join<USER_DATA>          JOIN_TYPE;
    typedef SE_Cap<USER_DATA>           CAP_TYPE;
    typedef SE_JoinTransform<USER_DATA> BUFFER_TYPE;
    typedef USER_DATA                   DATA_TYPE;

    SE_Tuple                           m_endpt;
    SE_SegmentInfo*                    m_segs;
    JOIN_TYPE*                         m_join;
    CAP_TYPE*                          m_cap;
    BUFFER_TYPE                        m_joinbuf;
    typename BUFFER_TYPE::Transformer* m_tx;

    bool                  m_closed;
    double                m_tolerance;
    double                m_position;
    double                m_length;
    double                m_sym_ext[2];
    double                m_clip_ext[2];
    double                m_draw_ext[2];

    /* Fills segs with information from geometry. Caller must delete returned array */
    SE_SegmentInfo* ParseGeometry(SE_RenderLineStyle* style, LineBuffer* geom, int contour, int& nsegs);
    void ProcessSegments(BUFFER_TYPE& joins, SE_SegmentInfo* segs, int nsegs);

    /* Specialize these functions for the various types of user data */
    SE_INLINE void ProcessUserData(USER_DATA& data, JOIN_TYPE* join, BUFFER_TYPE& buffer);
    SE_INLINE void ProcessUserData(USER_DATA& data, CAP_TYPE* cap, BUFFER_TYPE& buffer);
    SE_INLINE double& GetTolerance(USER_DATA& data);

public:
    SE_JoinProcessor( JOIN_TYPE* join,
                      CAP_TYPE* cap,
                      LineBuffer* geom,
                      int contour,
                      SE_RenderLineStyle* style );
    ~SE_JoinProcessor();

    SE_INLINE void UpdateLinePosition(double position);
    SE_INLINE double StartPosition() const;
    SE_INLINE double EndPosition() const;

    virtual LineBuffer* Transform(LineBuffer* data, LineBufferPool* lbp);
    virtual void Transform(const SE_Tuple outline[4],
                           std::vector<SE_Tuple>& uvquads,
                           std::vector<SE_Tuple>& txquads);
    void AppendOutline(LineBuffer* lb);
};


struct NullData
{
};


struct OptData
{
    double join_width;
    double join_error;
};


typedef SE_JoinProcessor<NullData> NullProcessor;
typedef SE_JoinProcessor<OptData> OptProcessor;

// Function definitions

template<class USER_DATA>
SE_JoinProcessor<USER_DATA>::SE_JoinProcessor( JOIN_TYPE* join,
                                               CAP_TYPE* cap,
                                               LineBuffer* geom,
                                               int contour,
                                               SE_RenderLineStyle* style ) :
    m_join(join),
    m_cap(cap),
    m_joinbuf(join->join_height(), 3 * geom->cntr_size(contour) / 2)
{
    int nsegs;
    SE_SegmentInfo* segbuf = ParseGeometry(style, geom, contour, nsegs);
    ProcessSegments(m_joinbuf, segbuf, nsegs);
}


template<class USER_DATA>
SE_JoinProcessor<USER_DATA>::~SE_JoinProcessor()
{
    delete[] m_segs;
    delete m_tx;
}


template<class USER_DATA>
double& SE_JoinProcessor<USER_DATA>::GetTolerance(USER_DATA& /*data*/)
{
    m_tolerance = .3;
    return m_tolerance;
}


template<class USER_DATA>
SE_SegmentInfo* SE_JoinProcessor<USER_DATA>::ParseGeometry(SE_RenderLineStyle* style,
                                                           LineBuffer* geometry,
                                                           int contour, int& nsegs)
{
    nsegs = geometry->cntr_size(contour) - 1;

    /* If the contour is closed, dispense with offsets and make the transform continuous */
    double startoff, endoff;
    m_closed = geometry->contour_closed(contour);
    if (m_closed)
        startoff = endoff = 0.0;
    else
        startoff = style->startOffset, endoff = style->endOffset;

    m_sym_ext[0] = std::min<double>( std::min<double>(style->bounds[0].x, style->bounds[1].x),
                                            std::min<double>(style->bounds[2].x, style->bounds[3].x) );
    double left = std::max<double>(0.0, startoff);
    m_sym_ext[1] = std::max<double>( std::max<double>(style->bounds[0].x, style->bounds[1].x),
                                            std::max<double>(style->bounds[2].x, style->bounds[3].x) );
    double right = std::min<double>(-endoff, 0.0);

    SE_SegmentInfo* segbuf = m_segs = new SE_SegmentInfo[nsegs];

    m_length = 0.0;
    SE_SegmentInfo* segs = segbuf;
    int first_idx = geometry->contour_start_point(contour);
    int last_idx = geometry->contour_end_point(contour);

    for (int i = first_idx, j = first_idx; i < last_idx; ++i)
    {
        segs->vertex = (SE_Tuple*)&geometry->x_coord(j);
        segs->next = *((SE_Tuple*)&geometry->x_coord(i+1)) - *((SE_Tuple*)&geometry->x_coord(j));
        /* TODO: handle colinear series of points (3+) */
        segs->nextlen = segs->next.length();
        /* TODO: not very robust! Find something mathematically sound! */
        if (segs->nextlen < .005)
        {
            nsegs--;
            continue;
        }
        j = i+1;
        segs->vertpos = m_length;
        m_length += segs->nextlen;
        segs++;
    }

    m_clip_ext[0] = left;
    m_clip_ext[1] = m_length + right;

    if (endoff >= 0.0 && startoff < 0.0)
    {
        m_draw_ext[1] = m_clip_ext[1];
        m_draw_ext[0] = m_clip_ext[1] -
            ceil((m_clip_ext[1] - m_clip_ext[0]) / style->repeat) * style->repeat;
    }
    else
    {
        m_draw_ext[0] = m_clip_ext[0];
        m_draw_ext[1] = m_clip_ext[1];
    }

    /* Extend the end segments, so that all of the line stylization is within the domain
     * of the transform */
    if (m_length - left + right <= 0.0)
    {
        nsegs = 0;
        return m_segs;
    }

    if (left > 0.0)
    {
        int i = 0;
        while(++i < nsegs && segbuf[i].vertpos < left);
        if (segbuf[i].vertpos == left)
        {
            nsegs -= i;
            segbuf += i;
        }
        else
        {
            nsegs -= i - 1;
            segbuf += i - 1;
            double frac = (left - segbuf[i-1].vertpos) / segbuf[i-1].nextlen;
            m_endpt = *segbuf[i-1].vertex + (segbuf[i-1].next * frac);
            segbuf[i-1].vertex = &m_endpt;
            segbuf[i-1].vertpos = left;
            segbuf[i-1].next *= 1.0 - frac;
            segbuf[i-1].nextlen *= 1.0 - frac;
        }
    }

    if (right < 0.0)
    {
        int i = nsegs;
        double threshold = segbuf[nsegs-1].vertpos + segbuf[nsegs-1].nextlen + right;
        while(--i >= 0 && segbuf[i].vertpos > threshold);
        nsegs = i + 1;

        if (segbuf[i].vertpos == threshold)
            --nsegs;
        else
        {
            double frac = (threshold - segbuf[i].vertpos) / segbuf[i].nextlen;
            segbuf[i].next *= 1.0 - frac;
            segbuf[i].nextlen *= 1.0 - frac;
        }
    }

    return segbuf;
}


template<class USER_DATA>
void SE_JoinProcessor<USER_DATA>::ProcessSegments(BUFFER_TYPE& joins, SE_SegmentInfo* segs, int nsegs)
{
    if (nsegs == 0)
    {
        m_tx = NULL;
        return;
    }

    SE_SegmentInfo* curseg = segs;
    SE_SegmentInfo* lastseg = segs + nsegs - 1;

    if (!m_closed)
    {
        USER_DATA data;
        m_cap->Construct(*segs, GetTolerance(data), true);
        m_cap->Transform(joins);
        ProcessUserData(data, m_cap, joins);
    }
    else
    {
        USER_DATA data;
        m_join->Construct(*lastseg, *segs, GetTolerance(data));
        m_join->Transform(joins);
        ProcessUserData(data, m_join, joins);
    }

    while (curseg++ < lastseg)
    {
        USER_DATA data;
        m_join->Construct(*(curseg-1), *curseg, GetTolerance(data));
        m_join->Transform(joins);
        ProcessUserData(data, m_join, joins);
    }

    if (!m_closed)
    {
        USER_DATA data;
        m_cap->Construct(*lastseg, GetTolerance(data), false);
        m_cap->Transform(joins);
        ProcessUserData(data, m_cap, joins);
    }
    else
    {
        USER_DATA data;
        m_join->Construct(*lastseg, *segs, GetTolerance(data));
        m_join->Transform(joins);
        ProcessUserData(data, m_join, joins);
    }
    joins.Close();

    /* We (potentially) sacrifice 1/10,000 of a symbol so that we don't end up with
     * incredibly thin slices of adjacent symbols at the ends of the line*/
    double delta = (m_sym_ext[1] - m_sym_ext[0]) * 1e-5;
    m_tx = joins.GetTransformer(m_clip_ext[0] + delta, m_clip_ext[1] - delta);
}


template<class USER_DATA>
void SE_JoinProcessor<USER_DATA>::UpdateLinePosition(double position)
{
    m_position = position;
}


template<class USER_DATA> double SE_JoinProcessor<USER_DATA>::StartPosition() const
{
    return m_draw_ext[0];
}


template<class USER_DATA> double SE_JoinProcessor<USER_DATA>::EndPosition() const
{
    return m_draw_ext[1];
}


template<class USER_DATA>
void SE_JoinProcessor<USER_DATA>::ProcessUserData(USER_DATA& /*data*/,
                                                  JOIN_TYPE* /*join*/,
                                                  BUFFER_TYPE& /*buffer*/)
{
}


template<class USER_DATA>
void SE_JoinProcessor<USER_DATA>::ProcessUserData(USER_DATA& /*data*/,
                                                  CAP_TYPE* /*cap*/,
                                                  BUFFER_TYPE& /*buffer*/)
{
}


template<class USER_DATA>
LineBuffer* SE_JoinProcessor<USER_DATA>::Transform(LineBuffer* data, LineBufferPool* lbp)
{
    if (m_tx)
    {
        return m_tx->TransformLine(data, m_position, lbp);
    }
    else
        return lbp->NewLineBuffer(0);
}


template<class USER_DATA>
void SE_JoinProcessor<USER_DATA>::Transform(const SE_Tuple outline[4],
                                            std::vector<SE_Tuple>& uvquads,
                                            std::vector<SE_Tuple>& txquads)
{
    if (m_tx)
        m_tx->TransformArea(m_position, outline, uvquads, txquads);
}


template<class USER_DATA>
void SE_JoinProcessor<USER_DATA>::AppendOutline(LineBuffer* lb)
{
    m_joinbuf.GetTransformOutline(lb);
}

#endif // SE_JOINPROCESSOR_H
