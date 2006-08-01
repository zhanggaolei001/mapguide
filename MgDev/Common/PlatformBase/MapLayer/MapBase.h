//
//  Copyright (C) 2004-2006  Autodesk, Inc.
//
//  This library is free software; you can redistribute it and/or
//  modify it under the terms of version 2.1 of the GNU Lesser
//  General Public License as published by the Free Software Foundation.
//
//  This library is distributed in the hope that it will be useful,
//  but WITHOUT ANY WARRANTY; without even the implied warranty of
//  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
//  Lesser General Public License for more details.
//
//  You should have received a copy of the GNU Lesser General Public
//  License along with this library; if not, write to the Free Software
//  Foundation, Inc., 51 Franklin St, Fifth Floor, Boston, MA  02110-1301  USA
//

#ifndef _MG_MAP_H_
#define _MG_MAP_H_

/// \defgroup MgMap MgMap
/// \ingroup Mapping_Service_Module
/// \{

#include "Foundation.h"
#include <vector>
#include <list>
#include <map>
#include "LayerBase.h"
#include "LayerGroup.h"
#include "LayerCollection.h"
#include "LayerGroupCollection.h"
#include "MapCollection.h"
#include "ObjectChange.h"
#include "ChangeList.h"
#include "ReadOnlyLayerCollection.h"
#include "SelectionBase.h"

class MgPoint;
class MgMapBase;
template class MG_PLATFORMBASE_API Ptr<MgMapBase>;

#ifdef WIN32
#undef CreateService
#endif

#define LAYER_ZORDER_TOP        100.0
#define LAYER_ZORDER_INCR       100.0

typedef vector<double> FINITESCALES;
typedef map<double, double, less<double> > SORTEDSCALES;

