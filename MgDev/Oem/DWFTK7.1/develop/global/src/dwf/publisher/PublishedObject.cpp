//
//  Copyright (c) 2004 by Autodesk, Inc.
//
//  By using this code, you are agreeing to the terms and conditions of
//  the License Agreement included in the documentation for this code.
//
//  AUTODESK MAKES NO WARRANTIES, EXPRESSED OR IMPLIED,
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


#ifndef DWFTK_READ_ONLY

#include "dwf/publisher/Publisher.h"
#include "dwf/publisher/PublishedObject.h"
using namespace DWFToolkit;


_DWFTK_API
DWFPublishedObject::DWFPublishedObject( DWFPublishedObject::tKey nKey,
                                        const DWFString&         zName )
throw()
                  : _bRef( false )
                  , _nKey( nKey )
                  , _nIID( 0 )
                  , _nIndex( 0 )
                  , _pParent( NULL )
                  , _zName( zName )
{
    ;
}

_DWFTK_API
DWFPublishedObject::DWFPublishedObject( DWFPublishedObject& rObject )
throw()
                  : _bRef( rObject._bRef )
                  , _nKey( rObject._nKey )
                  , _nIID( rObject._nIID )
                  , _nIndex( rObject._nIndex )
                  , _pParent( rObject._pParent )
                  , _zName( rObject._zName )
{
    ;
}

_DWFTK_API
DWFPublishedObject&
DWFPublishedObject::operator=( DWFPublishedObject& rObject )
throw()
{
    _nKey = rObject._nKey;
    _nIID = rObject._nIID;
    _nIndex = rObject._nIndex;
    _pParent = rObject._pParent;
    _zName = rObject._zName;
    _bRef = rObject._bRef;

    return *this;
}

_DWFTK_API
DWFPublishedObject::~DWFPublishedObject()
throw()
{
    unsigned long iRefs = 0;
    for (; iRefs < _oReferenceList.size(); iRefs++)
    {
        DWFCORE_FREE_OBJECT( _oReferenceList[iRefs] );
    }
}

_DWFTK_API
void
DWFPublishedObject::accept( DWFPublishedObject::Visitor& rVisitor )
throw( DWFException )
{
    rVisitor.visitPublishedObject( *this );
}

_DWFTK_API
void
DWFPublishedObject::accept( DWFPropertyVisitor& rVisitor )
throw( DWFException )
{
    rVisitor.visitPropertyContainer( *this );
}

_DWFTK_API
void
DWFPublishedObject::addReference( DWFPublishedObject*       pObject,
                                  DWFPublishedObject::tKey  nKey,
                                  const DWFString*          zInstanceName,
                                  bool                      bPropertiesOnly )
throw( DWFException )
{
        //
        // this is a non-structural reference, we need to capture the properties
        //
    if (bPropertiesOnly)
    {
        //
        //
        //
        copyProperties( *pObject );
    }
        //
        // structural reference
        //
    else
    {
        tReference* pNewRef = DWFCORE_ALLOC_OBJECT( tReference );

        pNewRef->nKey = nKey;
        pNewRef->nIndex = 0;
        pNewRef->pObj = pObject;

        if (zInstanceName)
        {
            pNewRef->zName.assign( *zInstanceName );
        }

        _oReferenceList.push_back( pNewRef );
    }
}

_DWFTK_API
DWFPublishedObject::tReferenceList&
DWFPublishedObject::references()
throw( DWFException )
{
    return _oReferenceList;
}

_DWFTK_API
void
DWFPublishedObject::path( DWFString& zPath )
throw()
{
    if (_pParent)
    {
        _pParent->path( zPath );

        zPath.append( /*NOXLATE*/"/" );
    }
    else
    {
        //
        // segment "name" from key
        //
        char zSegmentID[12] = {0};
        ::sprintf( zSegmentID, /*NOXLATE*/"%lu", _nKey );

        //
        // add key-name to the path
        //
        zPath.append( zSegmentID );
    }
}

#endif
