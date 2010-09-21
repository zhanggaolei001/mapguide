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

#include "GeometryCommon.h"
#include "CoordSysCommon.h"
#include "CriticalSection.h"

#include "CoordSysGeodeticTransformation.h"
#include "CoordSysGeodeticTransformDefParams.h"
#include "CoordSysGeodeticAnalyticalTransformDefParams.h"
#include "CoordSysGeodeticInterpolationTransformDefParams.h"
#include "CoordSysGeodeticMultipleRegressionTransformDefParams.h"
#include "CoordSysGeodeticTransformDef.h"

#include "CoordSysTransform.h"          //for CCoordinateSystemTransform
#include "CoordSysUtil.h"               //for CsDictionaryOpenMode
#include "MentorDictionary.h"

using namespace CSLibrary;

#define CS_MAP_DEF_VARIABLE this->transformDefinition //needed by CoordSysMacro

#include "CoordSysMacro.h" //for DEFINE_GET_SET_STRING and DEFINE_GET_SET_NUMERIC

CCoordinateSystemGeodeticTransformDef::CCoordinateSystemGeodeticTransformDef(MgCoordinateSystemCatalog* pCatalog)
    : transformationDefType(0), transformDefinition(NULL), catalog(SAFE_ADDREF(pCatalog) /* make sure, we take a count on it */)
{
    //have we been passed a non-null argument?
    if (NULL == this->catalog)
        throw new MgNullArgumentException(L"CCoordinateSystemGeodeticTransformDef.ctor", __LINE__, __WFILE__, NULL, L"", NULL); 
}

CCoordinateSystemGeodeticTransformDef::~CCoordinateSystemGeodeticTransformDef()
{
    this->ReleaseInstance();
}

void CCoordinateSystemGeodeticTransformDef::ReleaseInstance()
{
    if (NULL != this->transformDefinition)
    {
        CS_free(this->transformDefinition);
        this->transformDefinition = NULL;
    }

    this->transformationDefType = 0;
}

void CCoordinateSystemGeodeticTransformDef::Dispose()
{
    delete this;
}

void CCoordinateSystemGeodeticTransformDef::Reset(INT32 transformationDefType)
{
    INT32 transformationType;
    switch(transformationDefType)
    {
    case MgCoordinateSystemGeodeticTransformDefType::None:
    case MgCoordinateSystemGeodeticTransformDefType::Analytical:
    case MgCoordinateSystemGeodeticTransformDefType::Interpolation:
    case MgCoordinateSystemGeodeticTransformDefType::MultipleRegression:
        transformationType = transformationDefType;
        break;
    default:
        throw new MgInvalidArgumentException(L"CCoordinateSystemGeodeticTransformDef.Reset", __LINE__, __WFILE__, NULL, L"", NULL);
    }
    
    //try creating a new [cs_GeodeticTransform_] instance before we wipe out our own stuff
    cs_GeodeticTransform_* newEmptyDef = (cs_GeodeticTransform_*)CS_malc(sizeof(cs_GeodeticTransform_));
    if (NULL == newEmptyDef) //uses CS_malc which returns NULL in case allocation fails
        throw new MgOutOfMemoryException(L"CCoordinateSystemGeodeticTransformDef.Initialize", __LINE__, __WFILE__, NULL, L"", NULL);

    MG_TRY()

    //now, 0 our temp memory we've allocated
    memset ((void*)newEmptyDef, 0, sizeof(cs_GeodeticTransform_));

    //ok - everything worked out so far; release this instance's information
    this->ReleaseInstance();
    _ASSERT(NULL == this->transformDefinition);
   
    this->transformDefinition = newEmptyDef;
    newEmptyDef = NULL; //make sure, we don't free that one after we get a hold on the (no longer temp) memory

    this->transformationDefType = transformationType;

    MG_CATCH(L"CCoordinateSystemGeodeticTransformDef.Reset")

    if (NULL != newEmptyDef) //will have been set to NULL before
        CS_free(newEmptyDef);

    MG_THROW()
}