/////////////////////////////////////////////////////////////////
/// \brief
/// Defines the runtime state of a map.
/// \remarks
/// This corresponds with the state of the map as seen by the
/// client. Note that this may differ from the MapDefinition
/// stored in the resource repository. For example, the user may
/// have altered the scale or hidden layers.
///
/// You can use the Save and Open methods to store the runtime
/// state into the session repository and retrieve it from the
/// session repository.
/// <!-- Example (PHP) -->
/// \htmlinclude PHPExampleTop.html
/// This example shows information about a map:
/// \code
/// <?php
/// try
/// {
///     // Include constants like MgServiceType::ResourceService
///     include 'C:\\Inetpub\\wwwroot\\PhpMapAgent\\MgConstants.php';
///     // Initialize
///     MgInitializeWebTier('C:\\Inetpub\\wwwroot\\PhpMapAgent\\webconfig.ini');
///     // Establish a connection with a MapGuide site.
///     $user = new MgUserInformation('Administrator', 'admin');
///     $siteConnection = new MgSiteConnection();
///     $siteConnection->Open($user);
///     // Create a session repository
///     $site = $siteConnection->GetSite();
///     $sessionID = $site->CreateSession();
///     $user->SetMgSessionId($sessionID);
///     // Get an instance of the required services.
///     $resourceService = $siteConnection->CreateService(MgServiceType::ResourceService);
///     $mappingService = $siteConnection->CreateService(MgServiceType::MappingService);
///
///     // Get a runtime map from a map definition
///     $resourceID = new  MgResourceIdentifier('Library://Calgary/Maps/Calgary.MapDefinition');
///     $map = new MgMap();
///     $map->Create($resourceService, $resourceID, 'Calgary');
///
///     // Show information about the map
///     echo "Name of map:               '" . $map->GetName() . "'n";
///     echo "   Session ID of map:      " . $map->GetSessionId() . "n";
///     echo "   Object ID:              " . $map->GetObjectId() . "n";
///
///     $envelope = $map->GetDataExtent();
///     echo "   Envelope:               ";
///     PrintEnvelope($envelope);
///
///     $extent = $map->GetMapExtent();
///     echo "   lower left coordinate:  ";
///     PrintCoordinate( $extent->GetLowerLeftCoordinate() );
///     echo "   upper right coordinate: " ;
///     PrintCoordinate( $extent->GetUpperRightCoordinate() );
///
///     $point = $map->GetViewCenter();
///     echo "   view center:            ";
///     PrintPoint($point);
///
///     echo "   View scale:             " . $map->GetViewScale() . "n";
///     echo "   Display dpi:            " . $map->GetDisplayDpi() . "n";
///     echo "   Display width:          " . $map->GetDisplayWidth() . "n";
///     echo "   Display height:         " . $map->GetDisplayHeight() . "n";
///
///     $layerCollection = $map->GetLayers();
///     echo "   Layers: n";
///     PrintLayerCollection( $layerCollection );
///
///     $layerGroupCollection = $map->GetLayerGroups();
///     echo "   Layer groups: n";
///     PrintLayerGroupCollection( $layerGroupCollection );
///
///     echo "   Finite display scales: n";
///     PrintFiniteDisplayScales( $map );
///
///     echo "Done n";
/// \}
/// catch (MgException $e)
/// {
///     echo "ERROR: " . $e->GetMessage() . "n";
///     echo $e->GetDetails() . "n";
///     echo $e->GetStackTrace() . "n";
/// \}
///
/// /********************************************************************/
/// function PrintEnvelope($envelope)
/// {
///     echo "depth = " . $envelope->GetDepth() . ", height = " . $envelope->GetHeight() . ", width = " . $envelope->GetWidth() . "n";
/// \}
///
/// /********************************************************************/
/// function PrintCoordinate($coordinate)
/// {
///     echo "(" . $coordinate->GetX() . ", " . $coordinate->GetY() . ", " . $coordinate->GetZ() . ") n";
/// \}
///
/// /********************************************************************/
/// function PrintPoint($point)
/// {
///     PrintCoordinate( $point->GetCoordinate() );
/// \}
///
/// /********************************************************************/
/// function PrintLayerCollection($layerCollection)
/// {
///     for ($i = 0; $i < $layerCollection->GetCount(); $i++)
///     {
///         $layer = $layerCollection->GetItem($i);
///         echo "      layer #" . ($i + 1) . ": n" ;
///         PrintLayer($layer);
///     }
/// \}
///
/// /********************************************************************/
/// function PrintLayer($layer)
/// {
///     echo "      name:                '" . $layer->GetName() . "'n";
///     $layerDefinition = $layer->GetLayerDefinition();
///     echo "      layer definition:    '" . $layerDefinition->ToString()  . "'n";
///     echo "      legend label:        '" . $layer->GetLegendLabel()  . "'n";
///     echo "      display in legend:   " . ConvertBooleanToString($layer->GetDisplayInLegend()) . "n";
///     echo "      expand in legend:    " . ConvertBooleanToString($layer->GetExpandInLegend()) . "n";
///     echo "      selectable:          " . ConvertBooleanToString($layer->GetSelectable()) . "n";
///     echo "      potentially visible: " . ConvertBooleanToString($layer->GetVisible()) . "n";
///     echo "      actually visible:    " . ConvertBooleanToString($layer->IsVisible()) . "n";
///     echo "      needs refresh:       " . ConvertBooleanToString($layer->NeedsRefresh()) . "n";
/// \}
///
/// /********************************************************************/
/// function PrintLayerGroupCollection($layerGroupCollection)
/// {
///     for ($i = 0; $i < $layerGroupCollection->GetCount(); $i++)
///     {
///         $layerGroup = $layerGroupCollection->GetItem($i);
///         echo "      layer group #" . ($i + 1) . ": " ;
///         PrintLayerGroup($layerGroup);
///     }
/// \}
///
/// /********************************************************************/
/// function PrintLayerGroup($layerGroup)
/// {
///     echo "      layer group name        '" . $layerGroup->GetName() . "'n";
///     echo "      display in legend:      " . ConvertBooleanToString($layerGroup->GetDisplayInLegend()) . "n";
///     echo "      expand in legend:       " . ConvertBooleanToString($layerGroup->GetExpandInLegend()) . "n";
///     $parentGroup = $layerGroup->GetGroup();
///     echo "      group                   " . $parentGroup->GetName() . "n";
///     echo "      legend label            " . $layerGroup->GetLegendLabel() . "n";
///     echo "      object ID               " . $layerGroup->GetObjectId() . "n";
///     echo "      potentially visible:    " . ConvertBooleanToString($layerGroup->GetVisible()) . "n";
///     echo "      actually visible:       " . ConvertBooleanToString($layerGroup->IsVisible()) . "n";
/// \}
///
/// /********************************************************************/
/// function PrintFiniteDisplayScales($map)
/// {
///     for ($i = 0; $i < $map->GetFiniteDisplayScaleCount(); $i++)
///     {
///         echo "      finite display scale #" . ($i + 1) . ": " . $map->GetFiniteDisplayScaleAt($i) . "'n";
///     }
/// \}
///
/// /********************************************************************/
/// // Converts a boolean to "yes" or "no".
/// function ConvertBooleanToString($boolean)
/// {
///     if (is_bool($boolean))
///         return ($boolean ? "yes" : "no");
///     else
///         return "ERROR in ConvertBooleanToString.";
/// \}
///
/// /********************************************************************/
/// ?>
/// \endcode
/// \htmlinclude ExampleBottom.html
class MG_PLATFORMBASE_API MgMapBase : public MgResource
{
    DECLARE_CREATE_OBJECT()
    DECLARE_CLASSNAME(MgMapBase)

PUBLISHED_API:

