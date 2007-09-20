//
//  Copyright (C) 2004-2007 by Autodesk, Inc.
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

#ifndef MG_FEATURE_SERVICE_H_
#define MG_FEATURE_SERVICE_H_

/// \defgroup MgFeatureService MgFeatureService
/// \ingroup Feature_Service_classes
/// \{

#include "FeatureServiceCommon.h"
#include "FeatureDefs.h"
#include "DataPropertyDefinition.h"
#include "ObjectPropertyDefinition.h"
#include "GeometricPropertyDefinition.h"
#include "RasterPropertyDefinition.h"
#include "ClassDefinition.h"
#include "Reader.h"
#include "FeatureReader.h"
#include "FeatureSet.h"
#include "SqlDataReader.h"
#include "DataReader.h"
#include "SpatialContextReader.h"
#include "LongTransactionReader.h"
#include "FeatureCommand.h"
#include "FeatureCommandCollection.h"
#include "DeleteFeatures.h"
#include "InsertFeatures.h"
#include "UpdateFeatures.h"
#include "Raster.h"
#include "RasterProperty.h"
#include "GeometryProperty.h"
#include "FeatureProperty.h"
#include "FeatureQueryOptions.h"
#include "FeatureAggregateOptions.h"
#include "FeatureSchema.h"
#include "FeatureSchemaCollection.h"
#include "ClassDefinitionCollection.h"
#include "FeatureSourceParams.h"
#include "CreateSdfParams.h"
#include "GwsFeatureReader.h"

class MgIntCollection;
class MgBatchPropertyCollection;

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// \brief
/// Provides an abstraction layer for the storage and retrieval
/// of feature data in a technology-independent way. The API
/// lets you determine what storage technologies are available
/// and what capabilities they have. Access to the storage
/// technology is modeled as a connection. For example, you can
/// connect to a file and do simple insertions or connect to a
/// relational database and do transaction-based operations.
///
/// \remarks
/// The following use cases are supported:
/// <ul>
///   <li>Connection to a datastore. See
///     MgFeatureService::GetFeatureProviders,
///     MgFeatureService::GetConnectionPropertyValues, \link MgFeatureService::TestConnection MgFeatureService::TestConnection Method (CREFSTRING, CREFSTRING) \endlink,
///     and \link MgFeatureService::TestConnection MgFeatureService::TestConnection Method (MgResourceIdentifier*) \endlink.
///   </li>
///   <li>Description of the capabilities of the FDO provider
///     providing access to the datastore. See
///     MgFeatureService::GetProviderCapabilities.
///   </li>
///   <li>Insertion, deletion, and update of feature data. See
///     MgFeatureService::UpdateFeatures, MgInsertFeatures,
///     MgDeleteFeatures, and MgUpdateFeatures.
///   </li>
///   <li>Selection of feature data. See
///     MgFeatureService::SelectFeatures and
///     MgFeatureService::SelectAggregate.
///   </li>
///   <li>Description of the schema used to store feature data. See
///     MgFeatureService::DescribeSchema,
///     MgFeatureService::DescribeSchemaAsXml,
///     MgFeatureService::GetSchemas, MgFeatureService::SchemaToXml,
///     MgFeatureService::GetClasses and
///     MgFeatureService::GetClassDefinition. See also \link Feature_Schema_Module Feature Schema \endlink.
///   </li>
///   <li>Creation of an SDF feature source to cache feature data
///     from other datastores. See
///     MgFeatureService::CreateFeatureSource. Using the latter
///     requires describing the schema in the source datastore.
///     Transporting the features from the source datastore requires
///     selecting them from the source and inserting them in the
///     target.
///   </li>
///   <li>Execute SQL commands. See
///     MgFeatureService::ExecuteSqlNonQuery and
///     MgFeatureService::ExecuteSqlQuery.
///   </li>
///   <li>Get the spatial contexts contained in the datastore. See
///     MgFeatureService::GetSpatialContexts.
///   </li>
/// </ul>
///
/// <!-- Example (PHP) -->
/// \htmlinclude PHPExampleTop.html
/// \code
/// <?php
/// include "C:\Program Files\MapGuideOpenSource\WebExtensions\www\mapviewerphp\constants.php";
/// $webconfigiDotIniPath = "C:\Program Files\MapGuideOpenSource\WebExtensions\www\webconfig.ini"
/// MgInitializeWebTier($webconfigiDotIniPath);
/// $adminUser = new MgUserInformation("Administrator", "admin");
/// $siteConnection = new MgSiteConnection();
/// $siteConnection->Open($adminUser);
/// $siteConnection->CreateService(MgServiceType::FeatureService);
/// ?>
/// \endcode
/// \htmlinclude ExampleBottom.html
///
/// <!-- Example (C#) -->
/// \htmlinclude CSharpExampleTop.html
/// \code
/// using OSGeo.MapGuide;
/// String webConfigFilename = <path to webconfig.ini file>;
/// MapGuideApi.MgInitializeWebTier(webConfigFilename);
/// MgUserInformation userInfo = new MgUserInformation("Administrator", "admin");
/// MgSiteConnection siteConnection = new MgSiteConnection();
/// siteConnection.Open(userInfo);
/// // Create the MgFeatureService and MgResourceService
/// MgResourceService resourceService = siteConnection.CreateService(MgServiceType.ResourceService) as MgResourceService;
/// MgFeatureService featureService = siteConnection.CreateService(MgServiceType.FeatureService) as MgFeatureService;
/// \endcode
/// \htmlinclude ExampleBottom.html
///
class MG_PLATFORMBASE_API MgFeatureService : public MgService
{
PUBLISHED_API:
    ///////////////////////////////////////////////////////////////////
    /// \brief
    /// Gets a list of the available FDO providers together with
    /// other information such as the names of the connection
    /// properties for each provider. This information is in XML
    /// format according to the \link FeatureProviderRegistry FeatureProviderRegistry \endlink
    /// schema.
    ///
    /// <!-- Syntax in .Net, Java, and PHP -->
    /// \htmlinclude DotNetSyntaxTop.html
    /// virtual MgByteReader GetFeatureProviders();
    /// \htmlinclude SyntaxBottom.html
    /// \htmlinclude JavaSyntaxTop.html
    /// virtual MgByteReader GetFeatureProviders();
    /// \htmlinclude SyntaxBottom.html
    /// \htmlinclude PHPSyntaxTop.html
    /// virtual MgByteReader GetFeatureProviders();
    /// \htmlinclude SyntaxBottom.html
    ///
    /// \return
    /// Returns an MgByteReader containing the provider registry in
    /// XML format.
    ///
    /// \exception MgFdoException
    ///
    virtual MgByteReader* GetFeatureProviders() = 0;

