//
//  Copyright (C) 2004-2015 by Autodesk, Inc.
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

#ifndef _MGGEOMETRYSIMPLIFICATIONALGORITHMTYPE_H_
#define _MGGEOMETRYSIMPLIFICATIONALGORITHMTYPE_H_

/// \defgroup MgGeometrySimplificationAlgorithmType MgGeometrySimplificationAlgorithmType
/// \ingroup Geometry_Module_classes
/// \{

////////////////////////////////////////////////////////////
/// \brief
/// MgGeometrySimplificationAlgorithmType defines constants indicating
/// the various simplification algorithms available for simplifying
/// geometry instances
///
/// \since 4.0
class MgGeometrySimplificationAlgorithmType
{
PUBLISHED_API:
    /////////////////////////////////////////////////////////////////
    /// \brief
    /// Specifies that the Douglas-Peucker algorithm be used for simplification.
    ///
    static const INT32 DouglasPeucker = 0;

    ///////////////////////////////////////////////////////
    /// \brief
    /// Specifies that the Topology Preserving algorithm be used for simplification
    ///
    static const INT32 TopologyPreserving = 1;
};
/// \}

#endif //_MGGEOMETRYSIMPLIFICATIONALGORITHMTYPE_H_