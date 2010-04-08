--TEST--
ldap_compare() - Basic ldap_compare test
--CREDITS--
Patrick Allaert <patrickallaert@php.net>
# Belgian PHP Testfest 2009
--SKIPIF--
<?php require_once('skipif.inc'); ?>
<?php require_once('skipifbindfailure.inc'); ?>
--FILE--
<?php
require "connect.inc";

$link = ldap_connect_and_bind($host, $port, $user, $passwd, $protocol_version);
insert_dummy_data($link);
var_dump(
	ldap_compare($link, "cn=userA,dc=my-domain,dc=com", "sn", "testSN1"),
	ldap_compare($link, "cn=userA,dc=my-domain,dc=com", "telephoneNumber", "yy-yy-yy-yy-yy")
);
?>
===DONE===
--CLEAN--
<?php
include "connect.inc";

$link = ldap_connect_and_bind($host, $port, $user, $passwd, $protocol_version);
remove_dummy_data($link);
?>
--EXPECT--
bool(true)
bool(false)
===DONE===
