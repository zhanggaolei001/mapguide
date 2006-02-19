#ifndef _OLEDBGIS_H__
#define _OLEDBGIS_H__

/*
> File: OLEDBGIS.h
> 
> Description:
> This file contains the GUIDs and constants that are required by the
> OpenGIS
> Features for OLE-COM Implementation Specification.
*/

// {A0690A28-FAF5-11d1-BAF5-080036DB0B03}
DEFINE_GUID(CATID_OGISDataProvider, 
0xa0690a28, 0xfaf5, 0x11d1, 0xba, 0xf5, 0x8, 0x0, 0x36, 0xdb, 0xb, 0x3);

// {A0690A29-FAF5-11d1-BAF5-080036DB0B03}
DEFINE_GUID(DBSCHEMA_OGIS_FEATURE_TABLES, 
0xa0690a29, 0xfaf5, 0x11d1, 0xba, 0xf5, 0x8, 0x0, 0x36, 0xdb, 0xb, 0x3);

// {A0690A2A-FAF5-11d1-BAF5-080036DB0B03}
DEFINE_GUID(DBSCHEMA_OGIS_GEOMETRY_COLUMNS, 
0xa0690a2a, 0xfaf5, 0x11d1, 0xba, 0xf5, 0x8, 0x0, 0x36, 0xdb, 0xb, 0x3);

// {A0690A2B-FAF5-11d1-BAF5-080036DB0B03}
DEFINE_GUID(DBSCHEMA_OGIS_SPATIAL_REF_SYSTEMS, 
0xa0690a2b, 0xfaf5, 0x11d1, 0xba, 0xf5, 0x8, 0x0, 0x36, 0xdb, 0xb, 0x3);

// {A0690A2C-FAF5-11d1-BAF5-080036DB0B03}
DEFINE_GUID(DBPROPSET_OGIS_SPATIAL_OPS, 
0xa0690a2c, 0xfaf5, 0x11d1, 0xba, 0xf5, 0x8, 0x0, 0x36, 0xdb, 0xb, 0x3);

enum DBPROPOGISENUM
{DBPROP_OGIS_TOUCHES = 0x1L,
DBPROP_OGIS_WITHIN=0x2L,
DBPROP_OGIS_CONTAINS=0x3L,
DBPROP_OGIS_CROSSES=0x4L,
DBPROP_OGIS_OVERLAPS=0x5L,
DBPROP_OGIS_DISJOINT=0x6L,
DBPROP_OGIS_INTERSECT=0x7L,
DBPROP_OGIS_ENVELOPE_INTERSECTS=0x8L,
DBPROP_OGIS_INDEX_INTERSECTS=0x9L
};

/* I think ESRI have numbers for those and for the geometry objects */
enum DBPROPOGISGEOMENUM {
DBGEOM_GEOMETRY = 0x1L,
DBGEOM_POINT = 0x2L, 
DBGEOM_CURVE = 0x3L,
DBGEOM_LINESTRING = 0x4L, 
DBGEOM_SURFACE = 0x5L, 
DBGEOM_POLYGON = 0x6L, 
DBGEOM_COLLECTION = 0x7L, 
DBGEOM_MULTISURFACE = 0xB, 
DBGEOM_MULTIPOLYGON = 0xC, 
DBGEOM_MULTICURVE = 0x9L, 
DBGEOM_MULTILINESTRING = 0xA, 
DBGEOM_MULTIPOINT = 0x8L };


#endif

