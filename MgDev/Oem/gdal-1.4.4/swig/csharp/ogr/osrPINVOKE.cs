/* ----------------------------------------------------------------------------
 * This file was automatically generated by SWIG (http://www.swig.org).
 * Version 1.3.31
 *
 * Do not make changes to this file unless you know what you are doing--modify
 * the SWIG interface file instead.
 * ----------------------------------------------------------------------------- */

namespace OSGeo.OGR {

using System;
using System.Runtime.InteropServices;

class osrPINVOKE {

  protected class SWIGExceptionHelper {

    public delegate void ExceptionDelegate(string message);
    public delegate void ExceptionArgumentDelegate(string message, string paramName);

    static ExceptionDelegate applicationDelegate = new ExceptionDelegate(SetPendingApplicationException);
    static ExceptionDelegate arithmeticDelegate = new ExceptionDelegate(SetPendingArithmeticException);
    static ExceptionDelegate divideByZeroDelegate = new ExceptionDelegate(SetPendingDivideByZeroException);
    static ExceptionDelegate indexOutOfRangeDelegate = new ExceptionDelegate(SetPendingIndexOutOfRangeException);
    static ExceptionDelegate invalidCastDelegate = new ExceptionDelegate(SetPendingInvalidCastException);
    static ExceptionDelegate invalidOperationDelegate = new ExceptionDelegate(SetPendingInvalidOperationException);
    static ExceptionDelegate ioDelegate = new ExceptionDelegate(SetPendingIOException);
    static ExceptionDelegate nullReferenceDelegate = new ExceptionDelegate(SetPendingNullReferenceException);
    static ExceptionDelegate outOfMemoryDelegate = new ExceptionDelegate(SetPendingOutOfMemoryException);
    static ExceptionDelegate overflowDelegate = new ExceptionDelegate(SetPendingOverflowException);
    static ExceptionDelegate systemDelegate = new ExceptionDelegate(SetPendingSystemException);

    static ExceptionArgumentDelegate argumentDelegate = new ExceptionArgumentDelegate(SetPendingArgumentException);
    static ExceptionArgumentDelegate argumentNullDelegate = new ExceptionArgumentDelegate(SetPendingArgumentNullException);
    static ExceptionArgumentDelegate argumentOutOfRangeDelegate = new ExceptionArgumentDelegate(SetPendingArgumentOutOfRangeException);

    [DllImport("osr_wrap", EntryPoint="SWIGRegisterExceptionCallbacks_osr")]
    public static extern void SWIGRegisterExceptionCallbacks_osr(
                                ExceptionDelegate applicationDelegate,
                                ExceptionDelegate arithmeticDelegate,
                                ExceptionDelegate divideByZeroDelegate, 
                                ExceptionDelegate indexOutOfRangeDelegate, 
                                ExceptionDelegate invalidCastDelegate,
                                ExceptionDelegate invalidOperationDelegate,
                                ExceptionDelegate ioDelegate,
                                ExceptionDelegate nullReferenceDelegate,
                                ExceptionDelegate outOfMemoryDelegate, 
                                ExceptionDelegate overflowDelegate, 
                                ExceptionDelegate systemExceptionDelegate);

    [DllImport("osr_wrap", EntryPoint="SWIGRegisterExceptionArgumentCallbacks_osr")]
    public static extern void SWIGRegisterExceptionCallbacksArgument_osr(
                                ExceptionArgumentDelegate argumentDelegate,
                                ExceptionArgumentDelegate argumentNullDelegate,
                                ExceptionArgumentDelegate argumentOutOfRangeDelegate);

    static void SetPendingApplicationException(string message) {
      SWIGPendingException.Set(new System.ApplicationException(message, SWIGPendingException.Retrieve()));
    }
    static void SetPendingArithmeticException(string message) {
      SWIGPendingException.Set(new System.ArithmeticException(message, SWIGPendingException.Retrieve()));
    }
    static void SetPendingDivideByZeroException(string message) {
      SWIGPendingException.Set(new System.DivideByZeroException(message, SWIGPendingException.Retrieve()));
    }
    static void SetPendingIndexOutOfRangeException(string message) {
      SWIGPendingException.Set(new System.IndexOutOfRangeException(message, SWIGPendingException.Retrieve()));
    }
    static void SetPendingInvalidCastException(string message) {
      SWIGPendingException.Set(new System.InvalidCastException(message, SWIGPendingException.Retrieve()));
    }
    static void SetPendingInvalidOperationException(string message) {
      SWIGPendingException.Set(new System.InvalidOperationException(message, SWIGPendingException.Retrieve()));
    }
    static void SetPendingIOException(string message) {
      SWIGPendingException.Set(new System.IO.IOException(message, SWIGPendingException.Retrieve()));
    }
    static void SetPendingNullReferenceException(string message) {
      SWIGPendingException.Set(new System.NullReferenceException(message, SWIGPendingException.Retrieve()));
    }
    static void SetPendingOutOfMemoryException(string message) {
      SWIGPendingException.Set(new System.OutOfMemoryException(message, SWIGPendingException.Retrieve()));
    }
    static void SetPendingOverflowException(string message) {
      SWIGPendingException.Set(new System.OverflowException(message, SWIGPendingException.Retrieve()));
    }
    static void SetPendingSystemException(string message) {
      SWIGPendingException.Set(new System.SystemException(message, SWIGPendingException.Retrieve()));
    }