    //////////////////////////////////////////////////////////////////
    /// \brief
    /// Constructs an empty un-initialized MgMap object.
    ///
    /// \remarks
    /// The instance of MgMap cannot be used until either the \link MgMapBase::Create Create \endlink
    /// or \link MgMapBase::Open Open \endlink
    /// method is called.
    ///
    /// <!-- Syntax in .Net, Java, and PHP -->
    /// \htmlinclude DotNetSyntaxTop.html
    /// MgMap();
    /// \htmlinclude SyntaxBottom.html
    /// \htmlinclude JavaSyntaxTop.html
    /// MgMap();
    /// \htmlinclude SyntaxBottom.html
    /// \htmlinclude PHPSyntaxTop.html
    /// MgMap();
    /// \htmlinclude SyntaxBottom.html
    ///
    /// <!-- Example (PHP) -->
    /// \htmlinclude PHPExampleTop.html
    /// See \link MgMapBase::Create Create \endlink.
    /// \htmlinclude ExampleBottom.html
    ///
    MgMapBase();

    //////////////////////////////////////////////////////////////////
    /// \brief
    /// Gets the name of this map.
    ///
    /// <!-- Syntax in .Net, Java, and PHP -->
    /// \htmlinclude DotNetSyntaxTop.html
    /// string GetName();
    /// \htmlinclude SyntaxBottom.html
    /// \htmlinclude JavaSyntaxTop.html
    /// String GetName();
    /// \htmlinclude SyntaxBottom.html
    /// \htmlinclude PHPSyntaxTop.html
    /// string GetName();
    /// \htmlinclude SyntaxBottom.html
    ///
    /// \return
    /// Returns the name of the map as a string.
    ///
    /// <!-- Example (PHP) -->
    /// \htmlinclude PHPExampleTop.html
    /// See \link MgMap MgMap Class \endlink.
    /// \htmlinclude ExampleBottom.html
    ///
    STRING GetName();

    //////////////////////////////////////////////////////////////////
    /// \brief
    /// Gets the identifier of the session associated with this map.
    ///
    /// <!-- Syntax in .Net, Java, and PHP -->
    /// \htmlinclude DotNetSyntaxTop.html
    /// string GetSessionId();
    /// \htmlinclude SyntaxBottom.html
    /// \htmlinclude JavaSyntaxTop.html
    /// String GetSessionId();
    /// \htmlinclude SyntaxBottom.html
    /// \htmlinclude PHPSyntaxTop.html
    /// string GetSessionId();
    /// \htmlinclude SyntaxBottom.html
    ///
    /// \return
    /// Returns the session id of the map as a string.
    ///
    /// <!-- Example (PHP) -->
    /// \htmlinclude PHPExampleTop.html
    /// See \link MgMap MgMap Class \endlink.
    /// \htmlinclude ExampleBottom.html
    ///
    STRING GetSessionId();

    //////////////////////////////////////////////////////////////////
    /// \brief
    /// Gets an identifier that can be used to uniquely identify this
    /// map.
    ///
    /// <!-- Syntax in .Net, Java, and PHP -->
    /// \htmlinclude DotNetSyntaxTop.html
    /// string GetObjectId();
    /// \htmlinclude SyntaxBottom.html
    /// \htmlinclude JavaSyntaxTop.html
    /// String GetObjectId();
    /// \htmlinclude SyntaxBottom.html
    /// \htmlinclude PHPSyntaxTop.html
    /// string GetObjectId();
    /// \htmlinclude SyntaxBottom.html
    ///
    /// \return
    /// Returns the unique identifier of this map as a string.
    ///
    /// <!-- Example (PHP) -->
    /// \htmlinclude PHPExampleTop.html
    /// See \link MgMap MgMap Class \endlink.
    /// \htmlinclude ExampleBottom.html
    ///
    STRING GetObjectId();

    //////////////////////////////////////////////////////////////////
    /// \brief
    /// Returns the resource identifier that specifies the location
    /// of the map definition that was used to create this map.
    ///
    /// <!-- Syntax in .Net, Java, and PHP -->
    /// \htmlinclude DotNetSyntaxTop.html
    /// MgResourceIdentifier GetMapDefinition();
    /// \htmlinclude SyntaxBottom.html
    /// \htmlinclude JavaSyntaxTop.html
    /// MgResourceIdentifier GetMapDefinition();
    /// \htmlinclude SyntaxBottom.html
    /// \htmlinclude PHPSyntaxTop.html
    /// MgResourceIdentifier GetMapDefinition();
    /// \htmlinclude SyntaxBottom.html
    ///
    /// \return
    /// Returns an MgResourceIdentifier that specifies the location
    /// of the map definition.
    ///
    /// <!-- Example (PHP) -->
    /// \htmlinclude PHPExampleTop.html
    /// See \link MgMap MgMap Class \endlink.
    /// \htmlinclude ExampleBottom.html
    ///
    MgResourceIdentifier* GetMapDefinition();