INT32 CCoordinateSystemGeodeticTransformDef::GetTransformationDefType(INT32 methodCode /* method code as read from the dictionary entry */)
{
    INT32 transformationType;
    switch(methodCode)
    {
    //standalone methods; see information in cs_geodetic.h 
    case cs_DTCMTH_NULLX:
    case cs_DTCMTH_WGS72:
        transformationType = MgCoordinateSystemGeodeticTransformDefType::None;
        break;

    //multiple Regression methods
    case cs_DTCMTH_MULRG:
    case cs_DTCMTH_PLYNM:
        transformationType = MgCoordinateSystemGeodeticTransformDefType::MultipleRegression;
        break;

    //geocentric methods
    case cs_DTCMTH_3PARM:
    case cs_DTCMTH_MOLOD:
    case cs_DTCMTH_AMOLO:
    case cs_DTCMTH_GEOCT:
    case cs_DTCMTH_4PARM:
    case cs_DTCMTH_6PARM:
    case cs_DTCMTH_BURSA:
    case cs_DTCMTH_FRAME:
    case cs_DTCMTH_7PARM:
    case cs_DTCMTH_BDKAS:
        transformationType = MgCoordinateSystemGeodeticTransformDefType::Analytical;
        break;

    //grid file interpolation methods; if a transformation uses grid file(s), this is the actual
    //type - the ones below are the format of the grid file(s) being used. For example,
    //the dictionary does then contains something like
    //GRID_FILE: NTv2,FWD,.\Australia\Agd66\A66National(13.09.01).gsb
    case cs_DTCMTH_GFILE:
        transformationType = MgCoordinateSystemGeodeticTransformDefType::Interpolation;
        break;
    
    //the next entries are not expected; we're mapping them to the interpolation transformation type
    case cs_DTCMTH_CNTv1:
    case cs_DTCMTH_CNTv2:
    case cs_DTCMTH_FRNCH:
    case cs_DTCMTH_JAPAN:
    case cs_DTCMTH_ATS77:
    case cs_DTCMTH_OST97:
    case cs_DTCMTH_OST02:
        _ASSERT(false);
        transformationType = MgCoordinateSystemGeodeticTransformDefType::Interpolation;
        break;

    default: //invalid / unknown [methodCode] given; don't know how to proceed here
        throw new MgInvalidArgumentException(L"CCoordinateSystemGeodeticTransformDef.Initialize", __LINE__, __WFILE__, NULL, L"", NULL);
    }

    return transformationType;
}

void CCoordinateSystemGeodeticTransformDef::Initialize(const cs_GeodeticTransform_& transformDef)
{
    //take the transformation type from the param we've been passed; we'll use that information to build the correct
    //parameter object later on
    INT32 transformationType = this->GetTransformationDefType(transformDef.methodCode);

    this->Reset(transformationType);
    *this->transformDefinition = transformDef;
}

MgCoordinateSystemGeodeticTransformation* CCoordinateSystemGeodeticTransformDef::CreateTransformation(bool createInverse)
{
    VERIFY_INITIALIZED(L"CCoordinateSystemGeodeticTransformDef.CreateTransformation");

    if (MgCoordinateSystemGeodeticTransformDefType::None == this->GetTransformDefType() || !this->IsValid())
        throw new MgInvalidOperationException(L"CCoordinateSystemGeodeticTransformDef.CreateTransformation", __LINE__,__WFILE__, NULL, L"", NULL);
    
    //we don't take ownership of the transformation being returned but
    //will release [sourceDatum] and [targetDatum];
    //new [CCoordinateSystemGeodeticTransformation] will have to ADDREF if needed
    return new CCoordinateSystemGeodeticTransformation(this->catalog, this, createInverse);
}

MgCoordinateSystemGeodeticTransformDef* CCoordinateSystemGeodeticTransformDef::CreateClone()
{
    VERIFY_INITIALIZED(L"CCoordinateSystemGeodeticTransformDef.CreateClone");

    Ptr<CCoordinateSystemGeodeticTransformDef> clonedTransformDef = new CCoordinateSystemGeodeticTransformDef(this->catalog.p);
    clonedTransformDef->Initialize(*this->transformDefinition);
    clonedTransformDef->transformDefinition->protect = 0; //unset the protection flag; otherwise the caller wouldn't be able to change any values

    return clonedTransformDef.Detach();
}