    ////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    /// \brief
    /// Gets a set of connection values that are used to make
    /// connections to an FDO provider that permits multiple
    /// connections.
    ///
    /// \remarks
    /// You connect to the provider using a set of values that is one
    /// value short of addressing a source of feature data. This set
    /// of values is also known as a "partial connection string".
    /// The provider returns a set of values each of which represents
    /// a final value needed to connect to feature data. You can now
    /// construct a set of "full connection strings", and you can
    /// test the validity of each of these using the \link MgFeatureService::TestConnection MgFeatureService::TestConnection Method \endlink.
    /// You make a fully functional connection using another variant
    /// of the \link MgFeatureService::TestConnection MgFeatureService::TestConnection Method \endlink.
    /// Currently, the only use for this method is to list the
    /// datastores in an Oracle database. Feature data is stored in a
    /// datastore in an Oracle database. This is explained in the
    /// section on the Oracle provider in the \link ConnectionToFeatureSource Connection To Feature Source \endlink
    /// topic.
    ///
    /// <!-- Syntax in .Net, Java, and PHP -->
    /// \htmlinclude DotNetSyntaxTop.html
    /// virtual MgStringCollection GetConnectionPropertyValues(string providerName, string propertyName, string partialConnString);
    /// \htmlinclude SyntaxBottom.html
    /// \htmlinclude JavaSyntaxTop.html
    /// virtual MgStringCollection GetConnectionPropertyValues(String providerName, String propertyName, String partialConnString);
    /// \htmlinclude SyntaxBottom.html
    /// \htmlinclude PHPSyntaxTop.html
    /// virtual MgStringCollection GetConnectionPropertyValues(string providerName, string propertyName, string partialConnString);
    /// \htmlinclude SyntaxBottom.html
    ///
    /// \param providerName (String/string)
    /// The name of the Fdo feature provider. Permissible
    /// values are obtained by calling the \link MgFeatureService::GetFeatureProviders MgFeatureService::GetFeatureProviders Method \endlink.
    /// \param propertyName (String/string)
    /// The name of the enumerable property for which
    /// values need to be retrieved. Connection property
    /// names are contained in the output of the
    /// MgFeatureService::GetFeatureProviders method.
    /// The value of the ConnectionProperty element's
    /// Enumerable attribute must be true.
    /// \param partialConnString (String/string)
    /// A partial connection string, which is sufficient
    /// to connect to a provider.
    ///
    /// \return
    /// Returns an MgStringCollection or NULL, if nothing is found.
    ///
    /// <!-- Examples (PHP) -->
    /// \htmlinclude PHPExamplesTop.html
    /// \code
    /// $datastores = $featureService->GetConnectionPropertyValues("Autodesk.Oracle", "DataStore", "Service=MapGuideService;Username=MapGuideUser;Password=test;DataStore=");
    /// \endcode
    /// \htmlinclude ExampleBottom.html
    ///
    /// \exception MgInvalidArgumentException
    /// \exception MgFdoException
    ///
    virtual MgStringCollection* GetConnectionPropertyValues( CREFSTRING providerName,
                                                             CREFSTRING propertyName,
                                                             CREFSTRING partialConnString    ) = 0;

    ///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    /// \brief
    /// Connects to the Feature Provider specified in the connection
    /// string. See \link ConnectionToFeatureSource Connection To Feature Source \endlink.
    ///
    /// \remarks
    /// You use this method to verify that the connection property
    /// values are valid. You then use these values to construct a
    /// feature source file that you will install in the repository.
    ///
    /// <!-- Syntax in .Net, Java, and PHP -->
    /// \htmlinclude DotNetSyntaxTop.html
    /// virtual bool TestConnection(string providerName, string connectionString);
    /// \htmlinclude SyntaxBottom.html
    /// \htmlinclude JavaSyntaxTop.html
    /// virtual boolean TestConnection(String providerName, String connectionString);
    /// \htmlinclude SyntaxBottom.html
    /// \htmlinclude PHPSyntaxTop.html
    /// virtual bool TestConnection(string providerName, string connectionString);
    /// \htmlinclude SyntaxBottom.html
    ///
    /// \param providerName (String/string)
    /// The name of the Fdo feature provider. Permissible
    /// values are obtained by calling the \link MgFeatureService::GetFeatureProviders MgFeatureService::GetFeatureProviders Method \endlink
    /// and looking at the values in the
    /// //FeatureProviderRegistry/FeatureProvider/Name
    /// element.
    /// \param connectionString (String/string)
    /// Connection string for Feature Provider. Connection
    /// property names that appear in the connection string
    /// as keys can be obtained from the output of
    /// GetFeatureProviders method. Look at the
    /// //FeatureProviderRegistry/FeatureProvider/ConnectionProperties/ConnectionProperty/Name
    /// elements.
    ///
    /// \return
    /// Returns true if the connection was successful; otherwise
    /// returns false.
    ///
    /// <!-- Example (PHP) -->
    /// \htmlinclude PHPExampleTop.html
    /// $boolResult =
    /// $featureService->TestConnection("Autodesk.Oracle",
    /// "Service=MapGuideService;Username=MapGuideUser;Password=test;DataStore=MapGuide");
    /// \htmlinclude ExampleBottom.html
    ///
    /// \exception MgFdoException
    ///
    virtual bool TestConnection(CREFSTRING providerName, CREFSTRING connectionString) = 0;

    /////////////////////////////////////////////////////////////////////////////////////////////////////
    /// \brief
    /// Connects to the feature source specified by the resource
    /// identifier and verifies that the feature source has been
    /// correctly configured and installed in the resource
    /// repository. See \link ConnectionToFeatureSource Connection To Feature Source \endlink.
    ///
    /// <!-- Syntax in .Net, Java, and PHP -->
    /// \htmlinclude DotNetSyntaxTop.html
    /// virtual bool TestConnection(MgResourceIdentifier resource);
    /// \htmlinclude SyntaxBottom.html
    /// \htmlinclude JavaSyntaxTop.html
    /// virtual boolean TestConnection(MgResourceIdentifier resource);
    /// \htmlinclude SyntaxBottom.html
    /// \htmlinclude PHPSyntaxTop.html
    /// virtual bool TestConnection(MgResourceIdentifier resource);
    /// \htmlinclude SyntaxBottom.html
    ///
    /// \param resource (MgResourceIdentifier)
    /// The resource identifier for the
    /// feature source.
    ///
    /// \return
    /// Returns true if connection was successful; otherwise returns
    /// false.
    ///
    /// <!-- Example (PHP) -->
    /// \htmlinclude PHPExampleTop.html
    /// \code
    /// $boolResult = $featureService->TestConnection("Library://FeatureService/testSHP.FeatureSource");
    /// \endcode
    /// \htmlinclude ExampleBottom.html
    ///
    /// \exception MgFdoException
    ///
    /// <!-- Example (C#) -->
    /// \htmlinclude CSharpExampleTop.html
    /// \code
    /// using OSGeo.MapGuide;
    /// // the SDF file identified by this MgResourceIdentifier exists in the repository
    /// private MgResourceIdentifier resourceId;
    /// private Boolean connected;
    /// private MgFeatureService featureService;
    ///
    /// resourceId = new MgResourceIdentifier("Library://PlatformApiDocTests/SdfFeatureClass.FeatureSource");
    /// // see the comments preceding the class declaration for code showing the creation of MgFeatureService object
    /// connected = featureService.TestConnection(resourceId);
    /// \endcode
    /// \htmlinclude ExampleBottom.html
    ///
    virtual bool TestConnection(MgResourceIdentifier* resource) = 0;

