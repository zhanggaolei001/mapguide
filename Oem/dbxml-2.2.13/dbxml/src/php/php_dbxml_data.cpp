/*-
 *  Copyright (c) 2004
 *  Sleepycat Software.  All rights reserved.
 *
 *  http://www.apache.org/licenses/LICENSE-2.0.txt
 * 
 *  authors: Wez Furlong <wez@omniti.com>  
 *           George Schlossnagle <george@omniti.com>
 */

#include "php_dbxml_int.hpp"

ZEND_RSRC_DTOR_FUNC(php_dbxml_XmlData_dtor)
{
    php_dbxml_delete_XmlData(rsrc->ptr);
}

PHP_DBXML_METHOD_BEGIN(XmlData, XmlData)
{
  XmlData This;
  char *data = NULL;
  int data_len;

  if (FAILURE == zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC, "|s", &data, &data_len)) {
    RETURN_FALSE;
  }

  if (data) {
    This = XmlData(data, data_len);
  }

  php_dbxml_set_XmlData_object_pointer(getThis(), This TSRMLS_CC);
} PHP_DBXML_METHOD_END()

PHP_DBXML_METHOD_BEGIN(XmlData, get_data)
{
  PHP_DBXML_STUFFED_THIS(XmlData);
 
  if (ZEND_NUM_ARGS()) {
    WRONG_PARAM_COUNT;
  }

  RETURN_STRINGL((char*)This.get_data(), This.get_size(), 1);
} PHP_DBXML_METHOD_END()

PHP_DBXML_METHOD_BEGIN(XmlData, set_data)
{
  char *data;
  int data_len;
  PHP_DBXML_STUFFED_THIS(XmlData);

  if (FAILURE == zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC, "s", &data, &data_len)) {
    RETURN_FALSE;
  }

  /* TODO: DANGER? does this copy... ? */
  This.set_data(data);
  This.set_size(data_len);
} PHP_DBXML_METHOD_END()


function_entry php_dbxml_XmlData_methods[] = {
  PHP_ME(XmlData, XmlData,        NULL, 0)
  PHP_ME(XmlData, get_data,        NULL, 0)
  PHP_ME(XmlData, set_data,        NULL, 0)
  {NULL,NULL,NULL}
};

