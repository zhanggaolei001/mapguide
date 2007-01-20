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

#ifndef MGSERVERTILESERVICE_H_
#define MGSERVERTILESERVICE_H_

#include "ServerTileDllExport.h"
#include "TileCache.h"

class MG_SERVER_TILE_API MgServerTileService : public MgTileService
{
    DECLARE_CLASSNAME(MgServerTileService)

public:
    MgServerTileService();
    ~MgServerTileService(void);
    DECLARE_CREATE_SERVICE()

    virtual MgByteReader* GetTile(MgMap* map,
                                  CREFSTRING baseMapLayerGroupName,
                                  INT32 tileColumn,
                                  INT32 tileRow);

    virtual MgByteReader* GetTile(MgResourceIdentifier* mapDefinition,
                                  CREFSTRING baseMapLayerGroupName,
                                  INT32 tileColumn,
                                  INT32 tileRow,
                                  INT32 scaleIndex);

    virtual void SetTile(MgByteReader* img,
                         MgMap* map,
                         INT32 scaleIndex,
                         CREFSTRING baseMapLayerGroupName,
                         INT32 tileColumn,
                         INT32 tileRow);

    virtual void ClearCache(MgMap* map);

    virtual void NotifyResourcesChanged(MgSerializableCollection* resources);

    void SetConnectionProperties(MgConnectionProperties* connProp);

private:

    void ClearMapCache(CREFSTRING mapName);

    // member data
    Ptr<MgTileCache> m_tileCache;

    typedef std::map<STRING, MgMemoryStreamHelper*> MapCache;
    static MapCache sm_mapCache;
    static ACE_Recursive_Thread_Mutex sm_mutex;
    static INT32 sm_mapCacheSize;
    static bool sm_renderOnly;

};

#endif
