/* ----------------------------------------------------------------------------
 * This file was automatically generated by SWIG (http://www.swig.org).
 * Version 1.3.25
 *
 * Do not make changes to this file unless you know what you are doing--modify
 * the SWIG interface file instead.
 * ----------------------------------------------------------------------------- */


using System;
using System.Runtime.InteropServices;

public class Feature : IDisposable {
  private HandleRef swigCPtr;
  protected bool swigCMemOwn;

  internal Feature(IntPtr cPtr, bool cMemoryOwn) {
    swigCMemOwn = cMemoryOwn;
    swigCPtr = new HandleRef(this, cPtr);
  }

  internal static HandleRef getCPtr(Feature obj) {
    return (obj == null) ? new HandleRef(null, IntPtr.Zero) : obj.swigCPtr;
  }

  public virtual void Dispose() {
    if(swigCPtr.Handle != IntPtr.Zero && swigCMemOwn) {
      swigCMemOwn = false;
      throw new MethodAccessException("C++ destructor does not have public access");
    }
    swigCPtr = new HandleRef(null, IntPtr.Zero);
    GC.SuppressFinalize(this);
  }

  public Feature(FeatureDefn feature_def) : this(ogrPINVOKE.new_Feature(FeatureDefn.getCPtr(feature_def)), true) {
  }

  public void Destroy() {
    ogrPINVOKE.Feature_Destroy(swigCPtr);
  }

  public FeatureDefn GetDefnRef() {
    IntPtr cPtr = ogrPINVOKE.Feature_GetDefnRef(swigCPtr);
    FeatureDefn ret = (cPtr == IntPtr.Zero) ? null : new FeatureDefn(cPtr, false);
    return ret;
  }

  public int SetGeometry(Geometry geom) {
    int ret = ogrPINVOKE.Feature_SetGeometry(swigCPtr, Geometry.getCPtr(geom));
    return ret;
  }

  public int SetGeometryDirectly(Geometry geom) {
    int ret = ogrPINVOKE.Feature_SetGeometryDirectly(swigCPtr, Geometry.getCPtr(geom));
    return ret;
  }

  public Geometry GetGeometryRef() {
    IntPtr cPtr = ogrPINVOKE.Feature_GetGeometryRef(swigCPtr);
    Geometry ret = (cPtr == IntPtr.Zero) ? null : new Geometry(cPtr, false);
    return ret;
  }

  public Feature Clone() {
    IntPtr cPtr = ogrPINVOKE.Feature_Clone(swigCPtr);
    Feature ret = (cPtr == IntPtr.Zero) ? null : new Feature(cPtr, true);
    return ret;
  }

  public int Equal(Feature feature) {
    int ret = ogrPINVOKE.Feature_Equal(swigCPtr, Feature.getCPtr(feature));
    return ret;
  }

  public int GetFieldCount() {
    int ret = ogrPINVOKE.Feature_GetFieldCount(swigCPtr);
    return ret;
  }

  public FieldDefn GetFieldDefnRef(int id) {
    IntPtr cPtr = ogrPINVOKE.Feature_GetFieldDefnRef__SWIG_0(swigCPtr, id);
    FieldDefn ret = (cPtr == IntPtr.Zero) ? null : new FieldDefn(cPtr, true);
    return ret;
  }

  public FieldDefn GetFieldDefnRef(string name) {
    IntPtr cPtr = ogrPINVOKE.Feature_GetFieldDefnRef__SWIG_1(swigCPtr, name);
    FieldDefn ret = (cPtr == IntPtr.Zero) ? null : new FieldDefn(cPtr, true);
    return ret;
  }

  public string GetFieldAsString(int id) {
    string ret = ogrPINVOKE.Feature_GetFieldAsString__SWIG_0(swigCPtr, id);
    return ret;
  }

  public string GetFieldAsString(string name) {
    string ret = ogrPINVOKE.Feature_GetFieldAsString__SWIG_1(swigCPtr, name);
    return ret;
  }

  public int GetFieldAsInteger(int id) {
    int ret = ogrPINVOKE.Feature_GetFieldAsInteger__SWIG_0(swigCPtr, id);
    return ret;
  }

  public int GetFieldAsInteger(string name) {
    int ret = ogrPINVOKE.Feature_GetFieldAsInteger__SWIG_1(swigCPtr, name);
    return ret;
  }

  public double GetFieldAsDouble(int id) {
    double ret = ogrPINVOKE.Feature_GetFieldAsDouble__SWIG_0(swigCPtr, id);
    return ret;
  }

  public double GetFieldAsDouble(string name) {
    double ret = ogrPINVOKE.Feature_GetFieldAsDouble__SWIG_1(swigCPtr, name);
    return ret;
  }

  public int IsFieldSet(int id) {
    int ret = ogrPINVOKE.Feature_IsFieldSet__SWIG_0(swigCPtr, id);
    return ret;
  }

  public int IsFieldSet(string name) {
    int ret = ogrPINVOKE.Feature_IsFieldSet__SWIG_1(swigCPtr, name);
    return ret;
  }

  public int GetFieldIndex(string name) {
    int ret = ogrPINVOKE.Feature_GetFieldIndex(swigCPtr, name);
    return ret;
  }

  public int GetFID() {
    int ret = ogrPINVOKE.Feature_GetFID(swigCPtr);
    return ret;
  }

  public int SetFID(int fid) {
    int ret = ogrPINVOKE.Feature_SetFID(swigCPtr, fid);
    return ret;
  }

  public void DumpReadable() {
    ogrPINVOKE.Feature_DumpReadable(swigCPtr);
  }

  public void UnsetField(int id) {
    ogrPINVOKE.Feature_UnsetField__SWIG_0(swigCPtr, id);
  }

  public void UnsetField(string name) {
    ogrPINVOKE.Feature_UnsetField__SWIG_1(swigCPtr, name);
  }

  public void SetField(int id, string value) {
    ogrPINVOKE.Feature_SetField__SWIG_0(swigCPtr, id, value);
  }

  public void SetField(string name, string value) {
    ogrPINVOKE.Feature_SetField__SWIG_1(swigCPtr, name, value);
  }

  public int SetFrom(Feature other, int forgiving) {
    int ret = ogrPINVOKE.Feature_SetFrom(swigCPtr, Feature.getCPtr(other), forgiving);
    return ret;
  }

  public string GetStyleString() {
    string ret = ogrPINVOKE.Feature_GetStyleString(swigCPtr);
    return ret;
  }

  public void SetStyleString(string the_string) {
    ogrPINVOKE.Feature_SetStyleString(swigCPtr, the_string);
  }

  public int GetFieldType(int id) {
    int ret = ogrPINVOKE.Feature_GetFieldType__SWIG_0(swigCPtr, id);
    return ret;
  }

  public int GetFieldType(string name, string value) {
    int ret = ogrPINVOKE.Feature_GetFieldType__SWIG_1(swigCPtr, name, value);
    return ret;
  }

}
