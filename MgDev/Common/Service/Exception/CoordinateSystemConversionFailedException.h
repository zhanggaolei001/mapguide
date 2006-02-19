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

/// \ingroup Exceptions_Module

#ifndef MG_COORDINATE_SYSTEM_CONVERSION_FAILED_EXCEPTION_H_
#define MG_COORDINATE_SYSTEM_CONVERSION_FAILED_EXCEPTION_H_

#include "Common.h"

///////////////////////////////////////////////////////////////////////////////
/// \brief
/// Thrown when a coordinate system conversion fails.
///
class MG_SERVICE_API MgCoordinateSystemConversionFailedException : public MgApplicationException
{
    DECLARE_CLASSNAME(MgCoordinateSystemConversionFailedException)

EXTERNAL_API:

    ///////////////////////////////////////////////////////////////////////////
    /// \brief
    /// Construct a MgCoordinateSystemConversionFailedException object.
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
    MgCoordinateSystemConversionFailedException(CREFSTRING methodName, INT32 lineNumber,
        CREFSTRING fileName, MgStringCollection* whatArguments,
        CREFSTRING whyMessageId, MgStringCollection* whyArguments) throw();

    ///////////////////////////////////////////////////////////////////////////
    /// \brief
    /// Destructor for a MgCoordinateSystemConversionFailedException object.
    ///
    virtual ~MgCoordinateSystemConversionFailedException() throw();

INTERNAL_API:

    DECLARE_EXCEPTION_DEFAULTS(MgCoordinateSystemConversionFailedException)

CLASS_ID:

    static const INT32 m_cls_id = Common_Exception_MgCoordinateSystemConversionFailedException;
};

#endif
