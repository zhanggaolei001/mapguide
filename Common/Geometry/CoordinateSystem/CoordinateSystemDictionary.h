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

#ifndef _MGCOORDINATESYSTEMDICTIONARY_H_
#define _MGCOORDINATESYSTEMDICTIONARY_H_

/// \defgroup MgCoordinateSystemDictionary MgCoordinateSystemDictionary
/// \ingroup Coordinate_System_classes
/// \{

////////////////////////////////////////////////////////////////
/// \brief
/// Basic functionality for the coordinate system dictionary
///

class MgCoordinateSystemDictionary : public MgCoordinateSystemDictionaryBase
{
    DECLARE_CLASSNAME(MgCoordinateSystemDictionary)

PUBLISHED_API:
        virtual MgCoordinateSystem* NewCoordinateSystem()=0;
        virtual MgCoordinateSystem* GetCoordinateSystem(CREFSTRING sName)=0;

protected:
    /////////////////////////////////////////////////////////////////
    /// \brief
    /// Get the class Id
    ///
    /// \return
    /// The integer value
    ///
    INT32 GetClassId(){return m_cls_id;};

CLASS_ID:
    static const INT32 m_cls_id = CoordinateSystem_CoordinateSystemDictionary;
};
/// \}

#endif //_MGCOORDINATESYSTEMDICTIONARY_H_