--TEST--
Test json_encode() function : basic functionality with UTF8 string input
--SKIPIF--
<?php 
if (!extension_loaded("json")) {
 	die('skip JSON extension not available in this build');
}	 
?> 
--FILE--
<?php
/* Prototype  : string json_encode  ( mixed $value  )
 * Description: Returns the JSON representation of a value
 * Source code: ext/json/php_json.c
 * Alias to functions: 
 */
echo "*** Testing json_encode() : basic functionality with UTF-8 input***\n";

$utf8_string = base64_decode('5pel5pys6Kqe44OG44Kt44K544OI44Gn44GZ44CCMDEyMzTvvJXvvJbvvJfvvJjvvJnjgII=');
var_dump(json_encode($utf8_string)); 

?>
===Done===
--EXPECTF-- 
*** Testing json_encode() : basic functionality with UTF-8 input***
string(103) ""\u65e5\u672c\u8a9e\u30c6\u30ad\u30b9\u30c8\u3067\u3059\u300201234\uff15\uff16\uff17\uff18\uff19\u3002""
===Done===
