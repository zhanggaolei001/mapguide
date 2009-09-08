//
//  Copyright (C) 2004-2009 by Autodesk, Inc.
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
#include "CoordSysUtil.h"
#include "CriticalSection.h"
#include "Spatial/MathUtility.h"
#include "Spatial/SpatialUtility.h"

#include "CoordSys.h"
#include "CoordSysGrids.h"
#include "CoordSysMeasure.h"
#include "CoordSysEnumInteger32.h"
#include "MentorUtil.h"

using namespace CSLibrary;

//=============================================================================
// CCoordinateSystemGridSpecification -- Assembly which contains all grid
//                                       parameter values.
//
// This object is basically used for convenience, placing all commonly used
// grid specification parameters into a single object.  Another grid parameter
// can be added without changing any calling sequences.  Note that the default
// constructor constructs an invalid parameter structure.
//
// The default presision value is 1 meter (currently).  If the CurvePrecision
// member is not set, this value will be used.
const double CCoordinateSystemGridSpecification::m_DefaultPrecision = 1.0;
CCoordinateSystemGridSpecification::CCoordinateSystemGridSpecification (void) : m_EastingBase           (0.0),
                                                                                m_NorthingBase          (0.0),
                                                                                m_EastingIncrement      (0.0),
                                                                                m_NorthingIncrement     (0.0),
                                                                                m_CurvePrecision        (0.0),
                                                                                m_TickEastingIncrement  (0),
                                                                                m_TickNorthingIncrement (0),
                                                                                m_UnitType              (MgCoordinateSystemUnitType::Linear),
                                                                                m_UnitCode              (MgCoordinateSystemUnitCode::Meter)
{
}
CCoordinateSystemGridSpecification::CCoordinateSystemGridSpecification (const CCoordinateSystemGridSpecification& source)
                                                                             :
                                                                        m_EastingBase           (source.m_EastingBase),
                                                                        m_NorthingBase          (source.m_NorthingBase),
                                                                        m_EastingIncrement      (source.m_EastingIncrement),
                                                                        m_NorthingIncrement     (source.m_NorthingIncrement),
                                                                        m_CurvePrecision        (source.m_CurvePrecision),
                                                                        m_TickEastingIncrement  (source.m_TickEastingIncrement),
                                                                        m_TickNorthingIncrement (source.m_TickNorthingIncrement),
                                                                        m_UnitType              (source.m_UnitType),
                                                                        m_UnitCode              (source.m_UnitCode)
{
}
CCoordinateSystemGridSpecification::~CCoordinateSystemGridSpecification (void)
{
}
CCoordinateSystemGridSpecification& CCoordinateSystemGridSpecification::operator= (const CCoordinateSystemGridSpecification& rhs)
{
    if (this != &rhs)
    {
        m_EastingBase           = rhs.m_EastingBase;
        m_NorthingBase          = rhs.m_NorthingBase;
        m_EastingIncrement      = rhs.m_EastingIncrement;
        m_NorthingIncrement     = rhs.m_NorthingIncrement;
        m_CurvePrecision        = rhs.m_CurvePrecision;
        m_TickEastingIncrement  = rhs.m_TickEastingIncrement;
        m_TickNorthingIncrement = rhs.m_TickNorthingIncrement;
        m_UnitType              = rhs.m_UnitType;
        m_UnitCode              = rhs.m_UnitCode;
    }
    return *this;
}
double CCoordinateSystemGridSpecification::GetEastingBase(void)
{
    return m_EastingBase;
}
double CCoordinateSystemGridSpecification::GetNorthingBase(void)
{
    return m_NorthingBase;
}
double CCoordinateSystemGridSpecification::GetEastingIncrement(void)
{
    return m_EastingIncrement;
}
double CCoordinateSystemGridSpecification::GetNorthingIncrement(void)
{
    return m_NorthingIncrement;
}
double CCoordinateSystemGridSpecification::GetTickEastingIncrement(void)
{
    return m_TickEastingIncrement;
}
double CCoordinateSystemGridSpecification::GetTickNorthingIncrement(void)
{
    return m_TickNorthingIncrement;
}
INT32 CCoordinateSystemGridSpecification::GetUnitType(void)
{
    return m_UnitType;
}
INT32 CCoordinateSystemGridSpecification::GetUnitCode(void)
{
    return m_UnitCode;
}
bool CCoordinateSystemGridSpecification::IsSameAs(MgCoordinateSystemGridSpecification* specification)
{
    bool areTheSame (false);
    
    double dblTol (1.0E-04);
    
    areTheSame  = fabs (specification->GetEastingBase()       - m_EastingBase)       < dblTol;
    areTheSame &= fabs (specification->GetNorthingBase()      - m_NorthingBase)      < dblTol;
    areTheSame &= fabs (specification->GetEastingIncrement()  - m_EastingIncrement)  < dblTol;
    areTheSame &= fabs (specification->GetNorthingIncrement() - m_NorthingIncrement) < dblTol;
    
    areTheSame &= fabs (specification->GetTickEastingIncrement()  - m_TickEastingIncrement)  < dblTol;
    areTheSame &= fabs (specification->GetTickNorthingIncrement() - m_TickNorthingIncrement) < dblTol;

    areTheSame &= (specification->GetUnitType() == m_UnitType);
    areTheSame &= (specification->GetUnitCode() == m_UnitCode);

    areTheSame &= fabs (specification->GetCurvePrecision()    - m_CurvePrecision)    < 1.0E-08;

    return areTheSame;
}
double CCoordinateSystemGridSpecification::GetCurvePrecision(void)
{
    return m_CurvePrecision;
}