    static void SetPendingArgumentException(string message, string paramName) {
      SWIGPendingException.Set(new System.ArgumentException(message, paramName, SWIGPendingException.Retrieve()));
    }
    static void SetPendingArgumentNullException(string message, string paramName) {
      Exception e = SWIGPendingException.Retrieve();
      if (e != null) message = message + " Inner Exception: " + e.Message;
      SWIGPendingException.Set(new System.ArgumentNullException(paramName, message));
    }
    static void SetPendingArgumentOutOfRangeException(string message, string paramName) {
      Exception e = SWIGPendingException.Retrieve();
      if (e != null) message = message + " Inner Exception: " + e.Message;
      SWIGPendingException.Set(new System.ArgumentOutOfRangeException(paramName, message));
    }

    static SWIGExceptionHelper() {
      SWIGRegisterExceptionCallbacks_osr(
                                applicationDelegate,
                                arithmeticDelegate,
                                divideByZeroDelegate,
                                indexOutOfRangeDelegate,
                                invalidCastDelegate,
                                invalidOperationDelegate,
                                ioDelegate,
                                nullReferenceDelegate,
                                outOfMemoryDelegate,
                                overflowDelegate,
                                systemDelegate);

      SWIGRegisterExceptionCallbacksArgument_osr(
                                argumentDelegate,
                                argumentNullDelegate,
                                argumentOutOfRangeDelegate);
    }
  }

  protected static SWIGExceptionHelper swigExceptionHelper = new SWIGExceptionHelper();

  public class SWIGPendingException {
    [ThreadStatic]
    private static Exception pendingException = null;
    private static int numExceptionsPending = 0;

    public static bool Pending {
      get {
        bool pending = false;
        if (numExceptionsPending > 0)
          if (pendingException != null)
            pending = true;
        return pending;
      } 
    }

    public static void Set(Exception e) {
      if (pendingException != null)
        throw new ApplicationException("FATAL: An earlier pending exception from unmanaged code was missed and thus not thrown (" + pendingException.ToString() + ")", e);
      pendingException = e;
      lock(typeof(osrPINVOKE)) {
        numExceptionsPending++;
      }
    }

    public static Exception Retrieve() {
      Exception e = null;
      if (numExceptionsPending > 0) {
        if (pendingException != null) {
          e = pendingException;
          pendingException = null;
          lock(typeof(osrPINVOKE)) {
            numExceptionsPending--;
          }
        }
      }
      return e;
    }
  }


  protected class SWIGStringHelper {

    public delegate string SWIGStringDelegate(string message);
    static SWIGStringDelegate stringDelegate = new SWIGStringDelegate(CreateString);

    [DllImport("osr_wrap", EntryPoint="SWIGRegisterStringCallback_osr")]
    public static extern void SWIGRegisterStringCallback_osr(SWIGStringDelegate stringDelegate);

    static string CreateString(string cString) {
      return cString;
    }

    static SWIGStringHelper() {
      SWIGRegisterStringCallback_osr(stringDelegate);
    }
  }

  static protected SWIGStringHelper swigStringHelper = new SWIGStringHelper();


  [DllImport("osr_wrap", EntryPoint="CSharp_SRS_PT_ALBERS_CONIC_EQUAL_AREA_get")]
  public static extern string SRS_PT_ALBERS_CONIC_EQUAL_AREA_get();

  [DllImport("osr_wrap", EntryPoint="CSharp_SRS_PT_AZIMUTHAL_EQUIDISTANT_get")]
  public static extern string SRS_PT_AZIMUTHAL_EQUIDISTANT_get();

  [DllImport("osr_wrap", EntryPoint="CSharp_SRS_PT_CASSINI_SOLDNER_get")]
  public static extern string SRS_PT_CASSINI_SOLDNER_get();

  [DllImport("osr_wrap", EntryPoint="CSharp_SRS_PT_CYLINDRICAL_EQUAL_AREA_get")]
  public static extern string SRS_PT_CYLINDRICAL_EQUAL_AREA_get();

  [DllImport("osr_wrap", EntryPoint="CSharp_SRS_PT_ECKERT_IV_get")]
  public static extern string SRS_PT_ECKERT_IV_get();

  [DllImport("osr_wrap", EntryPoint="CSharp_SRS_PT_ECKERT_VI_get")]
  public static extern string SRS_PT_ECKERT_VI_get();

  [DllImport("osr_wrap", EntryPoint="CSharp_SRS_PT_EQUIDISTANT_CONIC_get")]
  public static extern string SRS_PT_EQUIDISTANT_CONIC_get();

  [DllImport("osr_wrap", EntryPoint="CSharp_SRS_PT_EQUIRECTANGULAR_get")]
  public static extern string SRS_PT_EQUIRECTANGULAR_get();

  [DllImport("osr_wrap", EntryPoint="CSharp_SRS_PT_GALL_STEREOGRAPHIC_get")]
  public static extern string SRS_PT_GALL_STEREOGRAPHIC_get();