    //////////////////////////////////////////////////////////////////
    /// \brief
    /// Gets the spatial reference system used to display this map.
    ///
    /// <!-- Syntax in .Net, Java, and PHP -->
    /// \htmlinclude DotNetSyntaxTop.html
    /// string GetMapSRS();
    /// \htmlinclude SyntaxBottom.html
    /// \htmlinclude JavaSyntaxTop.html
    /// String GetMapSRS();
    /// \htmlinclude SyntaxBottom.html
    /// \htmlinclude PHPSyntaxTop.html
    /// string GetMapSRS();
    /// \htmlinclude SyntaxBottom.html
    ///
    /// \return
    /// Returns the spatial reference system in the OpenGIS \link WKT WKT \endlink
    /// (Well Known Text) format as a string.
    ///
    /// <!-- Example (PHP) -->
    /// \htmlinclude PHPExampleTop.html
    /// See \link MgMap MgMap Class \endlink.
    /// \htmlinclude ExampleBottom.html
    ///
    STRING GetMapSRS();

    //////////////////////////////////////////////////////////////////
    /// \brief
    /// Returns the the overall extent of the map.
    ///
    /// <!-- Syntax in .Net, Java, and PHP -->
    /// \htmlinclude DotNetSyntaxTop.html
    /// MgEnvelope GetMapExtent();
    /// \htmlinclude SyntaxBottom.html
    /// \htmlinclude JavaSyntaxTop.html
    /// MgEnvelope GetMapExtent();
    /// \htmlinclude SyntaxBottom.html
    /// \htmlinclude PHPSyntaxTop.html
    /// MgEnvelope GetMapExtent();
    /// \htmlinclude SyntaxBottom.html
    ///
    /// \return
    /// Returns an MgEnvelope that defines the overall extent of the
    /// map.
    ///
    /// <!-- Example (PHP) -->
    /// \htmlinclude PHPExampleTop.html
    /// See \link MgMap MgMap Class \endlink.
    /// \htmlinclude ExampleBottom.html
    ///
    MgEnvelope* GetMapExtent();

    //////////////////////////////////////////////////////////////////
    /// \brief
    /// Returns this maps layers.
    ///
    /// <!-- Syntax in .Net, Java, and PHP -->
    /// \htmlinclude DotNetSyntaxTop.html
    /// MgLayerCollection GetLayers();
    /// \htmlinclude SyntaxBottom.html
    /// \htmlinclude JavaSyntaxTop.html
    /// MgLayerCollection GetLayers();
    /// \htmlinclude SyntaxBottom.html
    /// \htmlinclude PHPSyntaxTop.html
    /// MgLayerCollection GetLayers();
    /// \htmlinclude SyntaxBottom.html
    ///
    /// \return
    /// Returns an MgLayerCollection that contains the map layers.
    ///
    /// <!-- Example (PHP) -->
    /// \htmlinclude PHPExampleTop.html
    /// See \link MgMap MgMap Class \endlink.
    /// \htmlinclude ExampleBottom.html
    ///
    MgLayerCollection* GetLayers();

    //////////////////////////////////////////////////////////////////
    /// \brief
    /// Returns this maps layer groups.
    ///
    /// <!-- Syntax in .Net, Java, and PHP -->
    /// \htmlinclude DotNetSyntaxTop.html
    /// MgLayerGroupCollection GetLayerGroups();
    /// \htmlinclude SyntaxBottom.html
    /// \htmlinclude JavaSyntaxTop.html
    /// MgLayerGroupCollection GetLayerGroups();
    /// \htmlinclude SyntaxBottom.html
    /// \htmlinclude PHPSyntaxTop.html
    /// MgLayerGroupCollection GetLayerGroups();
    /// \htmlinclude SyntaxBottom.html
    ///
    /// \return
    /// Returns an MgLayerGroupCollection that contains the map
    /// layer groups.
    ///
    /// <!-- Example (PHP) -->
    /// \htmlinclude PHPExampleTop.html
    /// See \link MgMap MgMap Class \endlink.
    /// \htmlinclude ExampleBottom.html
    ///
    MgLayerGroupCollection* GetLayerGroups();

    //////////////////////////////////////////////////////////////////
    /// \brief
    /// Initializes a new MgMap object given a resource service, map
    /// definition, and a name for the map. This method is used for
    /// MapGuide Viewers or for offline map production.
    ///
    /// <!-- Syntax in .Net, Java, and PHP -->
    /// \htmlinclude DotNetSyntaxTop.html
    /// void Create(MgResourceService resourceService, MgResourceIdentifier mapDefinition, string mapName);
    /// \htmlinclude SyntaxBottom.html
    /// \htmlinclude JavaSyntaxTop.html
    /// void Create(MgResourceService resourceService, MgResourceIdentifier mapDefinition, String mapName);
    /// \htmlinclude SyntaxBottom.html
    /// \htmlinclude PHPSyntaxTop.html
    /// void Create(MgResourceService resourceService, MgResourceIdentifier mapDefinition, string mapName);
    /// \htmlinclude SyntaxBottom.html
    ///
    /// \param resourceService (MgResourceService)
    /// An MgResourceService that can be used to
    /// retrieve the map definition.
    /// \param mapDefinition (MgResourceIdentifier)
    /// An MgResourceIdentifier that specifies the
    /// location of the map definition in a resource
    /// repository.
    /// \param mapName (String/string)
    /// A string that specifies the name of the map.
    ///
    /// <!-- Example (PHP) -->
    /// \htmlinclude PHPExampleTop.html
    /// \code
    /// // Assuming the resource service has already been intialized
    /// $resourceID = new  MgResourceIdentifier('Library://Calgary/Maps/Calgary.MapDefinition');
    /// $map = new MgMap();
    /// $map->Create($resourceService, $resourceID, 'Calgary');
    /// \endcode
    /// \htmlinclude ExampleBottom.html
    ///
    void Create(MgResourceService* resourceService, MgResourceIdentifier* mapDefinition, CREFSTRING mapName);

