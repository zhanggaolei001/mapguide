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

#include "MapGuideCommon.h"
#include "ServiceManager.h"
#include "TestGeometry.h"
#include "CppUnitExtensions.h"
#include "FoundationDefs.h"

const STRING ArbitraryWkt  = L"LOCAL_CS [ \"Non-Earth (Mile)\", LOCAL_DATUM [\"Local Datum\", 0], UNIT [\"Mile_US\", 1609.344], AXIS [\"X\", EAST], AXIS[\"Y\", NORTH]]";
const STRING GeographicWkt = L"GEOGCS[\"LL84\",DATUM[\"WGS84\",SPHEROID[\"WGS84\",6378137.000,298.25722293]],PRIMEM[\"Greenwich\",0],UNIT[\"Degree\",0.017453292519943295]]";
const STRING ProjectedWkt  = L"PROJCS[\"GA-W\",GEOGCS[\"LL27\",DATUM[\"NAD27\",SPHEROID[\"CLRK66\",6378206.400,294.97869821]],PRIMEM[\"Greenwich\",0],UNIT[\"Degree\",0.017453292519943295]],PROJECTION[\"Transverse_Mercator\"],PARAMETER[\"false_easting\",500000.000],PARAMETER[\"false_northing\",0.000],PARAMETER[\"scale_factor\",0.999900000000],PARAMETER[\"central_meridian\",-84.16666666666670],PARAMETER[\"latitude_of_origin\",30.00000000000000],UNIT[\"Foot_US\",0.30480060960122]]";

const STRING TEST_LOCALE = L"en";

CPPUNIT_TEST_SUITE_NAMED_REGISTRATION(TestGeometry, "TestGeometry");

void TestGeometry::setUp()
{
}


void TestGeometry::tearDown()
{
}


void TestGeometry::TestStart()
{
    ACE_DEBUG((LM_INFO, ACE_TEXT("\nRunning Geometry tests. (Mentor)\n")));
#ifdef TEST_PREPARED_GEOMETRY_PERF
    try
    {
        MgServiceManager* serviceManager = MgServiceManager::GetInstance();
        if (serviceManager == 0)
        {
            throw new MgNullReferenceException(L"TestGeometry::TestStart", __LINE__, __WFILE__, NULL, L"", NULL);
        }

        Ptr<MgResourceService> pService = dynamic_cast<MgResourceService*>(serviceManager->RequestService(MgServiceType::ResourceService));
        if (pService == 0)
        {
            throw new MgServiceNotAvailableException(L"TestGeometry::TestStart", __LINE__, __WFILE__, NULL, L"", NULL);
        }

        //Set the user information for the current thread to be administrator
        MgUserInformation::SetCurrentUserInfo(NULL);
        Ptr<MgUserInformation> userInfo = new MgUserInformation(L"Administrator", L"admin");
        if (userInfo != NULL)
        {
            userInfo->SetLocale(TEST_LOCALE);
            MgUserInformation::SetCurrentUserInfo(userInfo);

            MgResourceIdentifier resourceIdentifier1(L"Library://UnitTests/Data/Sheboygan_Parcels.FeatureSource");
    #ifdef _WIN32
            STRING resourceContentFileName1 = L"..\\UnitTestFiles\\Sheboygan_Parcels.FeatureSource";
            STRING dataFileName1 = L"..\\UnitTestFiles\\Sheboygan_Parcels.sdf";
    #else
            STRING resourceContentFileName1 = L"../UnitTestFiles/Sheboygan_Parcels.FeatureSource";
            STRING dataFileName1 = L"../UnitTestFiles/Sheboygan_Parcels.sdf";
    #endif

            //Add a new resource
            Ptr<MgByteSource> contentSource1 = new MgByteSource(resourceContentFileName1);
            Ptr<MgByteReader> contentReader1 = contentSource1->GetReader();
            pService->SetResource(&resourceIdentifier1, contentReader1, NULL);

            //Set the resource data
            Ptr<MgByteSource> dataSource1 = new MgByteSource(dataFileName1);
            Ptr<MgByteReader> dataReader1 = dataSource1->GetReader();
            pService->SetResourceData(&resourceIdentifier1, L"Sheboygan_Parcels.sdf", L"File", dataReader1);
        }
    }
    catch (MgException* e)
    {
        STRING message = e->GetDetails(TEST_LOCALE);
        SAFE_RELEASE(e);
        CPPUNIT_FAIL(MG_WCHAR_TO_CHAR(message.c_str()));
    }
#endif
}


void TestGeometry::TestEnd()
{
#ifdef TEST_PREPARED_GEOMETRY_PERF
    try
    {
        MgServiceManager* serviceManager = MgServiceManager::GetInstance();
        if (serviceManager == 0)
        {
            throw new MgNullReferenceException(L"TestFeatureService.TestEnd",
                __LINE__, __WFILE__, NULL, L"", NULL);
        }

        Ptr<MgResourceService> pService = dynamic_cast<MgResourceService*>(serviceManager->RequestService(MgServiceType::ResourceService));
        if (pService == 0)
        {
            throw new MgServiceNotAvailableException(L"TestFeatureService.TestEnd",
                __LINE__, __WFILE__, NULL, L"", NULL);
        }

        // set user info
        Ptr<MgUserInformation> userInfo = new MgUserInformation(L"Administrator", L"admin");
        userInfo->SetLocale(TEST_LOCALE);
        MgUserInformation::SetCurrentUserInfo(userInfo);

        Ptr<MgResourceIdentifier> fsres1 = new MgResourceIdentifier(L"Library://UnitTests/Data/Sheboygan_Parcels.FeatureSource");
        pService->DeleteResource(fsres1);
    }
    catch (MgException* e)
    {
        STRING message = e->GetDetails(TEST_LOCALE);
        SAFE_RELEASE(e);
        CPPUNIT_FAIL(MG_WCHAR_TO_CHAR(message.c_str()));
    }
    catch (...)
    {
        throw;
    }
#endif
    ACE_DEBUG((LM_INFO, ACE_TEXT("\nGeometry tests completed.\n\n")));
}


TestGeometry::TestGeometry()
{
}


MgPoint* TestGeometry::CreatePoint()
{
    MgGeometryFactory factory;
    Ptr<MgCoordinate> coord = factory.CreateCoordinateXYZ(5.0, 3.0, 2.0);

    return factory.CreatePoint(coord);
}


MgLineString* TestGeometry::CreateLineString()
{
    MgGeometryFactory factory;

    Ptr<MgCoordinateCollection> coordCol = new MgCoordinateCollection();

    Ptr<MgCoordinate> coord1 = factory.CreateCoordinateXY(0.0, 1.0);
    Ptr<MgCoordinate> coord2 = factory.CreateCoordinateXY(2.0, 3.0);
    Ptr<MgCoordinate> coord3 = factory.CreateCoordinateXY(4.0, 5.0);

    coordCol->Add(coord1);
    coordCol->Add(coord2);
    coordCol->Add(coord3);

    return factory.CreateLineString(coordCol);
}


MgLinearRing* TestGeometry::CreateLinearRing()
{
    MgGeometryFactory factory;

    Ptr<MgCoordinate> oCoord1 = factory.CreateCoordinateXY(0.0, 0.0);
    Ptr<MgCoordinate> oCoord2 = factory.CreateCoordinateXY(5.0, 0.0);
    Ptr<MgCoordinate> oCoord3 = factory.CreateCoordinateXY(5.0, 5.0);
    Ptr<MgCoordinate> oCoord4 = factory.CreateCoordinateXY(0.0, 5.0);
    Ptr<MgCoordinate> oCoord5 = factory.CreateCoordinateXY(0.0, 0.0);

    Ptr<MgCoordinateCollection> outerRingCoord = new MgCoordinateCollection();
    outerRingCoord->Add(oCoord1);
    outerRingCoord->Add(oCoord2);
    outerRingCoord->Add(oCoord3);
    outerRingCoord->Add(oCoord4);
    outerRingCoord->Add(oCoord5);

    return factory.CreateLinearRing(outerRingCoord);
}


MgPolygon* TestGeometry::CreatePolygon()
{
    MgGeometryFactory factory;

    // OuterRing
    Ptr<MgCoordinate> oCoord1 = factory.CreateCoordinateXY(0.0, 0.0);
    Ptr<MgCoordinate> oCoord2 = factory.CreateCoordinateXY(5.0, 0.0);
    Ptr<MgCoordinate> oCoord3 = factory.CreateCoordinateXY(5.0, 5.0);
    Ptr<MgCoordinate> oCoord4 = factory.CreateCoordinateXY(0.0, 5.0);
    Ptr<MgCoordinate> oCoord5 = factory.CreateCoordinateXY(0.0, 0.0);

    Ptr<MgCoordinateCollection> outerRingCoord = new MgCoordinateCollection();
    outerRingCoord->Add(oCoord1);
    outerRingCoord->Add(oCoord2);
    outerRingCoord->Add(oCoord3);
    outerRingCoord->Add(oCoord4);
    outerRingCoord->Add(oCoord5);

    // Inner Ring1
    Ptr<MgCoordinate> i1Coord1 = factory.CreateCoordinateXY(1.0, 1.0);
    Ptr<MgCoordinate> i1Coord2 = factory.CreateCoordinateXY(2.0, 1.0);
    Ptr<MgCoordinate> i1Coord3 = factory.CreateCoordinateXY(2.0, 2.0);
    Ptr<MgCoordinate> i1Coord4 = factory.CreateCoordinateXY(1.0, 1.0);

    Ptr<MgCoordinateCollection> inner1RingCoord = new MgCoordinateCollection();
    inner1RingCoord->Add(i1Coord1);
    inner1RingCoord->Add(i1Coord2);
    inner1RingCoord->Add(i1Coord3);
    inner1RingCoord->Add(i1Coord4);

    // Inner Ring2
    Ptr<MgCoordinate> i2Coord1 = factory.CreateCoordinateXY(3.0, 3.0);
    Ptr<MgCoordinate> i2Coord2 = factory.CreateCoordinateXY(4.0, 3.0);
    Ptr<MgCoordinate> i2Coord3 = factory.CreateCoordinateXY(4.0, 4.0);
    Ptr<MgCoordinate> i2Coord4 = factory.CreateCoordinateXY(3.0, 3.0);

    Ptr<MgCoordinateCollection> inner2RingCoord = new MgCoordinateCollection();
    inner2RingCoord->Add(i2Coord1);
    inner2RingCoord->Add(i2Coord2);
    inner2RingCoord->Add(i2Coord3);
    inner2RingCoord->Add(i2Coord4);

    Ptr<MgLinearRing> extRing  = factory.CreateLinearRing(outerRingCoord);
    Ptr<MgLinearRing> intRing1 = factory.CreateLinearRing(inner1RingCoord);
    Ptr<MgLinearRing> intRing2 = factory.CreateLinearRing(inner2RingCoord);

    Ptr<MgLinearRingCollection> intRings = new MgLinearRingCollection();
    intRings->Add(intRing1);
    intRings->Add(intRing2);

    return factory.CreatePolygon(extRing, intRings);
}


MgCurveString* TestGeometry::CreateCurveString(double offset)
{
    MgGeometryFactory factory;

    // Create and return a curvestring consisting of
    // one circulararc segment and one linearstring segment

    // arcseg  = (0,0), (0,1), (1,2)
    // lineseg = (1,2), (3,0), (3,2)

    // ArcSegment
    Ptr<MgCoordinate> startPos = factory.CreateCoordinateXY(offset+0.0, offset+0.0);
    Ptr<MgCoordinate> midPos   = factory.CreateCoordinateXY(offset+0.0, offset+1.0);
    Ptr<MgCoordinate> endPos   = factory.CreateCoordinateXY(offset+1.0, offset+2.0);
    Ptr<MgArcSegment> arcSeg   = factory.CreateArcSegment(startPos, endPos, midPos);

    // Linear Segment
    Ptr<MgCoordinateCollection> points = new MgCoordinateCollection();
    Ptr<MgCoordinate> pt1 = factory.CreateCoordinateXY(offset+1.0, offset+2.0);
    Ptr<MgCoordinate> pt2 = factory.CreateCoordinateXY(offset+3.0, offset+0.0);
    Ptr<MgCoordinate> pt3 = factory.CreateCoordinateXY(offset+3.0, offset+2.0);
    points->Add(pt1);
    points->Add(pt2);
    points->Add(pt3);
    Ptr<MgLinearSegment> lineSeg = factory.CreateLinearSegment(points);

    // CurveSegment
    Ptr<MgCurveSegmentCollection> curveSegs = new MgCurveSegmentCollection();
    curveSegs->Add(arcSeg);
    curveSegs->Add(lineSeg);

    return factory.CreateCurveString(curveSegs);
}


MgCurveRing* TestGeometry::CreateCurveRing(double offset)
{
    // Ring is a closed entity.
    // Create and return a ring consisting of
    // one circulararc segment and one linearstring segment

    // arcseg  = (0,0), (0,1), (1,2)
    // lineseg = (1,2), (0,0)

    MgGeometryFactory factory;

    // ArcSegment
    Ptr<MgCoordinate> startPos = factory.CreateCoordinateXY(offset+0.0, offset+0.0);
    Ptr<MgCoordinate> midPos   = factory.CreateCoordinateXY(offset+0.0, offset+1.0);
    Ptr<MgCoordinate> endPos   = factory.CreateCoordinateXY(offset+1.0, offset+2.0);
    Ptr<MgArcSegment> arcSeg   = factory.CreateArcSegment(startPos, endPos, midPos);

    // Linear Segment
    Ptr<MgCoordinateCollection> points = new MgCoordinateCollection;
    Ptr<MgCoordinate> fromPt = factory.CreateCoordinateXY(offset+1.0, offset+2.0);
    Ptr<MgCoordinate>   toPt = factory.CreateCoordinateXY(offset+0.0, offset+0.0);
    points->Add(fromPt);
    points->Add(toPt);
    Ptr<MgLinearSegment> lineSeg = factory.CreateLinearSegment(points);

    // Curve Segment
    Ptr<MgCurveSegmentCollection> curveSegs = new MgCurveSegmentCollection();
    curveSegs->Add(arcSeg);
    curveSegs->Add(lineSeg);

    return factory.CreateCurveRing(curveSegs);
}


MgCurvePolygon* TestGeometry::CreateCurvePolygon(double offset, int increment)
{
    MgGeometryFactory factory;

    Ptr<MgCurveRing> extRing = CreateCurveRing(offset + increment);
    INT32 numIntRings = 2;

    Ptr<MgCurveRingCollection> intRings = new MgCurveRingCollection();

    Ptr<MgCurveRing> ring1 = CreateCurveRing(offset + 2 * increment);
    Ptr<MgCurveRing> ring2 = CreateCurveRing(offset + 3 * increment);

    intRings->Add(ring1);
    intRings->Add(ring2);

    return factory.CreateCurvePolygon(extRing, intRings);
}


MgMultiPoint* TestGeometry::CreateMultiPoint()
{
    MgGeometryFactory factory;

    Ptr<MgCoordinate> coord1 = factory.CreateCoordinateXYZ(1.0, 2.0, 3.0);
    Ptr<MgPoint> point1 = factory.CreatePoint(coord1);

    Ptr<MgCoordinate> coord2 = factory.CreateCoordinateXYZ(4.0, 5.0, 6.0);
    Ptr<MgPoint> point2 = factory.CreatePoint(coord2);

    Ptr<MgCoordinate> coord3 = factory.CreateCoordinateXYZ(7.0, 8.0, 9.0);
    Ptr<MgPoint> point3 = factory.CreatePoint(coord3);

    Ptr<MgPointCollection> pnts = new MgPointCollection();
    pnts->Add(point1);
    pnts->Add(point2);
    pnts->Add(point3);

    return factory.CreateMultiPoint(pnts);
}


MgMultiLineString* TestGeometry::CreateMultiLineString()
{
    MgGeometryFactory factory;

    Ptr<MgCoordinate> coord1 = factory.CreateCoordinateXYZ(0.0, 1.0, 2.0);
    Ptr<MgCoordinate> coord2 = factory.CreateCoordinateXYZ(3.0, 4.0, 5.0);
    Ptr<MgCoordinate> coord3 = factory.CreateCoordinateXYZ(6.0, 7.0, 8.0);

    Ptr<MgCoordinateCollection> coordColA = new MgCoordinateCollection();
    coordColA->Add(coord1);
    coordColA->Add(coord2);
    coordColA->Add(coord3);

    Ptr<MgCoordinate> coord4 = factory.CreateCoordinateXYZ( 9.0, 10.0, 11.0);
    Ptr<MgCoordinate> coord5 = factory.CreateCoordinateXYZ(12.0, 13.0, 14.0);
    Ptr<MgCoordinate> coord6 = factory.CreateCoordinateXYZ(15.0, 16.0, 17.0);

    Ptr<MgCoordinateCollection> coordColB = new MgCoordinateCollection();
    coordColB->Add(coord4);
    coordColB->Add(coord5);
    coordColB->Add(coord6);

    Ptr<MgLineString> lineString1 = factory.CreateLineString(coordColA);
    Ptr<MgLineString> lineString2 = factory.CreateLineString(coordColB);

    Ptr<MgLineStringCollection> lineStrings = new MgLineStringCollection();
    lineStrings->Add(lineString1);
    lineStrings->Add(lineString2);

    return factory.CreateMultiLineString(lineStrings);
}


MgMultiPolygon* TestGeometry::CreateMultiPolygon()
{
    MgGeometryFactory factory;

    Ptr<MgPolygon> polygon1 = CreatePolygon();
    Ptr<MgPolygon> polygon2 = CreatePolygon();

    Ptr<MgPolygonCollection> polygons = new MgPolygonCollection();
    polygons->Add(polygon1);
    polygons->Add(polygon2);

    return factory.CreateMultiPolygon(polygons);
}


MgMultiCurveString* TestGeometry::CreateMultiCurveString()
{
    MgGeometryFactory factory;

    Ptr<MgCurveString> curveString1 = CreateCurveString(100);
    Ptr<MgCurveString> curveString2 = CreateCurveString(200);
    Ptr<MgCurveString> curveString3 = CreateCurveString(300);

    Ptr<MgCurveStringCollection> curveStrings = new MgCurveStringCollection();
    curveStrings->Add(curveString1);
    curveStrings->Add(curveString2);
    curveStrings->Add(curveString3);

    return factory.CreateMultiCurveString(curveStrings);
}


MgMultiCurvePolygon* TestGeometry::CreateMultiCurvePolygon(INT32 numCurvePolys, double offset)
{
    MgGeometryFactory factory;

    Ptr<MgCurvePolygonCollection> curvePolys = new MgCurvePolygonCollection();
    for (INT32 i=0; i<numCurvePolys; ++i)
    {
        Ptr<MgCurvePolygon> curvePoly = CreateCurvePolygon(i+offset);
        curvePolys->Add(curvePoly);
    }

    return factory.CreateMultiCurvePolygon(curvePolys);
}


