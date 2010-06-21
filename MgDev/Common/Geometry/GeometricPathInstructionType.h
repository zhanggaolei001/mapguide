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

#ifndef _MGGEOMETRICPATHINSTRUCTIONTYPE_H_
#define _MGGEOMETRICPATHINSTRUCTIONTYPE_H_

/// \cond INTERNAL
///////////////////////////////////////////////////////////////////////////////
/// \brief
/// MgGeometricPathInstructionType defines enumerated values used to specify
/// the instructions contained in a geometric path. See MgGeometricPathIterator
/// for a definition of a geometric path.
class MgGeometricPathInstructionType
{
EXTERNAL_API:
    ///////////////////////////////////////////////////////////////////////////
    /// \brief
    /// Defines the beginning coordinate of a new segment in a geometric
    /// path.
    ///
    static const INT32 MoveTo = 0;

    ///////////////////////////////////////////////////////////////////////////
    /// \brief
    /// Defines a straight line from the last coordinate in the geometric
    /// path to the coordinate included with this instruction.
    ///
    static const INT32 LineTo = 1;

    ///////////////////////////////////////////////////////////////////////////
    /// \brief
    /// Defines a quadratic curve from the last coordinate in the geometric
    /// path using the first coordinate of this instruction as the end point
    /// and the second coordinate as the control point.
    ///
    static const INT32 QuadTo = 2;

    ///////////////////////////////////////////////////////////////////////////
    /// \brief
    /// Defines a line from the current coordinate in the geometric path back
    /// to the last MgGeometricPathInstruction.MoveTo, which is the beginning
    /// of the last segment in the path.
    ///
    static const INT32 Close = 4;
};
/// \endcond

#endif //_MGGEOMETRICPATHINSTRUCTIONTYPE_H_
