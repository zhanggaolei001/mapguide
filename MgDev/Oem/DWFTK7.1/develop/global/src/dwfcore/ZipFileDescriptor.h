//
//  Copyright (c) 2003-2005 by Autodesk, Inc.
//
//  By using this code, you are agreeing to the terms and conditions of
//  the License Agreement included in the documentation for this code.
//
//  AUTODESK MAKES NO WARRANTIES, EXPRESS OR IMPLIED,
//  AS TO THE CORRECTNESS OF THIS CODE OR ANY DERIVATIVE
//  WORKS WHICH INCORPORATE IT.
//
//  AUTODESK PROVIDES THE CODE ON AN "AS-IS" BASIS
//  AND EXPLICITLY DISCLAIMS ANY LIABILITY, INCLUDING
//  CONSEQUENTIAL AND INCIDENTAL DAMAGES FOR ERRORS,
//  OMISSIONS, AND OTHER PROBLEMS IN THE CODE.
//
//  Use, duplication, or disclosure by the U.S. Government is subject to
//  restrictions set forth in FAR 52.227-19 (Commercial Computer Software
//  Restricted Rights) and DFAR 252.227-7013(c)(1)(ii) (Rights in Technical
//  Data and Computer Software), as applicable.
//


#ifndef _DWFCORE_ZIP_FILE_DESCRIPTOR_H
#define _DWFCORE_ZIP_FILE_DESCRIPTOR_H


///
///\file        dwfcore/ZipFileDescriptor.h
///\brief       This header contains the declaration for the DWFZipFileDescriptor class.
///

#include "dwfcore/String.h"
#include "dwfcore/InputStream.h"
#include "dwfcore/OutputStream.h"
#include "dwfcore/FileDescriptor.h"
#include "dwfcore/zip/zip.h"
#include "dwfcore/zip/unzip.h"



