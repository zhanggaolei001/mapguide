//
//  Copyright (C) 2004-2010 by Autodesk, Inc.
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

//-------------------------------------------------------------------------
// DESCRIPTION: The StringObject class implementation.
//-------------------------------------------------------------------------

#include "../stdafx.h"
#include "StringObject.h"

//-------------------------------------------------------------------------
// PURPOSE: Default constructor of the StringObject class.
//-------------------------------------------------------------------------
StringObject::StringObject()
{
}

//-------------------------------------------------------------------------
// PURPOSE: Constructor. Initialize the StringObject class with a specific resource ID.
//-------------------------------------------------------------------------
StringObject::StringObject(const wchar_t* str) :
    m_str(str)
{
}

//-------------------------------------------------------------------------
// PURPOSE: Destructor. Delete all adopted objects.
//-------------------------------------------------------------------------
StringObject::~StringObject()
{
}

//-------------------------------------------------------------------------
// PURPOSE: Manage properties of this StringObject object.
//-------------------------------------------------------------------------
void StringObject::SetString(const MdfString& str)
{
    m_str = str;
}