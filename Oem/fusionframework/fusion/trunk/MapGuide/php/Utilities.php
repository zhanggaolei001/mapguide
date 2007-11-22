<?php
/**
 * Utilities.php
 *
 * $Id: Utilities.php 963 2007-10-16 15:37:30Z madair $
 *
 * Copyright (c) 2007, DM Solutions Group Inc.
 * Permission is hereby granted, free of charge, to any person obtaining a
 * copy of this software and associated documentation files (the "Software"),
 * to deal in the Software without restriction, including without limitation
 * the rights to use, copy, modify, merge, publish, distribute, sublicense,
 * and/or sell copies of the Software, and to permit persons to whom the
 * Software is furnished to do so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included
 * in all copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT.  IN NO EVENT SHALL
 * THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING
 * FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER
 * DEALINGS IN THE SOFTWARE.
 */

/*****************************************************************************
 * Purpose: Utility Functions for the MapGuide API
 *****************************************************************************/

 //------------------------------------------------------------------------------
function CreateFeatureSource($map, $dataSourceId, $featureName, $featureService, $geomType, $schema="") {
    //create feature source
    $classDef = new MgClassDefinition();

    $classDef->SetName($featureName);
    $classDef->SetDescription($featureName . " feature layer");
    $classDef->SetDefaultGeometryPropertyName("GEOM");

    //Set KEY property
    $prop = new MgDataPropertyDefinition("KEY");
    $prop->SetDataType(MgPropertyType::Int32);
    $prop->SetAutoGeneration(true);
    $prop->SetReadOnly(true);
    $classDef->GetIdentityProperties()->Add($prop);
    $classDef->GetProperties()->Add($prop);

    $prop = new MgGeometricPropertyDefinition("GEOM");
    $prop->SetGeometryTypes($geomType);
    $classDef->GetProperties()->Add($prop);

    //Create the schema
    if ($schema == "")
      $schema = "DrawToolSchema";
    $schema = new MgFeatureSchema($schema, "Temporary draw layer schema");
    $schema->GetClasses()->Add($classDef);

    //finally, creation of the feature source
    $params = new MgCreateSdfParams("LatLong", GetMapSRS($map), $schema);
    $featureService->CreateFeatureSource($dataSourceId, $params);
}

function ClearFeatureSource($featureService, $dataSourceId, $featureName) {
    $deleteCmd = new MgDeleteFeatures($featureName, "KEY > 0");
    $commands = new MgFeatureCommandCollection();
    $commands->Add($deleteCmd);
    $featureService->UpdateFeatures($dataSourceId, $commands, false);
}

//------------------------------------------------------------------------------
//duplicate a layer in the session so that it can refer to a different session
//feature source.
//the session id and the feature source are assumed to have the same path as their
//repository counterparts but $suffix is appended to the names.
function DuplicateSessionLayer($map, $resourceService, $sourceLayerId, $suffix) {
    //create the new session MgResourceIdentifier
    $destinationLayerId = CreateSessionResourceId($sourceLayerId, $suffix);

    //copy content from source layer
    $contentReader = $resourceService->GetResourceContent($sourceLayerId);
    $layerContent = $contentReader->ToString();

    //set the feature source this layer references -- must be in the session
    //the feature source need not exist before calling this function
    $sourceLayer = new MgLayer($sourceLayerId, $resourceService);
    $sourceFeatureSourceId = new MgResourceIdentifier($sourceLayer->GetFeatureSourceId());
    $destinationFeatureSourceId = CreateSessionResourceId($sourceFeatureSourceId, $suffix);


    //replace the featuresourceid and write xml to the session copy
    $layerContent = str_replace($sourceFeatureSourceId->ToString(),
                                $destinationFeatureSourceId->ToString(),
                                $layerContent);
    $byteSource = new MgByteSource($layerContent, strlen($layerContent));
    $resourceService->SetResource($destinationLayerId, $byteSource->GetReader(), null);

    //instantiate the new layer from its MgResourceIdentifier
    $layer = new MgLayer($destinationLayerId, $resourceService);

	//add the edit layer to the session map and set it to redraw but not be visible in the legend
	$layerCollection=$map->GetLayers();
	$originalLayer = FindLayer($layerCollection,$sourceLayer->GetLayerDefinition()->ToString());
    $nPosition = $layerCollection->IndexOf($originalLayer);
    $layerCollection->Insert($nPosition,$layer);
	$layer->SetDisplayInLegend(false);
	$layer->SetSelectable(true);
    $layer->ForceRefresh();

	//OR
	//remove the source layer from the session map and replace it with the
    //session copy
    //ReplaceLayer($map, $sourceLayer, $layer);

    //save the session map
    try{
	    $map->Save($resourceService);
    }
     catch (MgException $e)
    {
        echo "ERROR: " . $e->GetMessage() . "n";
        echo $e->GetDetails() . "n";
        echo $e->GetStackTrace() . "n";
    }


    return $layer;
}