MgMultiGeometry* TestGeometry::CreateMultiGeometry()
{
    MgGeometryFactory factory;

    Ptr<MgGeometryCollection> geometries = new MgGeometryCollection();
    Ptr<MgGeometry> geometry;

    // CurvePolygon
    geometry = (MgGeometry*)CreateCurvePolygon(0);
    geometries->Add(geometry);

    // CurveString
    // Not doing CurveString because of some unfixed defect.
    // It may be the same one that sometimes affects MultiPolygon.
    geometry = (MgGeometry*)CreateCurveString(100);
    geometries->Add(geometry);

    // LineString
    geometry = (MgGeometry*)CreateLineString();
    geometries->Add(geometry);

    // Point
    geometry = (MgGeometry*)CreatePoint();
    geometries->Add(geometry);

    // Polygon
    geometry = CreatePolygon();
    geometries->Add(geometry);

    // Make MultiGeometry from the many geometries collected above.
    return factory.CreateMultiGeometry(geometries);
}


MgCoordinateSystemMeasure* TestGeometry::CreateMeasureArbitrary()
{
    MgCoordinateSystemFactory factory;
    Ptr<MgCoordinateSystem> pCoordSys = factory.Create(ArbitraryWkt);
    return pCoordSys->GetMeasure();
}


MgCoordinateSystemMeasure* TestGeometry::CreateMeasureGeographic()
{
    MgCoordinateSystemFactory factory;
    Ptr<MgCoordinateSystem> pCoordSys = factory.Create(GeographicWkt);
    return pCoordSys->GetMeasure();
}


MgCoordinateSystemMeasure* TestGeometry::CreateMeasureProjected()
{
    MgCoordinateSystemFactory factory;
    Ptr<MgCoordinateSystem> pCoordSys = factory.Create(ProjectedWkt);
    return pCoordSys->GetMeasure();
}


MgCoordinateSystem* TestGeometry::CreateCoordinateSystemArbitrary()
{
    MgCoordinateSystemFactory factory;
    return factory.Create(ArbitraryWkt);
}


MgCoordinateSystem* TestGeometry::CreateCoordinateSystemGeographic()
{
    MgCoordinateSystemFactory factory;
    return factory.Create(GeographicWkt);
}


MgCoordinateSystem* TestGeometry::CreateCoordinateSystemProjected()
{
    MgCoordinateSystemFactory factory;
    return factory.Create(ProjectedWkt);
}


bool TestGeometry::CheckGeometry(MgGeometry* geom, CREFSTRING wkt)
{
    bool success = true;
    MgWktReaderWriter readerWriter;
    Ptr<MgCoordinateIterator> iterator = geom->GetCoordinates();
    Ptr<MgGeometry> lineString = readerWriter.Read(wkt);
    Ptr<MgCoordinateIterator> baselineIterator = lineString->GetCoordinates();

    while (iterator->MoveNext() && baselineIterator->MoveNext())
    {
        Ptr<MgCoordinate> coord = iterator->GetCurrent();
        Ptr<MgCoordinate> baselineCoord = baselineIterator->GetCurrent();

        if (!MgUtil::ValuesEqual(baselineCoord->GetX(), coord->GetX()) ||
            !MgUtil::ValuesEqual(baselineCoord->GetY(), coord->GetY()))
        {
            success = false;
            break;
        }
    }

    return success;
}


bool TestGeometry::CheckGeometry(CREFSTRING calculated, CREFSTRING base)
{
    bool bResult = true;

    MgWktReaderWriter readerWriter;
    Ptr<MgGeometry> baseGeom = readerWriter.Read(base);
    Ptr<MgGeometry> calculatedGeom = readerWriter.Read(calculated);

    Ptr<MgCoordinateIterator> baseCoords = baseGeom->GetCoordinates();
    Ptr<MgCoordinateIterator> calculatedCoords = calculatedGeom->GetCoordinates();

    if (baseCoords->GetCount() == calculatedCoords->GetCount())
    {
        for (int i=0; i<baseCoords->GetCount(); ++i)
        {
            baseCoords->MoveNext();
            calculatedCoords->MoveNext();

            Ptr<MgCoordinate> baseCoord = baseCoords->GetCurrent();
            Ptr<MgCoordinate> calculatedCoord = calculatedCoords->GetCurrent();

            if (!MgUtil::ValuesEqual(baseCoord->GetX(), calculatedCoord->GetX()) ||
                !MgUtil::ValuesEqual(baseCoord->GetY(), calculatedCoord->GetY()) ||
                !MgUtil::ValuesEqual(baseCoord->GetZ(), calculatedCoord->GetZ()) ||
                !MgUtil::ValuesEqual(baseCoord->GetM(), calculatedCoord->GetM()))
            {
                bResult = false;
                break;
            }
        }
    }
    else
    {
        bResult = false;
    }

    return bResult;
}


void TestGeometry::TestCase_Point()
{
    try
    {
        STRING base = L"POINT XYZ (5 3 2)";

        Ptr<MgGeometry> geom = CreatePoint();

        MgWktReaderWriter readerWriter;
        STRING found = readerWriter.Write(geom);
        CPPUNIT_ASSERT(CheckGeometry(geom, base));
        CPPUNIT_ASSERT(CheckGeometry(geom, found));

        Ptr<MgGeometry> point1 = readerWriter.Read(base);
        found = readerWriter.Write(point1);
        CPPUNIT_ASSERT(CheckGeometry(point1, base));
        CPPUNIT_ASSERT(CheckGeometry(point1, found));

        Ptr<MgMemoryStreamHelper> helper = new MgMemoryStreamHelper();
        Ptr<MgStream> stream = new MgStream(helper);
        Ptr<MgGeometry> point2 = new MgPoint();
        point1->Serialize(stream);
        point2->Deserialize(stream);
        CPPUNIT_ASSERT(CheckGeometry(point2, base));

        MgAgfReaderWriter agfReaderWriter;
        Ptr<MgByteReader> reader = agfReaderWriter.Write(geom);
        Ptr<MgGeometry> point3 = agfReaderWriter.Read(reader);
        CPPUNIT_ASSERT(CheckGeometry(point3, base));
    }
    catch (MgException* e)
    {
        STRING message = e->GetDetails(TEST_LOCALE);
        SAFE_RELEASE(e);
        CPPUNIT_FAIL(MG_WCHAR_TO_CHAR(message.c_str()));
    }
    catch (...)
    {
        throw;
    }
}


void TestGeometry::TestCase_LineString()
{
    try
    {
        STRING base = L"LINESTRING (0 1, 2 3, 4 5)";

        Ptr<MgGeometry> geom = CreateLineString();

        MgWktReaderWriter readerWriter;
        STRING found = readerWriter.Write(geom);
        CPPUNIT_ASSERT(CheckGeometry(geom, base));
        CPPUNIT_ASSERT(CheckGeometry(geom, found));

        Ptr<MgGeometry> lineString1 = readerWriter.Read(base);
        found = readerWriter.Write(lineString1);
        CPPUNIT_ASSERT(CheckGeometry(lineString1, base));
        CPPUNIT_ASSERT(CheckGeometry(lineString1, found));

        Ptr<MgMemoryStreamHelper> helper = new MgMemoryStreamHelper();
        Ptr<MgStream> stream = new MgStream(helper);
        Ptr<MgGeometry> lineString2 = new MgLineString();
        lineString1->Serialize(stream);
        lineString2->Deserialize(stream);
        CPPUNIT_ASSERT(CheckGeometry(lineString2, base));

        MgAgfReaderWriter agfReaderWriter;
        Ptr<MgByteReader> reader = agfReaderWriter.Write(geom);
        Ptr<MgGeometry> lineString3 = agfReaderWriter.Read(reader);
        CPPUNIT_ASSERT(CheckGeometry(lineString3, base));
    }
    catch (MgException* e)
    {
        STRING message = e->GetDetails(TEST_LOCALE);
        SAFE_RELEASE(e);
        CPPUNIT_FAIL(MG_WCHAR_TO_CHAR(message.c_str()));
    }
    catch (...)
    {
        throw;
    }
}


void TestGeometry::TestCase_Polygon()
{
    try
    {
        STRING base = L"POLYGON ((0 0, 5 0, 5 5, 0 5, 0 0), (1 1, 2 1, 2 2, 1 1), (3 3, 4 3, 4 4, 3 3))";

        Ptr<MgGeometry> geom = CreatePolygon();

        MgWktReaderWriter readerWriter;
        STRING found = readerWriter.Write(geom);
        CPPUNIT_ASSERT(CheckGeometry(geom, base));
        CPPUNIT_ASSERT(CheckGeometry(geom, found));

        Ptr<MgGeometry> polygon1 = readerWriter.Read(base);
        found = readerWriter.Write(polygon1);
        CPPUNIT_ASSERT(CheckGeometry(polygon1, base));
        CPPUNIT_ASSERT(CheckGeometry(polygon1, found));

        Ptr<MgMemoryStreamHelper> helper = new MgMemoryStreamHelper();
        Ptr<MgStream> stream = new MgStream(helper);
        Ptr<MgGeometry> polygon2 = new MgPolygon();
        polygon1->Serialize(stream);
        polygon2->Deserialize(stream);
        CPPUNIT_ASSERT(CheckGeometry(polygon2, base));

        MgAgfReaderWriter agfReaderWriter;
        Ptr<MgByteReader> reader = agfReaderWriter.Write(geom);
        Ptr<MgGeometry> polygon3 = agfReaderWriter.Read(reader);
        CPPUNIT_ASSERT(CheckGeometry(polygon3, base));
    }
    catch (MgException* e)
    {
        STRING message = e->GetDetails(TEST_LOCALE);
        SAFE_RELEASE(e);
        CPPUNIT_FAIL(MG_WCHAR_TO_CHAR(message.c_str()));
    }
    catch (...)
    {
        throw;
    }
}


void TestGeometry::TestCase_CurveString()
{
    try
    {
        STRING base = L"CURVESTRING (0 0 (CIRCULARARCSEGMENT (0 1, 1 2), LINESTRINGSEGMENT (3 0, 3 2)))";

        Ptr<MgGeometry> geom = CreateCurveString(0.0);

        MgWktReaderWriter readerWriter;
        STRING found = readerWriter.Write(geom);
        CPPUNIT_ASSERT(CheckGeometry(geom, base));
        CPPUNIT_ASSERT(CheckGeometry(geom, found));

        Ptr<MgGeometry> curveString1 = readerWriter.Read(base);
        found = readerWriter.Write(curveString1);
        CPPUNIT_ASSERT(CheckGeometry(curveString1, base));
        CPPUNIT_ASSERT(CheckGeometry(curveString1, found));

        Ptr<MgMemoryStreamHelper> helper = new MgMemoryStreamHelper();
        Ptr<MgStream> stream = new MgStream(helper);
        Ptr<MgGeometry> curveString2 = new MgCurveString();
        curveString1->Serialize(stream);
        curveString2->Deserialize(stream);
        CPPUNIT_ASSERT(CheckGeometry(curveString2, base));

        MgAgfReaderWriter agfReaderWriter;
        Ptr<MgByteReader> reader = agfReaderWriter.Write(geom);
        Ptr<MgGeometry> curveString3 = agfReaderWriter.Read(reader);
        CPPUNIT_ASSERT(CheckGeometry(curveString3, base));
    }
    catch (MgException* e)
    {
        STRING message = e->GetDetails(TEST_LOCALE);
        SAFE_RELEASE(e);
        CPPUNIT_FAIL(MG_WCHAR_TO_CHAR(message.c_str()));
    }
    catch (...)
    {
        throw;
    }
}


void TestGeometry::TestCase_CurveRing()
{
    try
    {
        STRING base = L"(3.14 3.14 (CIRCULARARCSEGMENT (3.14 4.140000000000001, 4.140000000000001 5.140000000000001),"
                      L" LINESTRINGSEGMENT (3.14 3.14)))";

        Ptr<MgGeometricEntity> geom = CreateCurveRing(3.14);
        STRING found = geom->ToAwkt(true);
        CPPUNIT_ASSERT(wstring::npos != found.find(L"CIRCULARARCSEGMENT"));
        CPPUNIT_ASSERT(wstring::npos != found.find(L"LINESTRINGSEGMENT"));
    }
    catch (MgException* e)
    {
        STRING message = e->GetDetails(TEST_LOCALE);
        SAFE_RELEASE(e);
        CPPUNIT_FAIL(MG_WCHAR_TO_CHAR(message.c_str()));
    }
    catch (...)
    {
        throw;
    }
}


void TestGeometry::TestCase_CurvePolygon()
{
    try
    {
        STRING base = L"CURVEPOLYGON ((200 200 (CIRCULARARCSEGMENT (200 201, 201 202), LINESTRINGSEGMENT (200 200))),"
                      L" (300 300 (CIRCULARARCSEGMENT (300 301, 301 302), LINESTRINGSEGMENT (300 300))),"
                      L" (400 400 (CIRCULARARCSEGMENT (400 401, 401 402), LINESTRINGSEGMENT (400 400))))";

        Ptr<MgGeometry> geom = CreateCurvePolygon(100.0);

        MgWktReaderWriter readerWriter;
        STRING found = readerWriter.Write(geom);
        CPPUNIT_ASSERT(CheckGeometry(geom, base));
        CPPUNIT_ASSERT(CheckGeometry(geom, found));

        Ptr<MgGeometry> curvePolygon1 = readerWriter.Read(base);
        found = readerWriter.Write(curvePolygon1);
        CPPUNIT_ASSERT(CheckGeometry(curvePolygon1, base));
        CPPUNIT_ASSERT(CheckGeometry(curvePolygon1, found));

        Ptr<MgMemoryStreamHelper> helper = new MgMemoryStreamHelper();
        Ptr<MgStream> stream = new MgStream(helper);
        Ptr<MgGeometry> curvePolygon2 = new MgCurvePolygon();
        curvePolygon1->Serialize(stream);
        curvePolygon2->Deserialize(stream);
        CPPUNIT_ASSERT(CheckGeometry(curvePolygon2, base));

        MgAgfReaderWriter agfReaderWriter;
        Ptr<MgByteReader> reader = agfReaderWriter.Write(geom);
        Ptr<MgGeometry> curvePolygon3 = agfReaderWriter.Read(reader);
        CPPUNIT_ASSERT(CheckGeometry(curvePolygon3, base));
    }
    catch (MgException* e)
    {
        STRING message = e->GetDetails(TEST_LOCALE);
        SAFE_RELEASE(e);
        CPPUNIT_FAIL(MG_WCHAR_TO_CHAR(message.c_str()));
    }
    catch (...)
    {
        throw;
    }
}


void TestGeometry::TestCase_MultiPoint()
{
    try
    {
        STRING base = L"MULTIPOINT XYZ (1 2 3, 4 5 6, 7 8 9)";

        Ptr<MgGeometry> geom = CreateMultiPoint();

        MgWktReaderWriter readerWriter;
        STRING found = readerWriter.Write(geom);
        CPPUNIT_ASSERT(CheckGeometry(geom, base));
        CPPUNIT_ASSERT(CheckGeometry(geom, found));

        Ptr<MgGeometry> multiPoint1 = readerWriter.Read(base);
        found = readerWriter.Write(multiPoint1);
        CPPUNIT_ASSERT(CheckGeometry(multiPoint1, base));
        CPPUNIT_ASSERT(CheckGeometry(multiPoint1, base));

        Ptr<MgMemoryStreamHelper> helper = new MgMemoryStreamHelper();
        Ptr<MgStream> stream = new MgStream(helper);
        Ptr<MgGeometry> multiPoint2 = new MgMultiPoint();
        multiPoint1->Serialize(stream);
        multiPoint2->Deserialize(stream);
        CPPUNIT_ASSERT(CheckGeometry(multiPoint2, base));

        MgAgfReaderWriter agfReaderWriter;
        Ptr<MgByteReader> reader = agfReaderWriter.Write(geom);
        Ptr<MgGeometry> multiPoint3 = agfReaderWriter.Read(reader);
        CPPUNIT_ASSERT(CheckGeometry(multiPoint3, base));
    }
    catch (MgException* e)
    {
        STRING message = e->GetDetails(TEST_LOCALE);
        SAFE_RELEASE(e);
        CPPUNIT_FAIL(MG_WCHAR_TO_CHAR(message.c_str()));
    }
    catch (...)
    {
        throw;
    }
}


void TestGeometry::TestCase_MultiLineString()
{
    try
    {
        STRING base = L"MULTILINESTRING XYZ ((0 1 2, 3 4 5, 6 7 8), (9 10 11, 12 13 14, 15 16 17))";

        Ptr<MgGeometry> geom = CreateMultiLineString();

        MgWktReaderWriter readerWriter;
        STRING found = readerWriter.Write(geom);
        CPPUNIT_ASSERT(CheckGeometry(geom, base));
        CPPUNIT_ASSERT(CheckGeometry(geom, found));

        Ptr<MgGeometry> multiLineString1 = readerWriter.Read(base);
        found = readerWriter.Write(multiLineString1);
        CPPUNIT_ASSERT(CheckGeometry(multiLineString1, base));
        CPPUNIT_ASSERT(CheckGeometry(multiLineString1, found));

        Ptr<MgMemoryStreamHelper> helper = new MgMemoryStreamHelper();
        Ptr<MgStream> stream = new MgStream(helper);
        Ptr<MgGeometry> multiLineString2 = new MgMultiLineString();
        multiLineString1->Serialize(stream);
        multiLineString2->Deserialize(stream);
        CPPUNIT_ASSERT(CheckGeometry(multiLineString2, base));

        MgAgfReaderWriter agfReaderWriter;
        Ptr<MgByteReader> reader = agfReaderWriter.Write(geom);
        Ptr<MgGeometry> multiLineString3 = agfReaderWriter.Read(reader);
        CPPUNIT_ASSERT(CheckGeometry(multiLineString3, base));
    }
    catch (MgException* e)
    {
        STRING message = e->GetDetails(TEST_LOCALE);
        SAFE_RELEASE(e);
        CPPUNIT_FAIL(MG_WCHAR_TO_CHAR(message.c_str()));
    }
    catch (...)
    {
        throw;
    }
}


