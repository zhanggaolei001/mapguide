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

PHP_DBXML_DECLARE_CLASS(XmlManager); /* done */
PHP_DBXML_DECLARE_CLASS(XmlContainer); /* done */
PHP_DBXML_DECLARE_CLASS(XmlData);
PHP_DBXML_DECLARE_CLASS(XmlDocument);
PHP_DBXML_DECLARE_CLASS(XmlIndexLookup); /* done */
PHP_DBXML_DECLARE_CLASS(XmlIndexSpecification); /* done */
PHP_DBXML_DECLARE_CLASS(XmlModify);       /* done */
PHP_DBXML_DECLARE_CLASS(XmlQueryContext); /* done */
PHP_DBXML_DECLARE_CLASS(XmlQueryExpression); /* done */
PHP_DBXML_DECLARE_CLASS(XmlResults);      /* done */
PHP_DBXML_DECLARE_CLASS(XmlValue);        /* done */
PHP_DBXML_DECLARE_CLASS(XmlUpdateContext);/* done */
PHP_DBXML_DECLARE_CLASS(XmlTransaction);  /* done */
PHP_DBXML_DECLARE_CLASS(XmlInputStream);  /* done */
#if 0
PHP_DBXML_DECLARE_CLASS(XmlResolver);     /* done */
#endif
PHP_DBXML_DECLARE_CLASS(XmlStatistics);     /* done */

#ifdef ZEND_ENGINE_2
ZEND_BEGIN_ARG_INFO(first_second_and_third_args_force_ref, 0)
    ZEND_ARG_PASS_INFO(1)
    ZEND_ARG_PASS_INFO(1)
    ZEND_ARG_PASS_INFO(1)
ZEND_END_ARG_INFO();
#else
static unsigned char first_second_and_third_args_force_ref[] = {3, BYREF_FORCE, BYREF_FORCE, BYREF_FORCE };
#endif

static PHP_FUNCTION(dbxml_version)
{
  int M, m, p;
  zval *maj = NULL, *min = NULL, *pat = NULL;
  
  if (ZEND_NUM_ARGS() && FAILURE == zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC, "z/z/z/", &maj, &min, &pat)) {
    return;
  }

  RETVAL_STRING((char*)dbxml_version(&M, &m, &p), 1);

  if (ZEND_NUM_ARGS()) {
    convert_to_long(maj);
    convert_to_long(min);
    convert_to_long(pat);
    Z_LVAL_P(maj) = M;
    Z_LVAL_P(min) = m;
    Z_LVAL_P(pat) = p;
  }
}

static PHP_FUNCTION(dbxml_set_log_level)
{
  long level, on;

  if (FAILURE == zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC, "ll", &level, &on)) {
    return;
  }

  DbXml::setLogLevel((DbXml::LogLevel)level, on);
}

static PHP_FUNCTION(dbxml_set_log_category)
{
  long level, on;

  if (FAILURE == zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC, "ll", &level, &on)) {
    return;
  }

  DbXml::setLogCategory((DbXml::LogCategory)level, on);
}

function_entry dbxml_functions[] = {
  PHP_FE(dbxml_version,           first_second_and_third_args_force_ref)
  PHP_FE(dbxml_set_log_level,     NULL)
  PHP_FE(dbxml_set_log_category,  NULL)
  {NULL,NULL,NULL}
};


