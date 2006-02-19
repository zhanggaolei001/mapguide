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

#ifndef _MGGEOMETRY_ENTITY_TYPE_H_
#define _MGGEOMETRY_ENTITY_TYPE_H_

/// \ingroup NOT_EXPOSED_module

////////////////////////////////////////////////////////////
/// \brief
/// MgGeometryEntityType defines two integer constants which
/// signify whether an MgGeometricEntity is a geometry or a
/// geometry ciomponent.
///
class MgGeometryEntityType
{
EXTERNAL_API:
    /////////////////////////////////////////////////////////////////
    /// \brief
    /// Specifies that the geometric entity is a geometry component.
    ///
    static const INT32 GeometryComponent = 0;

    ///////////////////////////////////////////////////////
    /// \brief
    /// Specifies that the geometric entity is a geometry.
    ///
    static const INT32 Geometry = 1;
};

#endif //_MGGEOMETRYCOMPONENTTYPE_H_