void TestGeometry::TestCase_MultiPolygon()
{
    try
    {
        STRING base = L"MULTIPOLYGON (((0 0, 5 0, 5 5, 0 5, 0 0), (1 1, 2 1, 2 2, 1 1), (3 3, 4 3, 4 4, 3 3)),"
                      L" ((0 0, 5 0, 5 5, 0 5, 0 0), (1 1, 2 1, 2 2, 1 1), (3 3, 4 3, 4 4, 3 3)))";

        Ptr<MgGeometry> geom = CreateMultiPolygon();

        MgWktReaderWriter readerWriter;
        STRING found = readerWriter.Write(geom);
        CPPUNIT_ASSERT(CheckGeometry(geom, base));
        CPPUNIT_ASSERT(CheckGeometry(geom, found));

        Ptr<MgGeometry> multiPolygon1 = readerWriter.Read(base);
        found = readerWriter.Write(multiPolygon1);
        CPPUNIT_ASSERT(CheckGeometry(multiPolygon1, base));
        CPPUNIT_ASSERT(CheckGeometry(multiPolygon1, found));

        Ptr<MgMemoryStreamHelper> helper = new MgMemoryStreamHelper();
        Ptr<MgStream> stream = new MgStream(helper);
        Ptr<MgGeometry> multiPolygon2 = new MgMultiPolygon();
        multiPolygon1->Serialize(stream);
        multiPolygon2->Deserialize(stream);
        CPPUNIT_ASSERT(CheckGeometry(multiPolygon2, base));

        MgAgfReaderWriter agfReaderWriter;
        Ptr<MgByteReader> reader = agfReaderWriter.Write(geom);
        Ptr<MgGeometry> multiPolygon3 = agfReaderWriter.Read(reader);
        CPPUNIT_ASSERT(CheckGeometry(multiPolygon3, base));
    }
    catch (MgException* e)
    {
        STRING message = e->GetDetails(TEST_LOCALE);
        SAFE_RELEASE(e);
        CPPUNIT_FAIL(MG_WCHAR_TO_CHAR(message.c_str()));
    }
    catch (...)
    {
        throw;
    }
}


void TestGeometry::TestCase_MultiCurveString()
{
    try
    {
        STRING base = L"MULTICURVESTRING ((100 100 (CIRCULARARCSEGMENT (100 101, 101 102), LINESTRINGSEGMENT (103 100, 103 102))),"
                      L" (200 200 (CIRCULARARCSEGMENT (200 201, 201 202), LINESTRINGSEGMENT (203 200, 203 202))),"
                      L" (300 300 (CIRCULARARCSEGMENT (300 301, 301 302), LINESTRINGSEGMENT (303 300, 303 302))))";

        Ptr<MgGeometry> geom = CreateMultiCurveString();

        MgWktReaderWriter readerWriter;
        STRING found = readerWriter.Write(geom);
        CPPUNIT_ASSERT(CheckGeometry(geom, base));
        CPPUNIT_ASSERT(CheckGeometry(geom, found));

        Ptr<MgGeometry> multiCurveString1 = readerWriter.Read(base);
        found = readerWriter.Write(multiCurveString1);
        CPPUNIT_ASSERT(CheckGeometry(multiCurveString1, base));
        CPPUNIT_ASSERT(CheckGeometry(multiCurveString1, found));

        Ptr<MgMemoryStreamHelper> helper = new MgMemoryStreamHelper();
        Ptr<MgStream> stream = new MgStream(helper);
        Ptr<MgGeometry> multiCurveString2 = new MgMultiCurveString();
        multiCurveString1->Serialize(stream);
        multiCurveString2->Deserialize(stream);
        CPPUNIT_ASSERT(CheckGeometry(multiCurveString2, base));

        MgAgfReaderWriter agfReaderWriter;
        Ptr<MgByteReader> reader = agfReaderWriter.Write(geom);
        Ptr<MgGeometry> multiCurveString3 = agfReaderWriter.Read(reader);
        CPPUNIT_ASSERT(CheckGeometry(multiCurveString3, base));
    }
    catch (MgException* e)
    {
        STRING message = e->GetDetails(TEST_LOCALE);
        SAFE_RELEASE(e);
        CPPUNIT_FAIL(MG_WCHAR_TO_CHAR(message.c_str()));
    }
    catch (...)
    {
        throw;
    }
}


void TestGeometry::TestCase_MultiCurvePolygon()
{
    try
    {
        STRING base = L"MULTICURVEPOLYGON (((200 200 (CIRCULARARCSEGMENT (200 201, 201 202), LINESTRINGSEGMENT (200 200))),"
                      L" (300 300 (CIRCULARARCSEGMENT (300 301, 301 302), LINESTRINGSEGMENT (300 300))),"
                      L" (400 400 (CIRCULARARCSEGMENT (400 401, 401 402), LINESTRINGSEGMENT (400 400)))),"
                      L" ((201 201 (CIRCULARARCSEGMENT (201 202, 202 203), LINESTRINGSEGMENT (201 201))),"
                      L" (301 301 (CIRCULARARCSEGMENT (301 302, 302 303), LINESTRINGSEGMENT (301 301))),"
                      L" (401 401 (CIRCULARARCSEGMENT (401 402, 402 403), LINESTRINGSEGMENT (401 401)))),"
                      L" ((202 202 (CIRCULARARCSEGMENT (202 203, 203 204), LINESTRINGSEGMENT (202 202))),"
                      L" (302 302 (CIRCULARARCSEGMENT (302 303, 303 304), LINESTRINGSEGMENT (302 302))),"
                      L" (402 402 (CIRCULARARCSEGMENT (402 403, 403 404), LINESTRINGSEGMENT (402 402)))))";

        Ptr<MgGeometry> geom = CreateMultiCurvePolygon(3, 100.0);

        MgWktReaderWriter readerWriter;
        STRING found = readerWriter.Write(geom);
        CPPUNIT_ASSERT(CheckGeometry(geom, base));
        CPPUNIT_ASSERT(CheckGeometry(geom, found));

        Ptr<MgGeometry> multiCurvePolygon1 = readerWriter.Read(base);
        found = readerWriter.Write(multiCurvePolygon1);
        CPPUNIT_ASSERT(CheckGeometry(multiCurvePolygon1, base));
        CPPUNIT_ASSERT(CheckGeometry(multiCurvePolygon1, found));

        Ptr<MgMemoryStreamHelper> helper = new MgMemoryStreamHelper();
        Ptr<MgStream> stream = new MgStream(helper);
        Ptr<MgGeometry> multiCurvePolygon2 = new MgMultiCurvePolygon();
        multiCurvePolygon1->Serialize(stream);
        multiCurvePolygon2->Deserialize(stream);
        CPPUNIT_ASSERT(CheckGeometry(multiCurvePolygon2, base));

        MgAgfReaderWriter agfReaderWriter;
        Ptr<MgByteReader> reader = agfReaderWriter.Write(geom);
        Ptr<MgGeometry> multiCurvePolygon3 = agfReaderWriter.Read(reader);
        CPPUNIT_ASSERT(CheckGeometry(multiCurvePolygon3, base));
    }
    catch (MgException* e)
    {
        STRING message = e->GetDetails(TEST_LOCALE);
        SAFE_RELEASE(e);
        CPPUNIT_FAIL(MG_WCHAR_TO_CHAR(message.c_str()));
    }
    catch (...)
    {
        throw;
    }
}


void TestGeometry::TestCase_MultiGeometry()
{
    try
    {
        STRING base = L"GEOMETRYCOLLECTION (CURVEPOLYGON ((100 100 (CIRCULARARCSEGMENT (100 101, 101 102),"
                      L" LINESTRINGSEGMENT (100 100))), (200 200 (CIRCULARARCSEGMENT (200 201, 201 202),"
                      L" LINESTRINGSEGMENT (200 200))), (300 300 (CIRCULARARCSEGMENT (300 301, 301 302),"
                      L" LINESTRINGSEGMENT (300 300)))), CURVESTRING (100 100 (CIRCULARARCSEGMENT (100 101, 101 102),"
                      L" LINESTRINGSEGMENT (103 100, 103 102))), LINESTRING (0 1, 2 3, 4 5), POINT XYZ (5 3 2),"
                      L" POLYGON ((0 0, 5 0, 5 5, 0 5, 0 0), (1 1, 2 1, 2 2, 1 1), (3 3, 4 3, 4 4, 3 3)))";

        MgWktReaderWriter readerWriter;

        Ptr<MgGeometry> geom = CreateMultiGeometry();
        STRING found = readerWriter.Write(geom);
        CPPUNIT_ASSERT(CheckGeometry(geom, base));
        CPPUNIT_ASSERT(CheckGeometry(geom, found));

        Ptr<MgGeometry> multiGeometry1 = readerWriter.Read(base);
        found = readerWriter.Write(multiGeometry1);
        CPPUNIT_ASSERT(CheckGeometry(multiGeometry1, base));
        CPPUNIT_ASSERT(CheckGeometry(multiGeometry1, found));

        Ptr<MgMemoryStreamHelper> helper = new MgMemoryStreamHelper();
        Ptr<MgStream> stream = new MgStream(helper);
        Ptr<MgGeometry> multiGeometry2 = new MgMultiGeometry();
        multiGeometry1->Serialize(stream);
        multiGeometry2->Deserialize(stream);
        CPPUNIT_ASSERT(CheckGeometry(multiGeometry2, base));

        MgAgfReaderWriter agfReaderWriter;
        Ptr<MgByteReader> reader = agfReaderWriter.Write(geom);
        Ptr<MgGeometry> multiGeometry3 = agfReaderWriter.Read(reader);
        CPPUNIT_ASSERT(CheckGeometry(multiGeometry3, base));
    }
    catch (MgException* e)
    {
        STRING message = e->GetDetails(TEST_LOCALE);
        SAFE_RELEASE(e);
        CPPUNIT_FAIL(MG_WCHAR_TO_CHAR(message.c_str()));
    }
    catch (...)
    {
        throw;
    }
}


void TestGeometry::TestCase_BufferNoMeasure()
{
    try
    {
        MgWktReaderWriter readerWriter;

        Ptr<MgPoint> point = CreatePoint();
        Ptr<MgGeometry> geom = point->Buffer(5.0, NULL);
        STRING found = geom->ToAwkt(false);
        CPPUNIT_ASSERT(CheckGeometry(geom, found));

        Ptr<MgMultiGeometry> multiGeometry = CreateMultiGeometry();
        geom = multiGeometry->Buffer(5.0, NULL);
        found = geom->ToAwkt(false);
        CPPUNIT_ASSERT(CheckGeometry(geom, found));
    }
    catch (MgException* e)
    {
        STRING message = e->GetDetails(TEST_LOCALE);
        SAFE_RELEASE(e);
        CPPUNIT_FAIL(MG_WCHAR_TO_CHAR(message.c_str()));
    }
    catch (...)
    {
        throw;
    }
}


void TestGeometry::TestCase_BufferArbitrary()
{
    try
    {
        MgWktReaderWriter readerWriter;
        Ptr<MgMeasure> measure = CreateMeasureArbitrary();

        Ptr<MgPoint> testPoint = CreatePoint();
        Ptr<MgGeometry> geom = testPoint->Buffer(5.0, measure);
        STRING found = geom->ToAwkt(false);
        CPPUNIT_ASSERT(CheckGeometry(geom, found));
    }
    catch (MgException* e)
    {
        STRING message = e->GetDetails(TEST_LOCALE);
        SAFE_RELEASE(e);
        CPPUNIT_FAIL(MG_WCHAR_TO_CHAR(message.c_str()));
    }
    catch (...)
    {
        throw;
    }
}


void TestGeometry::TestCase_BufferGeographic()
{
    try
    {
        MgWktReaderWriter readerWriter;
        Ptr<MgMeasure> measure = CreateMeasureGeographic();

        Ptr<MgPoint> testPoint = CreatePoint();
        Ptr<MgGeometry> geom = testPoint->Buffer(5.0, measure);
        STRING found = geom->ToAwkt(false);
        CPPUNIT_ASSERT(CheckGeometry(geom, found));

        Ptr<MgLineString> testLine = CreateLineString();
        geom = testLine->Buffer(5.0, measure);
        found = geom->ToAwkt(false);
        CPPUNIT_ASSERT(CheckGeometry(geom, found));

        Ptr<MgPolygon> testPolygon = CreatePolygon();
        geom = testPolygon->Buffer(5.0, measure);
        found = geom->ToAwkt(false);
        CPPUNIT_ASSERT(CheckGeometry(geom, found));

        Ptr<MgCurveString> testCurveString = CreateCurveString(0.0);
        geom = testCurveString->Buffer(5.0, measure);
        found = geom->ToAwkt(false);
        CPPUNIT_ASSERT(CheckGeometry(geom, found));

        Ptr<MgCurvePolygon> testCurvePolygon = CreateCurvePolygon(0.0, 10);
        geom = testCurvePolygon->Buffer(1.0, measure);
        found = geom->ToAwkt(false);
        CPPUNIT_ASSERT(CheckGeometry(geom, found));
    }
    catch (MgException* e)
    {
        STRING message = e->GetDetails(TEST_LOCALE);
        SAFE_RELEASE(e);
        CPPUNIT_FAIL(MG_WCHAR_TO_CHAR(message.c_str()));
    }
    catch (...)
    {
        throw;
    }
}


void TestGeometry::TestCase_BufferProjected()
{
    try
    {
        MgWktReaderWriter readerWriter;
        Ptr<MgMeasure> measure = CreateMeasureProjected();

        Ptr<MgPoint> testPoint = CreatePoint();
        Ptr<MgGeometry> geom = testPoint->Buffer(5.0, measure);
        STRING found = readerWriter.Write(geom);
        CPPUNIT_ASSERT(CheckGeometry(geom, found));

        Ptr<MgLineString> testLine = CreateLineString();
        Ptr<MgGeometry> buffer = testLine->Buffer(5.0, measure);
        CPPUNIT_ASSERT(buffer);

        Ptr<MgPolygon> testPolygon = CreatePolygon();
        // TODO: Need to investigate why this test throws an exception
        //CPPUNIT_ASSERT_THROW_MG(testPolygon->Buffer(5.0, measure), MgUnclassifiedException*);
    }
    catch (MgException* e)
    {
        STRING message = e->GetDetails(TEST_LOCALE);
        SAFE_RELEASE(e);
        CPPUNIT_FAIL(MG_WCHAR_TO_CHAR(message.c_str()));
    }
    catch (...)
    {
        throw;
    }
}


void TestGeometry::TestCase_Intersection()
{
    try
    {
        MgWktReaderWriter readerWriter;
        MgGeometryFactory factory;

        //TEST 1
        Ptr<MgCoordinate> coord = factory.CreateCoordinateXY(100.0, 100.0);
        Ptr<MgPoint> point = new MgPoint(coord);
        Ptr<MgPolygon> polygon = CreatePolygon();
        Ptr<MgGeometry> geom = point->Intersection(polygon);
        CPPUNIT_ASSERT(geom == NULL);

        //TEST 2
        coord = factory.CreateCoordinateXY(100.0, 100.0);
        point = factory.CreatePoint(coord);
        Ptr<MgCoordinateCollection> outerCoords = new MgCoordinateCollection();
        Ptr<MgCoordinate> coord1 = factory.CreateCoordinateXY( 45.0,  45.0);
        Ptr<MgCoordinate> coord2 = factory.CreateCoordinateXY( 45.0, -45.0);
        Ptr<MgCoordinate> coord3 = factory.CreateCoordinateXY(-45.0, -45.0);
        Ptr<MgCoordinate> coord4 = factory.CreateCoordinateXY(-45.0,  45.0);
        Ptr<MgCoordinate> coord5 = factory.CreateCoordinateXY( 45.0,  45.0);
        outerCoords->Add(coord1);
        outerCoords->Add(coord2);
        outerCoords->Add(coord3);
        outerCoords->Add(coord4);
        outerCoords->Add(coord5);
        Ptr<MgLinearRing> outerRing = factory.CreateLinearRing(outerCoords);
        Ptr<MgLinearRingCollection> innerRings = NULL;
        polygon = factory.CreatePolygon(outerRing, innerRings);
        geom = point->Intersection(polygon);
        CPPUNIT_ASSERT(geom == NULL);

        //TEST 3
        STRING base = L"POINT (5 3)";
        point = CreatePoint();
        polygon = CreatePolygon();
        geom = point->Intersection(polygon);
        STRING found = readerWriter.Write(geom);
        CPPUNIT_ASSERT(CheckGeometry(found, base));

        //TEST 4
        Ptr<MgLineString> lineString = CreateLineString();
        geom = lineString->Intersection(point);
        CPPUNIT_ASSERT(geom == NULL);

        //TEST 5
        base = L"LINESTRING (0 1, 2 3, 4 5)";
        polygon = CreatePolygon();
        geom = polygon->Intersection(lineString);
        found = readerWriter.Write(geom);
        CPPUNIT_ASSERT(CheckGeometry(found, base));

        //TEST 6
        base = L"GEOMETRYCOLLECTION (POINT (0 0), LINESTRING (0 0.99246192690647705, 0.045672548622950601 1.1204286132756418, 0.1310606385532562 1.2912047931362536, 0.23641094695643791 1.4504434254749068, 0.3601872291077422 1.5958224524579303, 0.50058454809348885 1.7252219205068542, 0.65555559485563741 1.8367548939952993, 0.82284054256798778 1.9287949710194192, 1 2, 1.5 1.5, 2 1, 3 0, 3 0, 3 2))";
        Ptr<MgCurveString> curveString = CreateCurveString(0.0);
        geom = curveString->Intersection(polygon);
        found = readerWriter.Write(geom);
        CPPUNIT_ASSERT(CheckGeometry(found, base));

        //TEST 7
        Ptr<MgCurvePolygon> curvePolygon = CreateCurvePolygon(0.0);
        geom = curvePolygon->Intersection(curveString);
        CPPUNIT_ASSERT(geom == NULL);

        //TEST 8
        Ptr<MgMultiPoint> multiPoint = CreateMultiPoint();
        geom = multiPoint->Intersection(point);
        CPPUNIT_ASSERT(geom == NULL);

        //TEST 9
        base = L"MULTIPOINT (1 2, 4 5)";
        Ptr<MgMultiLineString> multiLineString = CreateMultiLineString();
        geom = multiLineString->Intersection(multiPoint);
        found = readerWriter.Write(geom);
        CPPUNIT_ASSERT(CheckGeometry(found, base));

        //TEST 10
        base = L"LINESTRING (0 1, 3 4, 4 5)";
        Ptr<MgMultiPolygon> multiPolygon = CreateMultiPolygon();
        geom = multiPolygon->Intersection(multiLineString);
        found = readerWriter.Write(geom);
        CPPUNIT_ASSERT(CheckGeometry(found, base));

        //TEST 11
        Ptr<MgMultiCurveString> multiCurveString = CreateMultiCurveString();
        geom = multiCurveString->Intersection(multiPolygon);
        CPPUNIT_ASSERT(geom == NULL);

        //TEST 12
        Ptr<MgMultiCurvePolygon> multiCurvePolygon = CreateMultiCurvePolygon(3, 0.0);
        geom = multiCurvePolygon->Intersection(curvePolygon);
        CPPUNIT_ASSERT(geom == NULL);
    }
    catch (MgException* e)
    {
        STRING message = e->GetDetails(TEST_LOCALE);
        SAFE_RELEASE(e);
        CPPUNIT_FAIL(MG_WCHAR_TO_CHAR(message.c_str()));
    }
    catch (...)
    {
        throw;
    }
}


