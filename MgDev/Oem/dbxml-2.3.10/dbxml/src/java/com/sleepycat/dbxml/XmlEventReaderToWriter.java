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

public class XmlEventReaderToWriter {
  private long swigCPtr;
  protected boolean swigCMemOwn;

  protected XmlEventReaderToWriter(long cPtr, boolean cMemoryOwn) {
    swigCMemOwn = cMemoryOwn;
    swigCPtr = cPtr;
  }

  protected static long getCPtr(XmlEventReaderToWriter obj) {
    return (obj == null) ? 0 : obj.swigCPtr;
  }

  protected void finalize() {
    delete();
  }

  public void delete() /* no exception */ {
    if(swigCPtr != 0 && swigCMemOwn) {
      swigCMemOwn = false;
      dbxml_javaJNI.delete_XmlEventReaderToWriter(swigCPtr);
    }
    swigCPtr = 0;
  }

  public XmlEventReaderToWriter(XmlEventReader reader, XmlEventWriter writer, boolean ownsReader) throws XmlException { 
    this(dbxml_javaJNI.new_XmlEventReaderToWriter(XmlEventReader.getCPtr(reader), XmlEventWriter.getCPtr(writer), ownsReader), true);
    writer.delete();
    if (ownsReader)
	reader.delete();
}

  public void start() throws XmlException {
    dbxml_javaJNI.XmlEventReaderToWriter_start(swigCPtr);
  }

}
