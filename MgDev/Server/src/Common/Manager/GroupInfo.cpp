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

#include "GroupInfo.h"

///----------------------------------------------------------------------------
/// <summary>
/// Constructs the object.
/// </summary>
///
/// <exceptions>
/// MgException
/// </exceptions>
///----------------------------------------------------------------------------

MgGroupInfo::MgGroupInfo()
{
}

///----------------------------------------------------------------------------
/// <summary>
/// Constructs the object via copy constructor.
/// </summary>
///----------------------------------------------------------------------------

MgGroupInfo::MgGroupInfo(const MgGroupInfo& groupInfo)
{
    *this = groupInfo;
}

///----------------------------------------------------------------------------
/// <summary>
/// Destructs the object.
/// </summary>
///----------------------------------------------------------------------------

MgGroupInfo::~MgGroupInfo()
{
}

///----------------------------------------------------------------------------
/// <summary>
/// Performs overloaded assignment operation for this object.
/// </summary>
///----------------------------------------------------------------------------

MgGroupInfo& MgGroupInfo::operator=(const MgGroupInfo& groupInfo)
{
    if (this != &groupInfo)
    {
        m_users.clear();
        m_users = groupInfo.m_users;
    }

    return *this;
}

///----------------------------------------------------------------------------
/// <summary>
/// Determines whether or not the specified user is in this group.
/// </summary>
///----------------------------------------------------------------------------

bool MgGroupInfo::IsUserInGroup(CREFSTRING user) const
{
    return (m_users.end() != m_users.find(user));
}
