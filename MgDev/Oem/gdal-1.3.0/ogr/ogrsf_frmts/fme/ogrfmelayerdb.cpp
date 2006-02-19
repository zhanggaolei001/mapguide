/******************************************************************************
 * $Id: ogrfmelayerdb.cpp,v 1.3 2005/02/22 12:57:19 fwarmerdam Exp $
 *
 * Project:  FMEObjects Translator
 * Purpose:  Implementation of the OGRFMELayerDB class.  This is the
 *           class implementing behaviour for layers that are built on
 *           smart readers representing databases with spatial constraints, 
 *           and where clause support. 
 * Author:   Frank Warmerdam, warmerdam@pobox.com
 *
 ******************************************************************************
 * Copyright (c) 1999, 2001 Safe Software Inc.
 * All Rights Reserved
 *
 * This software may not be copied or reproduced, in all or in part, 
 * without the prior written consent of Safe Software Inc.
 *
 * The entire risk as to the results and performance of the software,
 * supporting text and other information contained in this file
 * (collectively called the "Software") is with the user.  Although
 * Safe Software Incorporated has used considerable efforts in preparing 
 * the Software, Safe Software Incorporated does not warrant the
 * accuracy or completeness of the Software. In no event will Safe Software 
 * Incorporated be liable for damages, including loss of profits or 
 * consequential damages, arising out of the use of the Software.
 ******************************************************************************
 *
 * $Log: ogrfmelayerdb.cpp,v $
 * Revision 1.3  2005/02/22 12:57:19  fwarmerdam
 * use OGRLayer base spatial filter support
 *
 * Revision 1.2  2005/02/02 20:54:27  fwarmerdam
 * track m_nFeaturesRead
 *
 * Revision 1.1  2002/05/24 06:23:57  warmerda
 * New
 *
 * Revision 1.8  2002/05/24 06:17:01  warmerda
 * clean up dependencies on strimp.h, and fme2ogrspatialref func
 *
 * Revision 1.7  2002/01/31 17:00:06  warmerda
 * added debug statement about first feature in layer
 *
 * Revision 1.6  2001/11/26 23:36:43  warmerda
 * override SetAttributeFilter on OGRFMELayerDB to avoid parsing
 *
 * Revision 1.5  2001/11/26 18:37:58  warmerda
 * Use WHERE instead of WHERE_CLAUSE for SDE
 *
 * Revision 1.4  2001/11/15 21:44:34  warmerda
 * add macros support for SDE
 *
 * Revision 1.3  2001/11/01 21:52:39  warmerda
 * added mutex to protect access to session
 *
 * Revision 1.2  2001/09/27 17:02:33  warmerda
 * updated to fME2002 dir structure
 *
 * Revision 1.1  2001/09/07 15:53:39  warmerda
 * New
 *
 */

#include "fme2ogr.h"
#include "cpl_conv.h"
#include "cpl_string.h"

CPL_CVSID("$Id: ogrfmelayerdb.cpp,v 1.3 2005/02/22 12:57:19 fwarmerdam Exp $");

/************************************************************************/
/*                           OGRFMELayerDB()                            */
/************************************************************************/

OGRFMELayerDB::OGRFMELayerDB( OGRFMEDataSource *poDSIn, 
                              const char *pszReaderNameIn, 
                              const char *pszDatasetIn,
                              IFMEStringArray *poUserDirectivesIn )
        : OGRFMELayer( poDSIn )

{
    nPreviousFeature = -1;

    poReader = NULL;

    pszReaderName = CPLStrdup( pszReaderNameIn );
    pszDataset = CPLStrdup( pszDatasetIn );

    poUserDirectives = poDS->GetFMESession()->createStringArray();

    for( FME_UInt32 i = 0; i < poUserDirectivesIn->entries(); i++ )
    {
        CPLDebug( "FMEOLEDB", "userDirective[%d] = %s\n", 
                  i, (const char *) (*poUserDirectivesIn)(i) );

        poUserDirectives->append( (*poUserDirectivesIn)(i) );
    }
}