    /////////////////////////////////////////////////////////////////////////////////////////////
    /// \brief
    /// Gets the capabilities of an FDO Provider expressed in XML
    /// according to the \link FdoProviderCapabilities_schema FdoProviderCapabilities \endlink schema.
    ///
    /// \remarks
    /// MgFeatureService derives most of its capabilities from the
    /// FDO Provider to which it is connected. Capabilities vary
    /// among providers. For example, the FDO Provider for ArcSDE
    /// supports all of the spatial operators, and the FDO Provider
    /// for Oracle supports only a subset. For a fuller discussion,
    /// see \link ProviderCapabilities Provider Capabilities \endlink.
    ///
    /// <!-- Syntax in .Net, Java, and PHP -->
    /// \htmlinclude DotNetSyntaxTop.html
    /// virtual MgByteReader GetCapabilities(string providerName);
    /// \htmlinclude SyntaxBottom.html
    /// \htmlinclude JavaSyntaxTop.html
    /// virtual MgByteReader GetCapabilities(String providerName);
    /// \htmlinclude SyntaxBottom.html
    /// \htmlinclude PHPSyntaxTop.html
    /// virtual MgByteReader GetCapabilities(string providerName);
    /// \htmlinclude SyntaxBottom.html
    ///
    /// \param providerName (String/string)
    /// The name of the FDO provider. Get the exact
    /// form of the name from
    /// MgFeatureService::GetFeatureProviders.
    ///
    /// \return
    /// Returns an MgByteReader containing the capabilities in XML
    /// format (or NULL).
    ///
    /// \exception MgInvalidArgumentException
    /// \exception MgFdoException
    ///
    virtual MgByteReader* GetCapabilities(CREFSTRING providerName) = 0;

    ////////////////////////////////////////////////////////////////////////////////////////////////////////
    /// \brief
    /// Gets the definitions of one or more schema contained in the
    /// feature source. See \link Feature_Schema_Module Feature Schema \endlink.
    ///
    /// <!-- Syntax in .Net, Java, and PHP -->
    /// \htmlinclude DotNetSyntaxTop.html
    /// virtual MgFeatureSchemaCollection DescribeSchema(MgResourceIdentifier resource, string schemaName);
    /// \htmlinclude SyntaxBottom.html
    /// \htmlinclude JavaSyntaxTop.html
    /// virtual MgFeatureSchemaCollection DescribeSchema(MgResourceIdentifier resource, String schemaName);
    /// \htmlinclude SyntaxBottom.html
    /// \htmlinclude PHPSyntaxTop.html
    /// virtual MgFeatureSchemaCollection DescribeSchema(MgResourceIdentifier resource, string schemaName);
    /// \htmlinclude SyntaxBottom.html
    ///
    /// \param resource (MgResourceIdentifier)
    /// A resource identifier for the feature
    /// source.
    /// \param schemaName (String/string)
    /// The name of the schema definition to
    /// retrieve or an empty string to retrieve
    /// all available schema definitions.
    ///
    /// \return
    /// Returns an MgFeatureSchemaCollection.
    ///
    /// \exception MgFeatureServiceException
    /// \exception MgInvalidArgumentException
    /// \exception MgFdoException
    ///
    /// \note
    /// Please refer to Overview section of this document or Fdo
    /// provider documents for details on connection properties,
    /// schema and classes.
    virtual MgFeatureSchemaCollection* DescribeSchema( MgResourceIdentifier* resource,
                                          CREFSTRING schemaName ) = 0;

    /////////////////////////////////////////////////////////////////////////////////////////
    /// \brief
    /// Gets the definition in XML format of a schema contained in
    /// the feature source. See \link Feature_Schema_Module Feature Schema \endlink.
    ///
    /// \remarks
    /// The XML representation of the schema definitions conforms to
    /// FDO XML schema, which are based on OGC GML schema. How to
    /// specify a schema definition in XML is discussed in the
    /// Autodesk FDO API Developer's Guide.
    ///
    /// <!-- Syntax in .Net, Java, and PHP -->
    /// \htmlinclude DotNetSyntaxTop.html
    /// virtual string DescribeSchemaAsXml(MgResourceIdentifier resource, string schemaName);
    /// \htmlinclude SyntaxBottom.html
    /// \htmlinclude JavaSyntaxTop.html
    /// virtual String DescribeSchemaAsXml(MgResourceIdentifier resource, String schemaName);
    /// \htmlinclude SyntaxBottom.html
    /// \htmlinclude PHPSyntaxTop.html
    /// virtual string DescribeSchemaAsXml(MgResourceIdentifier resource, string schemaName);
    /// \htmlinclude SyntaxBottom.html
    ///
    /// \param resource (MgResourceIdentifier)
    /// The resource identifier for the feature
    /// source
    /// \param schemaName (String/string)
    /// The name of the schema definition to
    /// retrieve or an empty string to retrieve
    /// all available schema definitions.
    ///
    /// \return
    /// Returns a string containing the FDO schema in XML format.
    ///
    /// \exception MgFeatureServiceException
    /// \exception MgInvalidArgumentException
    /// \exception MgFdoException
    ///
    virtual STRING DescribeSchemaAsXml( MgResourceIdentifier* resource,
                                          CREFSTRING schemaName ) = 0;

    ////////////////////////////////////////////////////////////////////////////
    /// \brief
    /// Translates the FDO schema information in the provided
    /// MgFeatureSchemaCollection object into a string containing an
    /// XML representation of the schema definitions in the feature
    /// source. See \link Feature_Schema_Module Feature Schema \endlink.
    ///
    /// \remarks
    /// The XML representation of the schema definitions conforms to
    /// FDO XML schema, which are based on OGC GML schema. How to
    /// specify a schema definition in XML is discussed in the
    /// Autodesk FDO API Developer's Guide.
    ///
    /// <!-- Syntax in .Net, Java, and PHP -->
    /// \htmlinclude DotNetSyntaxTop.html
    /// virtual string SchemaToXml(MgFeatureSchemaCollection schema);
    /// \htmlinclude SyntaxBottom.html
    /// \htmlinclude JavaSyntaxTop.html
    /// virtual String SchemaToXml(MgFeatureSchemaCollection schema);
    /// \htmlinclude SyntaxBottom.html
    /// \htmlinclude PHPSyntaxTop.html
    /// virtual string SchemaToXml(MgFeatureSchemaCollection schema);
    /// \htmlinclude SyntaxBottom.html
    ///
    /// \param schema (MgFeatureSchemaCollection)
    /// A FeatureSchemaCollection
    /// object.
    ///
    /// \return
    /// Returns a string containiing a set of FDO schema definitions
    /// in XML format.
    ///
    /// \exception MgFeatureServiceException
    /// \exception MgNullArgumentException
    /// \exception MgFdoException
    ///
    virtual STRING SchemaToXml(MgFeatureSchemaCollection* schema) = 0;