  [DllImport("osr_wrap", EntryPoint="CSharp_SRS_PT_GNOMONIC_get")]
  public static extern string SRS_PT_GNOMONIC_get();

  [DllImport("osr_wrap", EntryPoint="CSharp_SRS_PT_GOODE_HOMOLOSINE_get")]
  public static extern string SRS_PT_GOODE_HOMOLOSINE_get();

  [DllImport("osr_wrap", EntryPoint="CSharp_SRS_PT_HOTINE_OBLIQUE_MERCATOR_get")]
  public static extern string SRS_PT_HOTINE_OBLIQUE_MERCATOR_get();

  [DllImport("osr_wrap", EntryPoint="CSharp_SRS_PT_HOTINE_OBLIQUE_MERCATOR_TWO_POINT_NATURAL_ORIGIN_get")]
  public static extern string SRS_PT_HOTINE_OBLIQUE_MERCATOR_TWO_POINT_NATURAL_ORIGIN_get();

  [DllImport("osr_wrap", EntryPoint="CSharp_SRS_PT_LABORDE_OBLIQUE_MERCATOR_get")]
  public static extern string SRS_PT_LABORDE_OBLIQUE_MERCATOR_get();

  [DllImport("osr_wrap", EntryPoint="CSharp_SRS_PT_LAMBERT_CONFORMAL_CONIC_1SP_get")]
  public static extern string SRS_PT_LAMBERT_CONFORMAL_CONIC_1SP_get();

  [DllImport("osr_wrap", EntryPoint="CSharp_SRS_PT_LAMBERT_CONFORMAL_CONIC_2SP_get")]
  public static extern string SRS_PT_LAMBERT_CONFORMAL_CONIC_2SP_get();

  [DllImport("osr_wrap", EntryPoint="CSharp_SRS_PT_LAMBERT_CONFORMAL_CONIC_2SP_BELGIUM_get")]
  public static extern string SRS_PT_LAMBERT_CONFORMAL_CONIC_2SP_BELGIUM_get();

  [DllImport("osr_wrap", EntryPoint="CSharp_SRS_PT_LAMBERT_AZIMUTHAL_EQUAL_AREA_get")]
  public static extern string SRS_PT_LAMBERT_AZIMUTHAL_EQUAL_AREA_get();

  [DllImport("osr_wrap", EntryPoint="CSharp_SRS_PT_MERCATOR_1SP_get")]
  public static extern string SRS_PT_MERCATOR_1SP_get();

  [DllImport("osr_wrap", EntryPoint="CSharp_SRS_PT_MERCATOR_2SP_get")]
  public static extern string SRS_PT_MERCATOR_2SP_get();

  [DllImport("osr_wrap", EntryPoint="CSharp_SRS_PT_MILLER_CYLINDRICAL_get")]
  public static extern string SRS_PT_MILLER_CYLINDRICAL_get();

  [DllImport("osr_wrap", EntryPoint="CSharp_SRS_PT_MOLLWEIDE_get")]
  public static extern string SRS_PT_MOLLWEIDE_get();

  [DllImport("osr_wrap", EntryPoint="CSharp_SRS_PT_NEW_ZEALAND_MAP_GRID_get")]
  public static extern string SRS_PT_NEW_ZEALAND_MAP_GRID_get();

  [DllImport("osr_wrap", EntryPoint="CSharp_SRS_PT_OBLIQUE_STEREOGRAPHIC_get")]
  public static extern string SRS_PT_OBLIQUE_STEREOGRAPHIC_get();

  [DllImport("osr_wrap", EntryPoint="CSharp_SRS_PT_ORTHOGRAPHIC_get")]
  public static extern string SRS_PT_ORTHOGRAPHIC_get();

  [DllImport("osr_wrap", EntryPoint="CSharp_SRS_PT_POLAR_STEREOGRAPHIC_get")]
  public static extern string SRS_PT_POLAR_STEREOGRAPHIC_get();

  [DllImport("osr_wrap", EntryPoint="CSharp_SRS_PT_POLYCONIC_get")]
  public static extern string SRS_PT_POLYCONIC_get();

  [DllImport("osr_wrap", EntryPoint="CSharp_SRS_PT_ROBINSON_get")]
  public static extern string SRS_PT_ROBINSON_get();

  [DllImport("osr_wrap", EntryPoint="CSharp_SRS_PT_SINUSOIDAL_get")]
  public static extern string SRS_PT_SINUSOIDAL_get();

  [DllImport("osr_wrap", EntryPoint="CSharp_SRS_PT_STEREOGRAPHIC_get")]
  public static extern string SRS_PT_STEREOGRAPHIC_get();

  [DllImport("osr_wrap", EntryPoint="CSharp_SRS_PT_SWISS_OBLIQUE_CYLINDRICAL_get")]
  public static extern string SRS_PT_SWISS_OBLIQUE_CYLINDRICAL_get();

  [DllImport("osr_wrap", EntryPoint="CSharp_SRS_PT_TRANSVERSE_MERCATOR_get")]
  public static extern string SRS_PT_TRANSVERSE_MERCATOR_get();