/************************************************************************/
/*                           ~OGRFMELayerDB()                           */
/************************************************************************/

OGRFMELayerDB::~OGRFMELayerDB()

{
    if( poReader != NULL )
        poDS->GetFMESession()->destroyReader( poReader );

    CPLFree( pszReaderName );
    CPLFree( pszDataset );
}

/************************************************************************/
/*                           TestCapability()                           */
/************************************************************************/

int OGRFMELayerDB::TestCapability( const char * pszCap )

{
    if( EQUAL(pszCap,OLCRandomRead) )
        return FALSE;

    else if( EQUAL(pszCap,OLCSequentialWrite) 
             || EQUAL(pszCap,OLCRandomWrite) )
        return FALSE;

    else if( EQUAL(pszCap,OLCFastFeatureCount) )
        return TRUE;

    else if( EQUAL(pszCap,OLCFastSpatialFilter) )
        return TRUE;

    else 
        return FALSE;
}

/************************************************************************/
/*                           GetNextFeature()                           */
/************************************************************************/

OGRFeature *OGRFMELayerDB::GetNextFeature()

{
    OGRFeature      *poFeature;
    FME_Boolean     eEndOfSchema;
    FME_MsgNum      err;

    poDS->AcquireSession();

    if( poReader == NULL )
    {
        if( !CreateReader() )
        {
            return NULL;
            poDS->ReleaseSession();
        }
    }

    err = poReader->read( *poFMEFeature, eEndOfSchema );

    if( err )
    {
        CPLFMEError( poDS->GetFMESession(), "Error while reading feature." );
        poDS->ReleaseSession();
        return NULL;
    }

    if( eEndOfSchema == FME_TRUE )
    {
        poDS->ReleaseSession();
        return NULL;
    }

    poFeature = poDS->ProcessFeature( this, poFMEFeature );

    if( nPreviousFeature == -1 )
        CPLDebug( "FMEOLEDB", "Fetching first feature from layer `%s'.", 
                  GetLayerDefn()->GetName() );

    poFeature->SetFID( ++nPreviousFeature );
    m_nFeaturesRead++;

    poDS->ReleaseSession();

    return poFeature;
}

/************************************************************************/
/*                            ResetReading()                            */
/************************************************************************/
 
void OGRFMELayerDB::ResetReading()

{
    nPreviousFeature = -1;

    poDS->AcquireSession();

/* -------------------------------------------------------------------- */
/*      Blow away existing reader, if we have one.                      */
/* -------------------------------------------------------------------- */
    if( poReader != NULL )
        poDS->GetFMESession()->destroyReader( poReader );
    poReader = NULL;

    poDS->ReleaseSession();
}

/************************************************************************/
/*                              SetMacro()                              */
/*                                                                      */
/*      Set the value of one macro within a set of macros stored in     */
/*      comma delimeted name value pairs (as per RUNTIME_MACROS in      */
/*      user directives).                                               */
/************************************************************************/

static void SetMacro( IFMEString *poMacros, const char *pszTarget, 
                      const char *pszNewValue )

{
    char      *pszWorking, *pszValStart;
    int       nOldValLength;

    pszWorking = (char *) CPLMalloc(strlen(poMacros->data()) 
                                    + strlen(pszNewValue) 
                                    + strlen(pszTarget) + 20 );
    strcpy( pszWorking, poMacros->data() );

    pszValStart = strstr( pszWorking, pszTarget );
    if( pszValStart == NULL 
        || pszValStart[strlen(pszTarget)] != ',' )
    {
        if( strlen(pszWorking) > 0 )
            strcat( pszWorking, "," );

        sprintf( pszWorking + strlen(pszWorking), "%s,%s", 
                 pszTarget, pszNewValue );
        *poMacros = pszWorking;
        CPLFree( pszWorking );
        return;
    }

    pszValStart += strlen(pszTarget) + 1;

    for( nOldValLength = 0; 
         pszValStart[nOldValLength] != ',' 
             && pszValStart[nOldValLength] != '\0'; 
         nOldValLength++ ) {}

    memmove( pszValStart + strlen(pszNewValue), 
            pszValStart + nOldValLength, 
            strlen(pszValStart + nOldValLength)+1 );

    memcpy( pszValStart, pszNewValue, strlen( pszNewValue ) );

    *poMacros = pszWorking;
    CPLFree( pszWorking );
}