    //////////////////////////////////////////////////////////////////////////
    /// \brief
    /// Creates an MgFeatureSchemaCollection object using the XML
    /// schema provided
    ///
    /// \remarks
    /// The XML representation of the schema definitions conforms to
    /// FDO XML schema, which are based on OGC GML schema. How to
    /// specify a schema definition in XML is discussed in the
    /// Autodesk FDO API Developer's Guide.
    ///
    /// <!-- Syntax in .Net, Java, and PHP -->
    /// \htmlinclude DotNetSyntaxTop.html
    /// virtual MgFeatureSchemaCollection XmlToSchema(string xml);
    /// \htmlinclude SyntaxBottom.html
    /// \htmlinclude JavaSyntaxTop.html
    /// virtual MgFeatureSchemaCollection XmlToSchema(String xml);
    /// \htmlinclude SyntaxBottom.html
    /// \htmlinclude PHPSyntaxTop.html
    /// virtual MgFeatureSchemaCollection XmlToSchema(string xml);
    /// \htmlinclude SyntaxBottom.html
    ///
    /// \param xml (String/string)
    /// A string containing schema definitions
    /// in XML format.
    ///
    /// \return
    /// Returns an MgFeatureSchemaCollection object.
    ///
    /// \exception MgNullArgumentException
    /// \exception MgFdoException
    ///
    virtual MgFeatureSchemaCollection* XmlToSchema(CREFSTRING xml) = 0;

    //////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    /// \brief
    /// Selects features from a feature source according to the
    /// criteria set in the MgFeatureQueryOptions argument The
    /// criteria are applied to all of the features in the feature
    /// source. If you want to apply the criteria to a subset of the
    /// features, use MgFeatureService::SelectAggregate.
    /// See \link FiltersAndExpressions Filters and expressions \endlink.
    ///
    /// \remarks
    /// Be sure to Close() the MgFeatureReader object returned by this method.
    ///
    /// <!-- Syntax in .Net, Java, and PHP -->
    /// \htmlinclude DotNetSyntaxTop.html
    /// virtual MgFeatureReader SelectFeatures(MgResourceIdentifier resource, string className, MgFeatureQueryOptions options);
    /// \htmlinclude SyntaxBottom.html
    /// \htmlinclude JavaSyntaxTop.html
    /// virtual MgFeatureReader SelectFeatures(MgResourceIdentifier resource, String className, MgFeatureQueryOptions options);
    /// \htmlinclude SyntaxBottom.html
    /// \htmlinclude PHPSyntaxTop.html
    /// virtual MgFeatureReader SelectFeatures(MgResourceIdentifier resource, string className, MgFeatureQueryOptions options);
    /// \htmlinclude SyntaxBottom.html
    ///
    /// \param resource (MgResourceIdentifier)
    /// A resource identifier for the feature
    /// source.
    /// \param className (String/string)
    /// The name of the feature class from which
    /// the properties of interest are selected.
    /// \param options (MgFeatureQueryOptions)
    /// MgFeatureQueryOptions instance
    /// containing all required filters for this
    /// select operation.
    ///
    /// \return
    /// Returns an MgFeatureReader containing the set of selected
    /// features.
    ///
    /// \exception MgFeatureServiceException
    /// \exception MgInvalidArgumentException
    /// \exception MgFdoException
    ///
    virtual MgFeatureReader*  SelectFeatures(   MgResourceIdentifier* resource,
                                                CREFSTRING className,
                                                MgFeatureQueryOptions* options ) = 0;

    //////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    /// \brief
    /// Selects features from a feature source according to the
    /// criteria set in the MgFeatureQueryOptions argument The
    /// criteria are applied to all of the features in the feature
    /// source. Use the coordinateSystem argument to set the target
    /// coordinate system if you want to transform.
    /// If you want to apply the criteria to a subset of the
    /// features, use MgFeatureService::SelectAggregate.
    /// See \link FiltersAndExpressions Filters and expressions \endlink.
    ///
    /// \remarks
    /// Be sure to Close() the MgFeatureReader object returned by this method.
    ///
    /// <!-- Syntax in .Net, Java, and PHP -->
    /// \htmlinclude DotNetSyntaxTop.html
    /// virtual MgFeatureReader SelectFeatures(MgResourceIdentifier resource, string className, MgFeatureQueryOptions options, string coordinateSystem);
    /// \htmlinclude SyntaxBottom.html
    /// \htmlinclude JavaSyntaxTop.html
    /// virtual MgFeatureReader SelectFeatures(MgResourceIdentifier resource, String className, MgFeatureQueryOptions options, String coordinateSystem);
    /// \htmlinclude SyntaxBottom.html
    /// \htmlinclude PHPSyntaxTop.html
    /// virtual MgFeatureReader SelectFeatures(MgResourceIdentifier resource, string className, MgFeatureQueryOptions options, string coordinateSystem);
    /// \htmlinclude SyntaxBottom.html
    ///
    /// \param resource (MgResourceIdentifier)
    /// A resource identifier for the feature
    /// source.
    /// \param className (String/string)
    /// The name of the feature class from which
    /// the properties of interest are selected.
    /// \param options (MgFeatureQueryOptions)
    /// MgFeatureQueryOptions instance
    /// containing all required filters for this
    /// select operation.
    /// \param coordinateSystem (String/string)
    /// The name of the coordinate system to transform to.
    ///
    /// \return
    /// Returns an MgFeatureReader containing the set of selected
    /// features.
    ///
    /// \exception MgFeatureServiceException
    /// \exception MgInvalidArgumentException
    /// \exception MgFdoException
    ///
    virtual MgFeatureReader*  SelectFeatures(   MgResourceIdentifier* resource,
                                                CREFSTRING className,
                                                MgFeatureQueryOptions* options,
                                                CREFSTRING coordinateSystem ) = 0;

    //////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    /// \brief
    /// Selects groups of features from a feature source and applies
    /// filters to each of the groups according to the criteria set
    /// in the MgFeatureAggregateOptions argument. If you want to
    /// apply the criteria to all features without grouping them, use
    /// the \link MgFeatureService::SelectFeatures MgFeatureService::SelectFeatures Method \endlink.
    /// See \link FiltersAndExpressions Filters and expressions \endlink.
    ///
    /// \remarks
    /// Be sure to Close() the MgDataReader object returned by this method.
    ///
    /// <!-- Syntax in .Net, Java, and PHP -->
    /// \htmlinclude DotNetSyntaxTop.html
    /// virtual MgDataReader SelectAggregate(MgResourceIdentifier resource, string className, MgFeatureAggregateOptions options);
    /// \htmlinclude SyntaxBottom.html
    /// \htmlinclude JavaSyntaxTop.html
    /// virtual MgDataReader SelectAggregate(MgResourceIdentifier resource, String className, MgFeatureAggregateOptions options);
    /// \htmlinclude SyntaxBottom.html
    /// \htmlinclude PHPSyntaxTop.html
    /// virtual MgDataReader SelectAggregate(MgResourceIdentifier resource, string className, MgFeatureAggregateOptions options);
    /// \htmlinclude SyntaxBottom.html
    ///
    /// \param resource (MgResourceIdentifier)
    /// A resource identifier for the feature
    /// source.
    /// \param className (String/string)
    /// The name of the feature class on which
    /// the select operation is performed.
    /// \param options (MgFeatureAggregateOptions)
    /// An MgFeatureAggregateOptions instance
    /// containing all the criteria and filters
    /// required for this select operation.
    ///
    /// \return
    /// Returns an MgDataReader containing the group values.
    ///
    /// \exception MgFeatureServiceException
    /// \exception MgInvalidArgumentException
    /// \exception MgFdoException
    ///
    virtual MgDataReader*  SelectAggregate( MgResourceIdentifier* resource,
                                            CREFSTRING className,
                                            MgFeatureAggregateOptions* options ) = 0;