void CCoordinateSystemGridSpecification::SetGridBase(double eastingBase,double northingBase)
{
    m_EastingBase = eastingBase;
    m_NorthingBase = northingBase;
}
void CCoordinateSystemGridSpecification::SetGridIncrement(double eastingIncrement,double northingIncrement)
{
    m_EastingIncrement = eastingIncrement;
    m_NorthingIncrement = northingIncrement;
}
void CCoordinateSystemGridSpecification::SetTickIncrements(double eastingIncrement,double northingIncrement)
{
    m_TickEastingIncrement = eastingIncrement;
    m_TickNorthingIncrement = northingIncrement;
}
void CCoordinateSystemGridSpecification::SetUnits (INT32 unitCode,INT32 unitType)
{
    bool codeOk;
    INT32 lclUnitType;

    codeOk = GetUnitInfo(unitCode,&lclUnitType,NULL);
    if (!codeOk || unitType != lclUnitType)
    {
        throw new MgInvalidCoordinateSystemUnitsException(L"MgCoordinateSystemGridSpecification.SetUnits", __LINE__, __WFILE__, NULL, L"", NULL);
    }

    m_UnitCode = unitCode;
    m_UnitType = unitType;
}
void CCoordinateSystemGridSpecification::SetCurvePrecision (double curvePrecision)
{
    m_CurvePrecision = curvePrecision;
}

