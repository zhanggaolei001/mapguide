
#ifndef complex_polygon_gd_H
#define complex_polygon_gd_H

#include "gd.h"

struct EdgeState;
struct Point;

class complex_polygon_gd
{
public:
    complex_polygon_gd();
    ~complex_polygon_gd();

    void FillPolygon(Point * VertexList, int nVerts, int* Contours, int nContours, int Color, gdImagePtr target);

private:
    
    //This is what you want to implement for your own render target
    //for all the rest of the code to work with it
    inline void DrawHorizontalLineSeg(int Y, int StartX, int EndX, int Color, gdImagePtr target)
    {
        if (StartX <= EndX)
            gdImageLine(target, StartX, Y, EndX, Y, Color);
        //else //this condition fixes a case when EndX is to the left of StartX and we draw one pixel more than we should
        //    gdImageLine(target, StartX, Y, StartX, Y, Color);
    }

    void BuildGET(Point *, int* Contours, int nContours, EdgeState *, int MaxY);
    void MoveXSortedToAET(int);
    void ScanOutAET(int, int, gdImagePtr);
    void AdvanceAET(void);
    void XSortAET(void);

    /* Pointers to global edge table (GET) and active edge table (AET) */
    struct EdgeState *m_GETPtr, *m_AETPtr;
    EdgeState* m_bufEdgeState;
    size_t m_nBufEdgeState;
   
};

#endif