    ////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    /// \brief
    /// Executes the MgDeleteFeatures, MgInsertFeatures,
    /// MgUpdateFeatures, MgLockFeatures or MgUnlockFeatures commands
    /// contained in the given MgFeatureCommandCollection object.
    ///
    /// \remarks
    /// The XML returned by MgFeatureService::GetCapabilities says
    /// whether a provider supports SQL commands. See \link ProviderCapabilities Provider Capabilities \endlink.
    ///
    /// <!-- Syntax in .Net, Java, and PHP -->
    /// \htmlinclude DotNetSyntaxTop.html
    /// virtual MgPropertyCollection UpdateFeatures(MgResourceIdentifier resource, MgFeatureCommandCollection commands, bool useTransaction);
    /// \htmlinclude SyntaxBottom.html
    /// \htmlinclude JavaSyntaxTop.html
    /// virtual MgPropertyCollection UpdateFeatures(MgResourceIdentifier resource, MgFeatureCommandCollection commands, boolean useTransaction);
    /// \htmlinclude SyntaxBottom.html
    /// \htmlinclude PHPSyntaxTop.html
    /// virtual MgPropertyCollection UpdateFeatures(MgResourceIdentifier resource, MgFeatureCommandCollection commands, bool useTransaction);
    /// \htmlinclude SyntaxBottom.html
    ///
    /// \param resource (MgResourceIdentifier)
    /// A resource identifier for the feature
    /// source.
    /// \param commands (MgFeatureCommandCollection)
    /// A collection of feature commands to be
    /// executed.
    /// \param useTransaction (boolean/bool)
    /// If true and transactions are supported
    /// by the Fdo provider, execute all
    /// commands inside a transaction. If false,
    /// do not use a transaction.
    ///
    /// \return
    /// Returns an MgPropertyCollection object. Each property in the
    /// collection corresponds to a command in the
    /// MgFeatureCommandCollection argument. The property name is the
    /// index of the command in the feature command collection.
    /// <ul>
    ///   <li>If the command is of type MgDeleteFeatures, the property
    ///     type is an MgPropertyType::Int32, and its value is the number
    ///     of features deleted.</li>
    ///   <li>If the command is of type MgInsertFeatures, the property
    ///     type is an MgPropertyType::Feature, and its value is a
    ///     MgFeatureReader object. The feature reader object contains
    ///     the set of properties inserted into the datastore by the
    ///     insert command.</li>
    ///   <li>If the command is of type MgUpdateFeatures, the property
    ///     type is MgPropertyType::Int32, and its value is the number of
    ///     features updated.</li>
    ///   <li>If the command is of type MgLockFeatures, the property
    ///     type is MgPropertyType::Feature, and its value is the number
    ///     of features locked.</li>
    ///   <li>If the command is of type MgUnLockFeatures, the property
    ///     type is MgPropertyType::Int32, and its value is the number of
    ///     features unlocked.</li>
    /// </ul>
    ///
    /// \exception MgFeatureServiceException
    /// \exception MgInvalidArgumentException
    /// \exception MgInvalidOperationException
    /// \exception MgFdoException
    ///
    virtual MgPropertyCollection* UpdateFeatures( MgResourceIdentifier* resource,
                                                  MgFeatureCommandCollection* commands,
                                                  bool useTransaction ) = 0;

    ////////////////////////////////////////////////////////////////////////////////////////////////
    /// \brief
    /// Gets the locked features
    ///
    /// \remarks
    ///
    /// <!-- Syntax in .Net, Java, and PHP -->
    /// \htmlinclude DotNetSyntaxTop.html
    /// virtual MgFeatureReader GetLockedFeatures(MgResourceIdentifier resource, string className, MgFeatureAggregateOptions options);
    /// \htmlinclude SyntaxBottom.html
    /// \htmlinclude JavaSyntaxTop.html
    /// virtual MgFeatureReader GetLockedFeatures(MgResourceIdentifier resource, String className, MgFeatureAggregateOptions options);
    /// \htmlinclude SyntaxBottom.html
    /// \htmlinclude PHPSyntaxTop.html
    /// virtual MgFeatureReader GetLockedFeatures(MgResourceIdentifier resource, string className, MgFeatureAggregateOptions options);
    /// \htmlinclude SyntaxBottom.html
    ///
    /// \param resource (MgResourceIdentifier)
    /// A resource identifier for the feature
    /// source.
    /// \param className (String/string)
    /// The name of the feature class on which
    /// the select operation is performed.
    /// \param options (MgFeatureAggregateOptions)
    /// An MgFeatureAggregateOptions instance
    /// containing all the criteria and filters
    /// required for this select operation.
    ///
    /// \return
    /// Returns an MgFeatureReader containing the locked features.
    ///
    /// \exception MgFeatureServiceException
    /// \exception MgInvalidArgumentException
    /// \exception ...
    ///
    virtual MgFeatureReader* GetLockedFeatures( MgResourceIdentifier* resource,
                                                CREFSTRING className,
                                                MgFeatureQueryOptions* options ) = 0;

    ////////////////////////////////////////////////////////////////////////////////////////////////
    /// \brief
    /// Executes the SQL SELECT statement on the specified feature
    /// source.
    ///
    /// \remarks
    /// The XML returned by MgFeatureService::GetCapabilities says
    /// whether a provider supports SQL commands. See \link ProviderCapabilities Provider Capabilities \endlink.
    ///
    /// <!-- Syntax in .Net, Java, and PHP -->
    /// \htmlinclude DotNetSyntaxTop.html
    /// virtual MgSqlDataReader ExecuteSqlQuery(MgResourceIdentifier resource, string sqlStatement);
    /// \htmlinclude SyntaxBottom.html
    /// \htmlinclude JavaSyntaxTop.html
    /// virtual MgSqlDataReader ExecuteSqlQuery(MgResourceIdentifier resource, String sqlStatement);
    /// \htmlinclude SyntaxBottom.html
    /// \htmlinclude PHPSyntaxTop.html
    /// virtual MgSqlDataReader ExecuteSqlQuery(MgResourceIdentifier resource, string sqlStatement);
    /// \htmlinclude SyntaxBottom.html
    ///
    /// \param resource (MgResourceIdentifier)
    /// A resource identifier referring
    /// to a feature source.
    /// \param sqlStatement (String/string)
    /// The SQL SELECT statement.
    ///
    /// \return
    /// Returns an MgSqlDataReader instance (or NULL).
    ///
    /// \note
    /// If any statement other than SELECT is passed to this method,
    /// it will throw an MgFdoException.
    ///
    /// <!-- Example (PHP) -->
    /// \htmlinclude PHPExampleTop.html
    /// \code
    /// $sql = "select featid,abyte from featclass where featid = 0";
    /// $sqlDataReader = $featureService->ExecuteSqlQuery($activeFeatSrcResId, $sql);
    /// \endcode
    /// \htmlinclude ExampleBottom.html
    ///
    /// \exception MgFeatureServiceException
    /// \exception MgInvalidArgumentException
    /// \exception MgInvalidOperationException
    /// \exception MgFdoException
    ///
    virtual MgSqlDataReader* ExecuteSqlQuery( MgResourceIdentifier* resource,
                                              CREFSTRING sqlStatement ) = 0;

