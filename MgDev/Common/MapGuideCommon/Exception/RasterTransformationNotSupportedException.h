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

#ifndef MG_RASTER_TRANSFORMATION_NOT_SUPPORTED_H_
#define MG_RASTER_TRANSFORMATION_NOT_SUPPORTED_H_

/// \ingroup Exceptions_Module

///////////////////////////////////////////////////////////////////////////////
/// \brief
/// Thrown when a raster image from a layer is using a different coordinate system than the map.
///
class MG_MAPGUIDE_API MgRasterTransformationNotSupportedException : public MgApplicationException
{
    DECLARE_CLASSNAME(MgRasterTransformationNotSupportedException)

EXTERNAL_API:

    ///////////////////////////////////////////////////////////////////////////
    /// \brief
    /// Construct a MgRasterTransformationNotSupportedException object.
    ///
    /// \param methodName
    /// Name of the method where the exception occurred.
    /// \param lineNumber
    /// Line number where the exception occurred.
    /// \param fileName
    /// File name where the exception occurred.
    /// \param whatArguments
    /// Collection of arguments used to format the message that describes what the exception is.
    /// \param whyMessageId
    /// ID of the message that describes why the exception occurs.
    /// \param whyArguments
    /// Collection of arguments used to format the message that describes why the exception occurs.
    ///
    MgRasterTransformationNotSupportedException(CREFSTRING methodName, INT32 lineNumber,
        CREFSTRING fileName, MgStringCollection* whatArguments,
        CREFSTRING whyMessageId, MgStringCollection* whyArguments) throw();

    ///////////////////////////////////////////////////////////////////////////
    /// \brief
    /// Destructor for a MgRasterTransformationNotSupportedException object.
    ///
    virtual ~MgRasterTransformationNotSupportedException() throw();

INTERNAL_API:

    DECLARE_EXCEPTION_DEFAULTS(MgRasterTransformationNotSupportedException)

CLASS_ID:

    static const INT32 m_cls_id = MapGuide_Exception_MgRasterTransformationNotSupportedException;
};

#endif