PHP_MINIT_FUNCTION(dbxml)
{
  zend_class_entry ce;

  PHP_DBXML_REGISTER_CLASS(XmlData, php_dbxml_XmlData_dtor);
  PHP_DBXML_REGISTER_CLASS(XmlValue, php_dbxml_XmlValue_dtor);
  PHP_DBXML_REGISTER_CLASS(XmlContainer, php_dbxml_XmlContainer_dtor);
#if 0
  PHP_DBXML_REGISTER_CLASS(XmlResolver, NULL);
#endif
  PHP_DBXML_REGISTER_CLASS(XmlDocument, php_dbxml_XmlDocument_dtor);
  PHP_DBXML_REGISTER_CLASS(XmlIndexSpecification, php_dbxml_XmlIndexSpecification_dtor);
  PHP_DBXML_REGISTER_CLASS(XmlModify, php_dbxml_XmlModify_dtor);
  PHP_DBXML_REGISTER_CLASS(XmlQueryContext, php_dbxml_XmlQueryContext_dtor);
  PHP_DBXML_REGISTER_CLASS(XmlQueryExpression, php_dbxml_XmlQueryExpression_dtor);
  PHP_DBXML_REGISTER_CLASS(XmlResults, php_dbxml_XmlResults_dtor);
  PHP_DBXML_REGISTER_CLASS(XmlUpdateContext, php_dbxml_XmlUpdateContext_dtor);
  PHP_DBXML_REGISTER_CLASS(XmlTransaction, php_dbxml_XmlTransaction_dtor);
  PHP_DBXML_REGISTER_CLASS(XmlInputStream, php_dbxml_XmlInputStream_dtor);
  PHP_DBXML_REGISTER_CLASS(XmlStatistics, php_dbxml_XmlStatistics_dtor);
  PHP_DBXML_REGISTER_CLASS(XmlManager, php_dbxml_XmlManager_dtor);
  REGISTER_LONG_CONSTANT( "DBXML_ADOPT_DBENV", DBXML_ADOPT_DBENV, CONST_CS | CONST_PERSISTENT);
  REGISTER_LONG_CONSTANT( "DBXML_ALLOW_EXTERNAL_ACCESS", DBXML_ALLOW_EXTERNAL_ACCESS, CONST_CS | CONST_PERSISTENT);
  REGISTER_LONG_CONSTANT( "DBXML_ALLOW_AUTO_OPEN", DBXML_ALLOW_AUTO_OPEN, CONST_CS | CONST_PERSISTENT);
  REGISTER_LONG_CONSTANT( "DBXML_ALLOW_VALIDATION", DBXML_ALLOW_VALIDATION, CONST_CS | CONST_PERSISTENT);
  REGISTER_LONG_CONSTANT( "DBXML_TRANSACTIONAL", DBXML_TRANSACTIONAL, CONST_CS | CONST_PERSISTENT);
  REGISTER_LONG_CONSTANT( "DBXML_REVERSE_ORDER", DBXML_REVERSE_ORDER, CONST_CS | CONST_PERSISTENT);
  REGISTER_LONG_CONSTANT( "DBXML_INDEX_VALUES", DBXML_INDEX_VALUES, CONST_CS | CONST_PERSISTENT);
  REGISTER_LONG_CONSTANT( "DBXML_CHKSUM", DBXML_CHKSUM, CONST_CS | CONST_PERSISTENT);
  REGISTER_LONG_CONSTANT( "DBXML_ENCRYPT", DBXML_ENCRYPT, CONST_CS | CONST_PERSISTENT);
  REGISTER_LONG_CONSTANT( "DBXML_GEN_NAME", DBXML_GEN_NAME, CONST_CS | CONST_PERSISTENT);
  REGISTER_LONG_CONSTANT( "DBXML_LAZY_DOCS", DBXML_LAZY_DOCS, CONST_CS | CONST_PERSISTENT);
  REGISTER_LONG_CONSTANT( "DBXML_CACHE_DOCUMENTS", DBXML_CACHE_DOCUMENTS, CONST_CS | CONST_PERSISTENT);
  REGISTER_LONG_CONSTANT( "DBXML_NO_INDEX_NODES", DBXML_NO_INDEX_NODES, CONST_CS | CONST_PERSISTENT);
  REGISTER_LONG_CONSTANT( "DBXML_INDEX_NODES", DBXML_INDEX_NODES, CONST_CS | CONST_PERSISTENT);
  REGISTER_LONG_CONSTANT( "LEVEL_NONE", LEVEL_NONE, CONST_CS | CONST_PERSISTENT);
  REGISTER_LONG_CONSTANT( "LEVEL_DEBUG", LEVEL_DEBUG, CONST_CS | CONST_PERSISTENT);
  REGISTER_LONG_CONSTANT( "LEVEL_INFO", LEVEL_INFO, CONST_CS | CONST_PERSISTENT);
  REGISTER_LONG_CONSTANT( "LEVEL_WARNING", LEVEL_WARNING, CONST_CS | CONST_PERSISTENT);
  REGISTER_LONG_CONSTANT( "LEVEL_ERROR", LEVEL_ERROR, CONST_CS | CONST_PERSISTENT);
  REGISTER_LONG_CONSTANT( "LEVEL_ALL", LEVEL_ALL, CONST_CS | CONST_PERSISTENT);
  REGISTER_LONG_CONSTANT( "CATEGORY_NONE", CATEGORY_NONE, CONST_CS | CONST_PERSISTENT);
  REGISTER_LONG_CONSTANT( "CATEGORY_INDEXER", CATEGORY_INDEXER, CONST_CS | CONST_PERSISTENT);
  REGISTER_LONG_CONSTANT( "CATEGORY_QUERY", CATEGORY_QUERY, CONST_CS | CONST_PERSISTENT);
  REGISTER_LONG_CONSTANT( "CATEGORY_OPTIMIZER", CATEGORY_OPTIMIZER, CONST_CS | CONST_PERSISTENT);
  REGISTER_LONG_CONSTANT( "CATEGORY_DICTIONARY", CATEGORY_DICTIONARY, CONST_CS | CONST_PERSISTENT);
  REGISTER_LONG_CONSTANT( "CATEGORY_CONTAINER", CATEGORY_CONTAINER, CONST_CS | CONST_PERSISTENT);
  REGISTER_LONG_CONSTANT( "CATEGORY_NODESTORE", CATEGORY_NODESTORE, CONST_CS | CONST_PERSISTENT);
  REGISTER_LONG_CONSTANT( "CATEGORY_MANAGER", CATEGORY_MANAGER, CONST_CS | CONST_PERSISTENT);
  REGISTER_LONG_CONSTANT( "CATEGORY_ALL", CATEGORY_ALL, CONST_CS | CONST_PERSISTENT);
  REGISTER_STRING_CONSTANT("metaDataNamespace_uri", "http://www.sleepycat.com/2002/dbxml", CONST_CS | CONST_PERSISTENT);
  REGISTER_STRING_CONSTANT("metaDataNamespace_prefix", "dbxml", CONST_CS | CONST_PERSISTENT);
  REGISTER_STRING_CONSTANT("metaDataName_name", "name", CONST_CS | CONST_PERSISTENT);
  REGISTER_STRING_CONSTANT("metaDataName_root", "root", CONST_CS | CONST_PERSISTENT);
  REGISTER_LONG_CONSTANT( "XmlContainer_WholedocContainer", XmlContainer::WholedocContainer, CONST_CS | CONST_PERSISTENT);
  REGISTER_LONG_CONSTANT( "XmlContainer_NodeContainer", XmlContainer::NodeContainer, CONST_CS | CONST_PERSISTENT);
  REGISTER_LONG_CONSTANT( "XmlQueryContext_DeadValues", XmlQueryContext::DeadValues, CONST_CS | CONST_PERSISTENT);
  REGISTER_LONG_CONSTANT( "XmlQueryContext_LiveValues", XmlQueryContext::LiveValues, CONST_CS | CONST_PERSISTENT);
  REGISTER_LONG_CONSTANT( "XmlQueryContext_Eager", XmlQueryContext::Eager, CONST_CS | CONST_PERSISTENT);
  REGISTER_LONG_CONSTANT( "XmlQueryContext_Lazy", XmlQueryContext::Lazy, CONST_CS | CONST_PERSISTENT);
  REGISTER_LONG_CONSTANT( "XmlValue_ELEMENT_NODE", XmlValue::ELEMENT_NODE, CONST_CS | CONST_PERSISTENT);
  REGISTER_LONG_CONSTANT( "XmlValue_ATTRIBUTE_NODE", XmlValue::ATTRIBUTE_NODE, CONST_CS | CONST_PERSISTENT);
  REGISTER_LONG_CONSTANT( "XmlValue_TEXT_NODE", XmlValue::TEXT_NODE, CONST_CS | CONST_PERSISTENT);
  REGISTER_LONG_CONSTANT( "XmlValue_CDATA_SECTION_NODE", XmlValue::CDATA_SECTION_NODE, CONST_CS | CONST_PERSISTENT);
  REGISTER_LONG_CONSTANT( "XmlValue_ENTITY_REFERENCE_NODE", XmlValue::ENTITY_REFERENCE_NODE, CONST_CS | CONST_PERSISTENT);
  REGISTER_LONG_CONSTANT( "XmlValue_ENTITY_NODE", XmlValue::ENTITY_NODE, CONST_CS | CONST_PERSISTENT);
  REGISTER_LONG_CONSTANT( "XmlValue_PROCESSING_INSTRUCTION_NODE", XmlValue::PROCESSING_INSTRUCTION_NODE, CONST_CS | CONST_PERSISTENT);
  REGISTER_LONG_CONSTANT( "XmlValue_COMMENT_NODE", XmlValue::COMMENT_NODE, CONST_CS | CONST_PERSISTENT);
  REGISTER_LONG_CONSTANT( "XmlValue_DOCUMENT_NODE", XmlValue::DOCUMENT_NODE, CONST_CS | CONST_PERSISTENT);
  REGISTER_LONG_CONSTANT( "XmlValue_DOCUMENT_TYPE_NODE", XmlValue::DOCUMENT_TYPE_NODE, CONST_CS | CONST_PERSISTENT);
  REGISTER_LONG_CONSTANT( "XmlValue_DOCUMENT_FRAGMENT_NODE", XmlValue::DOCUMENT_FRAGMENT_NODE, CONST_CS | CONST_PERSISTENT);
  REGISTER_LONG_CONSTANT( "XmlValue_NOTATION_NODE", XmlValue::NOTATION_NODE, CONST_CS | CONST_PERSISTENT);
  REGISTER_LONG_CONSTANT( "XmlValue_NONE", XmlValue::NONE, CONST_CS | CONST_PERSISTENT);
  REGISTER_LONG_CONSTANT( "XmlValue_NODE", XmlValue::NODE, CONST_CS | CONST_PERSISTENT);
  REGISTER_LONG_CONSTANT( "XmlValue_ANY_SIMPLE_TYPE", XmlValue::ANY_SIMPLE_TYPE, CONST_CS | CONST_PERSISTENT);
  REGISTER_LONG_CONSTANT( "XmlValue_ANY_URI", XmlValue::ANY_URI, CONST_CS | CONST_PERSISTENT);
  REGISTER_LONG_CONSTANT( "XmlValue_BASE_64_BINARY", XmlValue::BASE_64_BINARY, CONST_CS | CONST_PERSISTENT);
  REGISTER_LONG_CONSTANT( "XmlValue_BOOLEAN", XmlValue::BOOLEAN, CONST_CS | CONST_PERSISTENT);
  REGISTER_LONG_CONSTANT( "XmlValue_DATE", XmlValue::DATE, CONST_CS | CONST_PERSISTENT);
  REGISTER_LONG_CONSTANT( "XmlValue_DATE_TIME", XmlValue::DATE_TIME, CONST_CS | CONST_PERSISTENT);
  REGISTER_LONG_CONSTANT( "XmlValue_DAY_TIME_DURATION", XmlValue::DAY_TIME_DURATION, CONST_CS | CONST_PERSISTENT);
  REGISTER_LONG_CONSTANT( "XmlValue_DECIMAL", XmlValue::DECIMAL, CONST_CS | CONST_PERSISTENT);
  REGISTER_LONG_CONSTANT( "XmlValue_DOUBLE", XmlValue::DOUBLE, CONST_CS | CONST_PERSISTENT);
  REGISTER_LONG_CONSTANT( "XmlValue_DURATION", XmlValue::DURATION, CONST_CS | CONST_PERSISTENT);
  REGISTER_LONG_CONSTANT( "XmlValue_FLOAT", XmlValue::FLOAT, CONST_CS | CONST_PERSISTENT);
  REGISTER_LONG_CONSTANT( "XmlValue_G_DAY", XmlValue::G_DAY, CONST_CS | CONST_PERSISTENT);
  REGISTER_LONG_CONSTANT( "XmlValue_G_MONTH", XmlValue::G_MONTH, CONST_CS | CONST_PERSISTENT);
  REGISTER_LONG_CONSTANT( "XmlValue_G_MONTH_DAY", XmlValue::G_MONTH_DAY, CONST_CS | CONST_PERSISTENT);
  REGISTER_LONG_CONSTANT( "XmlValue_G_YEAR", XmlValue::G_YEAR, CONST_CS | CONST_PERSISTENT);
  REGISTER_LONG_CONSTANT( "XmlValue_G_YEAR_MONTH", XmlValue::G_YEAR_MONTH, CONST_CS | CONST_PERSISTENT);
  REGISTER_LONG_CONSTANT( "XmlValue_HEX_BINARY", XmlValue::HEX_BINARY, CONST_CS | CONST_PERSISTENT);
  REGISTER_LONG_CONSTANT( "XmlValue_NOTATION", XmlValue::NOTATION, CONST_CS | CONST_PERSISTENT);
  REGISTER_LONG_CONSTANT( "XmlValue_QNAME", XmlValue::QNAME, CONST_CS | CONST_PERSISTENT);
  REGISTER_LONG_CONSTANT( "XmlValue_STRING", XmlValue::STRING, CONST_CS | CONST_PERSISTENT);
  REGISTER_LONG_CONSTANT( "XmlValue_TIME", XmlValue::TIME, CONST_CS | CONST_PERSISTENT);
  REGISTER_LONG_CONSTANT( "XmlValue_YEAR_MONTH_DURATION", XmlValue::YEAR_MONTH_DURATION, CONST_CS | CONST_PERSISTENT);
  REGISTER_LONG_CONSTANT( "XmlValue_UNTYPED_ATOMIC", XmlValue::UNTYPED_ATOMIC, CONST_CS | CONST_PERSISTENT);
  REGISTER_LONG_CONSTANT( "XmlIndexSpecification_UNIQUE_OFF", XmlIndexSpecification::UNIQUE_OFF, CONST_CS | CONST_PERSISTENT);
  REGISTER_LONG_CONSTANT( "XmlIndexSpecification_UNIQUE_ON", XmlIndexSpecification::UNIQUE_ON, CONST_CS | CONST_PERSISTENT);
  REGISTER_LONG_CONSTANT( "XmlIndexSpecification_PATH_NONE", XmlIndexSpecification::PATH_NONE, CONST_CS | CONST_PERSISTENT);
  REGISTER_LONG_CONSTANT( "XmlIndexSpecification_PATH_NODE", XmlIndexSpecification::PATH_NODE, CONST_CS | CONST_PERSISTENT);
  REGISTER_LONG_CONSTANT( "XmlIndexSpecification_PATH_EDGE", XmlIndexSpecification::PATH_EDGE, CONST_CS | CONST_PERSISTENT);
  REGISTER_LONG_CONSTANT( "XmlIndexSpecification_NODE_NONE", XmlIndexSpecification::NODE_NONE, CONST_CS | CONST_PERSISTENT);
  REGISTER_LONG_CONSTANT( "XmlIndexSpecification_NODE_ELEMENT", XmlIndexSpecification::NODE_ELEMENT, CONST_CS | CONST_PERSISTENT);
  REGISTER_LONG_CONSTANT( "XmlIndexSpecification_NODE_ATTRIBUTE", XmlIndexSpecification::NODE_ATTRIBUTE, CONST_CS | CONST_PERSISTENT);
  REGISTER_LONG_CONSTANT( "XmlIndexSpecification_NODE_METADATA", XmlIndexSpecification::NODE_METADATA, CONST_CS | CONST_PERSISTENT);
  REGISTER_LONG_CONSTANT( "XmlIndexSpecification_KEY_NONE", XmlIndexSpecification::KEY_NONE, CONST_CS | CONST_PERSISTENT);
  REGISTER_LONG_CONSTANT( "XmlIndexSpecification_KEY_PRESENCE", XmlIndexSpecification::KEY_PRESENCE, CONST_CS | CONST_PERSISTENT);
  REGISTER_LONG_CONSTANT( "XmlIndexSpecification_KEY_EQUALITY", XmlIndexSpecification::KEY_EQUALITY, CONST_CS | CONST_PERSISTENT);
  REGISTER_LONG_CONSTANT( "XmlIndexSpecification_KEY_SUBSTRING", XmlIndexSpecification::KEY_SUBSTRING, CONST_CS | CONST_PERSISTENT);
  REGISTER_LONG_CONSTANT( "XmlModify_Element", XmlModify::Element, CONST_CS | CONST_PERSISTENT);
  REGISTER_LONG_CONSTANT( "XmlModify_Attribute", XmlModify::Attribute, CONST_CS | CONST_PERSISTENT);
  REGISTER_LONG_CONSTANT( "XmlModify_Text", XmlModify::Text, CONST_CS | CONST_PERSISTENT);
  REGISTER_LONG_CONSTANT( "XmlModify_ProcessingInstruction", XmlModify::ProcessingInstruction, CONST_CS | CONST_PERSISTENT);
  REGISTER_LONG_CONSTANT( "XmlModify_Comment", XmlModify::Comment, CONST_CS | CONST_PERSISTENT);
  REGISTER_LONG_CONSTANT("XmlIndexLookup_NONE", XmlIndexLookup::NONE, CONST_CS | CONST_PERSISTENT);
  REGISTER_LONG_CONSTANT("XmlIndexLookup_EQ", XmlIndexLookup::EQ, CONST_CS | CONST_PERSISTENT);
  REGISTER_LONG_CONSTANT("XmlIndexLookup_GT", XmlIndexLookup::GT, CONST_CS | CONST_PERSISTENT);
  REGISTER_LONG_CONSTANT("XmlIndexLookup_GTE", XmlIndexLookup::GTE, CONST_CS | CONST_PERSISTENT);
  REGISTER_LONG_CONSTANT("XmlIndexLookup_LT", XmlIndexLookup::LT, CONST_CS | CONST_PERSISTENT);
  REGISTER_LONG_CONSTANT("XmlIndexLookup_LTE", XmlIndexLookup::LTE, CONST_CS | CONST_PERSISTENT);

  // validate Berkeley DB library version
  static const int dbMajorMin=4;
  static const int dbMinorMin=3;
  int major, minor, patch;
  (void) db_version(&major, &minor, &patch);
  if (major < dbMajorMin || minor < dbMinorMin) {
	  php_error_docref(NULL TSRMLS_CC, E_ERROR, "your copy Berkeley DB4 is older than required; it must be at least version 4.3");
	  return FAILURE;
  }
  return SUCCESS;
}

PHP_MINFO_FUNCTION(dbxml)
{
  php_info_print_table_start();
  php_info_print_table_header(2, "dbxml support", "enabled");
  php_info_print_table_row(2, "dbxml version", dbxml_version(NULL, NULL, NULL));
  php_info_print_table_end();
}

zend_module_entry dbxml_module_entry = {
  STANDARD_MODULE_HEADER,
  "dbxml",
  dbxml_functions,
  PHP_MINIT(dbxml),
  NULL,
  NULL,
  NULL,
  PHP_MINFO(dbxml),
  "0.1",
  STANDARD_MODULE_PROPERTIES
};

#if COMPILE_DL_DBXML
BEGIN_EXTERN_C()
ZEND_GET_MODULE(dbxml)
END_EXTERN_C()
#endif