//------------------------------------------------------------------------------
//duplicate a layer in the session so that it can refer to a session feature source
//the session id and the feature source are assumed to have the same path as their
//repository counterparts
function CopyLayerToSession($map, $resourceService, $libraryLayerId) {
    //create the session MgResourceIdentifier
    try{
    $destinationLayerId = ToggleRepository($libraryLayerId);
    $destinationLayerId->SetName($destinationLayerId->GetName().'-edit');

    //copy content from library layer
    $contentReader = $resourceService->GetResourceContent($libraryLayerId);
    $layerContent = $contentReader->ToString();

    //set the feature source this layer references -- must be in the session
    //the feature source need not exist before calling this function
    $libraryLayer = new MgLayer($libraryLayerId, $resourceService);
    $libraryFeatureSourceId = new MgResourceIdentifier($libraryLayer->GetFeatureSourceId());
    $destinationFeatureSourceId = ToggleRepository($libraryFeatureSourceId);


    //replace the featuresourceid and write xml to the session copy
    $layerContent = str_replace($libraryFeatureSourceId->ToString(),
                                $destinationFeatureSourceId->ToString(),
                                $layerContent);
    $byteSource = new MgByteSource($layerContent, strlen($layerContent));
    $resourceService->SetResource($destinationLayerId, $byteSource->GetReader(), null);

    //instantiate the new layer from its MgResourceIdentifier
    $layer = new MgLayer($destinationLayerId, $resourceService);

	//add the edit layer to the session map and set it to redraw but not be visible in the legend
	$layerCollection=$map->GetLayers();
	$originalLayer = FindLayer($layerCollection,$libraryLayer->GetLayerDefinition()->ToString());
    $nPosition = $layerCollection->IndexOf($originalLayer);
    $layerCollection->Insert($nPosition,$layer);
	$layer->SetDisplayInLegend(false);
	$layer->SetSelectable(true);
    $layer->ForceRefresh();

	//OR
	//remove the library layer from the session map and replace it with the
    //session copy
    //ReplaceLayer($map, $libraryLayer, $layer);

    //save the session map
	    $map->Save($resourceService);
    }
     catch (MgException $e)
    {
        echo "CopyLayerToSession threw exception\n";
        echo "ERROR: " . $e->GetMessage() . "n";
        echo $e->GetDetails() . "n";
        echo $e->GetStackTrace() . "n";
    }


    return $layer;
}

//------------------------------------------------------------------------------
//duplicate a layer from the session in the repository and make it point to a
//repository feature source. This makes a layer change persist across sessions.
function CopyLayerFromSession($map, $resourceService, $sessionLayerId) {
    $destinationLayerId = ToggleRepository($sessionLayerId);

    //copy content from session layer
    $contentReader = $resourceService->GetResourceContent($sessionLayerId);
    $layerContent = $contentReader->ToString();
    $byteSource = new MgByteSource($layerContent, strlen($layerContent));
    $resourceService->SetResource($destinationLayerId, $byteSource->GetReader(), null);

    //instantiate the new layer from its MgResourceIdentifier
    $layer = new MgLayer($destinationLayerId, $resourceService);

    //set the feature source this layer references -- must be in the session
    $sessionLayer = new MgLayer($sessionLayerId, $resourceService);
    $destinationFeatureSourceId = ToggleRepository($sessionLayer->GetFeatureSourceId());
    $layer->SetFeatureSourceId($destinationFeatureSourceId);

    $layer->ForceRefresh();

    //remove the session layer from the session map and replace it with the
    //library copy
    ReplaceLayer($map,  $sessionLayer, $layer);

    //save the session map
    $map->Save($resourceService);

    return $layer;
}

