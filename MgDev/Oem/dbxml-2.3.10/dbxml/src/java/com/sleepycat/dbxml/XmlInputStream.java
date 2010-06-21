/* ----------------------------------------------------------------------------
 * This file was automatically generated by SWIG (http://www.swig.org).
 * Version 1.3.29
 *
 * Do not make changes to this file unless you know what you are doing--modify
 * the SWIG interface file instead.
 * ----------------------------------------------------------------------------- */

package com.sleepycat.dbxml;

import com.sleepycat.db.*;
import com.sleepycat.db.internal.DbEnv;
import com.sleepycat.db.internal.DbConstants;

public class XmlInputStream {
  private long swigCPtr;
  protected boolean swigCMemOwn;

  protected XmlInputStream(long cPtr, boolean cMemoryOwn) {
    swigCMemOwn = cMemoryOwn;
    swigCPtr = cPtr;
  }

  protected static long getCPtr(XmlInputStream obj) {
    return (obj == null) ? 0 : obj.swigCPtr;
  }

  protected void finalize() {
    delete();
  }

  public void delete() /* no exception */ {
    if(swigCPtr != 0 && swigCMemOwn) {
      swigCMemOwn = false;
      dbxml_javaJNI.delete_XmlInputStream(swigCPtr);
    }
    swigCPtr = 0;
  }

  protected void swigDirectorDisconnect() {
    swigCMemOwn = false;
    delete();
  }

  public void swigReleaseOwnership() throws XmlException {
    swigCMemOwn = false;
    dbxml_javaJNI.XmlInputStream_change_ownership(this, swigCPtr, false);
  }

  public void swigTakeOwnership() throws XmlException {
    swigCMemOwn = true;
    dbxml_javaJNI.XmlInputStream_change_ownership(this, swigCPtr, true);
  }

  protected XmlInputStream() {
    this(dbxml_javaJNI.new_XmlInputStream(), true);
    dbxml_javaJNI.XmlInputStream_director_connect(this, swigCPtr, swigCMemOwn, true);
  }

  public long curPos() throws XmlException {
    return dbxml_javaJNI.XmlInputStream_curPos(swigCPtr);
  }

  public long readBytes(byte[] toFill, long maxToRead) throws XmlException {
    return dbxml_javaJNI.XmlInputStream_readBytes(swigCPtr, toFill, maxToRead);
  }

  public void freeMemory() throws XmlException {
    dbxml_javaJNI.XmlInputStream_freeMemory(swigCPtr);
  }

}
