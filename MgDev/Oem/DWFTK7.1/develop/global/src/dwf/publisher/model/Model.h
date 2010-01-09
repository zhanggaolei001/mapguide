//
//  Copyright (C) 1996-2010 by Autodesk, Inc.
//
//  By using this code, you are agreeing to the terms and conditions of
//  the License Agreement included in the documentation for this code.
//
//  AUTODESK MAKES NO WARRANTIES, EXPRESS OR IMPLIED, AS TO THE CORRECTNESS
//  OF THIS CODE OR ANY DERIVATIVE WORKS WHICH INCORPORATE IT. AUTODESK
//  PROVIDES THE CODE ON AN "AS-IS" BASIS AND EXPLICITLY DISCLAIMS ANY
//  LIABILITY, INCLUDING CONSEQUENTIAL AND INCIDENTAL DAMAGES FOR ERRORS,
//  OMISSIONS, AND OTHER PROBLEMS IN THE CODE.
//
//  Use, duplication, or disclosure by the U.S. Government is subject to
//  restrictions set forth in FAR 52.227-19 (Commercial Computer Software
//  Restricted Rights) and DFAR 252.227-7013(c)(1)(ii) (Rights in Technical
//  Data and Computer Software), as applicable.
//

#ifndef _DWFTK_MODEL_H
#define _DWFTK_MODEL_H


///
///\file        dwf/publisher/model/Model.h
///\brief       This file contains the DWFModel class declaration.
///

#ifndef DWFTK_READ_ONLY


#include "dwfcore/STL.h"
#include "dwfcore/TempFile.h"
#include "dwfcore/OutputStream.h"
using namespace DWFCore;

#include "dwf/Toolkit.h"
#include "dwf/w3dtk/W3DCamera.h"
#include "dwf/w3dtk/W3DStreamWriter.h"
#include "dwf/package/Units.h"
#include "dwf/publisher/Publisher.h"
#include "dwf/publisher/model/Segment.h"
#include "dwf/publisher/model/StyleSegment.h"
#include "dwf/publisher/model/IncludeSegment.h"