  [DllImport("osr_wrap", EntryPoint="CSharp_SRS_PT_TRANSVERSE_MERCATOR_SOUTH_ORIENTED_get")]
  public static extern string SRS_PT_TRANSVERSE_MERCATOR_SOUTH_ORIENTED_get();

  [DllImport("osr_wrap", EntryPoint="CSharp_SRS_PT_TRANSVERSE_MERCATOR_MI_22_get")]
  public static extern string SRS_PT_TRANSVERSE_MERCATOR_MI_22_get();

  [DllImport("osr_wrap", EntryPoint="CSharp_SRS_PT_TRANSVERSE_MERCATOR_MI_23_get")]
  public static extern string SRS_PT_TRANSVERSE_MERCATOR_MI_23_get();

  [DllImport("osr_wrap", EntryPoint="CSharp_SRS_PT_TRANSVERSE_MERCATOR_MI_24_get")]
  public static extern string SRS_PT_TRANSVERSE_MERCATOR_MI_24_get();

  [DllImport("osr_wrap", EntryPoint="CSharp_SRS_PT_TRANSVERSE_MERCATOR_MI_25_get")]
  public static extern string SRS_PT_TRANSVERSE_MERCATOR_MI_25_get();

  [DllImport("osr_wrap", EntryPoint="CSharp_SRS_PT_TUNISIA_MINING_GRID_get")]
  public static extern string SRS_PT_TUNISIA_MINING_GRID_get();

  [DllImport("osr_wrap", EntryPoint="CSharp_SRS_PT_VANDERGRINTEN_get")]
  public static extern string SRS_PT_VANDERGRINTEN_get();

  [DllImport("osr_wrap", EntryPoint="CSharp_SRS_PT_KROVAK_get")]
  public static extern string SRS_PT_KROVAK_get();

  [DllImport("osr_wrap", EntryPoint="CSharp_SRS_PP_CENTRAL_MERIDIAN_get")]
  public static extern string SRS_PP_CENTRAL_MERIDIAN_get();

  [DllImport("osr_wrap", EntryPoint="CSharp_SRS_PP_SCALE_FACTOR_get")]
  public static extern string SRS_PP_SCALE_FACTOR_get();

  [DllImport("osr_wrap", EntryPoint="CSharp_SRS_PP_STANDARD_PARALLEL_1_get")]
  public static extern string SRS_PP_STANDARD_PARALLEL_1_get();

  [DllImport("osr_wrap", EntryPoint="CSharp_SRS_PP_STANDARD_PARALLEL_2_get")]
  public static extern string SRS_PP_STANDARD_PARALLEL_2_get();

  [DllImport("osr_wrap", EntryPoint="CSharp_SRS_PP_PSEUDO_STD_PARALLEL_1_get")]
  public static extern string SRS_PP_PSEUDO_STD_PARALLEL_1_get();

  [DllImport("osr_wrap", EntryPoint="CSharp_SRS_PP_LONGITUDE_OF_CENTER_get")]
  public static extern string SRS_PP_LONGITUDE_OF_CENTER_get();

  [DllImport("osr_wrap", EntryPoint="CSharp_SRS_PP_LATITUDE_OF_CENTER_get")]
  public static extern string SRS_PP_LATITUDE_OF_CENTER_get();

  [DllImport("osr_wrap", EntryPoint="CSharp_SRS_PP_LONGITUDE_OF_ORIGIN_get")]
  public static extern string SRS_PP_LONGITUDE_OF_ORIGIN_get();

  [DllImport("osr_wrap", EntryPoint="CSharp_SRS_PP_LATITUDE_OF_ORIGIN_get")]
  public static extern string SRS_PP_LATITUDE_OF_ORIGIN_get();

  [DllImport("osr_wrap", EntryPoint="CSharp_SRS_PP_FALSE_EASTING_get")]
  public static extern string SRS_PP_FALSE_EASTING_get();

  [DllImport("osr_wrap", EntryPoint="CSharp_SRS_PP_FALSE_NORTHING_get")]
  public static extern string SRS_PP_FALSE_NORTHING_get();

  [DllImport("osr_wrap", EntryPoint="CSharp_SRS_PP_AZIMUTH_get")]
  public static extern string SRS_PP_AZIMUTH_get();

  [DllImport("osr_wrap", EntryPoint="CSharp_SRS_PP_LONGITUDE_OF_POINT_1_get")]
  public static extern string SRS_PP_LONGITUDE_OF_POINT_1_get();

  [DllImport("osr_wrap", EntryPoint="CSharp_SRS_PP_LATITUDE_OF_POINT_1_get")]
  public static extern string SRS_PP_LATITUDE_OF_POINT_1_get();

  [DllImport("osr_wrap", EntryPoint="CSharp_SRS_PP_LONGITUDE_OF_POINT_2_get")]
  public static extern string SRS_PP_LONGITUDE_OF_POINT_2_get();

  [DllImport("osr_wrap", EntryPoint="CSharp_SRS_PP_LATITUDE_OF_POINT_2_get")]
  public static extern string SRS_PP_LATITUDE_OF_POINT_2_get();

  [DllImport("osr_wrap", EntryPoint="CSharp_SRS_PP_LONGITUDE_OF_POINT_3_get")]
  public static extern string SRS_PP_LONGITUDE_OF_POINT_3_get();