// The following functions are identical to the published version, with the
// exception that the value returned are always converted to the units of
// the provided coordinate system.  Typically, the coodinate system
// provided as an argument will be that of the "grid" coordinate system.
double CCoordinateSystemGridSpecification::GetEastingBase (MgCoordinateSystem* gridCS)
{
    INT32 gridUnitType;
    INT32 gridCrsUnitCode;
    double unitConversion;

    MgCoordinateSystemCatalog* catalogPtr = gridCS->GetCatalog ();
    MgCoordinateSystemUnitInformation* unitInfoPtr = catalogPtr->GetUnitInformation ();
    gridCrsUnitCode = gridCS->GetUnitCode ();
    
    // Verify that the unit type of the specification match the unit type
    // of the grid coordinate system of the grid object.
    GetUnitInfo(gridCrsUnitCode,&gridUnitType,NULL);
    if (gridUnitType != m_UnitType)
    {
        throw new MgInvalidCoordinateSystemUnitsException(L"MgCoordinateSystemGridSpecification.GetEastingBase", __LINE__, __WFILE__, NULL, L"", NULL);
    }

    // Calculate the appropriate units conversion factor.
    if (m_UnitType == MgCoordinateSystemUnitType::Linear)
    {
        unitConversion = unitInfoPtr->GetLinearUnitScale (m_UnitCode) /
                         unitInfoPtr->GetLinearUnitScale (gridCrsUnitCode);
    }
    else
    {
        unitConversion = unitInfoPtr->GetAngularUnitScale (m_UnitCode) /
                         unitInfoPtr->GetAngularUnitScale (gridCrsUnitCode);
    }
    return (m_EastingBase * unitConversion);
}
double CCoordinateSystemGridSpecification::GetNorthingBase (MgCoordinateSystem* gridCS)
{
    INT32 gridUnitType;
    INT32 gridCrsUnitCode;
    double unitConversion;

    MgCoordinateSystemCatalog* catalogPtr = gridCS->GetCatalog ();
    MgCoordinateSystemUnitInformation* unitInfoPtr = catalogPtr->GetUnitInformation ();
    gridCrsUnitCode = gridCS->GetUnitCode ();

    // Verify that the unit type of the specification match the unit type
    // of the grid coordinate system of the grid object.
    GetUnitInfo(gridCrsUnitCode,&gridUnitType,NULL);
    if (gridUnitType != m_UnitType)
    {
        throw new MgInvalidCoordinateSystemUnitsException(L"MgCoordinateSystemGridSpecification.GetNorthingBase", __LINE__, __WFILE__, NULL, L"", NULL);
    }

    // Calculate the appropriate units conversion factor.
    if (m_UnitType == MgCoordinateSystemUnitType::Linear)
    {
        unitConversion = unitInfoPtr->GetLinearUnitScale (m_UnitCode) /
                         unitInfoPtr->GetLinearUnitScale (gridCrsUnitCode);
    }
    else
    {
        unitConversion = unitInfoPtr->GetAngularUnitScale (m_UnitCode) /
                         unitInfoPtr->GetAngularUnitScale (gridCrsUnitCode);
    }
    return (m_NorthingBase * unitConversion);
}
double CCoordinateSystemGridSpecification::GetEastingIncrement(MgCoordinateSystem* gridCS)
{
    INT32 gridUnitType;
    INT32 gridCrsUnitCode;
    double unitConversion;

    MgCoordinateSystemCatalog* catalogPtr = gridCS->GetCatalog ();
    MgCoordinateSystemUnitInformation* unitInfoPtr = catalogPtr->GetUnitInformation ();
    gridCrsUnitCode = gridCS->GetUnitCode ();

    // Verify that the unit type of the specification match the unit type
    // of the grid coordinate system of the grid object.
    GetUnitInfo(gridCrsUnitCode,&gridUnitType,NULL);
    if (gridUnitType != m_UnitType)
    {
        throw new MgInvalidCoordinateSystemUnitsException(L"MgCoordinateSystemGridSpecification.GetEastingIncrement", __LINE__, __WFILE__, NULL, L"", NULL);
    }

    // Calculate the appropriate units conversion factor.
    if (m_UnitType == MgCoordinateSystemUnitType::Linear)
    {
        unitConversion = unitInfoPtr->GetLinearUnitScale (m_UnitCode) /
                         unitInfoPtr->GetLinearUnitScale (gridCrsUnitCode);
    }
    else
    {
        unitConversion = unitInfoPtr->GetAngularUnitScale (m_UnitCode) /
                         unitInfoPtr->GetAngularUnitScale (gridCrsUnitCode);
    }
    return (m_EastingIncrement * unitConversion);
}
double CCoordinateSystemGridSpecification::GetNorthingIncrement(MgCoordinateSystem* gridCS)
{
    INT32 gridUnitType;
    INT32 gridCrsUnitCode;
    double unitConversion;

    MgCoordinateSystemCatalog* catalogPtr = gridCS->GetCatalog ();
    MgCoordinateSystemUnitInformation* unitInfoPtr = catalogPtr->GetUnitInformation ();
    gridCrsUnitCode = gridCS->GetUnitCode ();

    // Verify that the unit type of the specification match the unit type
    // of the grid coordinate system of the grid object.
    GetUnitInfo(gridCrsUnitCode,&gridUnitType,NULL);
    if (gridUnitType != m_UnitType)
    {
        throw new MgInvalidCoordinateSystemUnitsException(L"MgCoordinateSystemGridSpecification.GetNorthingIncrement", __LINE__, __WFILE__, NULL, L"", NULL);
    }

    // Calculate the appropriate units conversion factor.
    if (m_UnitType == MgCoordinateSystemUnitType::Linear)
    {
        unitConversion = unitInfoPtr->GetLinearUnitScale (m_UnitCode) /
                         unitInfoPtr->GetLinearUnitScale (gridCrsUnitCode);
    }
    else
    {
        unitConversion = unitInfoPtr->GetAngularUnitScale (m_UnitCode) /
                         unitInfoPtr->GetAngularUnitScale (gridCrsUnitCode);
    }
    return (m_NorthingIncrement * unitConversion);
}
double CCoordinateSystemGridSpecification::GetTickEastingIncrement(MgCoordinateSystem* gridCS)
{
    INT32 gridUnitType;
    INT32 gridCrsUnitCode;
    double unitConversion;

    MgCoordinateSystemCatalog* catalogPtr = gridCS->GetCatalog ();
    MgCoordinateSystemUnitInformation* unitInfoPtr = catalogPtr->GetUnitInformation ();
    gridCrsUnitCode = gridCS->GetUnitCode ();

    // Verify that the unit type of the specification match the unit type
    // of the grid coordinate system of the grid object.
    GetUnitInfo(gridCrsUnitCode,&gridUnitType,NULL);
    if (gridUnitType != m_UnitType)
    {
        throw new MgInvalidCoordinateSystemUnitsException(L"MgCoordinateSystemGridSpecification.GetTickEastingIncremen", __LINE__, __WFILE__, NULL, L"", NULL);
    }

    // Calculate the appropriate units conversion factor.
    if (m_UnitType == MgCoordinateSystemUnitType::Linear)
    {
        unitConversion = unitInfoPtr->GetLinearUnitScale (m_UnitCode) /
                         unitInfoPtr->GetLinearUnitScale (gridCrsUnitCode);
    }
    else
    {
        unitConversion = unitInfoPtr->GetAngularUnitScale (m_UnitCode) /
                         unitInfoPtr->GetAngularUnitScale (gridCrsUnitCode);
    }
    return (m_TickEastingIncrement * unitConversion);
}
double CCoordinateSystemGridSpecification::GetTickNorthingIncrement(MgCoordinateSystem* gridCS)
{
    INT32 gridUnitType;
    INT32 gridCrsUnitCode;
    double unitConversion;

    MgCoordinateSystemCatalog* catalogPtr = gridCS->GetCatalog ();
    MgCoordinateSystemUnitInformation* unitInfoPtr = catalogPtr->GetUnitInformation ();
    gridCrsUnitCode = gridCS->GetUnitCode ();

    // Verify that the unit type of the specification match the unit type
    // of the grid coordinate system of the grid object.
    GetUnitInfo(gridCrsUnitCode,&gridUnitType,NULL);
    if (gridUnitType != m_UnitType)
    {
        throw new MgInvalidCoordinateSystemUnitsException(L"MgCoordinateSystemGridSpecification.GetTickNorthingIncrement", __LINE__, __WFILE__, NULL, L"", NULL);
    }

    // Calculate the appropriate units conversion factor.
    if (m_UnitType == MgCoordinateSystemUnitType::Linear)
    {
        unitConversion = unitInfoPtr->GetLinearUnitScale (m_UnitCode) /
                         unitInfoPtr->GetLinearUnitScale (gridCrsUnitCode);
    }
    else
    {
        unitConversion = unitInfoPtr->GetAngularUnitScale (m_UnitCode) /
                         unitInfoPtr->GetAngularUnitScale (gridCrsUnitCode);
    }
    return (m_TickNorthingIncrement * unitConversion);
}
double CCoordinateSystemGridSpecification::GetCurvePrecision (MgCoordinateSystem* gridCS)
{
    double precisionInCsUnits (1.0);
    double precisionInMeters (1.0);
    double toMeters;
    double toDegrees;

    MgCoordinateSystemCatalog* catalogPtr = gridCS->GetCatalog ();
    MgCoordinateSystemUnitInformation* unitInfoPtr = catalogPtr->GetUnitInformation ();

    // UnitConversion will convert the units of the coordinate system to
    // meters by multiplication.  By inverting this, we have a value which
    // will convert meters to coordinate system units by multiplication.
    double csUnitConversion = 1.0 / gridCS->GetUnitScale ();

    // If the curve precision has not been set by the user, this gets very easy.
    if (m_CurvePrecision < 1.0E-24)     // i.e. == 0.0
    {
        precisionInMeters = m_DefaultPrecision;
    }
    else
    {
        if (m_UnitType == MgCoordinateSystemUnitType::Linear)
        {
            toMeters = unitInfoPtr->GetLinearUnitScale (m_UnitCode);
        }
        else
        {
            toDegrees = unitInfoPtr->GetAngularUnitScale (m_UnitCode);
            toMeters = (6378137.0 * M_PI * 2.0 / 360.0) / toDegrees;
        }
        precisionInMeters = m_CurvePrecision * toMeters;
    }
    precisionInCsUnits = precisionInMeters * csUnitConversion;
    return (precisionInCsUnits);
}
void CCoordinateSystemGridSpecification::Dispose ()
{
    delete this;
}

