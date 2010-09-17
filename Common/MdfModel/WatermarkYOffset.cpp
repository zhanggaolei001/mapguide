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
// DESCRIPTION:
// The WatermarkYOffset class implementation.
// WatermarkYOffset class is to define the offset of watermark at one dimension.
//-------------------------------------------------------------------------

#include <cmath>
#include "stdafx.h"
#include "WatermarkYOffset.h"

using namespace MDFMODEL_NAMESPACE;

const double WatermarkYOffset::doubleTolerance = 0.01;

//-------------------------------------------------------------------------
// PURPOSE: Construct and initialize an instance of the WatermarkYOffset class.
//-------------------------------------------------------------------------
WatermarkYOffset::WatermarkYOffset()
: m_unit(WatermarkOffset::Pixels)
, m_alignment(Center)
{
}

//-------------------------------------------------------------------------
// PURPOSE: Destructor. Release any dynamically allocated resources.
//-------------------------------------------------------------------------
WatermarkYOffset::~WatermarkYOffset()
{
}

//-------------------------------------------------------------------------
// Get the offset length 
//-------------------------------------------------------------------------
double WatermarkYOffset::GetLength() const
{
    return this->m_length;
}

//-------------------------------------------------------------------------
// Set the offset length 
//-------------------------------------------------------------------------
void WatermarkYOffset::SetLength(const double& dLength)
{
    this->m_length = dLength;
}

//-------------------------------------------------------------------------
// PURPOSE: Gets a value determining the meaning of the Unit property value.
// RETURNS: The type of value stored in the Unit property.
//-------------------------------------------------------------------------
WatermarkOffset::WatermarkOffsetUnit WatermarkYOffset::GetUnit() const
{
    return this->m_unit;
}

//-------------------------------------------------------------------------
// PURPOSE: Sets a value determining the meaning of the Unit property value.
// PARAMETERS:
//          unit - The type of value stored in the Unit property.
//-------------------------------------------------------------------------
void WatermarkYOffset::SetUnit(WatermarkOffset::WatermarkOffsetUnit unit)
{
    this->m_unit = unit;
}

//-------------------------------------------------------------------------
// PURPOSE: Gets a value determining the meaning of the Alignment property value.
// RETURNS: The type of value stored in the Alignment property.
//-------------------------------------------------------------------------
WatermarkYOffset::VerticalAlignment WatermarkYOffset::GetAlignment() const
{
    return this->m_alignment;
}

//-------------------------------------------------------------------------
// PURPOSE: Sets a value determining the meaning of the Alignment property value.
// PARAMETERS:
//          alignment - The type of value stored in the Alignment property.
//-------------------------------------------------------------------------
void WatermarkYOffset::SetAlignment(WatermarkYOffset::VerticalAlignment alignment)
{
    this->m_alignment = alignment;
}

bool WatermarkYOffset::Equals(WatermarkYOffset* another)
{
    return another
            && fabs(this->m_length - another->m_length) < doubleTolerance
            && this->m_unit == another->m_unit
            && this->m_alignment == another->m_alignment;
}

#ifdef _WIN32
#ifdef _DEBUG
int WatermarkYOffset::DumpMemoryLeaks()
{
    return _CrtDumpMemoryLeaks();
}
#endif
#endif