  [DllImport("osr_wrap", EntryPoint="CSharp_SRS_PP_LATITUDE_OF_POINT_3_get")]
  public static extern string SRS_PP_LATITUDE_OF_POINT_3_get();

  [DllImport("osr_wrap", EntryPoint="CSharp_SRS_PP_RECTIFIED_GRID_ANGLE_get")]
  public static extern string SRS_PP_RECTIFIED_GRID_ANGLE_get();

  [DllImport("osr_wrap", EntryPoint="CSharp_SRS_PP_LANDSAT_NUMBER_get")]
  public static extern string SRS_PP_LANDSAT_NUMBER_get();

  [DllImport("osr_wrap", EntryPoint="CSharp_SRS_PP_PATH_NUMBER_get")]
  public static extern string SRS_PP_PATH_NUMBER_get();

  [DllImport("osr_wrap", EntryPoint="CSharp_SRS_PP_PERSPECTIVE_POINT_HEIGHT_get")]
  public static extern string SRS_PP_PERSPECTIVE_POINT_HEIGHT_get();

  [DllImport("osr_wrap", EntryPoint="CSharp_SRS_PP_FIPSZONE_get")]
  public static extern string SRS_PP_FIPSZONE_get();

  [DllImport("osr_wrap", EntryPoint="CSharp_SRS_PP_ZONE_get")]
  public static extern string SRS_PP_ZONE_get();

  [DllImport("osr_wrap", EntryPoint="CSharp_SRS_UL_METER_get")]
  public static extern string SRS_UL_METER_get();

  [DllImport("osr_wrap", EntryPoint="CSharp_SRS_UL_FOOT_get")]
  public static extern string SRS_UL_FOOT_get();

  [DllImport("osr_wrap", EntryPoint="CSharp_SRS_UL_FOOT_CONV_get")]
  public static extern string SRS_UL_FOOT_CONV_get();

  [DllImport("osr_wrap", EntryPoint="CSharp_SRS_UL_US_FOOT_get")]
  public static extern string SRS_UL_US_FOOT_get();

  [DllImport("osr_wrap", EntryPoint="CSharp_SRS_UL_US_FOOT_CONV_get")]
  public static extern string SRS_UL_US_FOOT_CONV_get();

  [DllImport("osr_wrap", EntryPoint="CSharp_SRS_UL_NAUTICAL_MILE_get")]
  public static extern string SRS_UL_NAUTICAL_MILE_get();

  [DllImport("osr_wrap", EntryPoint="CSharp_SRS_UL_NAUTICAL_MILE_CONV_get")]
  public static extern string SRS_UL_NAUTICAL_MILE_CONV_get();

  [DllImport("osr_wrap", EntryPoint="CSharp_SRS_UL_LINK_get")]
  public static extern string SRS_UL_LINK_get();

  [DllImport("osr_wrap", EntryPoint="CSharp_SRS_UL_LINK_CONV_get")]
  public static extern string SRS_UL_LINK_CONV_get();

  [DllImport("osr_wrap", EntryPoint="CSharp_SRS_UL_CHAIN_get")]
  public static extern string SRS_UL_CHAIN_get();

  [DllImport("osr_wrap", EntryPoint="CSharp_SRS_UL_CHAIN_CONV_get")]
  public static extern string SRS_UL_CHAIN_CONV_get();

  [DllImport("osr_wrap", EntryPoint="CSharp_SRS_UL_ROD_get")]
  public static extern string SRS_UL_ROD_get();

  [DllImport("osr_wrap", EntryPoint="CSharp_SRS_UL_ROD_CONV_get")]
  public static extern string SRS_UL_ROD_CONV_get();

  [DllImport("osr_wrap", EntryPoint="CSharp_SRS_DN_NAD27_get")]
  public static extern string SRS_DN_NAD27_get();

  [DllImport("osr_wrap", EntryPoint="CSharp_SRS_DN_NAD83_get")]
  public static extern string SRS_DN_NAD83_get();

  [DllImport("osr_wrap", EntryPoint="CSharp_SRS_DN_WGS72_get")]
  public static extern string SRS_DN_WGS72_get();

  [DllImport("osr_wrap", EntryPoint="CSharp_SRS_DN_WGS84_get")]
  public static extern string SRS_DN_WGS84_get();

  [DllImport("osr_wrap", EntryPoint="CSharp_SRS_WGS84_SEMIMAJOR_get")]
  public static extern double SRS_WGS84_SEMIMAJOR_get();

  [DllImport("osr_wrap", EntryPoint="CSharp_SRS_WGS84_INVFLATTENING_get")]
  public static extern double SRS_WGS84_INVFLATTENING_get();

  [DllImport("osr_wrap", EntryPoint="CSharp_UseExceptions")]
  public static extern void UseExceptions();

  [DllImport("osr_wrap", EntryPoint="CSharp_DontUseExceptions")]
  public static extern void DontUseExceptions();

