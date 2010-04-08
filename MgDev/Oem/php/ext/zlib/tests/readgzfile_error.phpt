--TEST--
Test function readgzfile() by calling it more than or less than its expected arguments
--SKIPIF--
<?php
if (!extension_loaded('zlib')) die ('skip zlib extension not available in this build');
?>
--FILE--
<?php


$filename = dirname(__FILE__)."/004.txt.gz";
$use_include_path = false;
$extra_arg = 'nothing'; 

var_dump(readgzfile( $filename, $use_include_path, $extra_arg ) );

var_dump(readgzfile(  ) );


?>
===DONE===
--EXPECTF--

Warning: readgzfile() expects at most 2 parameters, 3 given in %s on line %d
NULL

Warning: readgzfile() expects at least 1 parameter, 0 given in %s on line %d
NULL
===DONE===