<?php
   include 'resizableadmin.php';

    LoadSessionVars();

    // Did the user logout?
    CheckForLogout();

    // Are we cancelling?  If so, there is nothing to do.
    CheckForCancel( 'performanceReport.php' );

    // Define Local values
    $mapProfileResult=new MapProfileResult();

    function GetProfilingResults()
    {
        global $mapProfileResult;
        $resultSource=new DOMDocument();
        //As the profiling API is not finished, now we just use a temp xml file to simulate it.
        //we will change it in part 3.
        $resultSource->load("profilingmapxml/profileResults.xml");
        $mapProfileResult->ReadFromXML($resultSource);
        $mapProfileResult->GetBaseLayerCount();
    }

    GetProfilingResults();

    //add one line gap
    echo "\n";

    //output the basic information of the map resource
    //get the extent display string
    list($x1, $y1, $x2, $y2) = explode(",", $mapProfileResult->MapProfileData->DataExtents);
    $extents= '"X1:' . $x1 . '    Y1:' . $y1.'    X2:' . $x2 . '    Y2:' . $y2.'"';

    //get the scale display string
    $scale= "1:" . number_format($mapProfileResult->MapProfileData->Scale,0,"."," ");

    //get the center point display string
    list($centerPointX, $centerPointY) = explode("*", $_REQUEST["centerPoint"]);
    $centerPoint= '"X:'.trim($centerPointX).'    Y:'.trim($centerPointY).'"';

    //export the map information
    echo '"Resource Name",'.$mapProfileResult->MapProfileData->MapResourceId;
    echo ',"Data Extents",'.$extents,"\n";
    echo '"Base Layers",'.$mapProfileResult->MapProfileData->BaseLayerCount.',"Image Format",';
    echo $mapProfileResult->MapProfileData->ImageFormat,"\n";
    echo '"Center Point",'.$centerPoint.',Layers,';
    echo $mapProfileResult->MapProfileData->LayerCount,"\n";
    echo '"Coordinate System",'.$mapProfileResult->MapProfileData->CoordinateSystem;
    echo ',"Render Type",'.$mapProfileResult->MapProfileData->RenderType,"\n";
    echo 'Scale,'.$scale,"\n";

    //add two lines gap to divide the information into different sections
    echo "\n";
    echo "\n";

    //output the render time information
    echo '"Total Generation Time:","'.$mapProfileResult->MapProfileData->TotalMapRenderTime . ' ms"',"\n";

    echo '"Layers ","'.$mapProfileResult->MapProfileData->TotalLayerRenderTime . ' ms",';
    echo $mapProfileResult->MapProfileData->GetLayerRenderPercent() .'%',"\n";

    echo '"Labels ","'.$mapProfileResult->MapProfileData->TotalLabelRenderTime . ' ms",';
    echo $mapProfileResult->MapProfileData->GetLabelRenderPercent() .'%',"\n";

    echo '"Watermarks ","'.$mapProfileResult->MapProfileData->TotalWatermarkRenderTime . ' ms",';
    echo $mapProfileResult->MapProfileData->GetWartermarkRenderPercent() .'%',"\n";

    echo '"Images ","'.$mapProfileResult->MapProfileData->TotalImageRenderTime . ' ms",';
    echo $mapProfileResult->MapProfileData->GetImageRenderPercent() .'%',"\n";

    echo '"Other ","'.$mapProfileResult->MapProfileData->GetOtherRenderTime() . ' ms",';
    echo $mapProfileResult->MapProfileData->GetOthersRenderPercent() .'%',"\n";
    
    //add two lines gap to divide the information into different sections
    echo "\n";
    echo "\n";

    //output the detailed information of each layer
    echo 'Layer,"Render Time","Feature Class","Coordinate System",Type,Filter,"Scale Range"',"\n";

    foreach ($mapProfileResult->LayerProfileData->LayerProfileDataCollection as $layerProfileData)
    {
        echo '"'.$layerProfileData->LayerName.'",' ;
        echo '"'.$layerProfileData->TotalRenderTime.' ms",' ;
        echo '"'.$layerProfileData->FeatureClass .'",';
        echo '"'.$layerProfileData->CoordinateSystem .'",';
        echo '"'.$layerProfileData->LayerType.'",' ;
        echo '"'.$layerProfileData->Filters.'",' ;
        echo '"'.$layerProfileData->ScaleRange.'"' ;
        echo "\n";
    }

    //construct a readable file name
    $tempMapName = strrchr($mapProfileResult->MapProfileData->MapResourceId, '/');
    $tempMapName = substr($tempMapName, 1, strlen($tempMapName) - 15);
    $Date = date("Y-m-d_His");
    $Filename = $Date."_".$tempMapName.".csv";

    header("Content-type:application/vnd.ms-excel");
    header("Content-Disposition:filename=".$Filename);
?>