//------------------------------------------------------------------------------
//remove a session layer and point the session map file back to the repository's
//original layer. Useful for discarding edit changes.
function DiscardSessionLayer($map, $resourceService, $sessionLayerId) {
    $originalLayerId = ToggleRepository($sessionLayerId);

    //instantiate the original and session layers from their MgResourceIdentifier
    //and swap them
    $layer = new MgLayer($originalLayerId, $resourceService);
    $sessionLayer = new MgLayer($sessionLayerId, $resourceService);
    ReplaceLayer($map, $layer, $sessionLayer);

    $layer->ForceRefresh();

    //save the session map
    $map->Save($resourceService);

}

//------------------------------------------------------------------------------
//replace one layer with another in the session map
function ReplaceLayer($map, &$old, &$new) {
    $layerCollection=$map->GetLayers();
    $originalLayer = FindLayer($layerCollection, $old->GetLayerDefinition()->ToString());
    $nPosition = $layerCollection->IndexOf($originalLayer);
    $layerCollection->Remove($originalLayer);
    $layerCollection->Insert($nPosition,$new);

    return $nPosition;
}

//------------------------------------------------------------------------------
function GetMapSrs($map)
{
    $srs = $map->GetMapSRS();
    if($srs != "")
       return $srs;

    //SRS is currently optional. Waiting for this to change, set the default SRS to ArbitrayXY meters
    //
    return "LOCALCS[\"*XY-MT*\",LOCAL_DATUM[\"*X-Y*\",10000],UNIT[\"Meter\", 1],AXIS[\"X\",EAST],AXIS[\"Y\",NORTH]]";
}

//------------------------------------------------------------------------------
function BuildLayerDefinitionContent($dataSource, $featureName, $tip)
{
    $xmlLineTemplate = '<?xml version="1.0" encoding="UTF-8"?>
      <LayerDefinition version="1.0.0">
        <FeatureLayerDefinition>
          <Metadata />
          <LegendBitmap/>
          <ResourceId>%s</ResourceId>
          <FeatureClass>%s</FeatureClass>
          <Key/>
          <Geometry>%s</Geometry>
          <MapTip>%s</MapTip>
          <Filter></Filter>
          <FeatureScaleRange>
            <MinScale>0</MinScale>
            <MaxScale>1000000000000</MaxScale>
            <LineTypeStyle>
              <FeatureClassName>Line</FeatureClassName>
              <LineRule>
                <LineSymbolization>
                  <Stroke>
                    <LineStyle>Solid</LineStyle>
                    <Thickness>%s</Thickness>
                    <Color>%s</Color>
                    <Unit>Points</Unit>
                  </Stroke>
                </LineSymbolization>
                <LegendLabel/>
                <LegendBitmap/>
                <Filter/>
                <Label/>
              </LineRule>
            </LineTypeStyle>
          </FeatureScaleRange>
        </FeatureLayerDefinition>
      </LayerDefinition>
    ';

    $layerTempl = $xmlLineTemplate;
    $xmlStr = sprintf($layerTempl,
                      $dataSource,
                      $featureName,
                      "GEOM",
                      $tip,
                      1,
                      "ff0000");
    $src = new MgByteSource($xmlStr, strlen($xmlStr));
    return $src->GetReader();
}

/////////////////////////////////////////////////////////////////////////////////
//Repository Manipulation Utilities
/////////////////////////////////////////////////////////////////////////////////