  public class StringListMarshal : IDisposable {
    public readonly IntPtr[] _ar;
    public StringListMarshal(string[] ar) {
      _ar = new IntPtr[ar.Length+1];
      for (int cx = 0; cx < ar.Length; cx++) {
	      _ar[cx] = System.Runtime.InteropServices.Marshal.StringToHGlobalAnsi(ar[cx]);
      }
      _ar[ar.Length] = IntPtr.Zero;
    }
    public virtual void Dispose() {
	  for (int cx = 0; cx < _ar.Length-1; cx++) {
          System.Runtime.InteropServices.Marshal.FreeHGlobal(_ar[cx]);
      }
      GC.SuppressFinalize(this);
    }
  }


  [DllImport("osr_wrap", EntryPoint="CSharp_GetWellKnownGeogCSAsWKT")]
  public static extern int GetWellKnownGeogCSAsWKT(string jarg1, out string jarg2);

  [DllImport("osr_wrap", EntryPoint="CSharp_GetUserInputAsWKT")]
  public static extern int GetUserInputAsWKT(string jarg1, out string jarg2);

  [DllImport("osr_wrap", EntryPoint="CSharp_GetProjectionMethods")]
  public static extern IntPtr GetProjectionMethods();

  [DllImport("osr_wrap", EntryPoint="CSharp_GetProjectionMethodParameterList")]
  public static extern IntPtr GetProjectionMethodParameterList(string jarg1, out string jarg2);

  [DllImport("osr_wrap", EntryPoint="CSharp_GetProjectionMethodParamInfo")]
  public static extern void GetProjectionMethodParamInfo(string jarg1, string jarg2, out string jarg3, out string jarg4, ref double jarg5);

  [DllImport("osr_wrap", EntryPoint="CSharp_new_SpatialReference")]
  public static extern IntPtr new_SpatialReference(string jarg1);

  [DllImport("osr_wrap", EntryPoint="CSharp_delete_SpatialReference")]
  public static extern void delete_SpatialReference(HandleRef jarg1);

  [DllImport("osr_wrap", EntryPoint="CSharp_SpatialReference___str__")]
  public static extern string SpatialReference___str__(HandleRef jarg1);

  [DllImport("osr_wrap", EntryPoint="CSharp_SpatialReference_IsSame")]
  public static extern int SpatialReference_IsSame(HandleRef jarg1, HandleRef jarg2);

  [DllImport("osr_wrap", EntryPoint="CSharp_SpatialReference_IsSameGeogCS")]
  public static extern int SpatialReference_IsSameGeogCS(HandleRef jarg1, HandleRef jarg2);

  [DllImport("osr_wrap", EntryPoint="CSharp_SpatialReference_IsGeographic")]
  public static extern int SpatialReference_IsGeographic(HandleRef jarg1);

  [DllImport("osr_wrap", EntryPoint="CSharp_SpatialReference_IsProjected")]
  public static extern int SpatialReference_IsProjected(HandleRef jarg1);

  [DllImport("osr_wrap", EntryPoint="CSharp_SpatialReference_IsLocal")]
  public static extern int SpatialReference_IsLocal(HandleRef jarg1);

  [DllImport("osr_wrap", EntryPoint="CSharp_SpatialReference_GetAttrValue")]
  public static extern string SpatialReference_GetAttrValue(HandleRef jarg1, string jarg2, int jarg3);

  [DllImport("osr_wrap", EntryPoint="CSharp_SpatialReference_SetAttrValue")]
  public static extern int SpatialReference_SetAttrValue(HandleRef jarg1, string jarg2, string jarg3);

  [DllImport("osr_wrap", EntryPoint="CSharp_SpatialReference_SetAngularUnits")]
  public static extern int SpatialReference_SetAngularUnits(HandleRef jarg1, string jarg2, double jarg3);

  [DllImport("osr_wrap", EntryPoint="CSharp_SpatialReference_GetAngularUnits")]
  public static extern double SpatialReference_GetAngularUnits(HandleRef jarg1);

  [DllImport("osr_wrap", EntryPoint="CSharp_SpatialReference_SetLinearUnits")]
  public static extern int SpatialReference_SetLinearUnits(HandleRef jarg1, string jarg2, double jarg3);

  [DllImport("osr_wrap", EntryPoint="CSharp_SpatialReference_GetLinearUnits")]
  public static extern double SpatialReference_GetLinearUnits(HandleRef jarg1);

  [DllImport("osr_wrap", EntryPoint="CSharp_SpatialReference_GetLinearUnitsName")]
  public static extern string SpatialReference_GetLinearUnitsName(HandleRef jarg1);

  [DllImport("osr_wrap", EntryPoint="CSharp_SpatialReference_GetAuthorityCode")]
  public static extern string SpatialReference_GetAuthorityCode(HandleRef jarg1, string jarg2);

  [DllImport("osr_wrap", EntryPoint="CSharp_SpatialReference_GetAuthorityName")]
  public static extern string SpatialReference_GetAuthorityName(HandleRef jarg1, string jarg2);

  [DllImport("osr_wrap", EntryPoint="CSharp_SpatialReference_SetUTM")]
  public static extern int SpatialReference_SetUTM(HandleRef jarg1, int jarg2, int jarg3);

  [DllImport("osr_wrap", EntryPoint="CSharp_SpatialReference_SetStatePlane")]
  public static extern int SpatialReference_SetStatePlane(HandleRef jarg1, int jarg2, int jarg3, string jarg4, double jarg5);