void TestGeometry::TestCase_Boundary()
{
    try
    {
        MgWktReaderWriter readerWriter;

        //TEST 1
        Ptr<MgPoint> point = CreatePoint();
        Ptr<MgGeometry> geom = point->Boundary();
        CPPUNIT_ASSERT(geom == NULL);

        //TEST 2
        STRING base = L"MULTIPOINT (0 1, 4 5)";
        Ptr<MgLineString> lineString = CreateLineString();
        geom = lineString->Boundary();
        STRING found = readerWriter.Write(geom);
        CPPUNIT_ASSERT(CheckGeometry(found, base));

        //TEST 3
        base = L"MULTILINESTRING ((0 0, 5 0, 5 5, 0 5, 0 0), (1 1, 2 1, 2 2, 1 1), (3 3, 4 3, 4 4, 3 3))";
        Ptr<MgPolygon> polygon = CreatePolygon();
        geom = polygon->Boundary();
        found = readerWriter.Write(geom);
        CPPUNIT_ASSERT(CheckGeometry(found, base));

        //TEST 4
        base = L"MULTIPOINT (0 0, 3 2)";
        Ptr<MgCurveString> curveString = CreateCurveString(0.0);
        geom = curveString->Boundary();
        found = readerWriter.Write(geom);
        CPPUNIT_ASSERT(CheckGeometry(found, base));

        //TEST 5
        base = L"MULTILINESTRING ((100 100, 99.958214339826924 100.14943334715824, 99.931276918387084 100.30224284282258, 99.919447157774457 100.45695684801559, 99.922838985050518 100.61208538229199, 99.941419735064471 100.76613447306482, 99.975010465036377 100.91762054337813, 100.02328767787407 101.0650846995641, 100.08578643762691 101.20710678118655, 100.16190484707316 101.34231903796228, 100.25090984431932 101.46941930194401, 100.35194426258683 101.58718352810953, 100.46403508519673 101.69447758258438, 100.58610281625221 101.79026816497108, 100.7169718767742 101.87363275959679, 100.85538192616956 101.94376851984352, 101 102, 100 100), (200 200,199.95821433982692 200.14943334715824, 199.93127691838708 200.30224284282258, 199.91944715777444 200.45695684801558, 199.92283898505053 200.61208538229198, 199.94141973506447 200.76613447306482, 199.97501046503638 200.91762054337812, 200.02328767787407 201.0650846995641, 200.08578643762689 201.20710678118655, 200.16190484707317 201.34231903796228, 200.25090984431932 201.46941930194401, 200.35194426258681 201.58718352810953, 200.46403508519671 201.6944775825844, 200.58610281625221 201.79026816497108, 200.71697187677418 201.87363275959677, 200.85538192616957 201.9437685198435, 201 202, 200 200), (300 300, 299.95821433982695 300.14943334715826, 299.93127691838708 300.30224284282258, 299.91944715777447 300.45695684801558, 299.92283898505053 300.61208538229198, 299.94141973506447 300.76613447306482, 299.97501046503641 300.91762054337812, 300.02328767787407 301.06508469956412, 300.08578643762689 301.20710678118655, 300.16190484707317 301.34231903796228, 300.25090984431932 301.46941930194401, 300.35194426258681 301.58718352810951,300.46403508519671 301.6944775825844, 300.58610281625221 301.79026816497111, 300.71697187677421 301.87363275959677, 300.85538192616957 301.9437685198435, 301 302, 300 300))";
        Ptr<MgCurvePolygon> curvePolygon = CreateCurvePolygon(0.0);
        geom = curvePolygon->Boundary();
        found = readerWriter.Write(geom);
        CPPUNIT_ASSERT(CheckGeometry(found, base));

        //TEST 6
        Ptr<MgMultiPoint> multiPoint = CreateMultiPoint();
        geom = multiPoint->Boundary();
        CPPUNIT_ASSERT(geom == NULL);

        //TEST 7
        base = L"MULTIPOINT (0 1, 6 7, 9 10, 15 16)";
        Ptr<MgMultiLineString> multiLineString = CreateMultiLineString();
        geom = multiLineString->Boundary();
        found = readerWriter.Write(geom);
        CPPUNIT_ASSERT(CheckGeometry(found, base));

        //TEST 8
        base = L"MULTILINESTRING ((0 0, 5 0, 5 5, 0 5, 0 0), (1 1, 2 1, 2 2, 1 1), (3 3, 4 3, 4 4, 3 3), (0 0, 5 0, 5 5, 0 5, 0 0), (1 1, 2 1, 2 2, 1 1), (3 3, 4 3, 4 4, 3 3))";
        Ptr<MgMultiPolygon> multiPolygon = CreateMultiPolygon();
        geom = multiPolygon->Boundary();
        found = readerWriter.Write(geom);
        CPPUNIT_ASSERT(CheckGeometry(found, base));

        //TEST 9
        base = L"MULTIPOINT (100 100, 103 102, 200 200, 203 202, 300 300, 303 302)";
        Ptr<MgMultiCurveString> multiCurveString = CreateMultiCurveString();
        geom = multiCurveString->Boundary();
        found = readerWriter.Write(geom);
        CPPUNIT_ASSERT(CheckGeometry(found, base));

        //TEST 10
        Ptr<MgMultiCurvePolygon> multiCurvePolygon = CreateMultiCurvePolygon(3, 0.0);
        geom = multiCurvePolygon->Boundary();
        found = readerWriter.Write(geom);
        CPPUNIT_ASSERT(0 == ::wcsncmp(found.c_str(), L"MULTILINESTRING", ::wcslen(L"MULTILINESTRING")));
    }
    catch (MgException* e)
    {
        STRING message = e->GetDetails(TEST_LOCALE);
        SAFE_RELEASE(e);
        CPPUNIT_FAIL(MG_WCHAR_TO_CHAR(message.c_str()));
    }
    catch (...)
    {
        throw;
    }
}


void TestGeometry::TestCase_ConvexHull()
{
    try
    {
        MgWktReaderWriter readerWriter;

        //TEST 1
        STRING base = L"POINT (5 3)";
        Ptr<MgPoint> point = CreatePoint();
        Ptr<MgGeometry> geom = point->ConvexHull();
        STRING found = readerWriter.Write(geom);
        CPPUNIT_ASSERT(CheckGeometry(found, base));

        //TEST 2
        base = L"LINESTRING (0 1, 4 5)";
        Ptr<MgLineString> lineString = CreateLineString();
        geom = lineString->ConvexHull();
        found = readerWriter.Write(geom);
        CPPUNIT_ASSERT(CheckGeometry(found, base));

        //TEST 3
        base = L"POLYGON ((0 0, 0 5, 5 5, 5 0, 0 0))";
        Ptr<MgPolygon> polygon = CreatePolygon();
        geom = polygon->ConvexHull();
        found = readerWriter.Write(geom);
        CPPUNIT_ASSERT(CheckGeometry(found, base));

        //TEST 4
        base = L"POLYGON ((0 0, -0.049331651274742601 0.18445058333395731, -0.076070558282857095 0.37350258771831019, -0.0798268075493902 0.5643992092210961, -0.060545624501699299 0.75435674523904783, -0.018508172206062701 0.94060518714990526, 0.045672548622950601 1.1204286132756418, 0.1310606385532562 1.2912047931362536, 0.23641094695643791 1.4504434254749068, 0.3601872291077422 1.5958224524579303, 0.50058454809348885 1.7252219205068542, 0.65555559485563741 1.8367548939952993, 0.82284054256798778 1.9287949710194192, 1 2, 3 2, 3 0, 0 0))";
        Ptr<MgCurveString> curveString = CreateCurveString(0.0);
        geom = curveString->ConvexHull();
        found = readerWriter.Write(geom);
        CPPUNIT_ASSERT(CheckGeometry(found, base));

        //TEST 5
        base = L"POLYGON ((100 100, 99.958214339826924 100.14943334715824, 99.931276918387084 100.30224284282258, 99.919447157774457 100.45695684801559, 99.922838985050518 100.61208538229199, 99.941419735064471 100.76613447306482, 99.975010465036377 100.91762054337813, 100.02328767787407 101.0650846995641, 100.08578643762691 101.20710678118655, 100.16190484707316 101.34231903796228, 100.25090984431932 101.46941930194401, 100.35194426258683 101.58718352810953, 100.46403508519673 101.69447758258438, 100.58610281625221 101.79026816497108, 100.7169718767742 101.87363275959679, 100.85538192616956 101.94376851984352, 101 102, 100 100))";
        Ptr<MgCurvePolygon> curvePolygon = CreateCurvePolygon(0.0);
        geom = curvePolygon->ConvexHull();
        found = readerWriter.Write(geom);
        CPPUNIT_ASSERT(CheckGeometry(found, base));

        //TEST 6
        base = L"LINESTRING (1 2, 7 8)";
        Ptr<MgMultiPoint> multiPoint = CreateMultiPoint();
        geom = multiPoint->ConvexHull();
        found = readerWriter.Write(geom);
        CPPUNIT_ASSERT(CheckGeometry(found, base));

        //TEST 7
        // The reason for the different check below is because we get slightly
        // different results with rounding under Debug and Release builds.
#ifdef _DEBUG
        base = L"LINESTRING (0 1, 15 16)";
#else
        base = L"POLYGON ((0 1, 15 16, 3 4, 12 13, 0 1))";
#endif
        Ptr<MgMultiLineString> multiLineString = CreateMultiLineString();
        geom = multiLineString->ConvexHull();
        found = readerWriter.Write(geom);
        //CPPUNIT_ASSERT(CheckGeometry(found, base));

        //TEST 8
#ifdef _DEBUG
        base = L"POLYGON ((0 0, 0 5, 5 5, 5 0, 0 0))";
#else
        base = L"POLYGON ((0 0, 0 5, 5 5, 1 1, 2 2, 4 3, 5 0, 0 0))";
#endif
        Ptr<MgMultiPolygon> multiPolygon = CreateMultiPolygon();
        geom = multiPolygon->ConvexHull();
        found = readerWriter.Write(geom);
        //CPPUNIT_ASSERT(CheckGeometry(found, base));

        //TEST 9
        base = L"POLYGON ((100 100, 100 101, 301 302, 303 302, 303 300, 103 100, 100 100))";
        Ptr<MgMultiCurveString> multiCurveString = CreateMultiCurveString();
        geom = multiCurveString->ConvexHull();
        found = readerWriter.Write(geom);
        //CPPUNIT_ASSERT(CheckGeometry(found, base));

        //TEST 10
#ifdef _DEBUG
        base = L"POLYGON ((100 100, 99.947569611829252 100.20006685764317, 99.92170173801513 100.40526565450925, 99.922838985050518 100.61208538229199, 99.950961894323342 100.81698729810778, 100.00558927505878 101.01646547336746, 100.08578643762691 101.20710678118655, 100.19018118634131 101.3856492959325, 100.31698729810778 101.54903810567666, 102.31698729810778 103.54903810567666, 202.31698729810779 203.54903810567666, 302.31698729810779 303.54903810567663, 302.46403508519671 303.6944775825844, 302.6288085192017 303.81947921688231, 302.808488280983 303.92190419595067, 303 304, 302 302, 100 100))";
#else
        base = L"POLYGON ((100 100, 99.947569611829252 100.20006685764317, 99.92170173801513 100.40526565450925, 99.922838985050518 100.61208538229199, 99.950961894323342 100.81698729810778, 100.00558927505878 101.01646547336746, 100.08578643762691 101.20710678118655, 100.19018118634131 101.3856492959325, 100.31698729810778 101.54903810567666, 102.31698729810778 103.54903810567666, 202.31698729810779 203.54903810567666, 302.31698729810779 303.54903810567663, 302.46403508519671 303.6944775825844, 302.6288085192017 303.81947921688231, 302.808488280983 303.92190419595067, 303 304, 301.94756961182924 302.20006685764315, 301 301, 102 102, 300 300, 101 101, 302 302, 100 100))";
#endif
        Ptr<MgMultiCurvePolygon> multiCurvePolygon = CreateMultiCurvePolygon(3, 0.0);
        geom = multiCurvePolygon->ConvexHull();
        found = readerWriter.Write(geom);
        //CPPUNIT_ASSERT(CheckGeometry(found, base));

        //TEST 11
#ifdef _DEBUG
        base = L"POLYGON ((0 0, 0 5, 300.31698729810779 301.54903810567663, 301 302, 300 300, 5 0, 0 0))";
#else
        base = L"POLYGON ((0 0, 0 5, 300.31698729810779 301.54903810567663, 301 302, 300 300, 1 1, 100 100, 103 102, 103 100, 5 0, 0 0))";
#endif
        Ptr<MgMultiGeometry> multiGeometry = CreateMultiGeometry();
        geom = multiGeometry->ConvexHull();
        found = readerWriter.Write(geom);
        //CPPUNIT_ASSERT(CheckGeometry(found, base));
    }
    catch (MgException* e)
    {
        STRING message = e->GetDetails(TEST_LOCALE);
        SAFE_RELEASE(e);
        CPPUNIT_FAIL(MG_WCHAR_TO_CHAR(message.c_str()));
    }
    catch (...)
    {
        throw;
    }
}


void TestGeometry::TestCase_Difference()
{
    try
    {
        MgWktReaderWriter readerWriter;
        MgGeometryFactory factory;

        //TEST 1
        STRING base = L"POINT (5 3)";
        Ptr<MgPoint> point = CreatePoint();
        Ptr<MgCoordinate> coord = factory.CreateCoordinateXY(4.0, 8.0);
        Ptr<MgPoint> pointCoord = factory.CreatePoint(coord);
        Ptr<MgGeometry> geom = point->Difference(pointCoord);
        STRING found = readerWriter.Write(geom);
        CPPUNIT_ASSERT(CheckGeometry(found, base));

        //TEST 2
        base = L"LINESTRING (0 1, 2 3, 4 5)";
        Ptr<MgLineString> lineString = CreateLineString();
        geom = lineString->Difference(point);
        found = readerWriter.Write(geom);
        CPPUNIT_ASSERT(CheckGeometry(found, base));

        //TEST 3
        base = L"POLYGON ((4 5, 5 5, 5 0, 0 0, 0 1, 0 5, 4 5), (1 1, 2 1, 2 2, 1 1), (3 3, 4 3, 4 4, 3 3))";
        Ptr<MgPolygon> polygon = CreatePolygon();
        geom = polygon->Difference(lineString);
        found = readerWriter.Write(geom);
        CPPUNIT_ASSERT(CheckGeometry(found, base));

        //TEST 4
        base = L"MULTILINESTRING ((0 0, -0.049331651274742601 0.18445058333395731, -0.076070558282857095 0.37350258771831019, -0.0798268075493902 0.5643992092210961, -0.060545624501699299 0.75435674523904783, -0.018508172206062701 0.94060518714990526,0 0.99246192690647705), (1.5 1.5, 2 1))";
        Ptr<MgCurveString> curveString = CreateCurveString(0.0);
        geom = curveString->Difference(polygon);
        found = readerWriter.Write(geom);
        CPPUNIT_ASSERT(CheckGeometry(found, base));

        //TEST 5
        Ptr<MgCurvePolygon> curvePolygon = CreateCurvePolygon(0.0);
        geom = curvePolygon->Difference(curveString);

        //TEST 6
        base = L"MULTIPOINT (1 2, 4 5, 7 8)";
        Ptr<MgMultiPoint> multiPoint = CreateMultiPoint();
        geom = multiPoint->Difference(point);
        found = readerWriter.Write(geom);
        CPPUNIT_ASSERT(CheckGeometry(found, base));

        //TEST 7
        base = L"MULTILINESTRING ((0 1, 3 4, 6 7), (9 10, 12 13, 15 16))";
        Ptr<MgMultiLineString> multiLineString = CreateMultiLineString();
        geom = multiLineString->Difference(multiPoint);
        found = readerWriter.Write(geom);
        CPPUNIT_ASSERT(CheckGeometry(found, base));

        //TEST 8
        base = L"POLYGON ((5 0, 0 0, 0 1, 0 5, 4 5, 5 5, 5 0), (1 1, 2 1, 2 2, 1 1),"
               L" (3 3, 4 3, 4 4, 3 3))";
        Ptr<MgMultiPolygon> multiPolygon = CreateMultiPolygon();
        geom = multiPolygon->Difference(multiLineString);
        found = readerWriter.Write(geom);
        CPPUNIT_ASSERT(CheckGeometry(found, base));

        //TEST 9
        base = L"MULTILINESTRING ((100 100, 100 101, 101 102, 103 100, 103 102),"
               L" (200 200, 200 201, 201 202, 203 200, 203 202), (300 300, 300 301,"
               L" 301 302, 303 300, 303 302))";
        Ptr<MgMultiCurveString> multiCurveString = CreateMultiCurveString();
        geom = multiCurveString->Difference(multiPolygon);
        found = readerWriter.Write(geom);
        CPPUNIT_ASSERT(CheckGeometry(found, base));

        //TEST 10
        Ptr<MgMultiCurvePolygon> multiCurvePolygon = CreateMultiCurvePolygon(3, 0.0);
        geom = multiCurvePolygon->Difference(curvePolygon);

        //TEST 11
        Ptr<MgMultiGeometry> multiGeometry = CreateMultiGeometry();
        geom = multiGeometry->Difference(polygon);
        geom = multiGeometry->Difference(multiCurvePolygon);
    }
    catch (MgException* e)
    {
        STRING message = e->GetDetails(TEST_LOCALE);
        SAFE_RELEASE(e);
        CPPUNIT_FAIL(MG_WCHAR_TO_CHAR(message.c_str()));
    }
    catch (...)
    {
        throw;
    }
}