//------------------------------------------------------------------------------
function DataSourceExists($resourceSrvc, $dataSourceId)
{
    try
    {
        $cnt = $resourceSrvc->GetResourceContent($dataSourceId);
        return true;
    }
    catch(MgResourceNotFoundException $rnfe)
    {
        return false;
    }
}
//------------------------------------------------------------------------------
//create a new MgResourceIdentifier for the session from a Library MgResourceIdentifier
//or vice versa
function ToggleRepository($originalResourceId)
{
    $newResourceID = new MgResourceIdentifier('Library://');
    if ($originalResourceId->GetRepositoryType() == "Library") {
        $newResourceID->SetRepositoryType("Session");
        //$newResourceID->SetRepositoryName($_GET['session']);
        $newResourceID->SetRepositoryName($GLOBALS['sessionID']);
    } else {
        $newResourceID->SetRepositoryType("Library");
    }
    $newResourceID->SetPath($originalResourceId->GetPath());
    $newResourceID->SetName($originalResourceId->GetName());
    $newResourceID->SetResourceType($originalResourceId->GetResourceType());

    //TODO: trap errors
    $newResourceID->Validate();
    return $newResourceID;
}

//------------------------------------------------------------------------------
//create a new MgResourceIdentifier for the session with a given suffix
function CreateSessionResourceId($originalResourceId, $suffix)
{
    $newResourceID = new MgResourceIdentifier('Library://');
    $newResourceID->SetRepositoryType("Session");
    $newResourceID->SetRepositoryName($GLOBALS['sessionID']);
    $newResourceID->SetPath($originalResourceId->GetPath());
    $newResourceID->SetName($originalResourceId->GetName() . $suffix);
    $newResourceID->SetResourceType($originalResourceId->GetResourceType());

    //TODO: trap errors
    try {
        $newResourceID->Validate();
    }
     catch (MgException $e) {
        echo "ERROR: " . $e->GetMessage() . "n";
        echo $e->GetDetails() . "n";
        echo $e->GetStackTrace() . "n";
    }
    return $newResourceID;
}

//------------------------------------------------------------------------------
function FindLayer($layers, $layerDef)
{
    $layer = null;
    for($i = 0; $i < $layers->GetCount(); $i++)
    {
        $layer1 = $layers->GetItem($i);
        if($layer1->GetLayerDefinition()->ToString() == $layerDef)
        {
            $layer = $layer1;
            break;
        }
    }
    return $layer;
}
//------------------------------------------------------------------------------
//get the attributes that correspond to a layer definition
//returns associative array of attributes.
function GetFeatureSourceAttributes($map, $layerResourceId, $featureService) {
    $aAttributes = array();
    $layerDef = $layerResourceId->ToString();
    $layers = $map->GetLayers();
    $layer = FindLayer($layers, $layerDef);
    if ($layer == NULL) {
        return $aAttributes;
    }
    $dataSourceId = new MgResourceIdentifier($layer->GetFeatureSourceId());
    $agf = new MgAgfReaderWriter();

    //get class definition from the featureSource
    $classDefinition = GetFeatureClassDefinition($featureService, $layer, $dataSourceId);
    //MgPropertyDefinition classProps
    $classProps = $classDefinition->GetProperties();
    $identProps = $classDefinition->GetIdentityProperties();
    $featureGeometryName = $layer->GetFeatureGeometryName();
    $drawProps = new MgPropertyCollection();
    for ($i=0; $i< $classProps->GetCount(); $i++)
    {
        $prop = $classProps->GetItem($i);
        if ($prop->GetPropertyType() == MgFeaturePropertyType::GeometricProperty)
        {
            //get the type of class to determine geometry
            //TODO: use bitwise comparison?
            $featureClass = $prop->GetGeometryTypes();
            if ($featureClass == MgFeatureGeometricType::Surface) {
                $aAttributes[$i] = 'surface';
            } elseif ($featureClass == MgFeatureGeometricType::Curve) {
                $aAttributes[$i] = 'curve';
            } elseif ($featureClass == MgFeatureGeometricType::Point) {
                $aAttributes[$i] = 'point';
            }

        } elseif ($prop->GetPropertyType() == MgFeaturePropertyType::DataProperty) {
            //therefore this is an MgDataPropertyDefinition subclassed object
            $aAttributes[$i] = array('name' => substr($prop->GetQualifiedName(),
                                               stripos($prop->GetQualifiedName(),'.') + 1),
                                     'description' => $prop->GetDescription(),
                                     'datatype' => $prop->GetDataType(),
                                     'readonly' => $prop->GetReadOnly(),
                                     'length' => $prop->GetLength(),
                                     'default' => $prop->GetDefaultValue(),
                                     'precision' => $prop->GetPrecision(),
                                     'scale' => $prop->GetScale(),
                                     'nullable' => $prop->GetNullable(),
                                     'identity' => $identProps->IndexOf($prop->GetName()) != -1
                                    );
        } else {
            echo 'Found Other Property:';
            echo $prop->GetQualifiedName();
            echo '<BR>';
        }
    }

    return $aAttributes;
}
//------------------------------------------------------------------------------
function add_layer_resource_to_map($layerResourceID,
     $resourceService,
     $layerDef,
     $layerLegendLabel,
     &$map)
     //Addsalayerdefition(whichcanbestoredeitherinthe
         //Libraryorasessionrepository)tothemap.
         //Returnsthelayer.
{
    $newLayer = new MgLayer($layerResourceID, $resourceService);
    //Add the new layer to the map's layer collection
    $newLayer->SetName($layerLegendLabel);
    $newLayer->SetVisible(true);
    $newLayer->SetLegendLabel($layerLegendLabel);
    $newLayer->SetDisplayInLegend(true);
    $layerCollection=$map->GetLayers();
    if(!FindLayer($layerCollection,$layerDef))
    {
        //Insertthenewlayeratposition0soitisat
        //thetopofthedrawingorder
        $layerCollection->Insert(0,$newLayer);
    }
    return $newLayer;
}

