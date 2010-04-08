--TEST--
Test replacing data into a DOMComment basic test
--CREDITS--
Andrew Larssen <al@larssen.org>
London TestFest 2008
--SKIPIF--
<?php require_once('skipif.inc'); ?>
--FILE--
<?php

//offset to large
$dom = new DomDocument();
$comment = $dom->createComment('test-comment');
try {
  $comment->replaceData(999,4,'-inserted');
} catch (DOMException $e ) {
  if ($e->getMessage() == 'Index Size Error'){
    echo "Throws DOMException for offest too large\n";
  }
}

?>
--EXPECTF--
Throws DOMException for offest too large