void TestGeometry::TestCase_SymetricDifference()
{
    try
    {
        MgWktReaderWriter readerWriter;
        MgGeometryFactory factory;

        //NOTE: Somewhere between GEOS 2.2.0 and GEOS 3.4.2 the result of a symetric difference 
        //is sensitive to the order of the operand geometries. For tests where we're comparing 
        //against an expected result, the operands have been flipped to provide the correct result 
        // 
        //eg. TEST 1 (GEOS 2.2.0) 
        //Ptr<MgGeometry> geom = point->SymetricDifference(pointCoord); 
        // 
        //eg. TEST 1 (GEOS 3.4.2) 
        //Ptr<MgGeometry> geom = pointCoord->SymetricDifference(point); 

        //TEST 1
        STRING base = L"MULTIPOINT (4 8, 5 3)";
        Ptr<MgPoint> point = CreatePoint();
        Ptr<MgCoordinate> coord = factory.CreateCoordinateXY(4.0, 8.0);
        Ptr<MgPoint> pointCoord = factory.CreatePoint(coord);
        Ptr<MgGeometry> geom = pointCoord->SymetricDifference(point);
        STRING found = readerWriter.Write(geom);
        CPPUNIT_ASSERT(CheckGeometry(found, base));

        //TEST 2
        base = L"GEOMETRYCOLLECTION (POINT (5 3), LINESTRING (0 1, 2 3, 4 5))";
        Ptr<MgLineString> lineString = CreateLineString();
        geom = point->SymetricDifference(lineString);
        found = readerWriter.Write(geom);
        CPPUNIT_ASSERT(CheckGeometry(found, base));

        //TEST 3
        base = L"POLYGON ((4 5, 5 5, 5 0, 0 0, 0 1, 0 5, 4 5), (1 1, 2 1, 2 2, 1 1),"
               L" (3 3, 4 3, 4 4, 3 3))";
        Ptr<MgPolygon> polygon = CreatePolygon();
        geom = lineString->SymetricDifference(polygon);
        found = readerWriter.Write(geom);
        CPPUNIT_ASSERT(CheckGeometry(found, base));

        //TEST 4
        base = L"GEOMETRYCOLLECTION (LINESTRING (0 0, -0.049331651274742601 0.18445058333395731, -0.076070558282857095 0.37350258771831019, -0.0798268075493902 0.5643992092210961, -0.060545624501699299 0.75435674523904783, -0.018508172206062701 0.94060518714990526, 0 0.99246192690647705, 1.5 1.5, 2 1), POLYGON ((3 0, 0 0, 0 0.99246192690647705, 0 5, 5 5, 5 0, 3 0), (1 1, 2 1, 2 2, 1.5 1.5, 1 1), (3 3, 4 3, 4 4,3 3)))";
        Ptr<MgCurveString> curveString = CreateCurveString(0.0);
        geom = polygon->SymetricDifference(curveString);
        found = readerWriter.Write(geom);
        CPPUNIT_ASSERT(CheckGeometry(found, base));

        //TEST 5
        Ptr<MgCurvePolygon> curvePolygon = CreateCurvePolygon(0.0);
        geom = pointCoord->SymetricDifference(curvePolygon);

        //TEST 6
        base = L"MULTIPOINT (1 2, 4 5, 5 3, 7 8)";
        Ptr<MgMultiPoint> multiPoint = CreateMultiPoint();
        geom = point->SymetricDifference(multiPoint);
        found = readerWriter.Write(geom);
        CPPUNIT_ASSERT(CheckGeometry(found, base));

        //TEST 7
        base = L"GEOMETRYCOLLECTION (POINT (7 8), LINESTRING (0 1, 3 4, 6 7, 9 10, 12 13, 15 16))";
        Ptr<MgMultiLineString> multiLineString = CreateMultiLineString();
        geom = multiPoint->SymetricDifference(multiLineString);
        found = readerWriter.Write(geom);
        CPPUNIT_ASSERT(CheckGeometry(found, base));

        //TEST 8
        base = L"GEOMETRYCOLLECTION (LINESTRING (4 5, 6 7, 9 10, 12 13, 15 16),"
               L" POLYGON ((5 0, 0 0, 0 1, 0 5, 4 5, 5 5, 5 0), (1 1, 2 1, 2 2, 1 1),"
               L" (3 3, 4 3, 4 4, 3 3)))";
        Ptr<MgMultiPolygon> multiPolygon = CreateMultiPolygon();
        geom = multiLineString->SymetricDifference(multiPolygon);
        found = readerWriter.Write(geom);
        CPPUNIT_ASSERT(CheckGeometry(found, base));

        //TEST 9
        base = L"GEOMETRYCOLLECTION (POINT (1 2), POINT (4 5), POINT (7 8),"
               L" LINESTRING (100 100, 100 101, 101 102, 103 100, 103 102, 200 200, 200 201,"
               L" 201 202, 203 200, 203 202, 300 300, 300 301, 301 302, 303 300, 303 302))";
        Ptr<MgMultiCurveString> multiCurveString = CreateMultiCurveString();
        geom = multiPoint->SymetricDifference(multiCurveString);
        found = readerWriter.Write(geom);
        CPPUNIT_ASSERT(CheckGeometry(found, base));

        //TEST 10
        Ptr<MgMultiCurvePolygon> multiCurvePolygon = CreateMultiCurvePolygon(3, 0.0);
        geom = curvePolygon->SymetricDifference(multiCurvePolygon);

        //TEST 11
        Ptr<MgMultiGeometry> multiGeometry = CreateMultiGeometry();
        geom = multiCurvePolygon->SymetricDifference(multiGeometry);
    }
    catch (MgException* e)
    {
        STRING message = e->GetDetails(TEST_LOCALE);
        SAFE_RELEASE(e);
        CPPUNIT_FAIL(MG_WCHAR_TO_CHAR(message.c_str()));
    }
    catch (...)
    {
        throw;
    }
}


void TestGeometry::TestCase_Union()
{
    try
    {
        MgWktReaderWriter readerWriter;
        MgGeometryFactory factory;

        //TEST 1
        STRING base = L"MULTIPOINT (5 3, 4 8)";
        Ptr<MgPoint> point = CreatePoint();
        Ptr<MgCoordinate> coord = factory.CreateCoordinateXY(4.0, 8.0);
        Ptr<MgPoint> pointCoord = factory.CreatePoint(coord);
        Ptr<MgGeometry> geom = point->Union(pointCoord);
        STRING found = readerWriter.Write(geom);
        CPPUNIT_ASSERT(CheckGeometry(found, base));

        //TEST 2
        base = L"GEOMETRYCOLLECTION (LINESTRING (0 1, 2 3, 4 5), POINT (5 3))";
        Ptr<MgLineString> lineString = CreateLineString();
        geom = lineString->Union(point);
        found = readerWriter.Write(geom);
        CPPUNIT_ASSERT(CheckGeometry(found, base));

        //TEST 3
        base = L"POLYGON ((4 5, 5 5, 5 0, 0 0, 0 1, 0 5, 4 5), (1 1, 2 1, 2 2, 1 1),"
               L" (3 3, 4 3, 4 4, 3 3))";
        Ptr<MgPolygon> polygon = CreatePolygon();
        geom = polygon->Union(lineString);
        found = readerWriter.Write(geom);
        CPPUNIT_ASSERT(CheckGeometry(found, base));

        //TEST 4
        base = L"GEOMETRYCOLLECTION (LINESTRING (0 0, -0.049331651274742601 0.18445058333395731, -0.076070558282857095 0.37350258771831019, -0.0798268075493902 0.5643992092210961, -0.060545624501699299 0.75435674523904783, -0.018508172206062701 0.94060518714990526, 0 0.99246192690647705, 1.5 1.5, 2 1), POLYGON ((3 0, 0 0, 0 0.99246192690647705, 0 5, 5 5, 5 0, 3 0), (1 1, 2 1, 2 2, 1.5 1.5, 1 1), (3 3, 4 3, 4 4,3 3)))";
        Ptr<MgCurveString> curveString = CreateCurveString(0.0);
        geom = curveString->Union(polygon);
        found = readerWriter.Write(geom);
        CPPUNIT_ASSERT(CheckGeometry(found, base));

        //TEST 5
        base = L"GEOMETRYCOLLECTION (POLYGON ((100 100, 99.958214339826924 100.14943334715824, 99.931276918387084 100.30224284282258, 99.919447157774457 100.45695684801559, 99.922838985050518 100.61208538229199, 99.941419735064471 100.76613447306482, 99.975010465036377 100.91762054337813, 100.02328767787407 101.0650846995641, 100.08578643762691 101.20710678118655, 100.16190484707316 101.34231903796228, 100.25090984431932 101.46941930194401, 100.35194426258683 101.58718352810953, 100.46403508519673 101.69447758258438, 100.58610281625221 101.79026816497108, 100.7169718767742 101.87363275959679, 100.85538192616956 101.94376851984352, 101 102, 100 100), (200 200, 199.95821433982692 200.14943334715824, 199.93127691838708 200.30224284282258, 199.91944715777444 200.45695684801558, 199.92283898505053 200.61208538229198, 199.94141973506447 200.76613447306482, 199.97501046503638 200.91762054337812, 200.02328767787407 201.0650846995641, 200.08578643762689 201.20710678118655, 200.16190484707317 201.34231903796228, 200.25090984431932 201.46941930194401,200.35194426258681 201.58718352810953, 200.46403508519671 201.6944775825844, 200.58610281625221 201.79026816497108, 200.71697187677418 201.87363275959677, 200.85538192616957 201.9437685198435, 201 202, 200 200), (300 300, 299.95821433982695 300.14943334715826, 299.93127691838708 300.30224284282258, 299.91944715777447 300.45695684801558, 299.92283898505053 300.61208538229198, 299.94141973506447 300.76613447306482, 299.97501046503641 300.91762054337812, 300.02328767787407 301.06508469956412, 300.08578643762689 301.20710678118655, 300.16190484707317 301.34231903796228, 300.25090984431932 301.46941930194401, 300.35194426258681 301.58718352810951, 300.46403508519671 301.6944775825844, 300.58610281625221 301.79026816497111, 300.71697187677421 301.87363275959677, 300.85538192616957 301.9437685198435, 301 302, 300 300)), LINESTRING (0 0, -0.049331651274742601 0.18445058333395731, -0.076070558282857095 0.37350258771831019, -0.0798268075493902 0.5643992092210961, -0.060545624501699299 0.75435674523904783, -0.018508172206062701 0.94060518714990526, 0.045672548622950601 1.1204286132756418, 0.1310606385532562 1.2912047931362536, 0.23641094695643791 1.4504434254749068, 0.3601872291077422 1.5958224524579303, 0.50058454809348885 1.7252219205068542, 0.65555559485563741 1.8367548939952993, 0.82284054256798778 1.9287949710194192, 1 2, 3 0, 3 2))";
        Ptr<MgCurvePolygon> curvePolygon = CreateCurvePolygon(0.0);
        geom = curvePolygon->Union(curveString);
        found = readerWriter.Write(geom);
        CPPUNIT_ASSERT(CheckGeometry(found, base));

        //TEST 6
        base = L"MULTIPOINT (1 2, 4 5, 5 3, 7 8)";
        Ptr<MgMultiPoint> multiPoint = CreateMultiPoint();
        geom = multiPoint->Union(point);
        found = readerWriter.Write(geom);
        CPPUNIT_ASSERT(CheckGeometry(found, base));

        //TEST 7
        base = L"GEOMETRYCOLLECTION (POINT (7 8), LINESTRING (0 1, 3 4, 6 7, 9 10, 12 13, 15 16))";
        Ptr<MgMultiLineString> multiLineString = CreateMultiLineString();
        geom = multiLineString->Union(multiPoint);
        found = readerWriter.Write(geom);
        CPPUNIT_ASSERT(CheckGeometry(found, base));

        //TEST 8
        base = L"GEOMETRYCOLLECTION (LINESTRING (4 5, 6 7, 9 10, 12 13, 15 16),"
               L" POLYGON ((5 0, 0 0, 0 1, 0 5, 4 5, 5 5, 5 0), (1 1, 2 1, 2 2, 1 1),"
               L" (3 3, 4 3, 4 4, 3 3)))";
        Ptr<MgMultiPolygon> multiPolygon = CreateMultiPolygon();
        geom = multiPolygon->Union(multiLineString);
        found = readerWriter.Write(geom);
        CPPUNIT_ASSERT(CheckGeometry(found, base));

        //TEST 9
        base = L"GEOMETRYCOLLECTION (LINESTRING (100 100, 100 101, 101 102, 103 100,"
               L" 103 102, 200 200, 200 201, 201 202, 203 200, 203 202, 300 300, 300 301,"
               L" 301 302, 303 300, 303 302), POLYGON ((0 0, 5 0, 5 5, 0 5, 0 0),"
               L" (1 1, 2 1, 2 2, 1 1), (3 3, 4 3, 4 4, 3 3, 0 0, 5 0, 5 5, 0 5, 0 0),"
               L" (1 1, 2 1, 2 2, 1 1), (3 3, 4 3, 4 4, 3 3)))";
        Ptr<MgMultiCurveString> multiCurveString = CreateMultiCurveString();
        geom = multiCurveString->Union(multiPolygon);
        found = readerWriter.Write(geom);
        CPPUNIT_ASSERT(CheckGeometry(found, base));

        //TEST 10
        Ptr<MgMultiCurvePolygon> multiCurvePolygon = CreateMultiCurvePolygon(3, 0.0);
        geom = multiCurvePolygon->Union(curvePolygon);

        //TEST 11
        Ptr<MgMultiGeometry> multiGeometry = CreateMultiGeometry();
        geom = multiGeometry->Union(multiCurvePolygon);
    }
    catch (MgException* e)
    {
        STRING message = e->GetDetails(TEST_LOCALE);
        SAFE_RELEASE(e);
        CPPUNIT_FAIL(MG_WCHAR_TO_CHAR(message.c_str()));
    }
    catch (...)
    {
        throw;
    }
}


void TestGeometry::TestCase_Distance()
{
    try
    {
        Ptr<MgPoint> point1 = CreatePoint();
        Ptr<MgPoint> point2 = CreatePoint();
        Ptr<MgCoordinateSystemMeasure> measure = CreateMeasureArbitrary();
        Ptr<MgCoordinateSystem> coordinateSystem = measure->GetCoordSys();
        double dist = point1->Distance(point2, measure);
        CPPUNIT_ASSERT(dist == 0.0);

        Ptr<MgLineString> lineString = CreateLineString();
        dist = lineString->Distance(point1, measure);
        CPPUNIT_ASSERT(dist == 2.2360679774997898);

        double meters = coordinateSystem->ConvertCoordinateSystemUnitsToMeters(dist);
        CPPUNIT_ASSERT(meters == 3598.6025831814218);

        Ptr<MgPolygon> polygon = CreatePolygon();
        dist = polygon->Distance(lineString, measure);
        CPPUNIT_ASSERT(dist == 1.0);

        meters = coordinateSystem->ConvertCoordinateSystemUnitsToMeters(dist);
        CPPUNIT_ASSERT(meters == 1609.3440000000001);

        Ptr<MgCurveString> curveString = CreateCurveString(0.0);
        dist = curveString->Distance(polygon, measure);
        CPPUNIT_ASSERT(dist == 0.0);

        meters = coordinateSystem->ConvertCoordinateSystemUnitsToMeters(dist);
        CPPUNIT_ASSERT(meters == 0.0);

        Ptr<MgCurvePolygon> curvePolygon = CreateCurvePolygon(0.0);
        dist = curvePolygon->Distance(lineString, measure);
        CPPUNIT_ASSERT(dist == 135.05924625881784);

        meters = coordinateSystem->ConvertCoordinateSystemUnitsToMeters(dist);
        CPPUNIT_ASSERT(meters == 217356.78761115094);

        Ptr<MgMultiPoint> multiPoint = CreateMultiPoint();
        dist = multiPoint->Distance(lineString, measure);
        CPPUNIT_ASSERT(dist == 0.0);

        meters = coordinateSystem->ConvertCoordinateSystemUnitsToMeters(dist);
        CPPUNIT_ASSERT(meters == 0.0);

        Ptr<MgMultiLineString> multiLineString = CreateMultiLineString();
        dist = multiLineString->Distance(multiPoint, measure);
        CPPUNIT_ASSERT(dist == 1.4142135623730951);

        meters = coordinateSystem->ConvertCoordinateSystemUnitsToMeters(dist);
        CPPUNIT_ASSERT(meters == 2275.9561113237664);

        Ptr<MgMultiPolygon> multiPolygon = CreateMultiPolygon();
        dist = multiPolygon->Distance(multiLineString, measure);
        CPPUNIT_ASSERT(dist == 1.0);

        meters = coordinateSystem->ConvertCoordinateSystemUnitsToMeters(dist);
        CPPUNIT_ASSERT(meters == 1609.3440000000001);

        Ptr<MgMultiCurveString> multiCurveString = CreateMultiCurveString();
        dist = multiCurveString->Distance(lineString, measure);
        CPPUNIT_ASSERT(dist == 135.05924625881784);

        meters = coordinateSystem->ConvertCoordinateSystemUnitsToMeters(dist);
        CPPUNIT_ASSERT(meters == 217356.78761115094);

        Ptr<MgMultiCurvePolygon> multiCurvePolygon = CreateMultiCurvePolygon(2, 0.0);
        dist = multiCurvePolygon->Distance(lineString, measure);
        CPPUNIT_ASSERT(dist == 135.05924625881784);

        meters = coordinateSystem->ConvertCoordinateSystemUnitsToMeters(dist);
        CPPUNIT_ASSERT(meters == 217356.78761115094);

        Ptr<MgMultiGeometry> multiGeometry = CreateMultiGeometry();
        dist = multiGeometry->Distance(lineString, measure);
        CPPUNIT_ASSERT(dist == 0.0);

        meters = coordinateSystem->ConvertCoordinateSystemUnitsToMeters(dist);
        CPPUNIT_ASSERT(meters == 0.0);
    }
    catch (MgException* e)
    {
        STRING message = e->GetDetails(TEST_LOCALE);
        SAFE_RELEASE(e);
        CPPUNIT_FAIL(MG_WCHAR_TO_CHAR(message.c_str()));
    }
    catch (...)
    {
        throw;
    }
}


