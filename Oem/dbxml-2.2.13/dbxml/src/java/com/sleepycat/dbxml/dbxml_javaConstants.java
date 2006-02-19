/* ----------------------------------------------------------------------------
 * This file was automatically generated by SWIG (http://www.swig.org).
 * Version 1.3.24
 *
 * Do not make changes to this file unless you know what you are doing--modify
 * the SWIG interface file instead.
 * ----------------------------------------------------------------------------- */

package com.sleepycat.dbxml;

public interface dbxml_javaConstants {
  public final static int DBXML_ADOPT_DBENV = 0x00000001;
  public final static int DBXML_ALLOW_EXTERNAL_ACCESS = 0x00000002;
  public final static int DBXML_ALLOW_AUTO_OPEN = 0x00000004;
  public final static int DBXML_ALLOW_VALIDATION = 0x00100000;
  public final static int DBXML_TRANSACTIONAL = 0x00200000;
  public final static int DBXML_REVERSE_ORDER = 0x00100000;
  public final static int DBXML_INDEX_VALUES = 0x00200000;
  public final static int DBXML_CACHE_DOCUMENTS = 0x00400000;
  public final static int DBXML_CHKSUM = 0x00400000;
  public final static int DBXML_ENCRYPT = 0x00800000;
  public final static int DBXML_NO_INDEX_NODES = 0x10000000;
  public final static int DBXML_GEN_NAME = 0x20000000;
  public final static int DBXML_LAZY_DOCS = 0x40000000;
  public final static int DBXML_INDEX_NODES = 0x80000000;

  public final static int LEVEL_NONE = 0x00000000;
  public final static int LEVEL_DEBUG = 0x00000001;
  public final static int LEVEL_INFO = 0x00000002;
  public final static int LEVEL_WARNING = 0x00000004;
  public final static int LEVEL_ERROR = 0x00000008;
  public final static int LEVEL_ALL = 0xFFFFFFFF;

  public final static int CATEGORY_NONE = 0x00000000;
  public final static int CATEGORY_INDEXER = 0x00000001;
  public final static int CATEGORY_QUERY = 0x00000002;
  public final static int CATEGORY_OPTIMIZER = 0x00000004;
  public final static int CATEGORY_DICTIONARY = 0x00000008;
  public final static int CATEGORY_CONTAINER = 0x00000010;
  public final static int CATEGORY_NODESTORE = 0x00000020;
  public final static int CATEGORY_MANAGER = 0x00000040;
  public final static int CATEGORY_ALL = 0xFFFFFFFF;

  public final static String metaDataNamespace_uri = "http://www.sleepycat.com/2002/dbxml";
  public final static String metaDataNamespace_prefix = "dbxml";
  public final static String metaDataName_name = "name";
  public final static String metaDataName_root = "root";
}
