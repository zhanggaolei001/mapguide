--TEST--
DOMDocumentType::publicId with empty value.
--CREDITS--
Eric Lee Stewart <ericleestewart@gmail.com>
# TestFest Atlanta 2009-05-25
--SKIPIF--
<?php require_once('skipif.inc'); ?>
--FILE--
<?php
$xml  = '<?xml version="1.0" encoding="UTF-8" ?>';
$xml .= '<!DOCTYPE chapter SYSTEM "http://www.xmlwriter.net/logo.gif">';
$xml .= '<chapter>1</chapter>';
$doc = new DOMDocument();
$doc->loadXML($xml);
$doctype = $doc->doctype;
var_dump($doctype->publicId);
?>
--EXPECT--
string(0) ""