    //////////////////////////////////////////////////////////////////
    /// \brief
    /// Initializes a new Map object given a spatial reference system,
    /// spatial extent of the map, and a name for the map. This method
    /// is used for the WMS service implementation and creates a map
    /// without any layers.
    ///
    /// <!-- Syntax in .Net, Java, and PHP -->
    /// \htmlinclude DotNetSyntaxTop.html
    /// void Create(string mapSRS, MgEnvelope mapExtent, string mapName);
    /// \htmlinclude SyntaxBottom.html
    /// \htmlinclude JavaSyntaxTop.html
    /// void Create(String mapSRS, MgEnvelope mapExtent, String mapName);
    /// \htmlinclude SyntaxBottom.html
    /// \htmlinclude PHPSyntaxTop.html
    /// void Create(string mapSRS, MgEnvelope mapExtent, string mapName);
    /// \htmlinclude SyntaxBottom.html
    ///
    /// \param mapSRS (String/string)
    /// A string specifying the spatial reference system in OpenGIS WKT
    /// format.
    /// \param mapExtent (MgEnvelope)
    /// An MgEnvelope defining the overall extent of the map.
    /// \param mapName (String/string)
    /// A string that specifies the name of the map.
    ///
    void Create(CREFSTRING mapSRS, MgEnvelope* mapExtent, CREFSTRING mapName);

    //////////////////////////////////////////////////////////////////
    /// \brief
    /// Loads the map object from a session repository.
    ///
    /// \remarks
    /// For more information, see \link Mapping_Service_Module Mapping Service \endlink.
    ///
    /// <!-- Syntax in .Net, Java, and PHP -->
    /// \htmlinclude DotNetSyntaxTop.html
    /// virtual void Open(MgResourceService resourceService, string mapName);
    /// \htmlinclude SyntaxBottom.html
    /// \htmlinclude JavaSyntaxTop.html
    /// virtual void Open(MgResourceService resourceService, String mapName);
    /// \htmlinclude SyntaxBottom.html
    /// \htmlinclude PHPSyntaxTop.html
    /// virtual void Open(MgResourceService resourceService, string mapName);
    /// \htmlinclude SyntaxBottom.html
    ///
    /// \param resourceService (MgResourceService)
    /// An MgResourceService that can be used to retrieve
    /// the map.
    /// \param mapName (String/string)
    /// A string that specifies the name of the map. This
    /// is the name that was specified when \link MgMapBase::Create Create \endlink
    /// was called to create the map object.
    ///
    /// \return
    /// Returns nothing.
    ///
    /// <!-- Example (PHP) -->
    /// \htmlinclude PHPExampleTop.html
    /// \code
    /// // Assuming the resource service has already been initialized
    /// $map = new MgMap();
    /// $map->Open($resourceService, 'Calgary');
    /// \endcode
    /// \htmlinclude ExampleBottom.html
    ///
    /// \todo
    ///   * [[Job for Philip: If I move that overview to the
    ///     Developer's Guide, update the xref here.]]
    ///
    virtual void Open(MgResourceService* resourceService, CREFSTRING mapName);

    //////////////////////////////////////////////////////////////////
    /// \brief
    /// Gets the current center point of the map, in the spatial
    /// reference system of the map.
    ///
    /// <!-- Syntax in .Net, Java, and PHP -->
    /// \htmlinclude DotNetSyntaxTop.html
    /// MgPoint GetViewCenter();
    /// \htmlinclude SyntaxBottom.html
    /// \htmlinclude JavaSyntaxTop.html
    /// MgPoint GetViewCenter();
    /// \htmlinclude SyntaxBottom.html
    /// \htmlinclude PHPSyntaxTop.html
    /// MgPoint GetViewCenter();
    /// \htmlinclude SyntaxBottom.html
    ///
    /// \return
    /// Returns an MgPoint that specifies the center of the map.
    ///
    /// <!-- Example (PHP) -->
    /// \htmlinclude PHPExampleTop.html
    /// See \link MgMap MgMap Class \endlink.
    /// \htmlinclude ExampleBottom.html
    ///
    MgPoint* GetViewCenter();