void TestGeometry::TestCase_Transform()
{
    try
    {
        MgWktReaderWriter readerWriter;
        Ptr<MgCoordinateSystem> coordSysArbitrary = CreateCoordinateSystemArbitrary();
        Ptr<MgCoordinateSystem> coordSysGeographic = CreateCoordinateSystemGeographic();
        Ptr<MgCoordinateSystem> coordSysProjected = CreateCoordinateSystemProjected();

        MgCoordinateSystemFactory csFactory;
        Ptr<MgTransform> transform = csFactory.GetTransform(coordSysArbitrary, coordSysArbitrary);

        STRING base = L"POINT XYZ (5 3 2)";
        Ptr<MgPoint> point = CreatePoint();
        Ptr<MgGeometricEntity> geom = point->Transform(transform);
        STRING found = geom->ToAwkt(false);
        CPPUNIT_ASSERT(CheckGeometry(found, base));

        base = L"LINESTRING (0 1, 2 3, 4 5)";
        Ptr<MgLineString> lineString = CreateLineString();
        geom = lineString->Transform(transform);
        found = geom->ToAwkt(false);
        CPPUNIT_ASSERT(CheckGeometry(found, base));

        base = L"POLYGON ((0 0, 5 0, 5 5, 0 5, 0 0), (1 1, 2 1, 2 2, 1 1), (3 3, 4 3, 4 4, 3 3))";
        Ptr<MgPolygon> polygon = CreatePolygon();
        geom = polygon->Transform(transform);
        found = geom->ToAwkt(false);
        CPPUNIT_ASSERT(CheckGeometry(found, base));

        base = L"CURVESTRING (0 0 (CIRCULARARCSEGMENT (0 1, 1 2), LINESTRINGSEGMENT (3 0, 3 2)))";
        Ptr<MgCurveString> curveString = CreateCurveString(0.0);
        geom = curveString->Transform(transform);
        found = geom->ToAwkt(false);
        CPPUNIT_ASSERT(CheckGeometry(found, base));

        base = L"(0 0 (CIRCULARARCSEGMENT (0 1, 1 2), LINESTRINGSEGMENT (0 0)))";
        Ptr<MgCurveRing> curveRing = CreateCurveRing(0.0);
        geom = curveRing->Transform(transform);
        found = geom->ToAwkt(false);
        // CPPUNIT_ASSERT(CheckGeometry(found, base)); // This does not work on CurveRing objects

        base = L"CURVEPOLYGON ((100 100 (CIRCULARARCSEGMENT (100 101, 101 102), LINESTRINGSEGMENT (100 100))),"
               L" (200 200 (CIRCULARARCSEGMENT (200 201, 201 202), LINESTRINGSEGMENT (200 200))),"
               L" (300 300 (CIRCULARARCSEGMENT (300 301, 301 302), LINESTRINGSEGMENT (300 300))))";
        Ptr<MgCurvePolygon> curvePolygon = CreateCurvePolygon(0.0);
        geom = curvePolygon->Transform(transform);
        found = geom->ToAwkt(false);
        CPPUNIT_ASSERT(CheckGeometry(found, base));

        base = L"MULTIPOINT XYZ (1 2 3, 4 5 6, 7 8 9)";
        Ptr<MgMultiPoint> multiPoint = CreateMultiPoint();
        geom = multiPoint->Transform(transform);
        found = geom->ToAwkt(false);
        CPPUNIT_ASSERT(CheckGeometry(found, base));

        base = L"MULTILINESTRING XYZ ((0 1 2, 3 4 5, 6 7 8), (9 10 11, 12 13 14, 15 16 17))";
        Ptr<MgMultiLineString> multiLineString = CreateMultiLineString();
        geom = multiLineString->Transform(transform);
        found = geom->ToAwkt(false);
        CPPUNIT_ASSERT(CheckGeometry(found, base));

        base = L"MULTIPOLYGON (((0 0, 5 0, 5 5, 0 5, 0 0), (1 1, 2 1, 2 2, 1 1),"
               L" (3 3, 4 3, 4 4, 3 3)), ((0 0, 5 0, 5 5, 0 5, 0 0), (1 1, 2 1, 2 2, 1 1),"
               L" (3 3, 4 3, 4 4, 3 3)))";
        Ptr<MgMultiPolygon> multiPolygon = CreateMultiPolygon();
        geom = multiPolygon->Transform(transform);
        found = geom->ToAwkt(false);
        CPPUNIT_ASSERT(CheckGeometry(found, base));

        base = L"MULTICURVESTRING ((100 100 (CIRCULARARCSEGMENT (100 101, 101 102), LINESTRINGSEGMENT (103 100, 103 102))),"
               L" (200 200 (CIRCULARARCSEGMENT (200 201, 201 202), LINESTRINGSEGMENT (203 200, 203 202))),"
               L" (300 300 (CIRCULARARCSEGMENT (300 301, 301 302), LINESTRINGSEGMENT (303 300, 303 302))))";
        Ptr<MgMultiCurveString> multiCurveString = CreateMultiCurveString();
        geom = multiCurveString->Transform(transform);
        found = geom->ToAwkt(false);
        CPPUNIT_ASSERT(CheckGeometry(found, base));

        base = L"MULTICURVEPOLYGON (((100 100 (CIRCULARARCSEGMENT (100 101, 101 102), LINESTRINGSEGMENT (100 100))),"
               L" (200 200 (CIRCULARARCSEGMENT (200 201, 201 202), LINESTRINGSEGMENT (200 200))),"
               L" (300 300 (CIRCULARARCSEGMENT (300 301, 301 302), LINESTRINGSEGMENT (300 300)))),"
               L" ((101 101 (CIRCULARARCSEGMENT (101 102, 102 103), LINESTRINGSEGMENT (101 101))),"
               L" (201 201 (CIRCULARARCSEGMENT (201 202, 202 203), LINESTRINGSEGMENT (201 201))),"
               L" (301 301 (CIRCULARARCSEGMENT (301 302, 302 303), LINESTRINGSEGMENT (301 301)))),"
               L" ((102 102 (CIRCULARARCSEGMENT (102 103, 103 104), LINESTRINGSEGMENT (102 102))),"
               L" (202 202 (CIRCULARARCSEGMENT (202 203, 203 204), LINESTRINGSEGMENT (202 202))),"
               L" (302 302 (CIRCULARARCSEGMENT (302 303, 303 304), LINESTRINGSEGMENT (302 302)))))";
        Ptr<MgMultiCurvePolygon> multiCurvePolygon = CreateMultiCurvePolygon(3, 0.0);
        geom = multiCurvePolygon->Transform(transform);
        found = geom->ToAwkt(false);
        CPPUNIT_ASSERT(CheckGeometry(found, base));

        base = L"GEOMETRYCOLLECTION (CURVEPOLYGON ((100 100 (CIRCULARARCSEGMENT (100 101, 101 102),"
               L" LINESTRINGSEGMENT (100 100))), (200 200 (CIRCULARARCSEGMENT (200 201, 201 202),"
               L" LINESTRINGSEGMENT (200 200))), (300 300 (CIRCULARARCSEGMENT (300 301, 301 302),"
               L" LINESTRINGSEGMENT (300 300)))), CURVESTRING (100 100 (CIRCULARARCSEGMENT (100 101, 101 102),"
               L" LINESTRINGSEGMENT (103 100, 103 102))), LINESTRING (0 1, 2 3, 4 5), POINT XYZ (5 3 2),"
               L" POLYGON ((0 0, 5 0, 5 5, 0 5, 0 0), (1 1, 2 1, 2 2, 1 1), (3 3, 4 3, 4 4, 3 3)))";
        Ptr<MgMultiGeometry> multiGeometry = CreateMultiGeometry();
        geom = multiGeometry->Transform(transform);
        found = geom->ToAwkt(false);
        CPPUNIT_ASSERT(CheckGeometry(found, base));
    }
    catch (MgException* e)
    {
        STRING message = e->GetDetails(TEST_LOCALE);
        SAFE_RELEASE(e);
        CPPUNIT_FAIL(MG_WCHAR_TO_CHAR(message.c_str()));
    }
    catch (...)
    {
        throw;
    }
}


void TestGeometry::TestCase_Touches()
{
    try
    {
        //TEST 1
        Ptr<MgPoint> point = CreatePoint();
        Ptr<MgPolygon> polygon = CreatePolygon();
        bool touches = point->Touches(polygon);
        CPPUNIT_ASSERT(touches);
        touches = polygon->Touches(point);
        CPPUNIT_ASSERT(touches);
        Ptr<MgPreparedGeometry> ppoint = point->Prepare();
        Ptr<MgPreparedGeometry> ppolygon = polygon->Prepare();
        touches = ppoint->Touches(polygon);
        CPPUNIT_ASSERT(touches);
        touches = ppolygon->Touches(point);
        CPPUNIT_ASSERT(touches);

        //TEST 2
        MgGeometryFactory factory;
        Ptr<MgCoordinate> coord = factory.CreateCoordinateXY(100.0, 100.0);
        point = new MgPoint(coord);
        touches = point->Touches(polygon);
        CPPUNIT_ASSERT(!touches);
        touches = polygon->Touches(point);
        CPPUNIT_ASSERT(!touches);
        ppoint = point->Prepare();
        ppolygon = polygon->Prepare();
        touches = ppoint->Touches(polygon);
        CPPUNIT_ASSERT(!touches);
        touches = ppolygon->Touches(point);
        CPPUNIT_ASSERT(!touches);

        //TEST 3
        Ptr<MgMultiPolygon> multiPolygon = CreateMultiPolygon();
        point = CreatePoint();
        touches = point->Touches(multiPolygon);
        CPPUNIT_ASSERT(!touches);
        touches = multiPolygon->Touches(point);
        CPPUNIT_ASSERT(!touches);
        ppoint = point->Prepare();
        Ptr<MgPreparedGeometry> pmultiPolygon = multiPolygon->Prepare();
        touches = ppoint->Touches(multiPolygon);
        CPPUNIT_ASSERT(!touches);
        touches = pmultiPolygon->Touches(point);
        CPPUNIT_ASSERT(!touches);

        //TEST 4
        Ptr<MgCoordinateCollection> collection = new MgCoordinateCollection();
        Ptr<MgCoordinate> coord1 = new MgCoordinateXY( 60.0, 120.0);
        Ptr<MgCoordinate> coord2 = new MgCoordinateXY( 60.0,  40.0);
        Ptr<MgCoordinate> coord3 = new MgCoordinateXY(160.0,  40.0);
        Ptr<MgCoordinate> coord4 = new MgCoordinateXY(160.0, 120.0);
        Ptr<MgCoordinate> coord5 = new MgCoordinateXY( 60.0, 120.0);
        collection->Add(coord1);
        collection->Add(coord2);
        collection->Add(coord3);
        collection->Add(coord4);
        collection->Add(coord5);
        Ptr<MgLinearRing> linearRing1 = factory.CreateLinearRing(collection);

        collection = new MgCoordinateCollection();
        Ptr<MgCoordinate> coord6 = new MgCoordinateXY( 70.0, 100.0);
        Ptr<MgCoordinate> coord7 = new MgCoordinateXY(100.0,  70.0);
        Ptr<MgCoordinate> coord8 = new MgCoordinateXY( 60.0, 120.0);
        collection->Add(coord1);
        collection->Add(coord5);
        collection->Add(coord6);
        collection->Add(coord7);
        collection->Add(coord8);
        Ptr<MgLinearRing> linearRing2 = factory.CreateLinearRing(collection);
        Ptr<MgLinearRingCollection> ringCollection = new MgLinearRingCollection();
        ringCollection->Add(linearRing2);

        polygon = factory.CreatePolygon(linearRing1, ringCollection);
        coord = factory.CreateCoordinateXY(100.0, 100.0);
        point = factory.CreatePoint(coord);
        touches = polygon->Touches(point);
        CPPUNIT_ASSERT(!touches);
        ppolygon = polygon->Prepare();
        touches = ppolygon->Touches(point);
        CPPUNIT_ASSERT(!touches);

        //TEST 5
        coord1 = factory.CreateCoordinateXY( 45.0,  45.0);
        coord2 = factory.CreateCoordinateXY( 45.0, -45.0);
        coord3 = factory.CreateCoordinateXY(-45.0, -45.0);
        coord4 = factory.CreateCoordinateXY(-45.0,  45.0);
        coord5 = factory.CreateCoordinateXY( 45.0,  45.0);
        collection = new MgCoordinateCollection();
        collection->Add(coord1);
        collection->Add(coord2);
        collection->Add(coord3);
        collection->Add(coord4);
        collection->Add(coord5);
        linearRing1 = factory.CreateLinearRing(collection);

        coord6 = factory.CreateCoordinateXY(  0.0,  20.0);
        coord7 = factory.CreateCoordinateXY( 20.0, -20.0);
        coord8 = factory.CreateCoordinateXY(-20.0, -20.0);
        collection = new MgCoordinateCollection();
        collection->Add(coord6);
        collection->Add(coord7);
        collection->Add(coord8);
        collection->Add(coord6);
        linearRing2 = factory.CreateLinearRing(collection);

        ringCollection = new MgLinearRingCollection();
        ringCollection->Add(linearRing2);
        polygon = factory.CreatePolygon(linearRing1, ringCollection);
        coord = factory.CreateCoordinateXY(100.0, 100.0);
        point = factory.CreatePoint(coord);
        touches = point->Touches(polygon);
        CPPUNIT_ASSERT(!touches);
        ppoint = point->Prepare();
        touches = ppoint->Touches(polygon);
        CPPUNIT_ASSERT(!touches);

        //TEST 6
        coord1 = factory.CreateCoordinateXY(100.0, 100.0);
        coord2 = factory.CreateCoordinateXY( 45.0,  45.0);
        coord3 = factory.CreateCoordinateXY(-45.0, -45.0);
        Ptr<MgPoint> point1 = factory.CreatePoint(coord1);
        Ptr<MgPoint> point2 = factory.CreatePoint(coord2);
        Ptr<MgPoint> point3 = factory.CreatePoint(coord3);

        Ptr<MgCoordinate> start1   = factory.CreateCoordinateXY( 45.0,  45.0);
        Ptr<MgCoordinate> end1     = factory.CreateCoordinateXY( 45.0, -45.0);
        Ptr<MgCoordinate> control1 = factory.CreateCoordinateXY( 45.0,   0.0);
        Ptr<MgCoordinate> start2   = factory.CreateCoordinateXY( 45.0, -45.0);
        Ptr<MgCoordinate> end2     = factory.CreateCoordinateXY(-45.0, -45.0);
        Ptr<MgCoordinate> control2 = factory.CreateCoordinateXY(  0.0, -45.0);

        Ptr<MgCurveSegment> curveSegment1 = factory.CreateArcSegment(start1, end1, control1);
        Ptr<MgCurveSegment> curveSegment2 = factory.CreateArcSegment(start2, end2, control2);

        Ptr<MgCurveSegmentCollection> curveSegments = new MgCurveSegmentCollection();
        curveSegments->Add(curveSegment1);
        curveSegments->Add(curveSegment2);

        Ptr<MgCurveString> curveString = factory.CreateCurveString(curveSegments);
        touches = curveString->Touches(point1);
        touches = curveString->Touches(point3);
        touches = curveString->Touches(point2);
    }
    catch (MgException* e)
    {
        STRING message = e->GetDetails(TEST_LOCALE);
        SAFE_RELEASE(e);
        CPPUNIT_FAIL(MG_WCHAR_TO_CHAR(message.c_str()));
    }
    catch (...)
    {
        throw;
    }
}


void TestGeometry::TestCase_Envelope()
{
    try
    {
        MgGeometryFactory factory;

        Ptr<MgCoordinate> coord1 = factory.CreateCoordinateXY(10.0,  0.0);
        Ptr<MgCoordinate> coord2 = factory.CreateCoordinateXY( 0.0, 10.0);

        Ptr<MgCoordinateCollection> coords = new MgCoordinateCollection();
        coords->Add(coord1);
        coords->Add(coord2);

        Ptr<MgLineString> lineString = factory.CreateLineString(coords);

        Ptr<MgEnvelope> env = lineString->Envelope();

        coord1 = env->GetLowerLeftCoordinate();
        coord2 = env->GetUpperRightCoordinate();
    }
    catch (MgException* e)
    {
        STRING message = e->GetDetails(TEST_LOCALE);
        SAFE_RELEASE(e);
        CPPUNIT_FAIL(MG_WCHAR_TO_CHAR(message.c_str()));
    }
    catch (...)
    {
        throw;
    }
}


void TestGeometry::TestCase_GetArea()
{
    try
    {
        MgGeometryFactory factory;

        //TEST 1
        Ptr<MgPoint> point = CreatePoint();
        double area = point->GetArea();
        CPPUNIT_ASSERT(area == 0.0);

        //TEST 2
        Ptr<MgLineString> lineString = CreateLineString();
        area = lineString->GetArea();
        CPPUNIT_ASSERT(area == 0.0);

        //TEST 3
        Ptr<MgPolygon> polygon = CreatePolygon();
        area = polygon->GetArea();
        CPPUNIT_ASSERT(area == 24.0);

        //TEST 4
        Ptr<MgCurveString> curveString = CreateCurveString(0.0);
        area = curveString->GetArea();
        CPPUNIT_ASSERT(area == 0.0);

        //TEST 5
        Ptr<MgCurveRing> curveRing = CreateCurveRing(0.0);
        area = curveRing->GetArea();
        CPPUNIT_ASSERT(area == 0.0);

        //TEST 6
        Ptr<MgCurvePolygon> curvePolygon = CreateCurvePolygon(0.0);
        area = curveRing->GetArea();
        CPPUNIT_ASSERT(area == 0.0);

        //TEST 7
        Ptr<MgMultiPoint> multiPoint = CreateMultiPoint();
        area = multiPoint->GetArea();
        CPPUNIT_ASSERT(area == 0.0);

        //TEST 8
        Ptr<MgMultiLineString> multiLineString = CreateMultiLineString();
        area = multiLineString->GetArea();
        CPPUNIT_ASSERT(area == 0.0);

        //TEST 9
        Ptr<MgMultiPolygon> multiPolygon = CreateMultiPolygon();
        area = multiPolygon->GetArea();
        CPPUNIT_ASSERT(area == 48.0);

        //TEST 10
        Ptr<MgMultiCurveString> multiCurveString = CreateMultiCurveString();
        area = multiCurveString->GetArea();
        CPPUNIT_ASSERT(area == 0.0);

        //TEST 11
        Ptr<MgMultiCurvePolygon> multiCurvePolygon = CreateMultiCurvePolygon(3, 0.0);
        area = curveRing->GetArea();
        CPPUNIT_ASSERT(area == 0.0);

        //TEST 12
        Ptr<MgMultiGeometry> multiGeometry = CreateMultiGeometry();
        area = multiGeometry->GetArea();
        CPPUNIT_ASSERT_DOUBLES_EQUAL(area, 23.375, 0.0001);

        //TEST 13
        Ptr<MgCoordinate> coord1 = factory.CreateCoordinateXYZ(-45.0, -45.0, 1.0);
        Ptr<MgCoordinate> coord2 = factory.CreateCoordinateXYZ(-45.0,  45.0, 2.0);
        Ptr<MgCoordinate> coord3 = factory.CreateCoordinateXYZ( 45.0,  45.0, 3.0);
        Ptr<MgCoordinate> coord4 = factory.CreateCoordinateXYZ( 45.0, -45.0, 4.0);
        Ptr<MgCoordinate> coord5 = factory.CreateCoordinateXYZ(-45.0, -45.0, 1.0);

        Ptr<MgCoordinateCollection> coords = new MgCoordinateCollection();
        coords->Add(coord1);
        coords->Add(coord2);
        coords->Add(coord3);
        coords->Add(coord4);
        coords->Add(coord5);

        Ptr<MgLinearRing> linearRing = factory.CreateLinearRing(coords);

        polygon = factory.CreatePolygon(linearRing, NULL);
        area = polygon->GetArea();
        CPPUNIT_ASSERT(area == 8100.0);
    }
    catch (MgException* e)
    {
        STRING message = e->GetDetails(TEST_LOCALE);
        SAFE_RELEASE(e);
        CPPUNIT_FAIL(MG_WCHAR_TO_CHAR(message.c_str()));
    }
    catch (...)
    {
        throw;
    }
}


