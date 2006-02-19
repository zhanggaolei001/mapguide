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

ZEND_RSRC_DTOR_FUNC(php_dbxml_XmlDocument_dtor)
{
  php_dbxml_delete_XmlDocument(rsrc->ptr);
}

PHP_DBXML_METHOD_BEGIN(XmlDocument, XmlDocument)
{
  php_error_docref(NULL TSRMLS_CC, E_ERROR, "This class cannot be instantiated directly");
} PHP_DBXML_METHOD_END()

PHP_DBXML_METHOD_BEGIN(XmlDocument, getName)
{
  PHP_DBXML_STUFFED_THIS(XmlDocument);
  std::string buffer = This.getName();
  RETURN_STRINGL((char *)buffer.data(), buffer.length(), 1);
} PHP_DBXML_METHOD_END()

PHP_DBXML_METHOD_BEGIN(XmlDocument, setName)
{
  PHP_DBXML_STUFFED_THIS(XmlDocument);
  char *name;
  long namelen;
  if(FAILURE == zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC, "s", &name, &namelen)) {
    return;
  }
  This.setName(std::string(name, namelen));
} PHP_DBXML_METHOD_END()

PHP_DBXML_METHOD_BEGIN(XmlDocument, getContent)
{
  PHP_DBXML_STUFFED_THIS(XmlDocument);
  XmlData xdata = This.getContent();
  php_dbxml_set_XmlData_object_factory(return_value, xdata TSRMLS_CC);
} PHP_DBXML_METHOD_END()

PHP_DBXML_METHOD_BEGIN(XmlDocument, getContentAsString)
{
  PHP_DBXML_STUFFED_THIS(XmlDocument);
  std::string buffer;
  This.getContent(buffer);
  RETURN_STRINGL((char *)buffer.data(), buffer.length(), 1);
} PHP_DBXML_METHOD_END()

PHP_DBXML_METHOD_BEGIN(XmlDocument, setContent)
{
  PHP_DBXML_STUFFED_THIS(XmlDocument);
  zval *zstr = NULL, *zdat = NULL;
  char *content;
  long contentlen;
  if(SUCCESS == zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC, "s", &content, &contentlen)) {
    This.setContent(std::string(content, contentlen));
  }
  else if(SUCCESS == zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC, "O", &zdat, php_dbxml_XmlData_ce)) {
    XmlData dat = php_dbxml_get_XmlData_object_pointer(zdat TSRMLS_CC);
    This.setContent(dat);
  }
  else if(SUCCESS == zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC, "O", &zstr, php_dbxml_XmlInputStream_ce)) {
    XmlInputStream *str = PHP_DBXML_GET(zstr, XmlInputStream);
    This.setContentAsXmlInputStream(str);
  }
  else {
    return;
  }
} PHP_DBXML_METHOD_END()


PHP_DBXML_METHOD_BEGIN(XmlDocument, fetchAllData)
{
  PHP_DBXML_STUFFED_THIS(XmlDocument);
  if (ZEND_NUM_ARGS()) {
    WRONG_PARAM_COUNT;
  }
  This.fetchAllData();
} PHP_DBXML_METHOD_END()

PHP_DBXML_METHOD_BEGIN(XmlDocument, getMetaData)
{
  PHP_DBXML_STUFFED_THIS(XmlDocument);
  zval *zvl = NULL, *zdat = NULL;
  char *uri, *name;
  long urilen, namelen;
  if(SUCCESS == zend_parse_parameters_ex(ZEND_PARSE_PARAMS_QUIET, ZEND_NUM_ARGS() TSRMLS_CC, "ss", 
      &uri, &urilen, &name, &namelen)) {
    XmlValue vl;
    if(This.getMetaData(std::string(uri, urilen), std::string(name, namelen), vl)) {
      php_dbxml_set_XmlValue_object_factory(return_value, vl TSRMLS_CC);
    } else {
      RETURN_FALSE;
    }
  }
} PHP_DBXML_METHOD_END()

function_entry php_dbxml_XmlDocument_methods[] = {
PHP_ME(XmlDocument, XmlDocument, NULL, 0)
PHP_ME(XmlDocument, getName, NULL, 0)
PHP_ME(XmlDocument, setName, NULL, 0)
PHP_ME(XmlDocument, getContent, NULL, 0)
PHP_ME(XmlDocument, getContentAsString, NULL, 0)
PHP_ME(XmlDocument, setContent, NULL, 0)
PHP_ME(XmlDocument, fetchAllData, NULL, 0)
PHP_ME(XmlDocument, getMetaData, NULL, 0)
{NULL, NULL, NULL}
};
/*  vim: set sts=2 ts=2 expandtab ai bs=2 : */