    //////////////////////////////////////////////////////////////////
    /// \brief
    /// Gets the current scale of the map.
    ///
    /// <!-- Syntax in .Net, Java, and PHP -->
    /// \htmlinclude DotNetSyntaxTop.html
    /// double GetViewScale();
    /// \htmlinclude SyntaxBottom.html
    /// \htmlinclude JavaSyntaxTop.html
    /// double GetViewScale();
    /// \htmlinclude SyntaxBottom.html
    /// \htmlinclude PHPSyntaxTop.html
    /// double GetViewScale();
    /// \htmlinclude SyntaxBottom.html
    ///
    /// \return
    /// Returns a double that specifies the scale of the map.
    ///
    /// <!-- Example (PHP) -->
    /// \htmlinclude PHPExampleTop.html
    /// See \link MgMap MgMap Class \endlink.
    /// \htmlinclude ExampleBottom.html
    ///
    double GetViewScale();

    //////////////////////////////////////////////////////////////////
    /// \brief
    /// Returns the extent of the data to be generated for the map
    /// in the spatial reference system of the map.
    ///
    /// <!-- Syntax in .Net, Java, and PHP -->
    /// \htmlinclude DotNetSyntaxTop.html
    /// MgEnvelope GetDataExtent();
    /// \htmlinclude SyntaxBottom.html
    /// \htmlinclude JavaSyntaxTop.html
    /// MgEnvelope GetDataExtent();
    /// \htmlinclude SyntaxBottom.html
    /// \htmlinclude PHPSyntaxTop.html
    /// MgEnvelope GetDataExtent();
    /// \htmlinclude SyntaxBottom.html
    ///
    /// \return
    /// Returns an MgEnvelope that defines the current data extent.
    ///
    /// <!-- Example (PHP) -->
    /// \htmlinclude PHPExampleTop.html
    /// See \link MgMap MgMap Class \endlink.
    /// \htmlinclude ExampleBottom.html
    ///
    MgEnvelope* GetDataExtent();

    //////////////////////////////////////////////////////////////////
    /// \brief
    /// Returns the number of dots per inch of the map display.
    ///
    /// <!-- Syntax in .Net, Java, and PHP -->
    /// \htmlinclude DotNetSyntaxTop.html
    /// int GetDisplayDpi();
    /// \htmlinclude SyntaxBottom.html
    /// \htmlinclude JavaSyntaxTop.html
    /// int GetDisplayDpi();
    /// \htmlinclude SyntaxBottom.html
    /// \htmlinclude PHPSyntaxTop.html
    /// int GetDisplayDpi();
    /// \htmlinclude SyntaxBottom.html
    ///
    /// \return
    /// Returns the number of dots per inch of the map display.
    ///
    /// <!-- Example (PHP) -->
    /// \htmlinclude PHPExampleTop.html
    /// See \link MgMap MgMap Class \endlink.
    /// \htmlinclude ExampleBottom.html
    ///
    INT32 GetDisplayDpi();

    //////////////////////////////////////////////////////////////////
    /// \brief
    /// Returns the current width of the map display in pixels.
    ///
    /// \remarks
    /// The width must be set by the client using the SETDISPLAYWIDTH
    /// command as part of a GetMap or GetMapUpdate HTTP request.
    ///
    /// <!-- Syntax in .Net, Java, and PHP -->
    /// \htmlinclude DotNetSyntaxTop.html
    /// int GetDisplayWidth();
    /// \htmlinclude SyntaxBottom.html
    /// \htmlinclude JavaSyntaxTop.html
    /// int GetDisplayWidth();
    /// \htmlinclude SyntaxBottom.html
    /// \htmlinclude PHPSyntaxTop.html
    /// int GetDisplayWidth();
    /// \htmlinclude SyntaxBottom.html
    ///
    /// \return
    /// Returns the width of the map display in pixels.
    ///
    /// <!-- Example (PHP) -->
    /// \htmlinclude PHPExampleTop.html
    /// See \link MgMap MgMap Class \endlink.
    /// \htmlinclude ExampleBottom.html
    ///
    INT32 GetDisplayWidth();

    //////////////////////////////////////////////////////////////////
    /// \brief
    /// Returns the current height of the map display in pixels.
    ///
    /// \remarks
    /// The height must be set by the client using the
    /// SETDISPLAYHEIGHT command as part of a GetMap or GetMapUpdate
    /// HTTP request.
    ///
    /// <!-- Syntax in .Net, Java, and PHP -->
    /// \htmlinclude DotNetSyntaxTop.html
    /// int GetDisplayHeight();
    /// \htmlinclude SyntaxBottom.html
    /// \htmlinclude JavaSyntaxTop.html
    /// int GetDisplayHeight();
    /// \htmlinclude SyntaxBottom.html
    /// \htmlinclude PHPSyntaxTop.html
    /// int GetDisplayHeight();
    /// \htmlinclude SyntaxBottom.html
    ///
    /// \return
    /// Returns the height of the map display in pixels.
    ///
    /// <!-- Example (PHP) -->
    /// \htmlinclude PHPExampleTop.html
    /// See \link MgMap MgMap Class \endlink.
    /// \htmlinclude ExampleBottom.html
    ///
    INT32 GetDisplayHeight();

