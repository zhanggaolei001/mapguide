--TEST--
EXPECTF
--FILE--
123
-123
+123
+1.1
abc
0abc
x
--EXPECTF--
%d
%i
%i
%f
%s
%x
%c