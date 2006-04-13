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

#ifndef _MGGEOMETRICPATHINSTRUCTION_H_
#define _MGGEOMETRICPATHINSTRUCTION_H_

/// \cond INTERNAL 
///////////////////////////////////////////////////////////////////////////////
/// \brief
/// MgGeometricPathInstruction is an abstract base class for all of the path
/// instruction types supported by the MgGeometricPathIterator.
class MgGeometricPathInstruction : public MgDisposable
{
EXTERNAL_API:

    ///////////////////////////////////////////////////////////////////////////
    /// \brief
    /// Gets the type of this instruction.
    ///
    /// \return
    /// Returns one of the values defined in MgGeometricPathInstructionType.
    ///
    virtual INT32 GetType() = 0;
};
/// \endcond 

#endif //_MGGEOMETRICPATHINSTRUCTION_H_
