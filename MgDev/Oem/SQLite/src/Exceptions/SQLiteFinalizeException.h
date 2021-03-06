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

#ifndef _SQLITE_FINALIZE_EXCEPTION_H
#define _SQLITE_FINALIZE_EXCEPTION_H

class SQLiteFinalizeException: public SqliteException
{
EXTERNAL_API:

    //////////////////////////////////////////////////////////////////
    ///<summary>
    /// Construct a SQLiteFinalizeException object
    ///<param name="methodName">Name of the method where the exception occured</param>
    ///<param name="lineNumber">Line number where the exception occured</param>
    ///<param name="fileName">File name where the exception occured</param>
    ///</summary>
    ///
    SQLiteFinalizeException(CREFSTRING methodName, UINT32 lineNumber, CREFSTRING fileName, CREFSTRING message) throw();

    //////////////////////////////////////////////////////////////////
    ///<summary>
    /// Destructor for a SQLiteFinalizeException object
    ///</summary>
    ///
    virtual ~SQLiteFinalizeException() throw();

    //////////////////////////////////////////////////////////////////
    ///<summary>
    /// Retrieve the formatted exception message for the specified locale.
    /// <param name="nLocale">The locale identifier to format the message text.</param>
    /// </summary>
    ///
    STRING GetExceptionMessage() throw();

INTERNAL_API:
    DECLARE_EXCEPTION_DEFAULTS(SQLiteFinalizeException)

CLASS_ID:
    static const INT32 m_cls_id = SQLITE_Exception_SQLiteFinalizeException;
};

#endif //_SQLITE_FINALIZE_EXCEPTION_H