namespace DWFToolkit
{

///
///\ingroup         dwfpublish3d
///
///\class       DWFModel   dwf/publisher/model/Model.h    "dwf/publisher/model/Model.h"
///\brief       A publishable object that represents a single EModel DWF section.
///\since       7.0.1
///
///             This class unifies the publication of EModel section graphics and metadata.
///             The model is used to capture the final scene graph, the object and property definitions,
///				and relationships to objects in the scene, simultaneously.
///             This implementation is intended to work well for large source databases 
///             where keeping the entire scene graph in memory is prohibitively slow or physically
///             constrained by system resources.  As such, the graphics are streamed to disk as they are acquired.
///             The structural relationships, however, are captured in memory for delayed examination and 
///             association.  This allows high flexibility for the publishers in processing the data.
///
class DWFModel : public DWFPublishableSection
               , private DWFPublishedObject::Factory
               , private DWFSegmentHandlerBuilder
               , private DWFGeometryHandlerBuilder
               , private DWFFeatureHandlerBuilder
               , private DWFAttributeHandlerBuilder
{

public:

    ///
    ///\brief   Do not quantize vertex normals.
    ///
    static char const keNormal_FullResolution = -1;
    ///
    ///\brief   Quantize vertex normals to 24 bits.
    ///
    static char const keNormal_DefaultResolution = 24;
    ///
    ///\brief   Quantize vertex normals to 72 bits.
    ///
    static char const keNormal_MaximumResolution = 72;
    ///
    ///\brief   Do not quantize vertex coordinates.
    ///
    static char const keVertex_FullResolution = -1;
    ///
    ///\brief   Quantize vertex coordinates to 54 bits.
    ///
    static char const keVertex_DefaultResolution = 54;
    ///
    ///\brief   Quantize vertex coordinates to 72 bits.
    ///
    static char const keVertex_MaximumResolution = 72;
    ///
    ///\brief   Do not quantize texture parameter coordinates.
    ///
    static char const keTextureParameter_FullResolution = -1;
    ///
    ///\brief   Quantize texture parameter coordinates to 54 bits.
    ///
    static char const keTextureParameter_DefaultResolution = 54;
    ///
    ///\brief   Quantize texture parameter coordinates to 72 bits.
    ///
    static char const keTextureParameter_MaximumResolution = 72;

    ///
    ///\brief   The winding order of the vertices of polygon or shell face(s).
    ///         This setting is critical for correctly surface and face shading and culling.
    ///
    typedef enum
    {
        eHandednessLeft,
        eHandednessRight,

        eHandednessNone

    } tePolygonHandedness;

public:

    ///
    ///             Constructor
    ///
    ///             Use this constructor to manage the graphics stream manually.
    ///
    ///\param       rModelStream    The output stream into which the w3d graphics to be written.
    ///\param       zModelTitle     Corresponds to the EModel section title.
    ///\param       zModelSource    Describes the source (application, component, etc.) of the model data.
    ///\param       zModelSourceID  Uniquely identifies the source (document, file, database, etc.) of the model data.
    ///\throw       None
    ///
    _DWFTK_API
    DWFModel( DWFOutputStream& rModelStream,
              const DWFString& zModelTitle = "",
              const DWFString& zModelSource = "",
              const DWFString& zModelSourceID = ""  )
        throw();

    ///
    ///             Constructor
    /// 
    ///             Use this constructor to allow the model to manange its own graphics stream.
    ///
    ///\param       zModelTitle     Corresponds to the EModel section title.
    ///\param       zModelSource    Describes the source (application, component, etc.) of the model data.
    ///\param       zModelSourceID  Uniquely identifies the source (document, file, database, etc.) of the model data.
    ///\throw       None
    ///
    _DWFTK_API
    DWFModel( const DWFString& zModelTitle = "",
              const DWFString& zModelSource = "",
              const DWFString& zModelSourceID = "" )
        throw();

    ///
    ///             Destructor
    ///
    ///\throw       None
    ///
    _DWFTK_API
    ~DWFModel()
        throw();

    ///
    ///             Prepares the model for first use.
    ///
    ///\param       ePolygonHandedness      Indicates the vertex winding order for all faces and polygons
    ///                                     in the model.  To use a different handedness, use the TK_Heuristic
    ///                                     op-code to manually override the setting where appropriate.
    ///
    ///\param       eModelUnits             Indicates into which unit space the \a pTransform matrix
    ///                                     will transform the model space.
    ///
    ///\param       pTransform              Used to transform model space into the \a eModelUnits unit space.
    ///                                     If this parameter is not specified, identity will be assumed.
    ///                                     If this parameter is specified,
    ///                                     it must be defined in order (left -> right) as follows:
    ///                                     \code using I as an example:
    ///                                     ( (1, 0, 0, 0) (0, 1, 0, 0) (0, 0, 1, 0) (0, 0, 0, 1) )
    ///
    ///                                        0  1  2  3   4  5  6  7   8  9  10 11  12 13 14 15
    ///                                     \endcode
    ///
    ///\param       bUseDefaultLighting     If \e true, a flag will be set to recommend
    ///                                     any viewer to use its own default lighting.
    ///                                     If \e false and there are lights in the scene,
    ///                                     viewers should honor them, otherwise 
    ///                                     it is recommended that the viewer use defaults.
    ///
    ///\param       bUsePublishedEdges      Must be set to \e true if any segment in the model
    ///                                     contains interior edge geometry that is preferred to be
    ///                                     used by the viewer as wireframe display.
    ///                                     If \e true, only those segments opened with published edges on
    ///                                     will be shown in wireframe; all other lines will be invisible.
    ///                                     If \e false, the viewer may choose to use its default algorithm.
    ///
    ///\param       bUseSilhouetteEdges     If \e true, the viewer should calculate and display silhouette edges
    ///                                     in wireframe mode, regardless of the published interior edge conditions.
    ///                                     If \e false, the viewer should not calculate nor display silhouette edges
    ///                                     in wireframe mode, regardless of the published interior edge conditions.
    ///
    ///\param       nTargetW3DVersion       Indicates the desired W3D format version to create.  Publishers may use
    ///                                     this parameter to create models that are backwards compatible with older
    ///                                     viewer products at the possible expense of visual effects.
    ///
    ///\throw       DWFException
    ///
    _DWFTK_API
    void open( tePolygonHandedness  ePolygonHandedness,
               DWFUnits::teType     eModelUnits,
               double*              pTransform          = NULL,
               bool                 bUseDefaultLighting = true,
               bool                 bUsePublishedEdges = false,
               bool                 bUseSilhouetteEdges = false,
               unsigned int         nTargetW3DVersion = 0 )
        throw( DWFException );

    ///
    ///             Completes the model.
    ///
    ///             This method should be paired with \a open() to scope the
    ///             model's usage.
    ///
    ///\return      The minimum required W3D format version required to support
    ///             the data and options used by the model.  If no
    ///             such requirement exists the method returns zero.
    ///
    ///\throw       DWFException
    ///
    _DWFTK_API
    unsigned int close()
        throw( DWFException );

    ///
    ///             Toggles the various compression techniques.
    ///
    ///\param       bEnableStreamCompression                Stream compression is enabled by default; this controls the inline LZ algorithm.
    ///\param       bEnableConnectivityCompression          Connectivity compression is enabled by default; this controls the loseless edge breaker algorithm.
    ///\param       bEnableGlobalQuantizationCompression    Global quantization compression is disabled by default; use this algorithm with caution
    ///                                                     as the underlying mechanism cannot account for object transformations and will not
    ///                                                     automatically calculate the world coordinates of each shell.  This can lead to coordinates
    ///                                                     being wrapped around the quantization boundary which visually manifests itself as a "stretching" effect.
    ///\throw       DWFException
    ///
    _DWFTK_API
    void enableW3DCompression( bool bEnableStreamCompression = true,
                               bool bEnableConnectivityCompression = true,
                               bool bEnableGlobalQuantizationCompression = false )
        throw( DWFException );

    ///
    ///             Toggles the vertex normals quantization compression.
    ///
    ///             The default is 24 bits (8-bits each for i,j,k);
    ///             use \a keNormal_FullResolution to disable normals compression.
    ///
    ///             By default, use <b>VERTEX NORMALS COMPRESSION IS ENABLED</b>.
    ///             It is suggested that publishers enable this compression technique
    ///             and adjust the bit resolution as small as possible without losing
    ///             visual fidelity.
    ///
    ///\param       nTotalNormalBits    The number of bits to use for all three dimensions
    ///                                 for the quantization compression.
    ///\throw       None
    ///
    _DWFTK_API
    void enableNormalsCompression( char nTotalNormalBits = keNormal_DefaultResolution )
        throw();

    ///
    ///             Toggles the vertex coordinate quantization compression.
    ///
    ///             The default is 54 bits (18-bits each for x,y,z).
    ///
    ///             Use \a keVertex_FullResolution to disable vertex compression.
    ///             Use \a keTextureParameter_FullResolution to disable texture parameter compression.
    ///
    ///             By default, vertex coordinate compression is disabled. However,
    ///             if publishers enable this compression technique, it is recommended
    ///             to adjust the bit resolution as small as possible without losing
    ///             visual fidelity. The following equation is recommended for
    ///             determining this value:
    ///             \code
    ///             nTotalVertexBits = 3 * ((unsigned int)(Log2(\e max_bounds/(\e epsilon/4.0))) + 1)
    ///
    ///             where:
    ///
    ///             \e epsilon is the maximum allowable error tolerable by the publishing application
    ///             (4.0 is a DWF-specific quality threshhold indicating that the quantization calculation
    ///             would introduce an additional 1/4 epsilon error at each vertex, at the most)
    ///
    ///             \e max_bounds is the absolute value of the largest bounding dimension: max(|x|,|y|,|z|)
    ///             \endcode
    ///
    ///\param       nTotalVertexBits        The number of bits to use for all three dimensions
    ///                                     for the quantization compression.
    ///\param       nTotalParameterBits     The number of bits to use for all three dimensions
    ///                                     for the quantization compression.
    ///\throw       None
    ///
    _DWFTK_API
    void enableVertexCompression( char nTotalVertexBits = keVertex_DefaultResolution,
                                  char nTotalParameterBits = keTextureParameter_FullResolution )
        throw();

    ///
    ///             Turns off every form of compression in the stream.
    ///
    ///             - Turns off on-the-fly LZ compression.
    ///             - Turns off connectivity compression.
    ///             - Turns off global quantization compression.
    ///             - Turns on full-resolution vertex coordinates.
    ///             - Turns on full-resolution vertex normals.
    ///
    ///\throw       DWFException
    ///
    _DWFTK_API
    void disableAllCompression()
        throw( DWFException );

    ///
    ///             Use the publisher to extract the model structure.
    ///
    ///\param       rPublisher      The publisher.
    ///\throw       DWFException
    ///
    _DWFTK_API
    void publish( DWFPublisher& rPublisher )
        throw( DWFException );

        //
        //
        // Scene Graphics
        //
        //

    ///
    ///             Opens a new segment.
    ///
    ///\return      A scene segment.
    ///\throw       DWFException
    ///
    _DWFTK_API
    DWFSegment openSegment()
        throw( DWFException );

    ///
    ///             Opens a new segment for this model's include library.
    ///
    ///\return      An include library segment.
    ///\throw       DWFException
    ///
    _DWFTK_API
    DWFIncludeSegment openIncludeSegment()
        throw( DWFException );

    ///
    ///             Opens a new segment for this model's style library.
    ///
    ///\return      A style library segment.
    ///\throw       DWFException
    ///
    _DWFTK_API
    DWFStyleSegment openStyleSegment()
        throw( DWFException );

    ///
    ///             Create a named view.
    ///
    ///             For best streaming view performance always specify a default view -
    ///             that is, one named <b>"default"</b>.  This should be done before any
    ///             scene graphics are added.
    ///
    ///\param       zName           A unique name for the view in the scene.
    ///\param       rViewCamera     Defines the view.
    ///\throw       DWFException
    ///
    _DWFTK_API
    void createView( const char*    zName,
                     W3DCamera&     rViewCamera )
        throw( DWFException );

    ///
    ///             Establish the bounding cuboid for the entire scene.
    ///
    ///\important   <b>Important:</b> Setting the bounding volume before writing any graphics data
    ///             will facilitate global quantization; and the opposite is also true:
    ///             not establishing this data will prevent globalization quantization calculations.
    ///
    ///\param       nMinX
    ///\param       nMinY
    ///\param       nMinZ
    ///\param       nMaxX
    ///\param       nMaxY
    ///\param       nMaxZ
    ///\throw       DWFException
    ///
    _DWFTK_API
    void setBoundingCube( float nMinX,   float nMinY,    float nMinZ,
                          float nMaxX,   float nMaxY,    float nMaxZ )
         throw( DWFException );

    ///
    ///             Establish the bounding spheroid for the entire scene.
    ///
    ///             <b>Important:</b> Setting the bounding volume before writing any graphics data
    ///             will faciliate global quantization; and the opposite is also true:
    ///             not establishing this data will prevent globalization quantization calculations.
    ///
    ///\param       nCenterX
    ///\param       nCenterY
    ///\param       nCenterZ
    ///\param       nRadius
    ///\throw       DWFException
    ///
    _DWFTK_API
    void setBoundingSphere( float nCenterX, float nCenterY, float nCenterZ,
                            float nRadius )
        throw( DWFException );

    ///
    ///             Changes the preferred color for wireframe mode edges
    ///             regardless of how they are defined (published or inferred.)
    ///
    ///\param       anRGB       RGB floating point color triplet.
    ///\throw       None
    ///
    _DWFTK_API
    void setEdgeColor( float anRGB[3] )
        throw();

        //
        //
        // Publishable features
        //
        //

    ///
    ///             Returns the default view camera.
    ///
    ///\return      The default view (may be NULL).  The caller must not delete this pointer.
    ///\throw       None
    ///
    _DWFTK_API
    const W3DCamera* getDefaultView() const
        throw();

    ///
    ///             Returns the bounding volume for the entire scene.
    ///
    ///             For Bounding Cuboid, the vector \a rBounds is arranged as follows:
    ///             Xmin, Ymin, Zmin, Xmax, Ymax, Zmax,
    ///
    ///             For Bounding Spheroid, the vector \a rBounds is arranged as follows:
    ///             Xcenter, Ycenter, Zcenter, radius
    ///
    ///\param       rBounds     The bounds of the scene.
    ///\throw       None
    ///
    _DWFTK_API
    void getBoundingVolume( vector<double>& rBounds ) const
        throw();

    ///
    ///             Returns a model lighting flag.
    ///
    ///\return      If \e true, a flag will be set to recommend
    ///             any viewer to use its own default lighting.
    ///             If \e false and there are lights in the scene,
    ///             viewers should honor them, otherwise 
	///             it is recommended that the viewer use defaults.
    ///
    ///\throw       None
    ///
    _DWFTK_API
    bool useModelLighting() const
        throw();

    ///
    ///             Returns the silhouette edge preferrence.
    ///
    ///\return      If \e true, the viewer should calculate and display silhouette edges
    ///             in wireframe mode, regardless of the published interior edge conditions.
    ///             If \e false, the viewer should not calculate nor display silhouette edges
    ///             in wireframe mode, regardless of the published interior edge conditions.
    ///
    ///\throw       None
    ///
    _DWFTK_API
    bool useSilhouetteEdges() const
        throw();

    ///
    ///             Returns the published edge color.
    ///
    ///\return      A floating point RGB triplet (may be NULL).  The caller must not delete this pointer.
    ///\throw       None
    ///
    _DWFTK_API
    const float* const getEdgeColor() const
        throw();

    ///
    ///             Returns the model units.
    ///
    ///\return      A enumeration indicating into which unit space the model should be transformed
    ///             by the matrix returned from \a getTransform().
    ///\throw       None
    ///
    _DWFTK_API
    DWFUnits::teType getUnits() const
        throw();

    ///
    ///             Returns the model unit transform.
    ///
    ///\return      Used to transform model space into the \a eModelUnits unit space.
    ///             If this parameter is not specified, identity will be assumed.
    ///             If this parameter is specified,
    ///             it must be defined in order (left -> right) as follows:
    ///             \code using I as an example:
    ///             ( (1, 0, 0, 0) (0, 1, 0, 0) (0, 0, 1, 0) (0, 0, 0, 1) )
    ///
    ///             0  1  2  3   4  5  6  7   8  9  10 11  12 13 14 15
    ///             \endcode
    ///\throw       None
    ///
    _DWFTK_API
    void getTransform( double* pTransform ) const
        throw();

    ///
    ///             Returns the polygon handedness setting.
    ///
    ///\return      An enumeration indicating the vertex winding order for all faces and polygons in the model. 
    ///\throw       None
    ///
    _DWFTK_API
    tePolygonHandedness getPolygonHandedness() const
        throw();

        //
        //
        // Publishable Interface
        //
        //

    ///
    ///\copydoc DWFPublishableSection::getMIMEType
    ///
    _DWFTK_API
    const DWFString& getMIMEType()
        throw( DWFException );

    ///
    ///\copydoc DWFPublishableSection::getInputStream
    ///
    _DWFTK_API
    DWFInputStream* getInputStream()
        throw( DWFException );

    ///
    ///\copydoc DWFPublishableSection::embedFont
    ///
    _DWFTK_API
    void embedFont( DWFEmbeddedFont* pFont )
        throw( DWFException );

    ///
    ///\copydoc DWFPublishableSection::addResource
    ///
    _DWFTK_API
    void addResource( DWFPublishableResource* pResource )
        throw( DWFException );

    ///
    ///\copydoc DWFPublishableSection::getResources
    ///
    _DWFTK_API
    DWFIterator<DWFPublishableResource*>* getResources()
        throw( DWFException );

private:

    ///
    ///\copydoc DWFPublishedObject::makePublishedObject
    ///
    DWFPublishedObject* makePublishedObject( DWFPublishedObject::tKey nKey,
                                             const DWFString&      zName )
        throw( DWFException );

    ///
    ///\copydoc DWFPublishedObject::findPublishedObject
    ///
    DWFPublishedObject& findPublishedObject( DWFPublishedObject::tKey nKey )
        throw( DWFException );

private:

        //
        //
        // SegmentHandlerBuilder Interface
        //
        //

    TK_Close_Segment& getCloseSegmentHandler()
        throw( DWFException );

    TK_Open_Segment& getOpenSegmentHandler()
        throw( DWFException );

    TK_Referenced_Segment& getIncludeSegmentHandler()
        throw( DWFException );

    TK_Referenced_Segment& getStyleSegmentHandler()
        throw( DWFException );

        //
        //
        // GeometryHandlerBuilder Interface
        //
        //

    TK_Area_Light& getAreaLightHandler()
        throw( DWFException );

    TK_Circle& getCircleHandler()
        throw( DWFException );

    TK_Circle& getCircularArcHandler()
        throw( DWFException );

    TK_Circle& getCircularChordHandler()
        throw( DWFException );

    TK_Circle& getCircularWedgeHandler()
        throw( DWFException );

    TK_Cutting_Plane& getCuttingPlaneHandler()
        throw( DWFException );

    TK_Point& getDistantLightHandler()
        throw( DWFException );

    TK_Ellipse& getEllipseHandler()
        throw( DWFException );

    TK_Ellipse& getEllipticalArcHandler()
        throw( DWFException );

    TK_Glyph_Definition& getGlyphDefinitionHandler()
        throw( DWFException );

    TK_Image& getImageHandler()
        throw( DWFException );

    TK_Line& getLineHandler()
        throw( DWFException );

    TK_Point& getLocalLightHandler()
        throw( DWFException );

    TK_NURBS_Curve& getNURBSCurveHandler()
        throw( DWFException );

    TK_NURBS_Surface& getNURBSSurfaceHandler()
        throw( DWFException );

    TK_PolyCylinder& getPolyCylinderHandler()
        throw( DWFException );

    TK_Polypoint& getPolygonHandler()
        throw( DWFException );

    TK_Polypoint& getPolylineHandler()
        throw( DWFException );

    //
    // IMPORTANT:   Setting this flag to true when you data is not in tristrips may produce garbage.
    //
    // bTriStripsOnly - the shell is assumed to contain triangles only and may not contain holes,
    //                  and the "faces" are actually the way that vertices are connected into triangle strips.
    //                  Start with the length of the strip, followed by the vertex indices to be connected.
    //                  The first 3 vertices form a triangle, and every additional vertex is
    //                  combined with the two previous ones to  define one additional triangle.
    //                  Exactly as with OpenGL's GL_TRIANGLE_STRIP primitive,
    //                  the orientation of every even triangle is reversed, beginning with the second.
    //
    // bDisableOptimization - Disable vertex and face optimization algorithm just before stream serialization
    //                          This optimization is on by default, it's tolerance parameters may be tuned
    //                          by calling optimize() (this method can also be used to disable the process)
    //
    TK_Shell& getShellHandler( bool bTriStripsOnly = false,
                               bool bDisableOptimization = false )
        throw( DWFException );

    TK_Spot_Light& getSpotLightHandler()
        throw( DWFException );

    TK_Text& getTextHandler()
        throw( DWFException );

    TK_Text& getTextWithEncodingHandler()
        throw( DWFException );

        //
        //
        // FeatureHandlerBuilder Interface
        //
        //

    TK_Texture& getTextureHandler()
        throw( DWFException );

    TK_Matrix& getTextureMatrixHandler()
        throw( DWFException );

        //
        //
        // AttributeHandlerBuilder Interface
        //
        //

    TK_Color& getColorHandler()
        throw( DWFException );

    TK_Color_Map& getColorMapHandler()
        throw( DWFException );

    TK_Color_RGB& getColorRGBHandler()
        throw( DWFException );

    TK_Named& getEdgePatternHandler()
        throw( DWFException );

    TK_Size& getEdgeWeightHandler()
        throw( DWFException );

    TK_Enumerated& getFacePatternHandler()
        throw( DWFException );

    TK_Enumerated& getHandednessHandler()
        throw( DWFException );

    TK_Heuristics& getHeuristicsHandler()
        throw( DWFException );

    TK_Named& getLinePatternHandler()
        throw( DWFException );

    TK_Line_Style& getLineStyleHandler()
        throw( DWFException );

    TK_Size& getLineWeightHandler()
        throw( DWFException );

    TK_Size& getMarkerSizeHandler()
        throw( DWFException );

    TK_Enumerated& getMarkerSymbolHandler()
        throw( DWFException );

    TK_Matrix& getModellingMatrixHandler()
        throw( DWFException );

    TK_Rendering_Options& getRenderingOptionsHandler()
        throw( DWFException );

    TK_Selectability& getSelectabilityHandler()
        throw( DWFException );

    TK_Enumerated& getTextAlignmentHandler()
        throw( DWFException );

    TK_Text_Font& getTextFontHandler()
        throw( DWFException );

    TK_Point& getTextPathHandler()
        throw( DWFException );

    TK_Size& getTextSpacingHandler()
        throw( DWFException );

    TK_User_Options& getUserOptionsHandler()
        throw( DWFException );

    TK_Unicode_Options& getUnicodeOptionsHandler()
        throw( DWFException );

    TK_Visibility& getVisibilityHandler()
        throw( DWFException );

    TK_Camera& getCameraHandler()
        throw( DWFException );

    TK_Camera& getViewHandler()
        throw( DWFException );

private:

    bool                    _bOpen;
    bool                    _bCompress;
    bool                    _bStreamDefaults;
    bool                    _bBoundingVolumeSet;
    bool                    _bUseDefaultLighting;
    bool                    _bModelLightsUsed;
    bool                    _bUseSilhouetteEdges;
    bool                    _bSetEdgeColor;
    float                   _anEdgeColor[3];

    DWFUnits::teType        _eUnits;
    double                  _anUnitsTransform[16];
    tePolygonHandedness     _eHandedness;

    unsigned int            _nStyleSegments;

    DWFString               _zMIME;

    DWFTempFile*            _pW3DFile;
    DWFInputStream*         _pW3DFileStream;
    char*                   _pVersionBuffer;

    BStreamFileToolkit      _oToolkit;
    W3DStreamWriter*        _pW3DStreamWriter;
    W3DCamera*              _pDefaultViewCamera;

    vector<double>                  _oBoundingVolume;
    DWFEmbeddedFont::tList          _oEmbeddedFonts;
    DWFPublishableResource::tList   _oResources;
    DWFPublishedObject::tMap        _oPublishedObjects;

private:

    //
    //
    //
    class _SpecialBufferedInputStream : public DWFInputStream
    {
    public:

        _SpecialBufferedInputStream( char*              pBuffer,
                                     unsigned int       nBufferBytes,
                                     DWFInputStream*    pStream )
            throw();

        virtual ~_SpecialBufferedInputStream()
            throw();

        size_t available() const
            throw( DWFException );

        size_t read( void*  pBuffer,
                     size_t nBytesToRead )
            throw( DWFException );

        off_t seek( int    eOrigin,
                    off_t  nOffset )
            throw( DWFException );

    private:

        unsigned int    _nBufferBytes;
        unsigned int    _nBufferBytesRead;
        char*           _pBuffer;
        DWFInputStream* _pStream;
    };

private:

    //
    // Not Implemented
    //

    DWFModel( const DWFModel& );
    DWFModel& operator=( const DWFModel& );
};


}


#endif
#endif