///////////////////////////////////////////////////////////////////////////////
///<summary>
/// The boundary of the grid or graticule.  In the case of geographic
/// coordinates, internal longitude ordinates may exceed 180 and latitude
/// ordinates may exceed 90 to support wrap around in a rational fashion.
/// In this initial release, the boundary will be a rectangle, and this will
/// be enforced by the constructors which are supported.  Expansion to support
/// more complex boundaries will be added by providing more constructors.
///</summary>
const INT32 CCoordinateSystemGridBoundary::MaxCurvePoints = 511;
CCoordinateSystemGridBoundary::CCoordinateSystemGridBoundary () : MgCoordinateSystemGridBoundary (),
                                                                  m_Large                        (false),
                                                                  m_MaxCurvePoints               (MaxCurvePoints),
                                                                  m_GridBoundary                 ()
{
}
CCoordinateSystemGridBoundary::CCoordinateSystemGridBoundary (MgCoordinate* southwest,
                                                              MgCoordinate* northeast)
                                                                :
                                                              MgCoordinateSystemGridBoundary (),
                                                              m_Large                        (false),
                                                              m_MaxCurvePoints               (MaxCurvePoints),
                                                              m_GridBoundary                 ()
{
   SetBoundaryExtents (southwest,northeast);
}
CCoordinateSystemGridBoundary::CCoordinateSystemGridBoundary (MgPolygon* boundary)
                                                                :
                                                              MgCoordinateSystemGridBoundary (),
                                                              m_Large                        (false),
                                                              m_MaxCurvePoints               (MaxCurvePoints),
                                                              m_GridBoundary                 ()
{
    m_GridBoundary = SAFE_ADDREF (boundary);
}
CCoordinateSystemGridBoundary::~CCoordinateSystemGridBoundary (void)
{
}
void CCoordinateSystemGridBoundary::SetBoundaryExtents (MgCoordinate* southwest,
                                                        MgCoordinate* northeast)
{
    MgGeometryFactory factory;
    Ptr<MgCoordinate> swPnt;
    Ptr<MgCoordinate> sePnt;
    Ptr<MgCoordinate> nePnt;
    Ptr<MgCoordinate> nwPnt;
    Ptr<MgCoordinate> clPnt;
    Ptr<MgCoordinateCollection> collection;

    MG_TRY()
        swPnt = factory.CreateCoordinateXY(southwest->GetX(),southwest->GetY());
        sePnt = factory.CreateCoordinateXY(northeast->GetX(),southwest->GetY());
        nePnt = factory.CreateCoordinateXY(northeast->GetX(),northeast->GetY());
        nwPnt = factory.CreateCoordinateXY(southwest->GetX(),northeast->GetY());
        clPnt = factory.CreateCoordinateXY(southwest->GetX(),southwest->GetY());
        
        if (!swPnt|| !swPnt || !nePnt || !nwPnt ||!clPnt)
        {
            throw new MgOutOfMemoryException(L"MgCoordinateSystemGridBoundary.SetBoundaryExtents",
                                             __LINE__, __WFILE__, NULL, L"", NULL);
        }

        collection = new MgCoordinateCollection();
        if (collection == NULL)
        {
            throw new MgOutOfMemoryException(L"MgCoordinateSystemGridBoundary.SetBoundaryExtents",
                                             __LINE__, __WFILE__, NULL, L"", NULL);
        }
        collection->Add (swPnt);
        collection->Add (sePnt);
        collection->Add (nePnt);
        collection->Add (nwPnt);
        collection->Add (clPnt);

        MgLinearRing* ring = factory.CreateLinearRing (collection);
        m_GridBoundary = factory.CreatePolygon (ring,NULL);
    MG_CATCH_AND_THROW(L"MgCoordinateSystemGridBoundary.SetBoundaryExtents")
}
void CCoordinateSystemGridBoundary::SetBoundaryExtents (MgPolygon* boundary)
{
    m_GridBoundary = SAFE_ADDREF (boundary);
}
MgPolygon* CCoordinateSystemGridBoundary::GetBoundary (void) const
{
    return SAFE_ADDREF (m_GridBoundary.p);
}
void CCoordinateSystemGridBoundary::GetBoundaryExtents (double& eastMin,double& eastMax,double& northMin,double& northMax) const
{
    double currentX;
    double currentY;
    Ptr<MgLinearRing> outerRing;
    Ptr<MgCoordinateIterator> ringItr;
    Ptr<MgCoordinate> coordPtr;
    
    MG_TRY ()
        // Set up the accumulation values so we will always capture the first
        // values encountered in the actual polygon.
        eastMin = northMin = 1.0E+300;
        eastMax = northMax = -1.0E+300;
        
        // We loop through theouter ring of the polygon.  For the purpose of this function,
        // the first ordinate in each coordinate is considered the easting and the
        // second ordinate in each coordinate is considered the northing.
        //
        // It remains unclear, at this point, if we need to know if the coordinate
        // system of the boundary is geographic or not.  We'll fund out pretty soon.
        outerRing = m_GridBoundary->GetExteriorRing ();
        ringItr = outerRing->GetCoordinates ();
        while (ringItr->MoveNext ())
        {
            coordPtr = ringItr->GetCurrent ();
            currentX = coordPtr->GetX ();
            currentY = coordPtr->GetY ();
            if (currentX < eastMin) eastMin = currentX;
            if (currentX > eastMax) eastMax = currentX;
            if (currentY < northMin) northMin = currentY;
            if (currentY > northMax) northMax = currentY;
        }
    MG_CATCH_AND_THROW(L"MgCoordinateSystemGridBoundary.GetBoundaryExtents")
    return;
}
// The Polygon returned by this function will not (usually) be a simple
// rectangle, but a series of complex curves which (usually) approximate
// a trapazoid.
MgPolygon* CCoordinateSystemGridBoundary::GetBoundary (MgCoordinateSystemTransform* transform,
                                                       double precision)
{
    MgGeometryFactory factory;

    INT32 index;
    INT32 interiorRingCount;

    Ptr<MgPolygon> result;
    Ptr<MgLinearRing> sourceRing;
    Ptr<MgLinearRing> targetRing;
    Ptr<MgLinearRing> exteriorRing;
    Ptr<MgLinearRingCollection> interiorRings;

    MG_TRY()
        // Convert the outer ring.
        sourceRing = m_GridBoundary->GetExteriorRing ();
        exteriorRing = TransformLinearRing (sourceRing,transform,precision);

        interiorRingCount = m_GridBoundary->GetInteriorRingCount ();
        if (interiorRingCount > 0)
        {
            // Create the repository for the interior rings, now that we know
            // there are some (this is rare).
            interiorRings = new MgLinearRingCollection ();
            
            for (index = 0;index < interiorRingCount;index += 1)
            {
                sourceRing = m_GridBoundary->GetInteriorRing (index);
                targetRing = TransformLinearRing (sourceRing,transform,precision);
                interiorRings->Add (targetRing);
            }
        }
        result = new MgPolygon (exteriorRing,interiorRings);
    MG_CATCH_AND_THROW(L"MgCoordinateSystemGridBoundary.GetBoundary")
    return result.Detach ();
}
MgLineStringCollection* CCoordinateSystemGridBoundary::ClipLineString (MgLineString* lineString) const
{
    MgGeometryFactory factory;
    Ptr<MgLineStringCollection> collection;
    Ptr<MgCoordinateIterator> polyItr;
    Ptr<MgCoordinateIterator> lineItr;

    MG_TRY()
        polyItr = m_GridBoundary->GetCoordinates ();
        lineItr = lineString->GetCoordinates ();
        collection = MgSpatialUtility::ClipStringToPolygon (polyItr,lineItr);
    MG_CATCH_AND_THROW(L"MgCoordinateSystemGridBoundary.ClipLineString")
    return collection.Detach ();
}
void CCoordinateSystemGridBoundary::Dispose ()
{
    delete this;
}
MgLinearRing* CCoordinateSystemGridBoundary::TransformLinearRing (MgLinearRing* linearRing,
                                                                  MgCoordinateSystemTransform* transform,
                                                                  double curvePrecision)
{
    MgGeometryFactory factory;

    Ptr<MgLinearRing> result;
    Ptr<MgCoordinateCollection> targetCollection;
    Ptr<MgLineString> convertedSegment;
    Ptr<MgCoordinate> curFromPnt;
    Ptr<MgCoordinate> curToPnt;
    Ptr<MgCoordinate> copyBufr;
    Ptr<MgCoordinateIterator> ringItr;
    Ptr<MgCoordinateIterator> lineItr;

    MG_TRY ()
        // NOTE:  Boundaries are required to proceed in a counterclockwise
        // direction, but this function will be used to transform both
        // exterior and interior rings.  So in this function we cannot count
        // on any specific order.  We should be able to rely on the fact that
        // each ring presented to us is indeed closed.

        // To create a MgLinearRing, we need an MgCoordinateCollection.  So we
        // create an empty MgCoordinateCollection, and then spend most of our
        // time adding points to this collection.  The primary source of these
        // points will be the MgLineStrings returned by the
        // MgCoordinateSystemTransform::GridLine object.  Perhaps that function
        // should be modified to return an MgCoordinateCollection?  Probably
        // doesn't make much difference as you can't (at least at thie time)
        // add one coordinate collection to another.  Too Bad!!!
        targetCollection = new MgCoordinateCollection ();

        ringItr = linearRing->GetCoordinates ();
        ringItr->MoveNext ();
        curToPnt = ringItr->GetCurrent ();
        copyBufr = transform->Transform (curToPnt);
        targetCollection->Add (copyBufr);
        while (ringItr->MoveNext ())
        {
            // Convert the current segment.
            curFromPnt = curToPnt;
            curToPnt = ringItr->GetCurrent ();
            convertedSegment = transform->GridLine (curFromPnt,curToPnt,curvePrecision,m_MaxCurvePoints);

            // Copy the converted segment to the target coordinate collection.
            lineItr = convertedSegment->GetCoordinates ();

            // To prevent duplicate points, we always skip adding the initial
            // point of a converted line string.  We dealt with the initial
            // point of the first segment above.  The first point of each
            // additional line segment will have been processed as the "to"
            // point of the last segment processed.  Always adding the last
            // point of each segment means we don't need to worry about an
            // extra point when we are done.
            lineItr->MoveNext ();

            // Copy the remainder of the converted line segment.
            while (lineItr->MoveNext ())
            {
                copyBufr = lineItr->GetCurrent ();
                targetCollection->Add (copyBufr);
            }
        }

        // OK, we should have now converted our ring to a collection of points.
        // If the ring provided was closed (as it should be) than the result we
        // have created should also be closed.  We can now convert this back to
        // a linear ring which is our required return type.
        result = new MgLinearRing (targetCollection);
    MG_CATCH_AND_THROW(L"MgCoordinateSystemGridBoundary.TransformLinearRing")
    
    return result.Detach ();
}
//=============================================================================
// CCoordinateSystemGridLine -- Associates an orientation and a value with a
//                              possibly interupted grid line.
//
CCoordinateSystemGridLine::CCoordinateSystemGridLine (INT32 orientation,double value)
                                                        :
                                                      MgCoordinateSystemGridLine (),
                                                      m_Orientation              (orientation),
                                                      m_Value                    (value),
                                                      m_LineSegments             ()

