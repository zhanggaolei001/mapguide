--TEST--
Bug #48770 (call_user_func_array() fails to call parent from inheriting class)
--XFAIL--
See Bug #48770
--FILE--
<?php
 
class A {
	public function func($str) {
		var_dump(__METHOD__ .': '. $str);
	}
	private function func2($str) {
		var_dump(__METHOD__ .': '. $str);
	}
	protected function func3($str) {
		var_dump(__METHOD__ .': '. $str);		
	}
	private function func22($str) {
		var_dump(__METHOD__ .': '. $str);		
	}
}

class B extends A {
	public function func($str) {
  		call_user_func_array(array($this, 'parent::func2'), array($str));
  		call_user_func_array(array($this, 'parent::func3'), array($str));
  		call_user_func_array(array($this, 'parent::func22'), array($str));
  		call_user_func_array(array($this, 'parent::inexistent'), array($str));
	}
	private function func2($str) {
		var_dump(__METHOD__ .': '. $str);
	}
	protected function func3($str) {
		var_dump(__METHOD__ .': '. $str);
	}
}

class C extends B {
	public function func($str) {
		parent::func($str);
	}
}

$c = new C;
$c->func('This should work!');

?>
--EXPECTF--
%unicode|string%(27) "A::func2: This should work!"
%unicode|string%(27) "A::func3: This should work!"

Warning: call_user_func_array() expects parameter 1 to be a valid callback, cannot access private method A::func22() in %s on line %d

Warning: call_user_func_array() expects parameter 1 to be a valid callback, class 'A' does not have a method 'inexistent' in %s on line %d
