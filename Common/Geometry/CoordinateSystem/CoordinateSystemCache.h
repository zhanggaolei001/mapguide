//
//  Copyright (C) 2004-2007 by Autodesk, Inc.
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

#ifndef MGCOORDINATESYSTEMCACHE_H_
#define MGCOORDINATESYSTEMCACHE_H_

#include "CoordinateSystem.h"

typedef std::map<STRING, MgCoordinateSystem*> MgCoordinateSystemMap;

class MgCoordinateSystemCache
{
/// Constructors/Destructor

public:

    MgCoordinateSystemCache();
    virtual ~MgCoordinateSystemCache();

private:

    // Unimplemented copy constructor and assignment operator.

    MgCoordinateSystemCache(const MgCoordinateSystemCache&);
    MgCoordinateSystemCache& operator=(const MgCoordinateSystemCache&);

/// Methods

public:

    static MgCoordinateSystemCache* GetInstance();

    void Clear();

    MgCoordinateSystem* Get(CREFSTRING key);
    void Set(CREFSTRING key, MgCoordinateSystem* value);

/// Data Members

private:

    static auto_ptr<MgCoordinateSystemCache> sm_coordinateSystemCache;

    ACE_Recursive_Thread_Mutex m_mutex;
    MgCoordinateSystemMap m_coordinateSystemMap;
};

#endif