  [DllImport("osr_wrap", EntryPoint="CSharp_SpatialReference_AutoIdentifyEPSG")]
  public static extern int SpatialReference_AutoIdentifyEPSG(HandleRef jarg1);

  [DllImport("osr_wrap", EntryPoint="CSharp_SpatialReference_SetProjection")]
  public static extern int SpatialReference_SetProjection(HandleRef jarg1, string jarg2);

  [DllImport("osr_wrap", EntryPoint="CSharp_SpatialReference_SetProjParm")]
  public static extern int SpatialReference_SetProjParm(HandleRef jarg1, string jarg2, double jarg3);

  [DllImport("osr_wrap", EntryPoint="CSharp_SpatialReference_GetProjParm")]
  public static extern double SpatialReference_GetProjParm(HandleRef jarg1, string jarg2, double jarg3);

  [DllImport("osr_wrap", EntryPoint="CSharp_SpatialReference_SetNormProjParm")]
  public static extern int SpatialReference_SetNormProjParm(HandleRef jarg1, string jarg2, double jarg3);

  [DllImport("osr_wrap", EntryPoint="CSharp_SpatialReference_GetNormProjParm")]
  public static extern double SpatialReference_GetNormProjParm(HandleRef jarg1, string jarg2, double jarg3);

  [DllImport("osr_wrap", EntryPoint="CSharp_SpatialReference_SetACEA")]
  public static extern int SpatialReference_SetACEA(HandleRef jarg1, double jarg2, double jarg3, double jarg4, double jarg5, double jarg6, double jarg7);

  [DllImport("osr_wrap", EntryPoint="CSharp_SpatialReference_SetAE")]
  public static extern int SpatialReference_SetAE(HandleRef jarg1, double jarg2, double jarg3, double jarg4, double jarg5);

  [DllImport("osr_wrap", EntryPoint="CSharp_SpatialReference_SetCS")]
  public static extern int SpatialReference_SetCS(HandleRef jarg1, double jarg2, double jarg3, double jarg4, double jarg5);

  [DllImport("osr_wrap", EntryPoint="CSharp_SpatialReference_SetBonne")]
  public static extern int SpatialReference_SetBonne(HandleRef jarg1, double jarg2, double jarg3, double jarg4, double jarg5);

  [DllImport("osr_wrap", EntryPoint="CSharp_SpatialReference_SetEC")]
  public static extern int SpatialReference_SetEC(HandleRef jarg1, double jarg2, double jarg3, double jarg4, double jarg5, double jarg6, double jarg7);

  [DllImport("osr_wrap", EntryPoint="CSharp_SpatialReference_SetEckertIV")]
  public static extern int SpatialReference_SetEckertIV(HandleRef jarg1, double jarg2, double jarg3, double jarg4);

  [DllImport("osr_wrap", EntryPoint="CSharp_SpatialReference_SetEckertVI")]
  public static extern int SpatialReference_SetEckertVI(HandleRef jarg1, double jarg2, double jarg3, double jarg4);

  [DllImport("osr_wrap", EntryPoint="CSharp_SpatialReference_SetEquirectangular")]
  public static extern int SpatialReference_SetEquirectangular(HandleRef jarg1, double jarg2, double jarg3, double jarg4, double jarg5);

  [DllImport("osr_wrap", EntryPoint="CSharp_SpatialReference_SetGS")]
  public static extern int SpatialReference_SetGS(HandleRef jarg1, double jarg2, double jarg3, double jarg4);

  [DllImport("osr_wrap", EntryPoint="CSharp_SpatialReference_SetWellKnownGeogCS")]
  public static extern int SpatialReference_SetWellKnownGeogCS(HandleRef jarg1, string jarg2);

  [DllImport("osr_wrap", EntryPoint="CSharp_SpatialReference_SetFromUserInput")]
  public static extern int SpatialReference_SetFromUserInput(HandleRef jarg1, string jarg2);

  [DllImport("osr_wrap", EntryPoint="CSharp_SpatialReference_CopyGeogCSFrom")]
  public static extern int SpatialReference_CopyGeogCSFrom(HandleRef jarg1, HandleRef jarg2);

  [DllImport("osr_wrap", EntryPoint="CSharp_SpatialReference_SetTOWGS84")]
  public static extern int SpatialReference_SetTOWGS84(HandleRef jarg1, double jarg2, double jarg3, double jarg4, double jarg5, double jarg6, double jarg7, double jarg8);

  [DllImport("osr_wrap", EntryPoint="CSharp_SpatialReference_GetTOWGS84")]
  public static extern int SpatialReference_GetTOWGS84(HandleRef jarg1, double[] jarg2);

  [DllImport("osr_wrap", EntryPoint="CSharp_SpatialReference_SetGeogCS")]
  public static extern int SpatialReference_SetGeogCS(HandleRef jarg1, string jarg2, string jarg3, string jarg4, double jarg5, double jarg6, string jarg7, double jarg8, string jarg9, double jarg10);

  [DllImport("osr_wrap", EntryPoint="CSharp_SpatialReference_SetProjCS")]
  public static extern int SpatialReference_SetProjCS(HandleRef jarg1, string jarg2);