    //////////////////////////////////////////////////////////////////
    /// \brief
    /// Gets the number of finite display scales in the map.
    ///
    /// <!-- Syntax in .Net, Java, and PHP -->
    /// \htmlinclude DotNetSyntaxTop.html
    /// int GetFiniteDisplayScaleCount();
    /// \htmlinclude SyntaxBottom.html
    /// \htmlinclude JavaSyntaxTop.html
    /// int GetFiniteDisplayScaleCount();
    /// \htmlinclude SyntaxBottom.html
    /// \htmlinclude PHPSyntaxTop.html
    /// int GetFiniteDisplayScaleCount();
    /// \htmlinclude SyntaxBottom.html
    ///
    /// \return
    /// Returns the number of finite display scales in the map.
    ///
    /// <!-- Example (PHP) -->
    /// \htmlinclude PHPExampleTop.html
    /// See \link MgMap MgMap Class \endlink.
    /// \htmlinclude ExampleBottom.html
    ///
    INT32 GetFiniteDisplayScaleCount();

    //////////////////////////////////////////////////////////////////
    /// \brief
    /// Gets the finite display scale at the specified index.
    ///
    /// <!-- Syntax in .Net, Java, and PHP -->
    /// \htmlinclude DotNetSyntaxTop.html
    /// int GetFiniteDisplayScaleAt(int index);
    /// \htmlinclude SyntaxBottom.html
    /// \htmlinclude JavaSyntaxTop.html
    /// int GetFiniteDisplayScaleAt(int index);
    /// \htmlinclude SyntaxBottom.html
    /// \htmlinclude PHPSyntaxTop.html
    /// int GetFiniteDisplayScaleAt(int index);
    /// \htmlinclude SyntaxBottom.html
    ///
    /// \param index (int)
    /// Index of the finite display scale to get.
    ///
    /// \return
    /// Returns the finite display scale.
    ///
    /// <!-- Example (PHP) -->
    /// \htmlinclude PHPExampleTop.html
    /// See \link MgMap MgMap Class \endlink.
    /// \htmlinclude ExampleBottom.html
    ///
    /// \exception MgOutOfRangeException if the index is invalid.
    ///
    double GetFiniteDisplayScaleAt(INT32 index);

EXTERNAL_API:

    //////////////////////////////////////////////////////////////////
    /// \brief
    /// Returns the background color for the map
    ///
    /// \return
    /// Background color.
    ///
    STRING GetBackgroundColor();

    //////////////////////////////////////////////////////////////////
    /// \brief
    /// Serialize data to a TCP/IP stream.
    ///
    /// \param stream
    /// Stream.
    ///
    virtual void Serialize(MgStream* stream);

    //////////////////////////////////////////////////////////////////
    /// \brief
    /// Deserialize data from a TCP/IP stream.
    ///
    /// \param stream
    /// Stream.
    ///
    virtual void Deserialize(MgStream* stream);

INTERNAL_API:

    //////////////////////////////////////////////////////////////////
    /// \brief
    /// Does it allow to set the name
    ///
    /// \return
    /// true - allows to set the name
    /// false - can not set the name
    ///
    virtual bool CanSetName();


    enum LayerRefreshMode
    {
        unspecified,
        refreshAll,
        refreshNone,
    };

    //////////////////////////////////////////////////////////////////
    /// Set the refresh mode for all layers in this map
    void SetLayerRefreshMode(LayerRefreshMode refreshMode);

    //////////////////////////////////////////////////////////////////
    /// Get the refresh mode for all layers in this map
    LayerRefreshMode GetLayerRefreshMode();

    /// \brief
    /// Destruct a MgMap object
    ///
    /// \return
    /// Nothing
    ///
    virtual ~MgMapBase();

    /// \brief
    /// Sets the current center point of the map, in the spatial reference system of the map
    ///
    /// \param center
    /// Center of the map
    ///
    void SetViewCenter(MgPoint* center);

    /// \brief
    /// Sets the current scale of the map
    ///
    /// \param scale
    /// Scale of the map
    ///
    void SetViewScale(double scale);

    /// \brief
    /// Sets the extent of the data to be generated for the map in the spatial reference system of the map.
    /// This method is reserved for use by ADV and should not be called directly
    ///
    /// \param extent
    /// Data extent
    ///
    void SetDataExtent(MgEnvelope* extent);

    /// \brief
    /// Sets the number of dots per inch of the map display
    /// This method is for use by the viewers and should not be called directly
    ///
    /// \param dpi
    /// Number of dots per inch of the map display
    ///
    void SetDisplayDpi(INT32 dpi);

    /// \brief
    /// Sets the current width of the map display in pixels
    /// This method is for use by the viewers and should not be called directly
    ///
    /// \param width
    /// Width of the map display in pixels
    ///
    void SetDisplayWidth(INT32 width);

    /// \brief
    /// Sets the current height of the map display in pixels
    /// This method is for use by the viewers and should not be called directly
    ///
    /// \param height
    /// Height of the map display in pixels
    ///
    void SetDisplayHeight(INT32 height);