{
    m_LineSegments = new MgLineStringCollection;
}
CCoordinateSystemGridLine::~CCoordinateSystemGridLine (void)
{
}
INT32 CCoordinateSystemGridLine::GetGridOrientation(void)
{
    return m_Orientation;
}
double CCoordinateSystemGridLine::GetRealValue(void)
{
    return m_Value;
}
INT32 CCoordinateSystemGridLine::GetCount (void)
{
    return m_LineSegments->GetCount ();
}
MgLineString* CCoordinateSystemGridLine::GetSegment (INT32 index)
{
    MgLineString* rtnValue = m_LineSegments->GetItem (index);
    return rtnValue;
}
MgLineStringCollection* CCoordinateSystemGridLine::GetSegmentCollection (void)
{
    return SAFE_ADDREF(m_LineSegments.p);
}
void CCoordinateSystemGridLine::SetSegmentCollection (MgLineStringCollection* segmentCollection)
{
    m_LineSegments = SAFE_ADDREF (segmentCollection);
}
void CCoordinateSystemGridLine::SetGridOrientation (INT32 orientation)
{
    m_Orientation = orientation;
}
void CCoordinateSystemGridLine::SetRealValue (double realValue)
{
    m_Value = realValue;
}
void CCoordinateSystemGridLine::ClearSegments (void)
{
    m_LineSegments->Clear ();
}    
void CCoordinateSystemGridLine::AddSegment (MgLineString* newSegment)
{
    m_LineSegments->Add (newSegment);
}
void CCoordinateSystemGridLine::Dispose ()
{
    delete this;
}
//=============================================================================
// CCoordinateSystemGridRegion -- Associates a label/designation with a
//                                MgPolygon object.
//
CCoordinateSystemGridRegion::CCoordinateSystemGridRegion (STRING label,MgPolygon* polygon)
                                    :
                                MgCoordinateSystemGridRegion (),
                                m_RegionLabel                (label),
                                m_Polygon                    ()
{
    m_Polygon = SAFE_ADDREF (polygon);
}                                
STRING CCoordinateSystemGridRegion::GetLabel ()
{
    return m_RegionLabel;
}
MgPolygon* CCoordinateSystemGridRegion::GetPolygon ()
{
    return SAFE_ADDREF(m_Polygon.p);
}
void CCoordinateSystemGridRegion::Dispose ()
{
    delete this;
}
//=============================================================================
// CCoordinateSystemGridTick -- Defines the location of a grid tick mark.
//
// Definition includes the iso value for the tick mark, the orientation of the
// tick mark (i.e. is the value an easting or a northing), and the direction
// of the reerence line at the tick insertion point.  Ticks are normally drawn
// normal to this direction.  If the tick mark was generated from a grid
// boundary line, the interior of the grid will always be to the left of the
// direction vector.
CCoordinateSystemGridTick::CCoordinateSystemGridTick (INT32 orientation,double value)
                                                        :
                                                      MgCoordinateSystemGridTick (),
                                                      m_Orientation              (orientation),
                                                      m_Value                    (value),
                                                      m_Position                 (),
                                                      m_Direction                ()
{
}                                                      
CCoordinateSystemGridTick::~CCoordinateSystemGridTick ()
{
}
void CCoordinateSystemGridTick::SetOrientation (INT32 orientation)
{
    m_Orientation = orientation;
}
void CCoordinateSystemGridTick::SetValue (double value)
{
    m_Value = value;
}
void CCoordinateSystemGridTick::SetPosition (MgCoordinate* position)
{
    m_Position = SAFE_ADDREF(position);
}
void CCoordinateSystemGridTick::SetDirection (MgCoordinate* direction)
{
    m_Direction = SAFE_ADDREF(direction);
}
INT32 CCoordinateSystemGridTick::GetTickOrientation ()
{
    return m_Orientation;
}
double CCoordinateSystemGridTick::GetValue ()
{
    return m_Value;
}
MgCoordinate* CCoordinateSystemGridTick::GetPosition ()
{
    return SAFE_ADDREF(m_Position.p);
}
MgCoordinate* CCoordinateSystemGridTick::GetDirectionVector ()
{
    return SAFE_ADDREF(m_Direction.p);
}
void CCoordinateSystemGridTick::Dispose ()
{
    delete this;
}
//=============================================================================
// An CCoordinateSystemGridLineCollection is collection of
// MgCoordinateSystemGridLine objects.  As manufactured, grid horizontal lines
// appear first in ascending order by grid value (easting in this case);
// followed by grid vertical lines in ascending order by grid value (northing
// in this case).
CCoordinateSystemGridLineCollection::CCoordinateSystemGridLineCollection (void)
                                        :
                                     MgCoordinateSystemGridLineCollection (),
                                     m_GridLineCollection ()
{
    m_GridLineCollection = new MgDisposableCollection();
}
CCoordinateSystemGridLineCollection::~CCoordinateSystemGridLineCollection(void)
{
    // Delete whatever lines may be there.
    Clear ();
}
INT32 CCoordinateSystemGridLineCollection::GetCount () const
{
    INT32 lineCount;
    
    lineCount = m_GridLineCollection->GetCount();
    return lineCount;
}
MgCoordinateSystemGridLine* CCoordinateSystemGridLineCollection::GetItem (INT32 index) const
{
    MgCoordinateSystemGridLine* gridLine = static_cast<MgCoordinateSystemGridLine*>(m_GridLineCollection->GetItem(index));
    return gridLine;
}
INT32 CCoordinateSystemGridLineCollection::IndexOf (INT32 gridOrientation,double gridValue) const
{
    INT32 index;
    INT32 rtnValue = -1;
    INT32 count;
    double delta;
    Ptr<MgCoordinateSystemGridLine> gridLine;

    MG_TRY ()
        // The combination of orientation and grid value should be unique.
        // Return is -1 if not found.
        count = m_GridLineCollection->GetCount ();
        for (index = 0;index < count;index += 1)
        {
            gridLine = static_cast<MgCoordinateSystemGridLine*>(m_GridLineCollection->GetItem (index));
            if (gridLine->GetGridOrientation () == gridOrientation)
            {
                delta = fabs (gridLine->GetRealValue () - gridValue);
                if (delta < 1.0E-012)
                {
                    rtnValue = index;
                    break;
                }
            }
        }
    MG_CATCH_AND_THROW(L"CCoordinateSystemGridLineCollection::IndexOf")
    return rtnValue;
}
void CCoordinateSystemGridLineCollection::RemoveAt (INT32 index)
{
    // The MgDisposableCollection object checks the index argument, and throws if appropriate.
    // The MgDisposableCollection object performs the "SAFE_RELEASE" operation.
    m_GridLineCollection->RemoveAt (index);
}
void CCoordinateSystemGridLineCollection::Clear()
{
    // The MgDisposableCollection object performs the "SAFE_RELEASE" operation.
    m_GridLineCollection->Clear ();
}
void CCoordinateSystemGridLineCollection::SetItem (INT32 index,MgCoordinateSystemGridLine* value)
{
    // The MgDisposableCollection object checks the index argument, and throws if appropriate.
    // The MgDisposableCollection object performs the "SAFE_RELEASE" & "SAFE_ADDREF" operations.
    m_GridLineCollection->SetItem (index,value);
}
void CCoordinateSystemGridLineCollection::Add (MgCoordinateSystemGridLine* value)
{
    // The MgDIsposableCollection object does the "SAFE_ADDREF" operation.
    m_GridLineCollection->Add (value);
}
void CCoordinateSystemGridLineCollection::AddCollection (MgCoordinateSystemGridLineCollection* aGridLineCollection)
{
    INT32 index;
    INT32 toAddCount;
    Ptr<MgCoordinateSystemGridLine> aGridLine;
    
    MG_TRY ()
        toAddCount = aGridLineCollection->GetCount ();
        for (index = 0;index < toAddCount;index += 1)
        {
            aGridLine = aGridLineCollection->GetItem (index);
            // This Add refers to the "this" object.
            m_GridLineCollection->Add (aGridLine);
        }
    MG_CATCH_AND_THROW(L"CCoordinateSystemGridLineCollection::IndexOf")
    return;
}
void CCoordinateSystemGridLineCollection::Dispose(void)
{
    delete this;
}