  [DllImport("osr_wrap", EntryPoint="CSharp_SpatialReference_ImportFromWkt")]
  public static extern int SpatialReference_ImportFromWkt(HandleRef jarg1, HandleRef jarg2);

  [DllImport("osr_wrap", EntryPoint="CSharp_SpatialReference_ImportFromProj4")]
  public static extern int SpatialReference_ImportFromProj4(HandleRef jarg1, string jarg2);

  [DllImport("osr_wrap", EntryPoint="CSharp_SpatialReference_ImportFromESRI")]
  public static extern int SpatialReference_ImportFromESRI(HandleRef jarg1, HandleRef jarg2);

  [DllImport("osr_wrap", EntryPoint="CSharp_SpatialReference_ImportFromEPSG")]
  public static extern int SpatialReference_ImportFromEPSG(HandleRef jarg1, int jarg2);

  [DllImport("osr_wrap", EntryPoint="CSharp_SpatialReference_ImportFromPCI")]
  public static extern int SpatialReference_ImportFromPCI(HandleRef jarg1, string jarg2, string jarg3, double[] jarg4);

  [DllImport("osr_wrap", EntryPoint="CSharp_SpatialReference_ImportFromUSGS")]
  public static extern int SpatialReference_ImportFromUSGS(HandleRef jarg1, int jarg2, int jarg3, double[] jarg4, int jarg5);

  [DllImport("osr_wrap", EntryPoint="CSharp_SpatialReference_ImportFromXML")]
  public static extern int SpatialReference_ImportFromXML(HandleRef jarg1, string jarg2);

  [DllImport("osr_wrap", EntryPoint="CSharp_SpatialReference_ExportToWkt")]
  public static extern int SpatialReference_ExportToWkt(HandleRef jarg1, out string jarg2);

  [DllImport("osr_wrap", EntryPoint="CSharp_SpatialReference_ExportToPrettyWkt")]
  public static extern int SpatialReference_ExportToPrettyWkt(HandleRef jarg1, out string jarg2, int jarg3);

  [DllImport("osr_wrap", EntryPoint="CSharp_SpatialReference_ExportToProj4")]
  public static extern int SpatialReference_ExportToProj4(HandleRef jarg1, out string jarg2);

  [DllImport("osr_wrap", EntryPoint="CSharp_SpatialReference_ExportToPCI")]
  public static extern int SpatialReference_ExportToPCI(HandleRef jarg1, out string jarg2, out string jarg3);

  [DllImport("osr_wrap", EntryPoint="CSharp_SpatialReference_ExportToUSGS")]
  public static extern int SpatialReference_ExportToUSGS(HandleRef jarg1, out int jarg2, out int jarg3, out int jarg5);

  [DllImport("osr_wrap", EntryPoint="CSharp_SpatialReference_ExportToXML")]
  public static extern int SpatialReference_ExportToXML(HandleRef jarg1, out string jarg2, string jarg3);

  [DllImport("osr_wrap", EntryPoint="CSharp_SpatialReference_CloneGeogCS")]
  public static extern IntPtr SpatialReference_CloneGeogCS(HandleRef jarg1);

  [DllImport("osr_wrap", EntryPoint="CSharp_SpatialReference_Validate")]
  public static extern int SpatialReference_Validate(HandleRef jarg1);

  [DllImport("osr_wrap", EntryPoint="CSharp_SpatialReference_StripCTParms")]
  public static extern int SpatialReference_StripCTParms(HandleRef jarg1);

  [DllImport("osr_wrap", EntryPoint="CSharp_SpatialReference_FixupOrdering")]
  public static extern int SpatialReference_FixupOrdering(HandleRef jarg1);

  [DllImport("osr_wrap", EntryPoint="CSharp_SpatialReference_Fixup")]
  public static extern int SpatialReference_Fixup(HandleRef jarg1);

  [DllImport("osr_wrap", EntryPoint="CSharp_SpatialReference_MorphToESRI")]
  public static extern int SpatialReference_MorphToESRI(HandleRef jarg1);

  [DllImport("osr_wrap", EntryPoint="CSharp_SpatialReference_MorphFromESRI")]
  public static extern int SpatialReference_MorphFromESRI(HandleRef jarg1);

  [DllImport("osr_wrap", EntryPoint="CSharp_new_CoordinateTransformation")]
  public static extern IntPtr new_CoordinateTransformation(HandleRef jarg1, HandleRef jarg2);

  [DllImport("osr_wrap", EntryPoint="CSharp_delete_CoordinateTransformation")]
  public static extern void delete_CoordinateTransformation(HandleRef jarg1);

  [DllImport("osr_wrap", EntryPoint="CSharp_CoordinateTransformation_TransformPoint__SWIG_0")]
  public static extern void CoordinateTransformation_TransformPoint__SWIG_0(HandleRef jarg1, double[] jarg2);

  [DllImport("osr_wrap", EntryPoint="CSharp_CoordinateTransformation_TransformPoint__SWIG_1")]
  public static extern void CoordinateTransformation_TransformPoint__SWIG_1(HandleRef jarg1, double[] jarg2, double jarg3, double jarg4, double jarg5);
}

}
