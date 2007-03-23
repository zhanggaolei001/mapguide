<?php

//
//  Copyright (C) 2004-2007 by Autodesk, Inc.
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

?>

<!DOCTYPE HTML PUBLIC "-//W3C//DTD HTML 4.01 Transitional//EN" "http://www.w3.org/TR/html4/loose.dtd">
<html>

	<head>
	    <title>Displays the schema</title>
	    <link href="displayschema.css" rel="stylesheet" type="text/css">
	</head>

	<body>

		<?php
		    include '../mapadmin/Constants.php';

		    $sessionId = $_GET['sessionId'];
		    $resName = $_GET['resId'];
		    $schemaName = $_GET['schemaName'];
		    $className = $_GET['className'];

			try
		    {
		    	$thisFile = __FILE__;
				$pos = strrpos($thisFile, '\\');
				if ($pos == false)
					$pos = strrpos($thisFile, '/');
				$configFilePath = substr($thisFile, 0, $pos+1) . "../webconfig.ini";
		        MgInitializeWebTier ($configFilePath);

				$userInfo = new MgUserInformation($sessionId);
		        $site = new MgSiteConnection();
		        $site->Open($userInfo);

				$featureSrvc = $site->CreateService(MgServiceType::FeatureService);

				$resId = new MgResourceIdentifier($resName);

				$xml = $featureSrvc->DescribeSchemaAsXml($resId, $schemaName);
				$xsl_file = 'displayschema.xsl';

				// Create new object for the XML file
				$xml_object = new DomDocument();
				if(!$xml)
					exit('Cannot open $xml_file');
				$xml_object->loadXML($xml);

				// Create new object for the XSL stylesheet
				$xsl_object = new DomDocument();
				if(!file_exists($xsl_file))
					exit('Cannot open $xsl_file');
				$xsl_object->load($xsl_file);

				// Configure the transformer
				$proc = new XSLTProcessor;
				$proc->importStyleSheet($xsl_object);

				$proc->setParameter('', 'schemaName', $schemaName);
				$proc->setParameter('', 'className', $className);
				$proc->setParameter('', 'resName', $resName);
				$proc->setParameter('', 'sessionId', $sessionId);

				$html = $proc->transformToXML($xml_object);

				print($html);
			}
		    catch (MgException $e)
		    {
		        echo $e->GetMessage();
		    }

		?>

	</body>

</html>