    ////////////////////////////////////////////////////////////////////////////////////////////////
    /// \brief
    /// Executes SQL statements NOT including SELECT statements.
    ///
    /// \remarks
    /// The XML returned by MgFeatureService::GetCapabilities says
    /// whether a provider supports SQL commands. See \link ProviderCapabilities Provider Capabilities \endlink.
    ///
    /// <!-- Syntax in .Net, Java, and PHP -->
    /// \htmlinclude DotNetSyntaxTop.html
    /// virtual int ExecuteSqlNonQuery(MgResourceIdentifier resource, string sqlNonSelectStatement);
    /// \htmlinclude SyntaxBottom.html
    /// \htmlinclude JavaSyntaxTop.html
    /// virtual int ExecuteSqlNonQuery(MgResourceIdentifier resource, String sqlNonSelectStatement);
    /// \htmlinclude SyntaxBottom.html
    /// \htmlinclude PHPSyntaxTop.html
    /// virtual int ExecuteSqlNonQuery(MgResourceIdentifier resource, string sqlNonSelectStatement);
    /// \htmlinclude SyntaxBottom.html
    ///
    /// \param resource (MgResourceIdentifier)
    /// A resource identifier for a
    /// feature source.
    /// \param sqlNonSelectStatement (String/string)
    /// The SQL statement that is NOT a
    /// SELECT statement.
    ///
    /// \return
    /// Returns a positive integer value indicating how many
    /// instances (rows) have been affected.
    ///
    /// <!-- Example (PHP) -->
    /// \htmlinclude PHPExampleTop.html
    /// \code
    /// $sql = "update featclass set abyte = 37 where featid = 0";
    /// $numRows = $featureService->ExecuteSqlNonQuery($activeFeatSrcResId, $sql);
    /// \endcode
    /// \htmlinclude ExampleBottom.html
    ///
    /// \exception MgFeatureServiceException
    /// \exception MgInvalidArgumentException
    /// \exception MgInvalidOperationException
    /// \exception MgFdoException
    ///
    virtual INT32 ExecuteSqlNonQuery( MgResourceIdentifier* resource,
                                      CREFSTRING sqlNonSelectStatement ) = 0;

    //////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    /// \brief
    /// Gets all of the spatial contexts available in the feature
    /// source or just the active one.
    ///
    /// \remarks
    /// The \link FdoSpatialContextList_schema FdoSpatialContextList \endlink XML schema contains
    /// a specification of the content of the spatial context
    /// information returned in the MgSpatialContextReader object.
    ///
    /// <!-- Syntax in .Net, Java, and PHP -->
    /// \htmlinclude DotNetSyntaxTop.html
    /// virtual MgSpatialContextReader GetSpatialContexts(MgResourceIdentifier resource, bool bActiveOnly = false);
    /// \htmlinclude SyntaxBottom.html
    /// \htmlinclude JavaSyntaxTop.html
    /// virtual MgSpatialContextReader GetSpatialContexts(MgResourceIdentifier resource, boolean bActiveOnly = false);
    /// \htmlinclude SyntaxBottom.html
    /// \htmlinclude PHPSyntaxTop.html
    /// virtual MgSpatialContextReader GetSpatialContexts(MgResourceIdentifier resource, bool bActiveOnly = false);
    /// \htmlinclude SyntaxBottom.html
    ///
    /// \param resource (MgResourceIdentifier)
    /// A resource identifier identifying a feature
    /// source in the repository.
    /// \param bActiveOnly (boolean/bool)
    /// If true, the return value contains only the
    /// active spatial context. If false, the return
    /// value contains all of the available spatial
    /// contexts.
    ///
    /// \return
    /// Returns an MgSpatialContextReader object.
    ///
    /// \exception MgFeatureServiceException
    /// \exception MgInvalidArgumentException
    /// \exception MgInvalidOperationException
    /// \exception MgFdoException
    ///
    virtual MgSpatialContextReader* GetSpatialContexts( MgResourceIdentifier* resource,
                                                        bool bActiveOnly) = 0;

    ////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    /// \brief
    /// Gets all available long transactions for the provider.
    ///
    /// \remarks
    /// The XML returned by MgFeatureService::GetCapabilities says
    /// whether a provider supports long transactions. See \link ProviderCapabilities Provider Capabilities \endlink.
    ///
    /// <!-- Syntax in .Net, Java, and PHP -->
    /// \htmlinclude DotNetSyntaxTop.html
    /// virtual MgLongTransactionReader GetLongTransactions(MgResourceIdentifier resource, bool bActiveOnly = false);
    /// \htmlinclude SyntaxBottom.html
    /// \htmlinclude JavaSyntaxTop.html
    /// virtual MgLongTransactionReader GetLongTransactions(MgResourceIdentifier resource, boolean bActiveOnly = false);
    /// \htmlinclude SyntaxBottom.html
    /// \htmlinclude PHPSyntaxTop.html
    /// virtual MgLongTransactionReader GetLongTransactions(MgResourceIdentifier resource, bool bActiveOnly = false);
    /// \htmlinclude SyntaxBottom.html
    ///
    /// \param resource (MgResourceIdentifier)
    /// A resource identifier for feature
    /// source.
    /// \param bActiveOnly (boolean/bool)
    /// If true, returns the active long
    /// transaction; otherwise returns all
    /// long transactions.
    ///
    /// \return
    /// Returns an MgLongTransactionReader instance or NULL.
    ///
    /// \exception MgFeatureServiceException
    /// \exception MgInvalidArgumentException
    /// \exception MgInvalidOperationException
    /// \exception MgFdoException
    ///
    virtual MgLongTransactionReader* GetLongTransactions( MgResourceIdentifier* resource,
                                                          bool bActiveOnly) = 0;

    ////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    /// \brief
    /// Set the active long transaction name for a feature source.
    ///
    /// \remarks
    /// The long transaction name is associated with the caller's session.  If
    /// no session is set then the method throws an MgSessionNotFoundException.
    ///
    /// <!-- Syntax in .Net, Java, and PHP -->
    /// \htmlinclude DotNetSyntaxTop.html
    /// virtual bool SetLongTransaction(MgResourceIdentifier resource, string longTransactionName);
    /// \htmlinclude SyntaxBottom.html
    /// \htmlinclude JavaSyntaxTop.html
    /// virtual boolean SetLongTransaction(MgResourceIdentifier resource, String longTransactionName);
    /// \htmlinclude SyntaxBottom.html
    /// \htmlinclude PHPSyntaxTop.html
    /// virtual bool SetLongTransaction(MgResourceIdentifier resource, string longTransactionName);
    /// \htmlinclude SyntaxBottom.html
    ///
    /// \param featureSourceId (MgResourceIdentifier)
    /// A resource identifier identifying a feature source in the repository.
    /// \param longTransactionName (String/string)
    /// The long transaction name to set.
    ///
    /// \return
    /// Returns true if the name was successfully set; otherwise
    /// returns false.
    ///
    /// \exception MgNullArgumentException
    /// \exception MgInvalidResourceTypeException
    /// \exception MgSessionNotFoundException
    ///
    virtual bool SetLongTransaction( MgResourceIdentifier* featureSourceId,
                                     CREFSTRING longTransactionName) = 0;