namespace DWFCore
{

class DWFZipFileDescriptor;

///
///\class       DWFZipFileIndex   dwfcore/ZipFileDescriptor.h  "dwfcore/ZipFileDescriptor.h"
///\brief       A wrapper implementation for a zip file (INFOZIP/PKZIP) index.
///\since       1.1
///\warning     No validation is made in the unzip library to ensure that a specific file's index is not
///                used for another file.
///
///
class DWFZipFileIndex : public DWFCoreMemory
{
    friend class DWFZipFileDescriptor;

protected:
    ///
    ///         Accesses the pointer to the file index structure.
    ///\return  A pointer to the index structure.
    ///\throw   None
    ///
    unzIndex * index() throw() { return &_oUnzIndex; }

private:
    ///
    ///         The file index structure.  We wrap unzIndex so as not to expose the unzip library
    ///             native type to the world.
    ///
    unzIndex    _oUnzIndex;

};

///
///\class       DWFZipFileDescriptor   dwfcore/ZipFileDescriptor.h  "dwfcore/ZipFileDescriptor.h"
///\brief       A descriptor implementation for zip (INFOZIP/PKZIP) file archive access and control.
///\since       1.0.1
///
///\warning     This object is not thread safe.  This is due to the underlying library implementation.
///\todo        Modify this class or derive another that provides thread-safe concurrent archive access.
///
class DWFZipFileDescriptor : public DWFCoreMemory
                           , public DWFFileDescriptor
{

public:

    ///
    ///\enum    teFileMode
    ///\brief   Enumeration values that define the characteristics
    ///         by which the archive will be opened and used.
    ///
    ///         One of these values must be provided to the constructor
    ///         to properly configure this descriptor.  At this time,
    ///         only two modes really exist, unzip (read-only) and zip
    ///         (write-only).  The values of the zip mode enumerations
    ///         should always be kept in sync with the compression levels
    ///         defined in zlib.h and used by zlib.
    ///
    typedef enum
    {
        ///
        ///     Open the archive for extracting data only.
        ///
        eUnzip              = -2,

        ///
        ///     Open the archive for storing data only; using the
        ///     default blend (by zlib) of speed and size.
        ///
        eZip                = -1,
        
        ///
        ///     Open the archive for storing data only; using no compression.
        ///
        eZipNone            = 0,

        ///
        ///     Open the archive for storing data only; choosing maximum 
        ///     data deflation speed over file size.
        ///
        eZipFastest         = 1,

        ///
        ///     Open the archive for storing data only; choosing data 
        ///     deflation speed over file size.  This option will
        ///     be slower and compress better than \a eZipFastest.
        ///
        eZipFast            = 3,

        ///
        ///     Open the archive for storing data only; choosing data
        ///     data deflation speed over file size.  This option will
        ///     be slower and compress better than \a eZipFast.
        ///
        eZipBlendFaster     = 5,

        ///
        ///     Open the archive for storing data only; choosing data
        ///     file size over data deflation speed.  This option will
        ///     be slower and compress better than \a eZipBlendFaster.
        ///
        eZipBlendSmaller    = 7,

        ///
        ///     Open the archive for storing data only; choosing data
        ///     file size over data deflation speed.  This option will
        ///     be slower and compress better than \a eZipBlendSmaller.
        ///
        eZipSmaller         = 8,

        ///
        ///     Open the archive for storing data only; choosing data
        ///     file size over data deflation speed.  This option will
        ///     be the slowest and compress the best.
        ///
        eZipSmallest        = 9

    } teFileMode;

    ///
    ///\enum    teEncryption
    ///\brief   Enumeration values that reflect the protection level of the archive.
    ///
    typedef enum
    {
        ///
        ///     The archive has been password protected.
        ///
        eEncrypted,

        ///
        ///     The archive has not been password protected.
        ///
        eNotEncrypted,

        ///
        ///     The archive protection status has not been 
        ///     or could not be determined.
        ///
        eEncryptionUnknown
    } teEncryption;

public:

    ///
    ///         Constructor
    ///
    ///         Use this constructor to open and manipulate an archive
    ///         defined with a DWFFile object.
    ///
    ///\param   rFile   The file on which this descriptor will operate.
    ///\param   eMode   An enumeration value that determines how this
    ///                 descriptor will operate on the archive.
    ///\throw   None
    ///
    _DWFCORE_API 
    DWFZipFileDescriptor( const DWFFile& rFile,
                          teFileMode     eMode )
        throw();

    ///
    ///         Constructor
    ///
    ///         Use this constructor to attach an input stream that
    ///         has been bound to or can act like a zip archive.
    ///         This constructor is useful for bridging zip functionality
    ///         and stream behavior.  The zip library that ships with
    ///         the core library has been modified to use the streaming
    ///         interfaces defined by the library.  This makes it possible
    ///         expand the use and distribution of the archive itself.
    ///
    ///\param   rStream The stream to operate on as a zip archive.
    ///\throw   None
    ///
    _DWFCORE_API 
    DWFZipFileDescriptor( DWFInputStream&  rStream )
        throw();

    ///
    ///         Destructor
    ///
    ///\throw   None
    ///
    _DWFCORE_API 
    virtual ~DWFZipFileDescriptor()
        throw();

    ///
    ///         Opens the archive.
    ///
    ///\throw   DWFException
    ///\throw   DWFInvalidTypeException     This indicates that a bad or malformed archive.
    ///
    _DWFCORE_API 
    virtual void open()
        throw( DWFException );

    ///
    ///         Opens the archive, using an index.
    ///
    ///\param   pIndex         A pointer to a DWFZipFileIndex object to be used as an index, 
    ///                        or to receive a newly created index (if the structure is empty).
    ///                        If this parameter is NULL, no index will be created.
    ///
    ///\throw   DWFException
    ///\throw   DWFInvalidTypeException     This indicates that a bad or malformed archive.
    ///
    _DWFCORE_API 
    virtual void openIndexed(DWFZipFileIndex* pIndex)
        throw( DWFException );


    ///
    ///         Closes the archive.
    ///
    ///\throw   None
    ///
    _DWFCORE_API 
    void close()
        throw( DWFException );

    ///
    ///         Returns the size of the archive, in bytes.
    ///
    ///\return  The size of the file, in bytes.
    ///\throw   DWFException
    ///
    _DWFCORE_API 
    size_t size()
        throw( DWFException );

    ///
    ///         Performs a read operation on the archive.
    ///
    ///         This method is not generally used unless the archive is to be
    ///         copied in whole or in part by the caller; Use \a unzip() 
    ///         to extract individual files from the archive.
    ///
    ///\note    This method will throw a DWFIOException if the descriptor
    ///         was not opened in \a eUnzip mode.
    ///
    ///\param   pBuffer         A pointer to a block of memory to receive the bytes.
    ///\param   nBytesToRead    The number of bytes to copy into \a pBuffer.
    ///                         This value should not exceed the capacity of the memory block at \a pBuffer.
    ///\return  The number of actual bytes read.
    ///\throw   DWFException
    ///
    _DWFCORE_API 
    size_t read( void* pBuffer, size_t nBytesToRead )
        throw( DWFException );

    ///
    ///         Performs a seek operation on the archive.
    ///
    ///\param   eOrigin     One of \b SEEK_SET, \b SEEK_CUR or \b SEEK_END.
    ///\param   nOffset     The number of bytes from \a eOrigin to move the internal cursor.
    ///\return  The previous cursor offset before the seek.
    ///\throw   DWFException
    ///
    _DWFCORE_API 
    off_t seek( int eOrigin, off_t nOffset )
        throw( DWFException );

    ///
    ///         Verifies that a particular file exists in the archive and,
    ///         if successful, positions the internal cursor on the file.
    ///
    ///\note    This method will always attempt to determine the encryption
    ///         status of the archived file.
    ///
    ///\param   rArchivedFile   The file in the archive to locate.
    ///\throw   DWFException    
    ///
    _DWFCORE_API 
    bool locate( const DWFString& rArchivedFile )
        throw( DWFException );

    ///
    ///         Returns a stream from which the specified file
    ///         can be extracted from the archive.
    ///
    ///\note    This method will throw a DWFIOException if the descriptor
    ///         was not opened in \a eUnzip mode.
    ///
    ///\param   zArchivedFile   The file to extract from the archive.
    ///\param   zPassword       The password required to access the protected zip archive.
    ///\return  A pointer to a stream from which the file can be read.  The caller
    ///         must delete this pointer using the \b DWFCORE_FREE_OBJECT macro.
    ///\throw   DWFException
    ///
    _DWFCORE_API 
    DWFInputStream* unzip( const DWFString& zArchivedFile,
                           const DWFString& zPassword = L"" )
        throw( DWFException );

    ///
    ///         Returns a stream with which the specified file
    ///         can be stored in the archive.
    ///
    ///\note    This method will throw a DWFIOException if the descriptor
    ///         was not opened in one of the zipping modes.
    ///
    ///\param   zArchiveFile    The file to store in the archive.
    ///\param   zPassword       An optional password to protect the archive.
    ///\return  A pointer to a stream with which the file can be stored.  The caller
    ///         must delete this pointer using the \b DWFCORE_FREE_OBJECT macro.
    ///\throw   DWFException
    ///
    _DWFCORE_API 
    DWFOutputStream* zip( const DWFString& zArchiveFile,
                          const DWFString& zPassword = L"" )
        throw( DWFException );

    ///
    ///         Returns the current encryption state.
    ///         This is determined on file-by-file basis within the archive.
    ///         Use this method in tandem with \a locate() to determine the
    ///         encryption status of the archive and/or a file within.
    ///
    ///\return  The current encryption state of the file or archive.
    ///\throw   DWFException
    ///
    _DWFCORE_API 
    teEncryption encryption()
        throw( DWFException );

protected:

    ///
    ///         The manner in which the archive was opened.
    ///
    teFileMode      _eMode;

    ///
    ///         The encryption state of the last file processed by \a locate().
    ///
    teEncryption    _eEncryption; 

    ///
    ///         The data structure representing an archive creation/writer stream (from the zip library.)
    ///
    zipFile         _pZipStream;

    ///
    ///         The data structure representing an archive reader stream (from the zip library.)
    ///
    unzFile         _pUnzipStream;

    ///
    ///         The external stream that provides read-access to a remote archive or something acting like one.
    ///
    DWFInputStream* _pInputStream;


    ///
    ///         The internal file index structure used if opened without an externally-provided index.
    ///
    DWFZipFileIndex _oZipFileIndex;

private:


    //
    // Not Implemented
    //
    DWFZipFileDescriptor();
    DWFZipFileDescriptor( const DWFZipFileDescriptor& );
    DWFZipFileDescriptor& operator=( const DWFZipFileDescriptor& );

};

}

#endif