//=============================================================================
// A CCoordinateSystemGridRegionCollection is collection of
// CCoordinateSystemGridRegion objects.
CCoordinateSystemGridRegionCollection::CCoordinateSystemGridRegionCollection ()
                                         :
                                       MgCoordinateSystemGridRegionCollection (),
                                       m_GridRegionCollection ()
{
    m_GridRegionCollection = new MgDisposableCollection();
}
CCoordinateSystemGridRegionCollection::~CCoordinateSystemGridRegionCollection (void)
{
    Clear ();
}
INT32 CCoordinateSystemGridRegionCollection::GetCount () const
{
    INT32 itemCount;
    itemCount = m_GridRegionCollection->GetCount ();
    return itemCount;
}
MgCoordinateSystemGridRegion* CCoordinateSystemGridRegionCollection::GetItem (INT32 index) const
{
    // The MgDisposableCollection object checks the index argument, and throws if appropriate.
    MgCoordinateSystemGridRegion* itemPtr = static_cast<MgCoordinateSystemGridRegion*>(m_GridRegionCollection->GetItem (index));
    return itemPtr;
}
void CCoordinateSystemGridRegionCollection::RemoveAt (INT32 index)
{
    // The MgDisposableCollection object checks the index argument, and throws if appropriate.
    // The MgDisposableCollection object performs the "SAFE_RELEASE" operation.
    m_GridRegionCollection->RemoveAt (index);
}
void CCoordinateSystemGridRegionCollection::Clear()
{
    m_GridRegionCollection->Clear ();
}
void CCoordinateSystemGridRegionCollection::SetItem (INT32 index, MgCoordinateSystemGridRegion* value)
{
    // The MgDisposableCollection object checks the index argument, and throws if appropriate.
    // The MgDisposableCollection object performs the "SAFE_RELEASE" & "SAFE_ADDREF" operations.
    m_GridRegionCollection->SetItem (index,value);
}
void CCoordinateSystemGridRegionCollection::Add (MgCoordinateSystemGridRegion* value)
{
    // The MgDisposableCollection object performs the "SAFE_ADDREF" operation.
    m_GridRegionCollection->Add (value);
}
void CCoordinateSystemGridRegionCollection::AddCollection (MgCoordinateSystemGridRegionCollection* aGridRegionCollection)
{
    INT32 index;
    INT32 toAddCount;
    Ptr<MgCoordinateSystemGridRegion> aGridRegion;
    
    MG_TRY ()
        toAddCount = aGridRegionCollection->GetCount ();
        for (index = 0;index < toAddCount;index += 1)
        {
            aGridRegion = aGridRegionCollection->GetItem (index);
            // This Add refers to the "this" object.
            m_GridRegionCollection->Add (aGridRegion);
        }
    MG_CATCH_AND_THROW(L"CCoordinateSystemGridRegionCollection::AddCollection")
    return;
}
void CCoordinateSystemGridRegionCollection::Dispose (void)
{
    // Destructor deletes the contents of the collection.
    delete this;
}

