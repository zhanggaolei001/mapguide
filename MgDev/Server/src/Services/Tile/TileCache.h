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

#ifndef _MG_TILE_CACHE_H_
#define _MG_TILE_CACHE_H_

#include "ServerTileDllExport.h"

// File-system-based cache for base map layer group tiles generated by the rendering service.
class MG_SERVER_TILE_API MgTileCache : public MgDisposable
{
public:
    MgTileCache();

    MgByteReader* Get(MgMap* map, int scaleIndex, CREFSTRING group, int i, int j);
    void Set(MgByteReader* img, MgMap* map, int scaleIndex, CREFSTRING group, int i, int j);
    void Clear(MgMap* map);
    void Clear(MgResourceIdentifier* resId);

protected:
    virtual void Dispose()
    {
        delete this;
    }

private:
    STRING GetBasePath(MgMap* map);
    STRING GetBasePath(MgResourceIdentifier* resId);
    STRING GetFullPath(MgMap* map, int scaleIndex, CREFSTRING group);
    STRING CreateFullPath(MgMap* map, int scaleIndex, CREFSTRING group);

    ACE_Recursive_Thread_Mutex m_mutexGet;
    ACE_Recursive_Thread_Mutex m_mutexSet;
    STRING m_path;
};

#endif
