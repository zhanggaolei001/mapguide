//
//  Copyright (C) 2004-2011 by Autodesk, Inc.
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

#ifndef MG_DUPLICATE_PARAMETER_EXCEPTION_H_
#define MG_DUPLICATE_PARAMETER_EXCEPTION_H_

///////////////////////////////////////////////////////////////////////////////
/// \brief
/// Thrown when a duplicate parameter is found.
///
class MG_MAPGUIDE_API MgDuplicateParameterException : public MgApplicationException
{
    DECLARE_CLASSNAME(MgDuplicateParameterException)

EXTERNAL_API:

    ///////////////////////////////////////////////////////////////////////////
    /// \brief
    /// Construct a MgDuplicateParameterException object.
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
    MgDuplicateParameterException(CREFSTRING methodName, INT32 lineNumber,
        CREFSTRING fileName, MgStringCollection* whatArguments,
        CREFSTRING whyMessageId, MgStringCollection* whyArguments) throw();

    ///////////////////////////////////////////////////////////////////////////
    /// \brief
    /// Destruct the MgDuplicateParameterException object.
    ///
    virtual ~MgDuplicateParameterException() throw();

INTERNAL_API:

    DECLARE_EXCEPTION_DEFAULTS(MgDuplicateParameterException)

CLASS_ID:

    static const INT32 m_cls_id = MapGuide_Exception_MgDuplicateParameterException;
};

#endif