void CCoordinateSystemGeodeticTransformDef::CopyTo(cs_GeodeticTransform_& transformDef) const
{
    VERIFY_INITIALIZED(L"CCoordinateSystemGeodeticTransformDef.CopyTo");
    
    //copy our values into the [cs_GeodeticTransform_] we've been passed here
    transformDef = *this->transformDefinition;
}

INT32 CCoordinateSystemGeodeticTransformDef::GetTransformDefType()
{
    return this->transformationDefType; //can be None
}

MgCoordinateSystemGeodeticTransformDefParams* CCoordinateSystemGeodeticTransformDef::GetParameters()
{
    VERIFY_INITIALIZED(L"CCoordinateSystemGeodeticTransformDef.GetParameters");

    switch(this->transformationDefType)
    {
    case MgCoordinateSystemGeodeticTransformDefType::None:
        return NULL;

    case MgCoordinateSystemGeodeticTransformDefType::Analytical:
        return static_cast<MgCoordinateSystemGeodeticAnalyticalTransformDefParams*>(new CCoordinateSystemGeodeticAnalyticalTransformDefParams(
            this->transformDefinition->parameters.geocentricParameters, this->transformDefinition->methodCode, this->IsProtected()));
    
    case MgCoordinateSystemGeodeticTransformDefType::Interpolation:
        return static_cast<MgCoordinateSystemGeodeticInterpolationTransformDefParams*>(
            new CCoordinateSystemGeodeticInterpolationTransformDefParams(this->transformDefinition->parameters.fileParameters, this->IsProtected()));
    
    case MgCoordinateSystemGeodeticTransformDefType::MultipleRegression:
        return static_cast<MgCoordinateSystemGeodeticMultipleRegressionTransformDefParams*>(new CCoordinateSystemGeodeticMultipleRegressionTransformDefParams(
            this->transformDefinition->parameters.dmaMulRegParameters, this->transformDefinition->methodCode, this->IsProtected()));
    
    default: //invalid state; why's that?
        _ASSERT(false);
        throw new MgInvalidOperationException(L"CCoordinateSystemGeodeticTransformDef.GetParameters", __LINE__, __WFILE__, NULL, L"", NULL);
    }
}

void CCoordinateSystemGeodeticTransformDef::SetParameters(MgCoordinateSystemGeodeticTransformDefParams* parameters)
{
    VERIFY_INITIALIZED(L"CCoordinateSystemGeodeticTransformDef.SetParameters");
    VERIFY_NOT_PROTECTED(L"CCoordinateSystemGeodeticTransformDef.SetParameters");

    //first check, whether this is a NONE transformation definition; if so, ignore the parameter altogether and wipe out
    //this instance's parameter information to NULL
    if (MgCoordinateSystemGeodeticTransformDefType::None == this->transformationDefType)
    {
        memset(&this->transformDefinition->parameters, 0, sizeof(this->transformDefinition->parameters.sizeDetermination.unionSize));
        return;
    }

    //otherwise: make sure, we've been passed non null paramaters...
    ENSURE_NOT_NULL(parameters, CCoordinateSystemGeodeticTransformDef::SetParameters);
    
    INT32 paramsMethodCode = 0x0;

    //...and the parameters are actually of the correct type, i.e. match whatever we've stored in [this->transformationDefType]
    CCoordinateSystemGeodeticTransformDefParams* transformDefParams = NULL;
    CCoordinateSystemGeodeticMultipleRegressionTransformDefParams* mulRegParams = NULL;
    CCoordinateSystemGeodeticAnalyticalTransformDefParams* analyticalParams = NULL;

    switch(this->transformationDefType)
    {
    case MgCoordinateSystemGeodeticTransformDefType::Analytical:
        analyticalParams = dynamic_cast<CCoordinateSystemGeodeticAnalyticalTransformDefParams*>(parameters);
        if (NULL != analyticalParams)
        {
            paramsMethodCode = analyticalParams->GetTransformationMethod();
            transformDefParams = analyticalParams;
        }
        break;

    case MgCoordinateSystemGeodeticTransformDefType::Interpolation:
        transformDefParams = dynamic_cast<CCoordinateSystemGeodeticInterpolationTransformDefParams*>(parameters);
        //the transformation method is "grid file"; the actual type doesn't matter as this
        //is specified through the [MgCoordinateSystemGeodeticInterpolationTransformDefParams] object;
        //such a transformation can use multiple grid files where each can have a different format
        paramsMethodCode = cs_DTCMTH_GFILE;
        break;
    
    case MgCoordinateSystemGeodeticTransformDefType::MultipleRegression:
        mulRegParams = dynamic_cast<CCoordinateSystemGeodeticMultipleRegressionTransformDefParams*>(parameters);
        if (NULL != mulRegParams)
        {
            paramsMethodCode = mulRegParams->GetTransformationMethod();
            transformDefParams = mulRegParams;
        }

        break;

    default:
        _ASSERT(false); //why's that?
        break;
    }

    if (NULL == transformDefParams)
        throw new MgInvalidOperationException(L"CCoordinateSystemGeodeticTransformDef.SetParameters", __LINE__, __WFILE__, NULL, L"", NULL);

    //copy the values from the parameter we've been passed into our own [parameters] section
    transformDefParams->CopyTo(&this->transformDefinition->parameters);
    this->transformDefinition->methodCode = paramsMethodCode;
}

