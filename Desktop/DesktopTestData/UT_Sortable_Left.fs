<?xml version="1.0" encoding="utf-8"?>
<FeatureSource xmlns:xsi="http://www.w3.org/2001/XMLSchema-instance" xmlns:xsd="http://www.w3.org/2001/XMLSchema" xsi:noNamespaceSchemaLocation="FeatureSource-1.0.0.xsd">
  <Provider>OSGeo.SQLite</Provider>
  <Parameter>
    <Name>File</Name>
    <Value>%MG_DATA_FILE_PATH%SortableLeft.sqlite</Value>
  </Parameter>
  <Extension>
    <AttributeRelate>
      <RelateProperty>
        <FeatureClassProperty>ID</FeatureClassProperty>
        <AttributeClassProperty>ID</AttributeClassProperty>
      </RelateProperty>
      <AttributeClass>Default:Parcels</AttributeClass>
      <ResourceId>Library://UnitTests/Data/SortableRight.FeatureSource</ResourceId>
      <Name>DATA</Name>
      <RelateType>LeftOuter</RelateType>
      <ForceOneToOne>true</ForceOneToOne>
    </AttributeRelate>
    <Name>ParcelsLeftOuterOneToOneSortMerge</Name>
    <FeatureClass>Default:ParcelFeatures</FeatureClass>
  </Extension>
  <Extension>
    <AttributeRelate>
      <RelateProperty>
        <FeatureClassProperty>ID</FeatureClassProperty>
        <AttributeClassProperty>ID</AttributeClassProperty>
      </RelateProperty>
      <AttributeClass>Default:Parcels</AttributeClass>
      <ResourceId>Library://UnitTests/Data/SortableRight.FeatureSource</ResourceId>
      <Name>DATA</Name>
      <RelateType>Inner</RelateType>
      <ForceOneToOne>true</ForceOneToOne>
    </AttributeRelate>
    <Name>ParcelsInnerOneToOneSortMerge</Name>
    <FeatureClass>Default:ParcelFeatures</FeatureClass>
  </Extension>
  <Extension>
    <AttributeRelate>
      <RelateProperty>
        <FeatureClassProperty>ID</FeatureClassProperty>
        <AttributeClassProperty>ID</AttributeClassProperty>
      </RelateProperty>
      <AttributeClass>Default:Parcels</AttributeClass>
      <ResourceId>Library://UnitTests/Data/SortableRight.FeatureSource</ResourceId>
      <Name>DATA</Name>
      <RelateType>LeftOuter</RelateType>
      <ForceOneToOne>false</ForceOneToOne>
    </AttributeRelate>
    <Name>ParcelsLeftOuterSortMerge</Name>
    <FeatureClass>Default:ParcelFeatures</FeatureClass>
  </Extension>
  <Extension>
    <AttributeRelate>
      <RelateProperty>
        <FeatureClassProperty>ID</FeatureClassProperty>
        <AttributeClassProperty>ID</AttributeClassProperty>
      </RelateProperty>
      <AttributeClass>Default:Parcels</AttributeClass>
      <ResourceId>Library://UnitTests/Data/SortableRight.FeatureSource</ResourceId>
      <Name>DATA</Name>
      <RelateType>Inner</RelateType>
      <ForceOneToOne>false</ForceOneToOne>
    </AttributeRelate>
    <Name>ParcelsInnerSortMerge</Name>
    <FeatureClass>Default:ParcelFeatures</FeatureClass>
  </Extension>
  
  <Extension>
    <AttributeRelate>
      <RelateProperty>
        <FeatureClassProperty>ID</FeatureClassProperty>
        <AttributeClassProperty>ID</AttributeClassProperty>
      </RelateProperty>
      <AttributeClass>Default:Parcels</AttributeClass>
      <ResourceId>Library://UnitTests/Data/UnsortableRight.FeatureSource</ResourceId>
      <Name>DATA</Name>
      <RelateType>LeftOuter</RelateType>
      <ForceOneToOne>true</ForceOneToOne>
    </AttributeRelate>
    <Name>ParcelsLeftOuterOneToOneNestedLoopSortedBlock</Name>
    <FeatureClass>Default:ParcelFeatures</FeatureClass>
  </Extension>
  <Extension>
    <AttributeRelate>
      <RelateProperty>
        <FeatureClassProperty>ID</FeatureClassProperty>
        <AttributeClassProperty>ID</AttributeClassProperty>
      </RelateProperty>
      <AttributeClass>Default:Parcels</AttributeClass>
      <ResourceId>Library://UnitTests/Data/UnsortableRight.FeatureSource</ResourceId>
      <Name>DATA</Name>
      <RelateType>Inner</RelateType>
      <ForceOneToOne>true</ForceOneToOne>
    </AttributeRelate>
    <Name>ParcelsInnerOneToOneNestedLoopSortedBlock</Name>
    <FeatureClass>Default:ParcelFeatures</FeatureClass>
  </Extension>
  <Extension>
    <AttributeRelate>
      <RelateProperty>
        <FeatureClassProperty>ID</FeatureClassProperty>
        <AttributeClassProperty>ID</AttributeClassProperty>
      </RelateProperty>
      <AttributeClass>Default:Parcels</AttributeClass>
      <ResourceId>Library://UnitTests/Data/UnsortableRight.FeatureSource</ResourceId>
      <Name>DATA</Name>
      <RelateType>LeftOuter</RelateType>
      <ForceOneToOne>false</ForceOneToOne>
    </AttributeRelate>
    <Name>ParcelsLeftOuterNestedLoopSortedBlock</Name>
    <FeatureClass>Default:ParcelFeatures</FeatureClass>
  </Extension>
  <Extension>
    <AttributeRelate>
      <RelateProperty>
        <FeatureClassProperty>ID</FeatureClassProperty>
        <AttributeClassProperty>ID</AttributeClassProperty>
      </RelateProperty>
      <AttributeClass>Default:Parcels</AttributeClass>
      <ResourceId>Library://UnitTests/Data/UnsortableRight.FeatureSource</ResourceId>
      <Name>DATA</Name>
      <RelateType>Inner</RelateType>
      <ForceOneToOne>false</ForceOneToOne>
    </AttributeRelate>
    <Name>ParcelsInnerNestedLoopSortedBlock</Name>
    <FeatureClass>Default:ParcelFeatures</FeatureClass>
  </Extension>
  
</FeatureSource>