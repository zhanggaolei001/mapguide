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

#ifndef _MgCoordinateXY_H_
#define _MgCoordinateXY_H_

/// \defgroup MgCoordinateXY MgCoordinateXY
/// \ingroup Geometry_Module_classes
/// \{

class MgCoordinateXY;
template class MG_GEOMETRY_API Ptr<MgCoordinateXY>;

////////////////////////////////////////////////////////////////
/// \brief
/// MgCoordinateXY is a concrete class derived from the abstract
/// class MgCoordinate.
///
/// \remarks
/// It has no public constructor. Instances
/// are created by calling the non-static
/// MgGeometryFactory::CreateCoordinateXY() method.
///
class MG_GEOMETRY_API MgCoordinateXY : public MgCoordinate
{
    DECLARE_CREATE_OBJECT()
    DECLARE_CLASSNAME(MgCoordinateXY)

PUBLISHED_API:
    /// <!-- Syntax in .Net, Java, and PHP -->
    /// \htmlinclude DotNetSyntaxTop.html
    /// virtual int GetDimension();
    /// \htmlinclude SyntaxBottom.html
    /// \htmlinclude JavaSyntaxTop.html
    /// virtual int GetDimension();
    /// \htmlinclude SyntaxBottom.html
    /// \htmlinclude PHPSyntaxTop.html
    /// virtual int GetDimension();
    /// \htmlinclude SyntaxBottom.html
    ///
    virtual INT32 GetDimension();  /// __get

    /// <!-- Syntax in .Net, Java, and PHP -->
    /// \htmlinclude DotNetSyntaxTop.html
    /// virtual double GetX();
    /// \htmlinclude SyntaxBottom.html
    /// \htmlinclude JavaSyntaxTop.html
    /// virtual double GetX();
    /// \htmlinclude SyntaxBottom.html
    /// \htmlinclude PHPSyntaxTop.html
    /// virtual double GetX();
    /// \htmlinclude SyntaxBottom.html
    ///
    virtual double GetX();  /// __get

    /// <!-- Syntax in .Net, Java, and PHP -->
    /// \htmlinclude DotNetSyntaxTop.html
    /// virtual double GetY();
    /// \htmlinclude SyntaxBottom.html
    /// \htmlinclude JavaSyntaxTop.html
    /// virtual double GetY();
    /// \htmlinclude SyntaxBottom.html
    /// \htmlinclude PHPSyntaxTop.html
    /// virtual double GetY();
    /// \htmlinclude SyntaxBottom.html
    ///
    virtual double GetY();  /// __get

    /// <!-- Syntax in .Net, Java, and PHP -->
    /// \htmlinclude DotNetSyntaxTop.html
    /// virtual double GetZ();
    /// \htmlinclude SyntaxBottom.html
    /// \htmlinclude JavaSyntaxTop.html
    /// virtual double GetZ();
    /// \htmlinclude SyntaxBottom.html
    /// \htmlinclude PHPSyntaxTop.html
    /// virtual double GetZ();
    /// \htmlinclude SyntaxBottom.html
    ///
    virtual double GetZ();  /// __get

    /// <!-- Syntax in .Net, Java, and PHP -->
    /// \htmlinclude DotNetSyntaxTop.html
    /// virtual double GetM();
    /// \htmlinclude SyntaxBottom.html
    /// \htmlinclude JavaSyntaxTop.html
    /// virtual double GetM();
    /// \htmlinclude SyntaxBottom.html
    /// \htmlinclude PHPSyntaxTop.html
    /// virtual double GetM();
    /// \htmlinclude SyntaxBottom.html
    ///
    virtual double GetM();  /// __get

INTERNAL_API:

    ///////////////////////////////////////////////////////////////////////////
    /// \brief
    /// Construct a MgCoordinateXY object
    ///
    MgCoordinateXY(double x, double y);

    ///////////////////////////////////////////////////////////////////////////
    /// \brief
    /// Construct an empty MgCoordinateXY object for deserialization
    ///
    MgCoordinateXY();

    //////////////////////////////////////////////////////////////////
    /// \brief
    /// Returns a copy of this object
    ///
    MgCoordinate* Copy();

    //////////////////////////////////////////////////////////////////
    /// \brief
    /// Serialize data to TCP/IP stream
    ///
    /// \param stream
    /// Stream
    ///
    virtual void Serialize(MgStream* stream);

    //////////////////////////////////////////////////////////////////
    /// \brief
    /// Deserialize data from TCP/IP stream
    ///
    /// \param stream
    /// Stream
    ///
    virtual void Deserialize(MgStream* stream);

    //////////////////////////////////////////////////////////////////
    /// \brief
    /// Test 2 coordinates for equality
    ///
    virtual bool Equals(MgCoordinate* coord);

    //////////////////////////////////////////////////////////////////
    /// \brief
    /// Convert to XML representation
    ///
    virtual void ToXml(string &str);

    //////////////////////////////////////////////////////////////////
    /// \brief
    /// Convert to AWKT representation
    ///
    virtual void ToAwkt(REFSTRING awktStr, REFSTRING coordDim, bool is2dOnly);

    //////////////////////////////////////////////////////////////////
    /// \brief
    /// Get the unique identifier for the class
    ///
    /// \return
    /// Class Identifider.
    ///
    virtual INT32 GetClassId();

protected:

    //////////////////////////////////////////////
    /// \brief
    /// Dispose this object.
    ///
    virtual void Dispose();

private:
    double      m_x;
    double      m_y;

CLASS_ID:
    static const INT32 m_cls_id = Geometry_CoordinateXY;
};
/// \}

#endif // _MgCoordinateXY_H_
