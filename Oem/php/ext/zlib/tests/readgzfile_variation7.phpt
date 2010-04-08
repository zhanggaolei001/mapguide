--TEST--
Test function readgzfile() by substituting agument 1 with string values.
--SKIPIF--
<?php
if (!extension_loaded('zlib')) die ('skip zlib extension not available in this build');
?>
--FILE--
<?php


$use_include_path = false;


$heredoc = <<<EOT
hello world
EOT;

$variation_array = array(
  'string DQ' => "string",
  'string SQ' => 'string',
  'mixed case string' => "sTrInG",
  'heredoc' => $heredoc
  );


foreach ( $variation_array as $var ) {
  var_dump(readgzfile( $var ,  $use_include_path ) );
}
?>
===DONE===
--EXPECTF--
bool(false)
bool(false)
bool(false)
bool(false)
===DONE===
