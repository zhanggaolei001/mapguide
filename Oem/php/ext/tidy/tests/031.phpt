--TEST--
tidy_config_count() function - basic test for tidy_config_count()
--CREDITS--
Christian Wenz <wenz@php.net>
--SKIPIF--
<?php
  if (!extension_loaded('tidy')) die ('skip tidy not present');
?>
--FILE--
<?php
$buffer = '<html></html>';
$config = array('doctype' => 'php');

$tidy = tidy_parse_string($buffer, $config);
var_dump(tidy_config_count($tidy));
?>
--EXPECTF--
int(%d)