function CreateDataPropertyForType($property) {
    switch ($property->GetDataType())
    {
       case MgPropertyType::Null :
         return null;
         break;
       case MgPropertyType::Boolean :
         return new MgBooleanProperty($property->GetName(), false);
         break;
       case MgPropertyType::Byte :
         return new MgByteProperty($property->GetName(), 0);
         break;
       case MgPropertyType::DateTime :
         return new MgDateTimeProperty($property->GetName(), new MgDateTime());
         break;
       case MgPropertyType::Single :
         return new MgSingleProperty($property->GetName(), 0);
         break;
       case MgPropertyType::Double :
         return new MgDoubleProperty($property->GetName(), 0);
         break;
       case MgPropertyType::Int16 :
         return new MgInt16Property($property->GetName(), 0);
         break;
       case MgPropertyType::Int32 :
         return new MgInt32Property($property->GetName(), 0);
         break;
       case MgPropertyType::Int64 :
         return new MgInt64Property($property->GetName(), 0);
         break;
       case MgPropertyType::String :
         return new MgStringProperty($property->GetName(), '');
         break;
       case MgPropertyType::Blob :
         $byteSource = new MgByteSource("",0);
         return new MgBlobProperty($property->GetName(), $byteSource->GetReader());
         break;
       case MgPropertyType::Clob :
         $byteSource = new MgByteSource("",0);
         return new MgClobProperty($property->GetName(), $byteSource->GetReader());
         break;

       default :
         return null;
    }
}
//-----------------------------------------------------------------
//function GetFeatureClassAndSchema
//@param MgFeatureService featureService
//@param MgResourceIdentifier dataSourceId
//@param MgLayer layer
//@return the classdefinition reference.
//
//@desc Get class definition and schema from the layer.
//@desc This works around changes between MG 1.0.1 and 1.0.2
//@desc described in MG341 (see mapguide.osego.org)
//@desc This function can be removed when all servers are updated.
//------------------------------------------------------------------
function GetFeatureClassDefinition($featureService, $layer, $dataSourceId){

    $qualifiedClass = $layer->GetFeatureClassName();
    if (strpos($qualifiedClass, ':') === false ) {
        $class = $qualifiedClass;
        $schema = $featureService->GetSchemas($dataSourceId)->GetItem(0);
    } else {
        list($schema, $class) = explode(':', $qualifiedClass);
    }
    return $featureService->GetClassDefinition($dataSourceId, $schema, $class);
}