/************************************************************************/
/*                         SetAttributeFilter()                         */
/************************************************************************/

OGRErr OGRFMELayerDB::SetAttributeFilter( const char *pszNewFilter )

{
    CPLFree( pszAttributeFilter );
    pszAttributeFilter = NULL;

    if( pszNewFilter != NULL )
        pszAttributeFilter = CPLStrdup( pszNewFilter );

    ResetReading();

    return OGRERR_NONE;
}

/************************************************************************/
/*                            CreateReader()                            */
/************************************************************************/

int OGRFMELayerDB::CreateReader()

{
    FME_MsgNum    err;
    IFMESession  *poSession = poDS->GetFMESession();
    FME_UInt32   i;

    CPLAssert( poReader == NULL && nPreviousFeature == -1 );

/* -------------------------------------------------------------------- */
/*      Make a copy of the user directives, so we won't be altering     */
/*      the originals.                                                  */
/* -------------------------------------------------------------------- */
    IFMEStringArray  *poUDC = poSession->createStringArray();

    for( i = 0; i < poUserDirectives->entries(); i++ )
        poUDC->append( (*poUserDirectives)(i) );
    
/* -------------------------------------------------------------------- */
/*      Update the IDLIST to just select the desired table.             */
/* -------------------------------------------------------------------- */
    
    for( i = 0; i < poUDC->entries(); i++ )
    {
        if( EQUAL((const char *) (*poUDC)(i),"IDLIST") )
        {
            IFMEString    *poIDList = poSession->createString();
            *poIDList = GetLayerDefn()->GetName();
            poUDC->setElement( i+1, *poIDList );
            poSession->destroyString( poIDList );
            break;
        }
    }

    if( i == poUDC->entries() )
    {
        poUDC->append( "IDLIST" );
        poUDC->append( GetLayerDefn()->GetName() );
    }
/* -------------------------------------------------------------------- */
/*      Update the macros for source information, if needed.            */
/* -------------------------------------------------------------------- */
    if( m_poFilterGeom != NULL )
    {
        const char *pszDirective = "RUNTIME_MACROS";

        if( !poUDC->contains(pszDirective) )
        {
            poUDC->append(pszDirective);
            poUDC->append("");
        }
        for( i = 0; i < poUDC->entries(); i++ )
        {
            if( EQUAL((const char *) (*poUDC)(i),pszDirective) )
            {
                IFMEString  *poMacroValue = poSession->createString();
                char      szSEARCH_ENVELOPE[1024];
                OGREnvelope      oEnvelope;

                poUDC->getElement( i+1, *poMacroValue );

                m_poFilterGeom->getEnvelope( &oEnvelope );
                
                if( EQUALN(pszReaderName,"SDE",3) )
                {
                    sprintf( szSEARCH_ENVELOPE, "%.16f", oEnvelope.MinX );
                    SetMacro( poMacroValue, "_SDE3MINX", szSEARCH_ENVELOPE );
                    
                    sprintf( szSEARCH_ENVELOPE, "%.16f", oEnvelope.MinY );
                    SetMacro( poMacroValue, "_SDE3MINY", szSEARCH_ENVELOPE );
                    
                    sprintf( szSEARCH_ENVELOPE, "%.16f", oEnvelope.MaxX );
                    SetMacro( poMacroValue, "_SDE3MAXX", szSEARCH_ENVELOPE );
                    
                    sprintf( szSEARCH_ENVELOPE, "%.16f", oEnvelope.MaxY );
                    SetMacro( poMacroValue, "_SDE3MAXY", szSEARCH_ENVELOPE );
                }
                else
                {
                    sprintf( szSEARCH_ENVELOPE, "%.16f", oEnvelope.MinX );
                    SetMacro( poMacroValue, "_ORACLE_MINX", szSEARCH_ENVELOPE);
                    
                    sprintf( szSEARCH_ENVELOPE, "%.16f", oEnvelope.MinY );
                    SetMacro( poMacroValue, "_ORACLE_MINY", szSEARCH_ENVELOPE);
                    
                    sprintf( szSEARCH_ENVELOPE, "%.16f", oEnvelope.MaxX );
                    SetMacro( poMacroValue, "_ORACLE_MAXX", szSEARCH_ENVELOPE);
                    
                    sprintf( szSEARCH_ENVELOPE, "%.16f", oEnvelope.MaxY );
                    SetMacro( poMacroValue, "_ORACLE_MAXY", szSEARCH_ENVELOPE);
                }

                poUDC->setElement( i+1, *poMacroValue );

                CPLDebug( "FMEOLEDB", "Update %s to:\n%s", 
                          pszDirective, poMacroValue->data() );

                poSession->destroyString( poMacroValue );
                break;
            }
        }
    }
    
/* -------------------------------------------------------------------- */
/*      Create new reader with desired constraints.                     */
/* -------------------------------------------------------------------- */
    poReader = poSession->createReader(pszReaderName, FME_FALSE, poUDC);
    poSession->destroyStringArray( poUDC );
    if( poReader == NULL )
    {
        CPLFMEError( poSession,
                     "Failed to create reader of type `%s'.\n",
                     pszReaderName );
        return FALSE;
    }

/* -------------------------------------------------------------------- */
/*      Setup constraints applied in open().                            */
/* -------------------------------------------------------------------- */
    IFMEStringArray     *poParms = poSession->createStringArray();

    if( pszAttributeFilter != NULL && strlen(pszAttributeFilter) > 0 )
    {
        if( EQUALN(pszReaderName,"SDE",3) )
            poParms->append( "WHERE" );
        else
            poParms->append( "WHERE_CLAUSE" );

        poParms->append( pszAttributeFilter );
    }
#ifdef notdef
    if( m_poFilterGeom != NULL )
    {
        char      szSEARCH_ENVELOPE[1024];
        OGREnvelope      oEnvelope;

        m_poFilterGeom->getEnvelope( &oEnvelope );

        sprintf( szSEARCH_ENVELOPE, "%.16f", oEnvelope.MinX );
        poParms->append( "SEARCH_ENVELOPE" );
        poParms->append( szSEARCH_ENVELOPE );

        sprintf( szSEARCH_ENVELOPE, "%.16f", oEnvelope.MinY );
        poParms->append( "SEARCH_ENVELOPE" );
        poParms->append( szSEARCH_ENVELOPE );

        sprintf( szSEARCH_ENVELOPE, "%.16f", oEnvelope.MaxX );
        poParms->append( "SEARCH_ENVELOPE" );
        poParms->append( szSEARCH_ENVELOPE );

        sprintf( szSEARCH_ENVELOPE, "%.16f", oEnvelope.MaxY );
        poParms->append( "SEARCH_ENVELOPE" );
        poParms->append( szSEARCH_ENVELOPE );
    }
#endif

    for( i = 0; i < poParms->entries(); i++ )
    {
        CPLDebug( "FMEOLEDB", "openParms[%d] = %s", 
                  i, (const char *) (*poParms)(i) );
    }

/* -------------------------------------------------------------------- */
/*      Now try to open the dataset.                                    */
/* -------------------------------------------------------------------- */
    err = poReader->open( pszDataset, *poParms );
    if( err )
    {
        CPLFMEError( poSession,
                     "Failed to open dataset `%s' with reader of type `%s'.\n",
                     pszDataset, pszReaderName );
        return FALSE;
    }

    poSession->destroyStringArray( poParms );

    return TRUE;
}

/************************************************************************/
/*                          GetFeatureCount()                           */
/************************************************************************/

int OGRFMELayerDB::GetFeatureCount( int bForce )

{
    /*
    ** This could be improved by just reading through the FME Features
    ** without having to convert to OGRFeatures.  Optimization deferred.
    */

    return OGRLayer::GetFeatureCount( bForce );
}