void TestGeometry::TestCase_GetCentroid()
{
    try
    {
        MgWktReaderWriter readerWriter;
        MgGeometryFactory factory;

        //TEST 1
        STRING base = L"POINT (5 3)";
        Ptr<MgPoint> point = CreatePoint();
        Ptr<MgPoint> centroid = point->GetCentroid();
        STRING found = readerWriter.Write(centroid);
        CPPUNIT_ASSERT(CheckGeometry(found, base));

        //TEST 2
        base = L"POINT (2 3)";
        Ptr<MgLineString> lineString = CreateLineString();
        centroid = lineString->GetCentroid();
        found = readerWriter.Write(centroid);
        CPPUNIT_ASSERT(CheckGeometry(found, base));

        //TEST 3
        base = L"POINT (2.5 2.5)";
        Ptr<MgPolygon> polygon = CreatePolygon();
        centroid = polygon->GetCentroid();
        found = readerWriter.Write(centroid);
        CPPUNIT_ASSERT(CheckGeometry(found, base));

        //TEST 4
        base = L"POINT (1.672 1.046)";
        Ptr<MgCurveString> curveString = CreateCurveString(0.0);
        centroid = curveString->GetCentroid();
        found = readerWriter.Write(centroid);
        CPPUNIT_ASSERT(CheckGeometry(found, base));

        //TEST 5
        base = L"POINT (0 0)";
        Ptr<MgCurveRing> curveRing = CreateCurveRing(0.0);
        centroid = curveRing->GetCentroid();

        //TEST 6
        base = L"POINT (0 0)";
        Ptr<MgCurvePolygon> curvePolygon = CreateCurvePolygon(0.0);
        centroid = curveRing->GetCentroid();

        //TEST 7
        base = L"POINT (4 5)";
        Ptr<MgMultiPoint> multiPoint = CreateMultiPoint();
        centroid = multiPoint->GetCentroid();
        found = readerWriter.Write(centroid);
        CPPUNIT_ASSERT(CheckGeometry(found, base));

        //TEST 8
        base = L"POINT (7.5 8.5)";
        Ptr<MgMultiLineString> multiLineString = CreateMultiLineString();
        centroid = multiLineString->GetCentroid();
        found = readerWriter.Write(centroid);
        CPPUNIT_ASSERT(CheckGeometry(found, base));

        //TEST 9
        base = L"POINT (2.5 2.5)";
        Ptr<MgMultiPolygon> multiPolygon = CreateMultiPolygon();
        centroid = multiPolygon->GetCentroid();
        found = readerWriter.Write(centroid);
        CPPUNIT_ASSERT(CheckGeometry(found, base));

        //TEST 10
        base = L"POINT (201.7 201.0)";
        Ptr<MgMultiCurveString> multiCurveString = CreateMultiCurveString();
        centroid = multiCurveString->GetCentroid();
        found = readerWriter.Write(centroid);
        CPPUNIT_ASSERT(CheckGeometry(found, base));

        //TEST 11
        base = L"POINT (0 0)";
        Ptr<MgMultiCurvePolygon> multiCurvePolygon = CreateMultiCurvePolygon(3, 0.0);
        centroid = curveRing->GetCentroid();

        //TEST 12
        base = L"POINT (-8.15 -8.15)";
        Ptr<MgMultiGeometry> multiGeometry = CreateMultiGeometry();
        centroid = multiGeometry->GetCentroid();
        found = readerWriter.Write(centroid);
        CPPUNIT_ASSERT(CheckGeometry(found, base));

        //TEST 13
        Ptr<MgCoordinate> coord1 = factory.CreateCoordinateXYZ(-45.0, -45.0, 1.0);
        Ptr<MgCoordinate> coord2 = factory.CreateCoordinateXYZ(-45.0,  45.0, 2.0);
        Ptr<MgCoordinate> coord3 = factory.CreateCoordinateXYZ( 45.0,  45.0, 3.0);
        Ptr<MgCoordinate> coord4 = factory.CreateCoordinateXYZ( 45.0, -45.0, 4.0);
        Ptr<MgCoordinate> coord5 = factory.CreateCoordinateXYZ(-45.0, -45.0, 1.0);

        Ptr<MgCoordinateCollection> coords = new MgCoordinateCollection();
        coords->Add(coord1);
        coords->Add(coord2);
        coords->Add(coord3);
        coords->Add(coord4);
        coords->Add(coord5);

        Ptr<MgLinearRing> linearRing = factory.CreateLinearRing(coords);

        base = L"POINT (0 0)";
        polygon = factory.CreatePolygon(linearRing, NULL);
        centroid = polygon->GetCentroid();
        found = readerWriter.Write(centroid);
        CPPUNIT_ASSERT(CheckGeometry(found, base));
    }
    catch (MgException* e)
    {
        STRING message = e->GetDetails(TEST_LOCALE);
        SAFE_RELEASE(e);
        CPPUNIT_FAIL(MG_WCHAR_TO_CHAR(message.c_str()));
    }
    catch (...)
    {
        throw;
    }
}


void TestGeometry::TestCase_GetInteriorPoint()
{
    try
    {
        MgGeometryFactory factory;

        Ptr<MgLinearRing> linearRing = CreateLinearRing();
        Ptr<MgPoint> point = linearRing->GetPointInRing();

        Ptr<MgPolygon> polygon = CreatePolygon();
        point = polygon->GetPointInRegion();

        Ptr<MgCurvePolygon> curvePolygon = CreateCurvePolygon(0.0);
        point = curvePolygon->GetPointInRegion();

        Ptr<MgCurveRing> curveRing = CreateCurveRing(0.0);
        point = curveRing->GetPointInRing();
    }
    catch (MgException* e)
    {
        STRING message = e->GetDetails(TEST_LOCALE);
        SAFE_RELEASE(e);
        CPPUNIT_FAIL(MG_WCHAR_TO_CHAR(message.c_str()));
    }
    catch (...)
    {
        throw;
    }
}

void TestGeometry::TestCase_CoordinateIterator()
{
    try
    {
        Ptr<MgGeometricEntity> point = CreatePoint();
        Ptr<MgCoordinateIterator> iterator = point->GetCoordinates();
        CPPUNIT_ASSERT(iterator->GetCount() == 1);

        Ptr<MgGeometricEntity> lineString = CreateLineString();
        iterator = lineString->GetCoordinates();
        CPPUNIT_ASSERT(iterator->GetCount() == 3);

        Ptr<MgGeometricEntity> polygon = CreatePolygon();
        iterator = polygon->GetCoordinates();
        CPPUNIT_ASSERT(iterator->GetCount() == 13);

        Ptr<MgGeometricEntity> curveString = CreateCurveString(0.0);
        iterator = curveString->GetCoordinates();
        CPPUNIT_ASSERT(iterator->GetCount() == 20);

        Ptr<MgGeometricEntity> curveRing = CreateCurveRing(0.0);
        iterator = curveRing->GetCoordinates();
        CPPUNIT_ASSERT(iterator->GetCount() == 19);

        Ptr<MgGeometricEntity> multiPoint = CreateMultiPoint();
        iterator = multiPoint->GetCoordinates();
        CPPUNIT_ASSERT(iterator->GetCount() == 3);

        Ptr<MgGeometricEntity> multiLineString = CreateMultiLineString();
        iterator = multiLineString->GetCoordinates();
        CPPUNIT_ASSERT(iterator->GetCount() == 6);

        Ptr<MgGeometricEntity> multiPolygon = CreateMultiPolygon();
        iterator = multiPolygon->GetCoordinates();
        CPPUNIT_ASSERT(iterator->GetCount() == 26);

        Ptr<MgGeometricEntity> multiCurveString = CreateMultiCurveString();
        iterator = multiCurveString->GetCoordinates();
        CPPUNIT_ASSERT(iterator->GetCount() == 60);

        Ptr<MgGeometricEntity> multiCurvePolygon = CreateMultiCurvePolygon(2, 0.0);
        iterator = multiCurvePolygon->GetCoordinates();
        CPPUNIT_ASSERT(iterator->GetCount() == 114);

        Ptr<MgGeometricEntity> multiGeometry = CreateMultiGeometry();
        iterator = multiGeometry->GetCoordinates();
        CPPUNIT_ASSERT(iterator->GetCount() == 94);
    }
    catch (...)
    {
        throw;
    }
}

void TestGeometry::TestCase_Simplify_BadParams()
{
    try
    {
        Ptr<MgGeometrySimplifier> simp = new MgGeometrySimplifier();
        Ptr<MgWktReaderWriter> wktRw = new MgWktReaderWriter();
        Ptr<MgGeometry> geom = wktRw->Read(L"POINT (1 1)");

        CPPUNIT_ASSERT_THROW_MG(simp->Simplify(NULL, 1.0, MgGeometrySimplificationAlgorithmType::DouglasPeucker), MgNullArgumentException*);
        CPPUNIT_ASSERT_THROW_MG(simp->Simplify(geom, 1.0, -1), MgInvalidArgumentException*);
        CPPUNIT_ASSERT_THROW_MG(simp->Simplify(geom, 1.0, 2), MgInvalidArgumentException*);
    }
    catch (MgException* e)
    {
        STRING message = e->GetDetails(TEST_LOCALE);
        SAFE_RELEASE(e);
        CPPUNIT_FAIL(MG_WCHAR_TO_CHAR(message.c_str()));
    }
    catch (...)
    {
        throw;
    }
}

void TestGeometry::TestCase_Simplify_DP()
{
    try
    {
        Ptr<MgGeometrySimplifier> simp = new MgGeometrySimplifier();
        INT32 algo = MgGeometrySimplificationAlgorithmType::DouglasPeucker;
        Ptr<MgWktReaderWriter> wktRw = new MgWktReaderWriter();

        //1 - PolygonNoReduction
        STRING wkt;
        wkt = L"POLYGON((20 220, 40 220, 60 220, 80 220, 100 220, \
                    120 220, 140 220, 140 180, 100 180, 60 180, 20 180, 20 220))";
        Ptr<MgGeometry> gTest = wktRw->Read(wkt);

        Ptr<MgGeometry> gInput = wktRw->Read(wkt);
        Ptr<MgGeometry> gOutput = simp->Simplify(gInput, 10.0, algo);
        CPPUNIT_ASSERT(NULL != gOutput.p);
        CPPUNIT_ASSERT(gOutput->IsValid());
        CPPUNIT_ASSERT(gTest->Equals(gOutput));

        // 2 - PolygonReductionWithSplit
        gTest = wktRw->Read(L"MULTIPOLYGON (((40.0 240.0, 160.0 240.0, 40.0 140.0, 40.0 240.0)), \
                    ((160.0 240.0, 280.0 240.0, 280.0 160.0, 160.0 240.0)))");
        gInput = wktRw->Read(L"POLYGON ((40 240, 160 241, 280 240, 280 160, \
                    160 240, 40 140, 40 240))");
        gOutput = simp->Simplify(gInput, 10.0, algo);
        CPPUNIT_ASSERT(NULL != gOutput.p);
        CPPUNIT_ASSERT(gOutput->IsValid());
        CPPUNIT_ASSERT(gTest->Equals(gOutput));
        
        // 3 - PolygonReduction
        gTest = wktRw->Read(L"POLYGON ((120 120, 140 199, 160 200, 180 199, 220 120, 120 120))");
        gInput = wktRw->Read(L"POLYGON ((120 120, 121 121, 122 122, 220 120, \
                    180 199, 160 200, 140 199, 120 120))");
        gOutput = simp->Simplify(gInput, 10.0, algo);
        CPPUNIT_ASSERT(NULL != gOutput.p);
        CPPUNIT_ASSERT(gOutput->IsValid());
        CPPUNIT_ASSERT(gTest->Equals(gOutput));

        // 4 - PolygonWithTouchingHole
        gTest = wktRw->Read(L"POLYGON ((80 200, 160 200, 240 200, 240 60, 80 60, 80 200), \
                    (160 200, 140 199, 120 120, 220 120, 180 199, 160 200)))");
        gInput = wktRw->Read(L"POLYGON ((80 200, 240 200, 240 60, 80 60, 80 200), \
                    (120 120, 220 120, 180 199, 160 200, 140 199, 120 120))");
        gOutput = simp->Simplify(gInput, 10.0, algo);
        CPPUNIT_ASSERT(NULL != gOutput.p);
        CPPUNIT_ASSERT(gOutput->IsValid());
        CPPUNIT_ASSERT(gTest->Equals(gOutput));

        // 5 - FlattishPolygon
        gInput = wktRw->Read(L"POLYGON ((0 0, 50 0, 53 0, 55 0, 100 0, 70 1, 60 1, 50 1, 40 1, 0 0))");
        gOutput = simp->Simplify(gInput, 10.0, algo);
        //Unlike GEOS, we don't support "POLYGON EMPTY", so we should be expecting NULL instead
        CPPUNIT_ASSERT(NULL == gOutput.p);

        // 6 - TinySquare
        gInput = wktRw->Read(L"POLYGON ((0 5, 5 5, 5 0, 0 0, 0 1, 0 5))");
        gOutput = simp->Simplify(gInput, 10.0, algo);
        //Unlike GEOS, we don't support "POLYGON EMPTY", so we should be expecting NULL instead
        CPPUNIT_ASSERT(NULL == gOutput.p);

        // 7 - TinyLineString
        gTest = wktRw->Read(L"LINESTRING (0 5, 5 5)");
        gInput = wktRw->Read(L"LINESTRING (0 5, 1 5, 2 5, 5 5)");
        gOutput = simp->Simplify(gInput, 10.0, algo);
        CPPUNIT_ASSERT(NULL != gOutput.p);
        CPPUNIT_ASSERT(gOutput->IsValid());
        CPPUNIT_ASSERT(gTest->Equals(gOutput));

        // 8 - MultiPoint
        gTest = wktRw->Read(L"MULTIPOINT(80 200, 240 200, 240 60, 80 60, 80 200, 140 199, 120 120)");
        gInput = wktRw->Read(L"MULTIPOINT(80 200, 240 200, 240 60, 80 60, 80 200, 140 199, 120 120)");
        gOutput = simp->Simplify(gInput, 10.0, algo);
        CPPUNIT_ASSERT(NULL != gOutput.p);
        CPPUNIT_ASSERT(gOutput->IsValid());
        CPPUNIT_ASSERT(gTest->Equals(gOutput));

        // 9 - MultiLineString
        gTest = wktRw->Read(L"MULTILINESTRING( (0 0, 100 0), (0 0, 100 0) )");
        gInput = wktRw->Read(L"MULTILINESTRING( (0 0, 50 0, 70 0, 80 0, 100 0), \
                    (0 0, 50 1, 60 1, 100 0) )");
        gOutput = simp->Simplify(gInput, 10.0, algo);
        CPPUNIT_ASSERT(NULL != gOutput.p);
        CPPUNIT_ASSERT(gOutput->IsValid());
        CPPUNIT_ASSERT(gTest->Equals(gOutput));

        // 10 - GeometryCollection
        gTest = wktRw->Read(L"MULTILINESTRING( (0 0, 100 0), (0 0, 100 0) )");
        gInput = wktRw->Read(L"GEOMETRYCOLLECTION ( \
                    MULTIPOINT (80 200, 240 200, 240 60, 80 60, 80 200, 140 199, 120 120), \
                    POLYGON ((80 200, 240 200, 240 60, 80 60, 80 200)), \
                    LINESTRING (80 200, 240 200, 240 60, 80 60, 80 200, 140 199, 120 120) )");
        gOutput = simp->Simplify(gInput, 10.0, algo);
        CPPUNIT_ASSERT(NULL != gOutput.p);
        CPPUNIT_ASSERT(gOutput->IsValid());
        //STRING sTest = gTest->ToAwkt(true);
        //STRING sOutput = gOutput->ToAwkt(true);
        //CPPUNIT_ASSERT(gTest->Equals(gOutput));
    }
    catch (MgException* e)
    {
        STRING message = e->GetDetails(TEST_LOCALE);
        SAFE_RELEASE(e);
        CPPUNIT_FAIL(MG_WCHAR_TO_CHAR(message.c_str()));
    }
    catch (...)
    {
        throw;
    }
}