//-----------------------------------------------------------------
//function GetLayerTypes
//@param MgFeatureService featureService
//@param MgLayer layer
//@return the layer types as an array.
//
//@desc utility function to determine the set of allowed feature types for a layer's
//@desc feature source.
//@desc N.B. this is a workaround because the MgLayer::GetLayerType function seems to
//@desc produce the same answer (1) for all layer types.
//------------------------------------------------------------------
function GetLayerTypes($featureService, $layer) {

    $dataSourceId = new MgResourceIdentifier($layer->GetFeatureSourceId());

    //get class definition from the featureSource
    $classDefinition = GetFeatureClassDefinition($featureService, $layer, $dataSourceId);

    //MgPropertyDefinition classProps
    $classProps = $classDefinition->GetProperties();
    $aLayerTypes = array();
    for ($i=0; $i< $classProps->GetCount(); $i++)
    {
        $prop = $classProps->GetItem($i);
        if ($prop->GetPropertyType() == MgFeaturePropertyType::GeometricProperty) {
            $featureClass = $prop->GetGeometryTypes();
            if ($featureClass & MgFeatureGeometricType::Surface) {
                array_push($aLayerTypes, '2'/*'surface'*/);
            }
            if ($featureClass & MgFeatureGeometricType::Curve) {
                array_push($aLayerTypes, '1'/*'curve'*/);
            }
            if ($featureClass & MgFeatureGeometricType::Solid) {
                array_push($aLayerTypes, '3'/*'solid'*/); //could use surface here for editing purposes?
            }
            if ($featureClass & MgFeatureGeometricType::Point){
                array_push($aLayerTypes, '0'/*'point'*/);
            }
            break;
        } else if ($prop->GetPropertyType() == MgFeaturePropertyType::RasterProperty) {
            array_push($aLayerTypes, '4' /* raster */);
        }

    }
    return $aLayerTypes;
}


/* retrieve the property mappings for a layer */
function GetLayerPropertyMappings($resourceService, $layer) {
    $mappings = array();
    $byteReader = $resourceService->GetResourceContent($layer->GetLayerDefinition());
    $xmldoc = DOMDocument::loadXML(ByteReaderToString($byteReader));
    $mappingNodeList = $xmldoc->getElementsByTagName('PropertyMapping');
    for ($i=0; $i<$mappingNodeList->length; $i++) {
        $mapping = $mappingNodeList->item($i);
        $nameElt = $mapping->getElementsByTagName('Name');
        $name = $nameElt->item(0)->nodeValue;
        $valueElt = $mapping->getElementsByTagName('Value');
        $value = $valueElt->item(0)->nodeValue;
        $mappings[$name] = $value;
    }
    return $mappings;
}

/* retrieve the property mappings for a layer */
function IsLayerEditable($resourceService, $layer) {
    $result = true;
    $dataSourceId = new MgResourceIdentifier($layer->GetFeatureSourceId());
    $byteReader = $resourceService->GetResourceContent($dataSourceId);
    $xmldoc = DOMDocument::loadXML(ByteReaderToString($byteReader));
    $parameterList = $xmldoc->getElementsByTagName('Parameter');
    for ($i=0; $i<$parameterList->length; $i++) {
        $parameter = $parameterList->item($i);
        $nameElt = $parameter->getElementsByTagName('Name');
        $name = $nameElt->item(0)->nodeValue;
        if ($name != 'ReadOnly') {
            continue;
        } else {
            $valueElt = $parameter->getElementsByTagName('Value');
            $value = $valueElt->item(0)->nodeValue;
            $result = (strcasecmp($value, 'TRUE') == 0) ? false : true;
            break;
        }
    }
    return $result;
}

function ByteReaderToString($byteReader)
{
    $buffer = '';
    do
    {
        $data = str_pad("\0", 50000, "\0");
        $len = $byteReader->Read($data, 50000);
        if ($len > 0)
        {
            $buffer = $buffer . substr($data, 0, $len);
        }
    } while ($len > 0);

    return $buffer;
}
?>