    /////////////////////////////////////////////////////////////////////////////
    /// \brief
    /// Gets a list of the names of all of the schemas available in
    /// the feature source. See \link Feature_Schema_Module Feature Schema \endlink.
    ///
    /// <!-- Syntax in .Net, Java, and PHP -->
    /// \htmlinclude DotNetSyntaxTop.html
    /// virtual MgStringCollection GetSchemas(MgResourceIdentifier resource);
    /// \htmlinclude SyntaxBottom.html
    /// \htmlinclude JavaSyntaxTop.html
    /// virtual MgStringCollection GetSchemas(MgResourceIdentifier resource);
    /// \htmlinclude SyntaxBottom.html
    /// \htmlinclude PHPSyntaxTop.html
    /// virtual MgStringCollection GetSchemas(MgResourceIdentifier resource);
    /// \htmlinclude SyntaxBottom.html
    ///
    /// \param resource (MgResourceIdentifier)
    /// A resource identifier for the
    /// feature source,
    ///
    /// \return
    /// Returns an MgStringCollection object listing the schema
    /// names.
    ///
    /// \exception MgFeatureServiceException
    /// \exception MgInvalidArgumentException
    /// \exception MgFdoException
    ///
    virtual MgStringCollection* GetSchemas( MgResourceIdentifier* resource ) = 0;

    /////////////////////////////////////////////////////////////////////////////////////////////
    /// \brief
    /// Gets a list of the names of all classes available within a
    /// specified schema . See \link Feature_Schema_Module Feature Schema \endlink.
    ///
    /// <!-- Syntax in .Net, Java, and PHP -->
    /// \htmlinclude DotNetSyntaxTop.html
    /// virtual MgStringCollection GetClasses(MgResourceIdentifier resource, string schemaName);
    /// \htmlinclude SyntaxBottom.html
    /// \htmlinclude JavaSyntaxTop.html
    /// virtual MgStringCollection GetClasses(MgResourceIdentifier resource, String schemaName);
    /// \htmlinclude SyntaxBottom.html
    /// \htmlinclude PHPSyntaxTop.html
    /// virtual MgStringCollection GetClasses(MgResourceIdentifier resource, string schemaName);
    /// \htmlinclude SyntaxBottom.html
    ///
    /// \param resource (MgResourceIdentifier)
    /// A resource identifier for a
    /// feature source.
    /// \param schemaName (String/string)
    /// A schema name.
    ///
    /// \return
    /// Returns an MgStringCollection containing a list of class
    /// names.  These names are fully qualified.  In other words, they are in the form <i>schema_name</i>:<i>class_name</i>.
    /// For example, SHP_Schema:lulc_n83.
    ///
    /// \exception MgFeatureServiceException
    /// \exception MgInvalidArgumentException
    /// \exception MgFdoException
    ///
    virtual MgStringCollection* GetClasses( MgResourceIdentifier* resource, CREFSTRING schemaName ) = 0;

    //////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    /// \brief
    /// Gets the class definition for the specified class. See \link Feature_Schema_Module Feature Schema \endlink.
    ///
    /// <!-- Syntax in .Net, Java, and PHP -->
    /// \htmlinclude DotNetSyntaxTop.html
    /// virtual MgClassDefinition GetClassDefinition(MgResourceIdentifier resource, string schemaName, string className);
    /// \htmlinclude SyntaxBottom.html
    /// \htmlinclude JavaSyntaxTop.html
    /// virtual MgClassDefinition GetClassDefinition(MgResourceIdentifier resource, String schemaName, String className);
    /// \htmlinclude SyntaxBottom.html
    /// \htmlinclude PHPSyntaxTop.html
    /// virtual MgClassDefinition GetClassDefinition(MgResourceIdentifier resource, string schemaName, string className);
    /// \htmlinclude SyntaxBottom.html
    ///
    /// \param resource (MgResourceIdentifier)
    /// A resource identifier for
    /// the feature source.
    /// \param schemaName (String/string)
    /// A schema name.
    /// \param className (String/string)
    /// A class name.
    ///
    /// \return
    /// Returns an MgClassDefinition instance for the specified
    /// class name.
    ///
    /// \exception MgFeatureServiceException
    /// \exception MgInvalidArgumentException
    /// \exception MgFdoException
    ///
    virtual MgClassDefinition* GetClassDefinition(  MgResourceIdentifier* resource,
                                                    CREFSTRING schemaName,
                                                    CREFSTRING className) = 0;

    ////////////////////////////////////////////////////////////////////////////////////////////////////////
    /// \brief
    /// Creates a feature source in the repository identified by the
    /// specified resource identifier, using the given feature source
    /// parameters.
    ///
    /// \remarks
    /// MgFeatureSourceParams is an abstract class. Currently the
    /// only concrete class is MgCreateSdfParams, and the only
    /// feature source that can be created this way is an SDF file.
    /// You can use this method to create an SDF file with the same
    /// schema and spatial context definition as the provider that
    /// you are connected to.
    ///
    /// <!-- Syntax in .Net, Java, and PHP -->
    /// \htmlinclude DotNetSyntaxTop.html
    /// virtual void CreateFeatureSource(MgResourceIdentifier resource, MgFeatureSourceParams sourceParams);
    /// \htmlinclude SyntaxBottom.html
    /// \htmlinclude JavaSyntaxTop.html
    /// virtual void CreateFeatureSource(MgResourceIdentifier resource, MgFeatureSourceParams sourceParams);
    /// \htmlinclude SyntaxBottom.html
    /// \htmlinclude PHPSyntaxTop.html
    /// virtual void CreateFeatureSource(MgResourceIdentifier resource, MgFeatureSourceParams sourceParams);
    /// \htmlinclude SyntaxBottom.html
    ///
    /// \param resource (MgResourceIdentifier)
    /// The resource identifier defining the
    /// location of the new feature source in
    /// the repository.
    /// \param sourceParams (MgFeatureSourceParams)
    /// The feature source parameters (feature
    /// schema and spatial context definitions).
    ///
    /// \return
    /// Returns nothing.
    ///
    virtual void CreateFeatureSource(MgResourceIdentifier* resource, MgFeatureSourceParams* sourceParams) = 0;