bool CCoordinateSystemGeodeticTransformDef::IsProtected()
{
    VERIFY_INITIALIZED(L"CCoordinateSystemGeodeticTransformDef.IsProtected");
    return (DICTIONARY_SYS_DEF == this->transformDefinition->protect);
}

bool CCoordinateSystemGeodeticTransformDef::IsValid()
{
    if (NULL == this->transformDefinition) //an unitialized definition is always invalid
        return false;

    Ptr<MgCoordinateSystemGeodeticTransformDefParams> params = this->GetParameters();
    if (!params->IsValid())
        return false;

    //TODO: would we also need to check, whether the datum(s) exists?

    /*
    CriticalClass.Enter();
    //TODO: pass correct parameters; make sure, CS_gxchk checks all stuff
    int nNumErrs = CS_gxchk(this->transformDefinition, 0, NULL, 0);
    CriticalClass.Leave();
    
    return (0 == nNumErrs);
    */
    return true;
}

//helper - don't delete
bool CCoordinateSystemGeodeticTransformDef::IsEncrypted()
{
    return false;
}

DEFINE_GET_SET_STRING(CCoordinateSystemGeodeticTransformDef,TransformName,this->transformDefinition->xfrmName)
DEFINE_GET_SET_STRING(CCoordinateSystemGeodeticTransformDef,SourceDatum,this->transformDefinition->srcDatum)
DEFINE_GET_SET_STRING(CCoordinateSystemGeodeticTransformDef,TargetDatum,this->transformDefinition->trgDatum)
DEFINE_GET_SET_STRING(CCoordinateSystemGeodeticTransformDef,Group,this->transformDefinition->group)
DEFINE_GET_SET_STRING(CCoordinateSystemGeodeticTransformDef,Description,this->transformDefinition->description)
DEFINE_GET_SET_STRING(CCoordinateSystemGeodeticTransformDef,Source,this->transformDefinition->source)

DEFINE_GET_SET_NUMERIC(CCoordinateSystemGeodeticTransformDef,EpsgCode,INT32,this->transformDefinition->epsgCode)
DEFINE_GET_SET_NUMERIC(CCoordinateSystemGeodeticTransformDef,EpsgVariation,INT32,this->transformDefinition->epsgVariation)
DEFINE_GET_SET_NUMERIC(CCoordinateSystemGeodeticTransformDef,InverseSupported,bool,this->transformDefinition->inverseSupported)
DEFINE_GET_SET_NUMERIC(CCoordinateSystemGeodeticTransformDef,MaxIterations,INT32,this->transformDefinition->maxIterations)
DEFINE_GET_SET_NUMERIC(CCoordinateSystemGeodeticTransformDef,ConvergenceValue,double,this->transformDefinition->cnvrgValue)
DEFINE_GET_SET_NUMERIC(CCoordinateSystemGeodeticTransformDef,ErrorValue,double,this->transformDefinition->errorValue)
DEFINE_GET_SET_NUMERIC(CCoordinateSystemGeodeticTransformDef,Accuracy,double,this->transformDefinition->accuracy)