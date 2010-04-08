--TEST--
XMLReader: libxml2 XML Reader, next 
--SKIPIF--
<?php if (!extension_loaded("xmlreader")) print "skip"; ?>
--FILE--
<?php 
/* $Id: 010.phpt 203342 2005-12-21 03:58:59Z pajoye $ */
$xmlstring = '<?xml version="1.0" encoding="UTF-8"?>
<prefix:books xmlns:prefix="uri" isbn="" prefix:isbn="12isbn">book1</prefix:books>';

$reader = new XMLReader();
$reader->XML($xmlstring);

// Only go through
$reader->read();
$reader->read();

$reader->next();
echo $reader->name;
echo " ";
echo $reader->getAttributeNs('isbn', 'uri');
echo "\n";
?>
===DONE===
--EXPECTF--
prefix:books 12isbn
===DONE===