void TestGeometry::TestCase_Simplify_TP()
{
    try
    {
        Ptr<MgGeometrySimplifier> simp = new MgGeometrySimplifier();
        INT32 algo = MgGeometrySimplificationAlgorithmType::TopologyPreserving;
        Ptr<MgWktReaderWriter> wktRw = new MgWktReaderWriter();

        //Point
        Ptr<MgGeometry> gTest = wktRw->Read(L"POINT (10 10)");
        Ptr<MgGeometry> gInput = wktRw->Read(L"POINT (10 10)");
        Ptr<MgGeometry> gOutput = simp->Simplify(gInput, 10.0, algo);
        CPPUNIT_ASSERT(NULL != gOutput.p);
        CPPUNIT_ASSERT(gOutput->IsValid());
        CPPUNIT_ASSERT(gTest->Equals(gOutput));

        // PolygonWithSpike
        gTest = wktRw->Read(L"POLYGON (( \
      3312459.605 6646878.353, \
      3312460.524 6646875.969, \
      3312459.427 6646878.421, \
      3312460.014 6646886.391, \
      3312465.889 6646887.398, \
      3312470.827 6646884.839, \
      3312477.289 6646871.694, \
      3312472.748 6646869.547, \
      3312459.605 6646878.353))");
        gInput = wktRw->Read(L"POLYGON ((3312459.605 6646878.353, \
      3312460.524 6646875.969, 3312459.427 6646878.421, \
      3312460.014 6646886.391, 3312465.889 6646887.398, \
      3312470.827 6646884.839, 3312475.4 6646878.027, \
      3312477.289 6646871.694, 3312472.748 6646869.547, \
      3312468.253 6646874.01, 3312463.52 6646875.779, \
      3312459.605 6646878.353))");
        gOutput = simp->Simplify(gInput, 2.0, algo);
        CPPUNIT_ASSERT(NULL != gOutput.p);
        CPPUNIT_ASSERT(gOutput->IsValid());

        // PolygonNoReduction
        gTest = wktRw->Read(L"POLYGON((20 220, 40 220, 60 220, 80 220, \
                    100 220, 120 220, 140 220, 140 180, 100 180, \
                    60 180, 20 180, 20 220))");
        gInput = wktRw->Read(L"POLYGON((20 220, 40 220, 60 220, 80 220, \
                    100 220, 120 220, 140 220, 140 180, 100 180, \
                    60 180, 20 180, 20 220))");
        gOutput = simp->Simplify(gInput, 10.0, algo);
        CPPUNIT_ASSERT(NULL != gOutput.p);
        CPPUNIT_ASSERT(gOutput->IsValid());
        CPPUNIT_ASSERT(gTest->Equals(gOutput));

        // PolygonNoReductionWithConflicts
        gTest = wktRw->Read(L"POLYGON ((40 240, 160 241, 280 240, 280 160, \
                        160 240, 40 140, 40 240))");
        gInput = wktRw->Read(L"POLYGON ((40 240, 160 241, 280 240, 280 160, \
                        160 240, 40 140, 40 240))");
        gOutput = simp->Simplify(gInput, 10.0, algo);
        CPPUNIT_ASSERT(NULL != gOutput.p);
        CPPUNIT_ASSERT(gOutput->IsValid());
        CPPUNIT_ASSERT(gTest->Equals(gOutput));

        // PolygonWithTouchingHole
        gTest = wktRw->Read(L"POLYGON ((80 200, 240 200, 240 60, 80 60, 80 200), \
                    (120 120, 220 120, 180 199, 160 200, 140 199, 120 120))");
        gInput = wktRw->Read(L"POLYGON ((80 200, 240 200, 240 60, 80 60, 80 200), \
                    (120 120, 220 120, 180 199, 160 200, 140 199, 120 120))");
        gOutput = simp->Simplify(gInput, 10.0, algo);
        CPPUNIT_ASSERT(NULL != gOutput.p);
        CPPUNIT_ASSERT(gOutput->IsValid());
        CPPUNIT_ASSERT(gTest->Equals(gOutput));

        // FlattishPolygon
        gTest = wktRw->Read(L"POLYGON ((0 0, 50 0, 53 0, 55 0, 100 0, \
                    70 1, 60 1, 50 1, 40 1, 0 0))");
        gInput = wktRw->Read(L"POLYGON ((0 0, 50 0, 53 0, 55 0, 100 0, \
                    70 1, 60 1, 50 1, 40 1, 0 0))");
        gOutput = simp->Simplify(gInput, 10.0, algo);
        CPPUNIT_ASSERT(NULL != gOutput.p);
        CPPUNIT_ASSERT(gOutput->IsValid());
        //STRING sTest = gTest->ToAwkt(true);
        //STRING sOutput = gOutput->ToAwkt(true);
        //CPPUNIT_ASSERT(gTest->Equals(gOutput));

        // PolygonWithFlattishHole
        gTest = wktRw->Read(L"POLYGON ((0 0, 0 200, 200 200, 200 0, 0 0), \
                    (140 40, 90 95, 40 160, 95 100, 140 40))");
        gInput = wktRw->Read(L"POLYGON ((0 0, 0 200, 200 200, 200 0, 0 0), \
                    (140 40, 90 95, 40 160, 95 100, 140 40))");
        gOutput = simp->Simplify(gInput, 10.0, algo);
        CPPUNIT_ASSERT(NULL != gOutput.p);
        CPPUNIT_ASSERT(gOutput->IsValid()); 
        CPPUNIT_ASSERT(gTest->Equals(gOutput));

        // Tiny square
        gTest = wktRw->Read(L"POLYGON ((0 5, 5 5, 5 0, 0 0, 0 1, 0 5))");
        gInput = wktRw->Read(L"POLYGON ((0 5, 5 5, 5 0, 0 0, 0 1, 0 5))");
        gOutput = simp->Simplify(gInput, 10.0, algo);
        CPPUNIT_ASSERT(NULL != gOutput.p);
        CPPUNIT_ASSERT(gOutput->IsValid());
        CPPUNIT_ASSERT(gTest->Equals(gOutput));
        
        // TinyClosedLineString
        gTest = wktRw->Read(L"LINESTRING (0 0, 5 0, 5 5, 0 0)");
        gInput = wktRw->Read(L"LINESTRING (0 0, 5 0, 5 5, 0 0)");
        gOutput = simp->Simplify(gInput, 10.0, algo);
        CPPUNIT_ASSERT(NULL != gOutput.p);
        CPPUNIT_ASSERT(gOutput->IsValid());
        CPPUNIT_ASSERT(gTest->Equals(gOutput));

        // MultiPoint
        gTest = wktRw->Read(L"MULTIPOINT(80 200, 240 200, 240 60, \
                    80 60, 80 200, 140 199, 120 120)");
        gInput = wktRw->Read(L"MULTIPOINT(80 200, 240 200, 240 60, \
                    80 60, 80 200, 140 199, 120 120)");
        gOutput = simp->Simplify(gInput, 10.0, algo);
        CPPUNIT_ASSERT(NULL != gOutput.p);
        CPPUNIT_ASSERT(gOutput->IsValid());
        CPPUNIT_ASSERT(gTest->Equals(gOutput));

        // MultiLineString
        gTest = wktRw->Read(L"MULTILINESTRING((0 0, 50 0, 70 0, 80 0, 100 0), \
                    (0 0, 50 1, 60 1, 100 0))");
        gInput = wktRw->Read(L"MULTILINESTRING((0 0, 50 0, 70 0, 80 0, 100 0), \
                    (0 0, 50 1, 60 1, 100 0))");
        gOutput = simp->Simplify(gInput, 10.0, algo);
        CPPUNIT_ASSERT(NULL != gOutput.p);
        CPPUNIT_ASSERT(gOutput->IsValid());
        //STRING sTest = gTest->ToAwkt(true);
        //STRING sOutput = gOutput->ToAwkt(true);
        //CPPUNIT_ASSERT(gTest->Equals(gOutput));

        // GeometryCollection
        gTest = wktRw->Read(L"GEOMETRYCOLLECTION ( \
                    MULTIPOINT (80 200, 240 200, 240 60, 80 60, 80 200, 140 199, 120 120), \
                    POLYGON ((80 200, 240 200, 240 60, 80 60, 80 200)), \
                    LINESTRING (80 200, 240 200, 240 60, 80 60, 80 200, 140 199, 120 120))");
        gInput = wktRw->Read(L"GEOMETRYCOLLECTION ( \
                    MULTIPOINT (80 200, 240 200, 240 60, 80 60, 80 200, 140 199, 120 120), \
                    POLYGON ((80 200, 240 200, 240 60, 80 60, 80 200)), \
                    LINESTRING (80 200, 240 200, 240 60, 80 60, 80 200, 140 199, 120 120))");
        gOutput = simp->Simplify(gInput, 10.0, algo);
        CPPUNIT_ASSERT(NULL != gOutput.p);
        CPPUNIT_ASSERT(gOutput->IsValid());
        CPPUNIT_ASSERT(gTest->Equals(gOutput));
    }
    catch (MgException* e)
    {
        STRING message = e->GetDetails(TEST_LOCALE);
        SAFE_RELEASE(e);
        CPPUNIT_FAIL(MG_WCHAR_TO_CHAR(message.c_str()));
    }
    catch (...)
    {
        throw;
    }
}

void TestGeometry::TestCase_PreparedGeometryPerformance()
{
    try
    {
        MgServiceManager* serviceManager = MgServiceManager::GetInstance();
        if (serviceManager == 0)
        {
            throw new MgNullReferenceException(L"TestGeometry::TestCase_PreparedGeometry", __LINE__, __WFILE__, NULL, L"", NULL);
        }

        Ptr<MgFeatureService> pService = dynamic_cast<MgFeatureService*>(serviceManager->RequestService(MgServiceType::FeatureService));
        if (pService == 0)
        {
            throw new MgServiceNotAvailableException(L"TestGeometry::TestCase_PreparedGeometry", __LINE__, __WFILE__, NULL, L"", NULL);
        }

        Ptr<MgAgfReaderWriter> agfRw = new MgAgfReaderWriter();
        Ptr<MgWktReaderWriter> wktRw = new MgWktReaderWriter();

        STRING wkt = L"POLYGON ((-87.70660400390625 43.761672246385025, -87.7045440673828 43.76576337413024, -87.7093505859375 43.77196151943297, -87.71999359130858 43.7755561494101, -87.73458480834961 43.770350063442635, -87.73355484008789 43.76315996157264, -87.73853302001953 43.758820688867885, -87.73595809936523 43.74642103270366, -87.72789001464842 43.735135112939105, -87.71844863891602 43.73191017368391, -87.71175384521484 43.73575527365514, -87.70797729492188 43.739228054975506, -87.7090072631836 43.74158447044938, -87.71278381347655 43.739848173302434, -87.71724700927734 43.737615717267765, -87.72720336914062 43.7374916894919, -87.72926330566406 43.74567697163676, -87.7313232421875 43.75125720420175, -87.73149490356445 43.75931662167704, -87.72222518920898 43.76092837491792, -87.72136688232422 43.76787081559809, -87.71467208862305 43.76712702120528, -87.71175384521484 43.76092837491792, -87.70660400390625 43.761672246385025))";
        Ptr<MgGeometry> testGeom = wktRw->Read(wkt);

        Ptr<MgResourceIdentifier> resource = new MgResourceIdentifier();
        STRING className = L"";
        Ptr<MgFeatureQueryOptions> options = new MgFeatureQueryOptions();
        CPPUNIT_ASSERT_THROW_MG(pService->SelectFeatures(resource, className, options), MgInvalidArgumentException*);

        resource = new MgResourceIdentifier(L"Library://UnitTests/Data/Sheboygan_Parcels.FeatureSource");
        className = L"Parcels";
        Ptr<MgFeatureReader> reader = pService->SelectFeatures(resource, className, options);
        Ptr<MgClassDefinition> clsDef = reader->GetClassDefinition();
        STRING geomName = clsDef->GetDefaultGeometryPropertyName();

        INT32 containsCount1 = 0;
        INT32 crossesCount1 = 0;
        INT32 disjointCount1 = 0;
        INT32 intersectsCount1 = 0;
        INT32 overlapsCount1 = 0;
        INT32 touchesCount1 = 0;
        INT32 withinCount1 = 0;

        long lStart = GetTickCount();
        while (reader->ReadNext())
        {
            try 
            {
                Ptr<MgByteReader> agf = ((MgReader*)reader)->GetGeometry(geomName);
                Ptr<MgGeometry> geom = agfRw->Read(agf);

                if (testGeom->Contains(geom))
                    containsCount1++;
                if (testGeom->Crosses(geom))
                    crossesCount1++;
                if (testGeom->Disjoint(geom))
                    disjointCount1++;
                if (testGeom->Intersects(geom))
                    intersectsCount1++;
                if (testGeom->Overlaps(geom))
                    overlapsCount1++;
                if (testGeom->Touches(geom))
                    touchesCount1++;
                if (testGeom->Within(geom))
                    withinCount1++;
            }
            catch (MgException* ex)
            {
                SAFE_RELEASE(ex);
            }
        }
        reader->Close();
        ACE_DEBUG((LM_INFO, ACE_TEXT("\n\n  Execution Time: = %6.4f (s)\n"), ((GetTickCount() - lStart) / 1000.0)));
        ACE_DEBUG((LM_INFO, ACE_TEXT("  Contains: %d, Crosses: %d, Disjoint: %d, Intersects: %d, Overlaps: %d, Touches: %d, Within: %d\n"), containsCount1, crossesCount1, disjointCount1, intersectsCount1, overlapsCount1, touchesCount1, withinCount1));

        //Now, with prepared geometry
        Ptr<MgPreparedGeometry> prep = testGeom->Prepare();

        reader = pService->SelectFeatures(resource, className, options);
        INT32 containsCount2 = 0;
        INT32 crossesCount2 = 0;
        INT32 disjointCount2 = 0;
        INT32 intersectsCount2 = 0;
        INT32 overlapsCount2 = 0;
        INT32 touchesCount2 = 0;
        INT32 withinCount2 = 0;

        lStart = GetTickCount();
        while (reader->ReadNext())
        {
            try
            {
                Ptr<MgByteReader> agf = ((MgReader*)reader)->GetGeometry(geomName);
                Ptr<MgGeometry> geom = agfRw->Read(agf);

                if (prep->Contains(geom))
                    containsCount2++;
                if (prep->Crosses(geom))
                    crossesCount2++;
                if (prep->Disjoint(geom))
                    disjointCount2++;
                if (prep->Intersects(geom))
                    intersectsCount2++;
                if (prep->Overlaps(geom))
                    overlapsCount2++;
                if (prep->Touches(geom))
                    touchesCount2++;
                if (prep->Within(geom))
                    withinCount2++;
            }
            catch (MgException* ex)
            {
                SAFE_RELEASE(ex);
            }
        }
        reader->Close();
        ACE_DEBUG((LM_INFO, ACE_TEXT("\n  Execution Time: = %6.4f (s)\n"), ((GetTickCount() - lStart) / 1000.0)));
        ACE_DEBUG((LM_INFO, ACE_TEXT("  Contains: %d, Crosses: %d, Disjoint: %d, Intersects: %d, Overlaps: %d, Touches: %d, Within: %d\n"), containsCount2, crossesCount2, disjointCount2, intersectsCount2, overlapsCount2, touchesCount2, withinCount2));

        CPPUNIT_ASSERT(containsCount1 == containsCount2);
        CPPUNIT_ASSERT(crossesCount2 == crossesCount2);
        CPPUNIT_ASSERT(disjointCount2 == disjointCount2);
        CPPUNIT_ASSERT(intersectsCount2 == intersectsCount2);
        CPPUNIT_ASSERT(overlapsCount2 == overlapsCount2);
        CPPUNIT_ASSERT(touchesCount2 == touchesCount2);
        CPPUNIT_ASSERT(withinCount2 == withinCount2);
    }
    catch (MgException* e)
    {
        STRING message = e->GetDetails(TEST_LOCALE);
        SAFE_RELEASE(e);
        CPPUNIT_FAIL(MG_WCHAR_TO_CHAR(message.c_str()));
    }
    catch (...)
    {
        throw;
    }
}

void TestGeometry::TestCase_CurvePolygon_AsGeoJSON()
{
    try
    {
        Ptr<MgWktReaderWriter> wktRw = new MgWktReaderWriter();
        Ptr<MgGeometry> geom = wktRw->Read(L"CURVEPOLYGON ((0 0 (LINESTRINGSEGMENT (10 10, 10 20, 20 20), ARC (20 15, 10 10))), (0 0 (ARC (11 11, 12 12), LINESTRINGSEGMENT (10 10, 20 20, 40 40, 90 90))))");

        Ptr<MgGeoJsonWriter> gw = new MgGeoJsonWriter();
        STRING geoJson = gw->GeometryToGeoJson(geom);

        CPPUNIT_ASSERT(geoJson.find(L"geometry\": null") == STRING::npos);
    }
    catch (MgException* e)
    {
        STRING message = e->GetDetails(TEST_LOCALE);
        SAFE_RELEASE(e);
        CPPUNIT_FAIL(MG_WCHAR_TO_CHAR(message.c_str()));
    }
    catch (...)
    {
        throw;
    }
}

void TestGeometry::TestCase_CurveString_AsGeoJSON()
{
    try
    {
        Ptr<MgWktReaderWriter> wktRw = new MgWktReaderWriter();
        Ptr<MgGeometry> geom = wktRw->Read(L"CURVESTRING (0 0 (CIRCULARARCSEGMENT (11 11, 12 12), LINESTRINGSEGMENT (10 10, 20 20, 30 40)))");

        Ptr<MgGeoJsonWriter> gw = new MgGeoJsonWriter();
        STRING geoJson = gw->GeometryToGeoJson(geom);

        CPPUNIT_ASSERT(geoJson.find(L"geometry\": null") == STRING::npos);
    }
    catch (MgException* e)
    {
        STRING message = e->GetDetails(TEST_LOCALE);
        SAFE_RELEASE(e);
        CPPUNIT_FAIL(MG_WCHAR_TO_CHAR(message.c_str()));
    }
    catch (...)
    {
        throw;
    }
}

void TestGeometry::TestCase_MultiCurvePolygon_AsGeoJSON()
{
    try
    {
        Ptr<MgWktReaderWriter> wktRw = new MgWktReaderWriter();
        Ptr<MgGeometry> geom = wktRw->Read(L"MULTICURVEPOLYGON (((0 0 (LINESTRINGSEGMENT (10 10, 10 20, 20 20), ARC (20 15, 10 10))), (0 0 (ARC (11 11, 12 12), LINESTRINGSEGMENT (10 10, 20 20, 40 40, 90 90)))),((0 0 (LINESTRINGSEGMENT (10 10, 10 20, 20 20), ARC (20 15, 10 10))), (0 0 (ARC (11 11, 12 12), LINESTRINGSEGMENT (10 10, 20 20, 40 40, 90 90)))))");

        Ptr<MgGeoJsonWriter> gw = new MgGeoJsonWriter();
        STRING geoJson = gw->GeometryToGeoJson(geom);

        CPPUNIT_ASSERT(geoJson.find(L"geometry\": null") == STRING::npos);
    }
    catch (MgException* e)
    {
        STRING message = e->GetDetails(TEST_LOCALE);
        SAFE_RELEASE(e);
        CPPUNIT_FAIL(MG_WCHAR_TO_CHAR(message.c_str()));
    }
    catch (...)
    {
        throw;
    }
}

void TestGeometry::TestCase_MultiCurveString_AsGeoJSON()
{
    try
    {
        Ptr<MgWktReaderWriter> wktRw = new MgWktReaderWriter();
        Ptr<MgGeometry> geom = wktRw->Read(L"MULTICURVESTRING ((0 0 (LINESTRINGSEGMENT (10 10, 20 20, 30 40))),(0 0 (ARC (11 11, 12 12), LINESTRINGSEGMENT (10 10, 20 20, 30 40))))");

        Ptr<MgGeoJsonWriter> gw = new MgGeoJsonWriter();
        STRING geoJson = gw->GeometryToGeoJson(geom);

        CPPUNIT_ASSERT(geoJson.find(L"geometry\": null") == STRING::npos);
    }
    catch (MgException* e)
    {
        STRING message = e->GetDetails(TEST_LOCALE);
        SAFE_RELEASE(e);
        CPPUNIT_FAIL(MG_WCHAR_TO_CHAR(message.c_str()));
    }
    catch (...)
    {
        throw;
    }
}