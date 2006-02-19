//
//  Copyright (C) 2004-2006  Autodesk, Inc.
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

#ifndef DATAVALUESTACK_H
#define DATAVALUESTACK_H

template <class T> class DataValueStack
{
public:

    DataValueStack()
    {
        m_count = 0;
        m_len = 0;
        m_data = NULL;
    }

    virtual ~DataValueStack()
    {
        //note this destructor will not call
        //the individual element destructors
        if (m_data)
            delete [] m_data;
    }

    inline void push(T* dv)
    {
        if (m_count >= m_len)
            make_bigger();

        m_data[m_count++] = dv;
    }

    inline T* pop()
    {
        if (empty())
            return NULL;

        return m_data[--m_count];
    }

    inline size_t size()
    {
        return m_count;
    }

    inline bool empty()
    {
        return m_count == 0;
    }

    inline T* top()
    {
        if (empty())
            return NULL;

        return m_data[m_count - 1];
    }

private:

    void make_bigger()
    {
        if (m_data)
        {
            T** temp = new T*[m_len*2];
            memcpy(temp, m_data, m_len * sizeof(T*));
            delete [] m_data;
            m_data = temp;
            m_len *= 2;
        }
        else
        {
            //initial allocation
            m_len = 4;
            m_data = new T*[m_len];
        }
    }


    T** m_data;
    size_t m_len;
    size_t m_count;
};

#endif