    /// \brief
    /// Gets the meters per unit for the map coordinate system.  This is calculated
    /// when the map is created.
    ///
    /// \return
    /// Number of meters for each coordsys unit
    ///
    double GetMetersPerUnit();

    /// \brief
    /// Searches the list of finite display scales for the scale nearest the
    /// supplied scale, and returns the index of that scale.
    ///
    /// \param scale
    /// The scale to use when searching.
    ///
    /// \return
    /// The index of the finite display scale nearest the supplied scale, or -1
    /// if there are no scales.
    ///
    INT32 FindNearestFiniteDisplayScaleIndex(double scale);

    /// \brief
    /// Callback method invoked when a group is removed from the group collection
    ///
    void OnGroupRemoved(MgLayerGroup* group);

    /// \brief
    /// Callback method invoked when a group is added to the group collection
    ///
    void OnGroupAdded(MgLayerGroup* group);

    /// \brief
    /// Callback method invoked when a group visibility has changed
    ///
    void OnGroupVisibilityChanged(MgLayerGroup* group, CREFSTRING visibility);

    /// \brief
    /// Callback method invoked when the display in legend state of a group has changed
    ///
    void OnGroupDisplayInLegendChanged(MgLayerGroup* group, CREFSTRING displayInLegendState);

    /// \brief
    /// Callback method invoked when the legend label of a group has changed
    ///
    void OnGroupLegendLabelChanged(MgLayerGroup* group, CREFSTRING legendLabel);

    /// \brief
    /// Callback method invoked when the parent of a group has changed
    ///
    void OnGroupParentChanged(MgLayerGroup* group, CREFSTRING parentId);

    /// \brief
    /// Callback method invoked when a layer is removed from the layer collection
    ///
    virtual void OnLayerRemoved(MgLayerBase* layer);

    /// \brief
    /// Callback method invoked when a layer is added to the group collection
    ///
    virtual void OnLayerAdded(MgLayerBase* layer);

    /// \brief
    /// Callback method invoked when a layer visibility has changed
    ///
    virtual void OnLayerVisibilityChanged(MgLayerBase* layer, CREFSTRING visibility);

    /// \brief
    /// Callback method invoked when the display in legend state of a layer has changed
    ///
    virtual void OnLayerDisplayInLegendChanged(MgLayerBase* layer, CREFSTRING displayInLegendState);

    /// \brief
    /// Callback method invoked when the legend label of a layer has changed
    ///
    virtual void OnLayerLegendLabelChanged(MgLayerBase* layer, CREFSTRING legendLabel);

    /// \brief
    /// Callback method invoked when the parent of a layer has changed
    ///
    virtual void OnLayerParentChanged(MgLayerBase* layer, CREFSTRING parentId);

    /// \brief
    /// Callback method invoked when the selectability of a layer has changed
    ///
    virtual void OnLayerSelectabilityChanged(MgLayerBase* layer, CREFSTRING selectability);

    /// \brief
    /// Callback method invoked when the selectability of a layer has changed
    ///
    virtual void OnLayerDefinitionChanged(MgLayerBase* layer);

    //////////////////////////////////////////////////////////////////
    /// \brief
    /// Get the changelists. Returns an empty collection of no changes were tracked
    ///
    MgNamedCollection* GetChangeLists();

    //////////////////////////////////////////////////////////////////
    /// \brief
    /// Clear any changes that have been made to layer or groups of this map
    ///
    void ClearChanges();

    //////////////////////////////////////////////////////////////////
    /// \brief
    /// Reset refresh flag for all the layers of this map
    ///
    void ResetLayersRefresh();

protected:

    void TrackChange(CREFSTRING objectId, bool layer, MgObjectChange::ChangeType type, CREFSTRING param);

    /// \brief
    /// Get the unique identifier for the class
    ///
    /// \return
    /// Class Identifider.
    ///
    virtual INT32 GetClassId()
    {
        return m_cls_id;
    }

    /// \brief
    /// Dispose this object.
    ///
    /// \return
    /// Returns nothing
    ///
    virtual void Dispose();

    virtual const char* GetResourceTypeName();

CLASS_ID:
    static const INT32 m_cls_id = PlatformBase_MapLayer_Map;

protected:
    STRING                    m_name;
    STRING                    m_objectId;
    Ptr<MgResourceIdentifier> m_mapDefinitionId;
    STRING                    m_srs;
    Ptr<MgLayerCollection>    m_layers;
    Ptr<MgLayerGroupCollection> m_groups;
    MgPoint*                  m_center;
    double                    m_scale;
    MgEnvelope*               m_mapExtent;
    MgEnvelope*               m_dataExtent;
    INT32                     m_displayDpi;
    INT32                     m_displayWidth;
    INT32                     m_displayHeight;
    Ptr<MgNamedCollection>    m_changeLists;
    bool                      m_trackChangesDisabled;
    LayerRefreshMode          m_layerRefreshMode;
    STRING                    m_backColor;
    double                    m_metersPerUnit;
    FINITESCALES              m_finiteDisplayScales;
};
/// \}

#endif