    ////////////////////////////////////////////////////////////////////////////////////////////////////////
    /// \brief
    /// Retrieves schema information about a set of feature classes for a given feature source.
    ///
    /// <!-- Syntax in .Net, Java, and PHP -->
    /// \htmlinclude DotNetSyntaxTop.html
    /// virtual MgByteReader CreateFeatureSource(MgResourceIdentifier featureSourceId, MgStringCollection featureClasses);
    /// \htmlinclude SyntaxBottom.html
    /// \htmlinclude JavaSyntaxTop.html
    /// virtual MgByteReader CreateFeatureSource(MgResourceIdentifier featureSourceId, MgStringCollection featureClasses);
    /// \htmlinclude SyntaxBottom.html
    /// \htmlinclude PHPSyntaxTop.html
    /// virtual MgByteReader CreateFeatureSource(MgResourceIdentifier featureSourceId, MgStringCollection featureClasses);
    /// \htmlinclude SyntaxBottom.html
    ///
    /// \param featureSourceId (MgResourceIdentifier)
    /// The resource identifier defining the
    /// location of the feature source in
    /// the repository.
    /// \param featureClasses (MgStringCollection)
    /// A collection of strings identifying the feature classes for which to
    /// retrieve schema information. If this collection is null or empty, information
    /// is returned for all feature classes.
    ///
    /// \return
    /// Returns an MgByteReader containing the XML schema.
    ///
    virtual MgByteReader* DescribeWfsFeatureType(MgResourceIdentifier* featureSourceId, MgStringCollection* featureClasses) = 0;

    ////////////////////////////////////////////////////////////////////////////////////////////////////////
    /// \brief
    /// Retrieves feature information based on the supplied criteria.
    ///
    /// <!-- Syntax in .Net, Java, and PHP -->
    /// \htmlinclude DotNetSyntaxTop.html
    /// virtual MgByteReader GetWfsFeature(MgResourceIdentifier featureSourceId, string featureClass, MgStringCollection requiredProperties, string srs, string filter, int maxFeatures);
    /// \htmlinclude SyntaxBottom.html
    /// \htmlinclude JavaSyntaxTop.html
    /// virtual MgByteReader GetWfsFeature(MgResourceIdentifier featureSourceId, String featureClass, MgStringCollection requiredProperties, String srs, String filter, int maxFeatures);
    /// \htmlinclude SyntaxBottom.html
    /// \htmlinclude PHPSyntaxTop.html
    /// virtual MgByteReader GetWfsFeature(MgResourceIdentifier featureSourceId, string featureClass, MgStringCollection requiredProperties, string srs, string filter, int maxFeatures);
    /// \htmlinclude SyntaxBottom.html
    ///
    /// \param featureSourceId (MgResourceIdentifier)
    /// The resource identifier defining the
    /// location of the feature source in
    /// the repository.
    /// \param featureClass (String/string)
    /// The feature class containing the features to retrieve.
    /// \param requiredProperties (MgStringCollection)
    /// The collection of properties to retrieve for each feature. If the
    /// collection is null or empty, all properties will be retrieved.
    /// \param srs (String/string)
    /// The spatial reference system in which to return feature geometries
    /// \param filter (String/string)
    /// An XML string containing the definition for an OGC filter
    /// \param maxFeatures (int)
    /// The maximum number of features to retrieve. If the value is less
    /// than or equal to zero, all features will be retrieved.
    ///
    /// \return
    /// Returns an MgByteReader containing the requested feature information.
    ///
    virtual MgByteReader* GetWfsFeature(MgResourceIdentifier* featureSourceId, CREFSTRING featureClass,
        MgStringCollection* requiredProperties, CREFSTRING srs, CREFSTRING filter, INT32 maxFeatures) = 0;

    ////////////////////////////////////////////////////////////////////////////////
    /// \brief
    /// This method enumerates all the providers and if they are FDO enabled for
    /// the specified provider and partial connection string.
    ///
    /// \param providerName (String/string)
    /// The name of the Fdo feature provider.
    /// \param partialConnString (String/string)
    /// The partial connection string to the Fdo provider.
    ///
    /// \returns
    /// Returns the list of data stores.
    virtual MgByteReader* EnumerateDataStores(CREFSTRING providerName, CREFSTRING partialConnString) = 0;

    ////////////////////////////////////////////////////////////////////////////////
    /// \brief
    /// This method returns all of the logical to physical schema mappings for
    /// the specified provider and partial connection string.
    ///
    /// \param providerName (String/string)
    /// The name of the Fdo feature provider.
    /// \param partialConnString (String/string)
    /// The partial connection string to the Fdo provider.
    ///
    /// \returns
    /// Returns the schema mapping.
    virtual MgByteReader* GetSchemaMapping(CREFSTRING providerName, CREFSTRING partialConnString) = 0;

INTERNAL_API:

    //////////////////////////////////////////////////////////////////
    /// \brief
    /// Construct an MgFeatureService object.
    ///
    MgFeatureService();

    virtual MgBatchPropertyCollection* GetFeatures(INT32 featureReaderId) = 0;
    virtual bool CloseFeatureReader(INT32 featureReaderId) = 0;
    virtual MgBatchPropertyCollection* GetSqlRows(INT32 sqlReader) = 0;
    virtual bool CloseSqlReader(INT32 sqlReader) = 0;
    virtual MgByteReader* GetRaster(INT32 featureReaderId, INT32 xSize, INT32 ySize, STRING propName) = 0;
    virtual MgBatchPropertyCollection* GetDataRows(INT32 dataReader) = 0;
    virtual bool CloseDataReader(INT32 dataReader) = 0;
    virtual bool CloseGwsFeatureReader(INT32 gwsFeatureReader) = 0;

    //////////////////////////////////////////////////////////////////
    /// \brief
    /// Returns the collection of identity properties for the specified class.
    /// If schemaName is empty, then className needs to be fully qualified.
    virtual MgPropertyDefinitionCollection* GetIdentityProperties(MgResourceIdentifier* resource,
                                                                  CREFSTRING schemaName,
                                                                  CREFSTRING className) = 0;

    virtual STRING GetFdoCacheInfo() = 0;

    virtual MgClassDefinition* GetClassDefinition(  MgResourceIdentifier* resource,
                                                    CREFSTRING schemaName,
                                                    CREFSTRING className,
                                                    bool serialize) = 0;


protected:

    /////////////////////////////////////////////////////////////////
    /// \brief
    /// Get the class Id
    ///
    /// \return
    /// The integer value
    ///
    virtual INT32 GetClassId();

    //////////////////////////////////////////////////////////////////
    /// \brief
    /// Dispose this object
    ///
    /// \return
    /// Nothing
    ///
    virtual void Dispose();

private:

CLASS_ID:
    static const INT32 m_cls_id = PlatformBase_FeatureService_FeatureService;
};

#define MG_CHECK_FEATURE_SET_COUNT(pointer, methodname)                       \
if (0 == pointer->GetCount())                                                 \
{                                                                             \
    throw new MgEmptyFeatureSetException(methodname,                          \
        __LINE__, __WFILE__, NULL, L"", NULL);                                \
}

#define MG_CHECK_PROPERTY_TYPE(property, type, methodname)                    \
if (property != type)                                                         \
{                                                                             \
    throw new MgInvalidPropertyTypeException(methodname,                      \
        __LINE__, __WFILE__, NULL, L"", NULL);                                \
}

/// \}

#endif
