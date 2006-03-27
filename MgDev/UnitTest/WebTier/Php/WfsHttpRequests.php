<?php
require_once("HttpRequest.php");
require_once("Utils.php");

//This file defines the operations that are currently supported by the unit test infrastructure for Drawing Service methods exposed through Htpp.
//There is one function per operation. Each function tries to retrieve the parameters that are required for its corresponding
//operation and send the Http request
//Edit that file to add more operations from Drawing Service that are exposed through Http

class WfsHttpRequests
{
    private $db;
    private $unitTestParamVm;
    private $URL;

    function __construct($db, $newURL)
    {
        $this->db = $db;
        $this->unitTestParamVm = new SqliteVM($db, true);
        $this->httpRequest = new HttpRequest();
        $this->URL = $newURL;
    }

    function __destruct()
    {
        unset($this->unitTestParamVm);
        unset($this->httpRequest);
        unset($this->db);
    }

    function GetCapabilities($paramSet)
    {
        try
        {
            $arrayParam = array();

            $this->unitTestParamVm->Execute("Select ParamValue from Params WHERE ParamSet=$paramSet AND ParamName=\"request\"");
            $arrayParam["request"]=$this->unitTestParamVm->GetString("ParamValue");

            $this->unitTestParamVm->Execute("Select ParamValue from Params WHERE ParamSet=$paramSet AND ParamName=\"service\"");
            $arrayParam["service"]=$this->unitTestParamVm->GetString("ParamValue");

            $this->unitTestParamVm->Execute("Select ParamValue from Params WHERE ParamSet=$paramSet AND ParamName=\"VERSION\"");
            $arrayParam["VERSION"]=$this->unitTestParamVm->GetString("ParamValue");

            return $this->httpRequest->SendRequest($this->URL, $arrayParam);
        }
        catch (SqliteException $s)
        {
            return new Result($s->GetMessage(), "text/plain");
        }
    }

    function DescribeFeatureType($paramSet)
    {
        try
        {
            $arrayParam = array();

            $this->unitTestParamVm->Execute("Select ParamValue from Params WHERE ParamSet=$paramSet AND ParamName=\"request\"");
            $arrayParam["request"]=$this->unitTestParamVm->GetString("ParamValue");

            $this->unitTestParamVm->Execute("Select ParamValue from Params WHERE ParamSet=$paramSet AND ParamName=\"service\"");
            $arrayParam["service"]=$this->unitTestParamVm->GetString("ParamValue");

            $this->unitTestParamVm->Execute("Select ParamValue from Params WHERE ParamSet=$paramSet AND ParamName=\"typeName\"");
            $arrayParam["typeName"]=$this->unitTestParamVm->GetString("ParamValue");

            return $this->httpRequest->SendRequest($this->URL, $arrayParam);
        }
        catch (SqliteException $s)
        {
            return new Result($s->GetMessage(), "text/plain");
        }
    }


    function GetFeature($paramSet)
    {
        try
        {
            $arrayParam = array();

            $this->unitTestParamVm->Execute("Select ParamValue from Params WHERE ParamSet=$paramSet AND ParamName=\"request\"");
            $arrayParam["request"]=$this->unitTestParamVm->GetString("ParamValue");

            $this->unitTestParamVm->Execute("Select ParamValue from Params WHERE ParamSet=$paramSet AND ParamName=\"service\"");
            $arrayParam["service"]=$this->unitTestParamVm->GetString("ParamValue");

            $this->unitTestParamVm->Execute("Select ParamValue from Params WHERE ParamSet=$paramSet AND ParamName=\"typeName\"");
            $arrayParam["typeName"]=$this->unitTestParamVm->GetString("ParamValue");

            return $this->httpRequest->SendRequest($this->URL, $arrayParam);
        }
        catch (SqliteException $s)
        {
            return new Result($s->GetMessage(), "text/plain");
        }
    }

    
}
?>