//=============================================================================
// A CCoordinateSystemGridTickCollection is collection of
// CCoordinateSystemGridTick objects.  CCoordinateSystemGridTickCollection
// objects will contain MgCoordinateSystemGridTick objects for the entire
// boundary or for an individual grid line.
CCoordinateSystemGridTickCollection::CCoordinateSystemGridTickCollection (void)
                                        :
                                     MgCoordinateSystemGridTickCollection (),
                                     m_GridTickCollection ()
{
    m_GridTickCollection = new MgDisposableCollection();
}
CCoordinateSystemGridTickCollection::~CCoordinateSystemGridTickCollection (void)
{
    Clear ();
}
INT32 CCoordinateSystemGridTickCollection::GetCount () const
{
    INT32 itemCount = m_GridTickCollection->GetCount ();
    return itemCount;
}
MgCoordinateSystemGridTick* CCoordinateSystemGridTickCollection::GetItem (INT32 index) const
{
    MgCoordinateSystemGridTick *itemPtr = static_cast<MgCoordinateSystemGridTick*>(m_GridTickCollection->GetItem (index));
    return itemPtr; 
}
void CCoordinateSystemGridTickCollection::RemoveAt (INT32 index)
{
    m_GridTickCollection->RemoveAt (index);
}
void CCoordinateSystemGridTickCollection::Clear()
{
    m_GridTickCollection->Clear ();
}
void CCoordinateSystemGridTickCollection::SetItem (INT32 index, MgCoordinateSystemGridTick* value)
{
    m_GridTickCollection->SetItem (index,value);
}
void CCoordinateSystemGridTickCollection::Add (MgCoordinateSystemGridTick* value)
{
    m_GridTickCollection->Add (value);
}
void CCoordinateSystemGridTickCollection::AddCollection (MgCoordinateSystemGridTickCollection* aGridTickCollection)
{
    INT32 index;
    INT32 toAddCount;
    Ptr<MgCoordinateSystemGridTick> aGridTick;
    
    MG_TRY ()
        toAddCount = aGridTickCollection->GetCount ();
        for (index = 0;index < toAddCount;index += 1)
        {
            aGridTick = aGridTickCollection->GetItem (index);
            m_GridTickCollection->Add (aGridTick);
        }
    MG_CATCH_AND_THROW(L"CCoordinateSystemGridTickCollection::AddCollection")
    return;
}
void CCoordinateSystemGridTickCollection::Dispose (void)
{
    delete this;
}
