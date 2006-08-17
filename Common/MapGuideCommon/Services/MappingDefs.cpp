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

#include "MapGuideCommon.h"
#include "MappingDefs.h"

///////////////////////////////////////////////////////////////////////////////
/// Page size units for Mapping Service.
///
const STRING MgPageUnitsType::Inches        = L"in";
const STRING MgPageUnitsType::Millimeters   = L"mm";

///////////////////////////////////////////////////////////////////////////////
/// Coordinate space for geometry returned from QueryFeatureProperties.
///
const STRING MgCoordinateSpace::None        = L"None";
const STRING MgCoordinateSpace::Map         = L"Map";
const STRING MgCoordinateSpace::Display     = L"Display";
