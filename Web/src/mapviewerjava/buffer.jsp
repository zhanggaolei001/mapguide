<%--
  -Copyright (C) 2004-2006  Autodesk, Inc.
  -This library is free software; you can redistribute it and/or
  -modify it under the terms of version 2.1 of the GNU Lesser
  -General Public License as published by the Free Software Foundation.

  -This library is distributed in the hope that it will be useful,
  -but WITHOUT ANY WARRANTY; without even the implied warranty of
  -MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
  -Lesser General Public License for more details.

  -You should have received a copy of the GNU Lesser General Public
  -License along with this library; if not, write to the Free Software
  -Foundation, Inc., 51 Franklin St, Fifth Floor, Boston, MA  02110-1301  USA
--%>

<%@ page contentType="text/html; charset=UTF-8" pageEncoding="UTF-8" %>
<%@ page import="org.osgeo.mapguide.*" %>
<%@ page import="java.util.*" %>
<%@ page import="java.io.*" %>
<%@ page import="java.text.*" %>
<%@ page import="javax.servlet.jsp.*" %>
<%@ page import="javax.servlet.http.*" %>
<%@ include file="common.jsp" %>

<%!
String mapName;
String sessionId;
String bufferName;
String layersParam;
int popup;
String lcolor;
String ffcolor;
String fbcolor;
int transparent;
double distance;
String units;
String linestyle;
String fillstyle;
String thickness;
int merge;
int foretrans;
String selText;
String srs;
String featureName = "Buffer";
String dataSource;
String locale;
%>

<%
    mapName = "";
    sessionId = "";
    bufferName = "";
    layersParam = "";
    int popup = 0;
    lcolor = "";
    ffcolor = "";
    fbcolor = "";
    transparent = 0;
    distance = 0;
    units = "";
    linestyle = "";
    fillstyle = "";
    thickness = "";
    merge = 0;
    foretrans = 50;
    selText = "";
    srs = "";
    dataSource = "";
    locale = "";

    response.setContentType("text/html; charset=UTF-8");
    request.setCharacterEncoding("UTF-8");
    PrintWriter outStream = response.getWriter();

    GetRequestParameters(request);
    MgLocalizer.SetLocalizedFilesPath(getServletContext().getRealPath("/") + "localized/");

    dataSource = "Session:" + sessionId + "//" + bufferName + "_Buffer.FeatureSource";
    String layerDef = "Session:" + sessionId + "//" + bufferName + "_Buffer.LayerDefinition";

    try
    {
        boolean newBuffer = false;

        InitializeWebTier();

        MgUserInformation cred = new MgUserInformation(sessionId);

        //connect to the site and get a feature service and a resource service instances
        MgSiteConnection site = new MgSiteConnection();
        site.Open(cred);
        MgFeatureService featureSrvc = (MgFeatureService)site.CreateService(MgServiceType.FeatureService);
        MgResourceService resourceSrvc = (MgResourceService)site.CreateService(MgServiceType.ResourceService);

        MgResourceIdentifier dataSourceId = new MgResourceIdentifier(dataSource);
        MgResourceIdentifier layerDefId = new MgResourceIdentifier(layerDef);

        //load the map runtime state
        //
        MgMap map = new MgMap();
        map.Open(resourceSrvc, mapName);

        //locate the buffer layer in the map. It might or might not already exist
        //
        MgLayerCollection layers = map.GetLayers();
        MgLayer layer = FindLayer(layers, bufferName);

        String[] layerNames = layersParam.split(",");

        // convert distance to meters
        if(units.equals("mi"))      //miles
            distance *= 1609.35;
        else if(units.equals("ki")) //kilometers
            distance *= 1000;
        else if(units.equals("fe")) //feet
            distance *= 0.30480;

        // calculate the distance in map units
        MgCoordinateSystemFactory srsFactory = new MgCoordinateSystemFactory();
        String srsDefMap = map.GetMapSRS();
        MgCoordinateSystem srsMap = null;
        boolean arbitraryMapSrs;
        if(srsDefMap != null && srsDefMap.length() > 0)
        {
            srsMap = srsFactory.Create(srsDefMap);
            arbitraryMapSrs = (srsMap.GetType() == MgCoordinateSystemType.Arbitrary);
            if(!arbitraryMapSrs)
            {
                distance = srsMap.ConvertMetersToCoordinateSystemUnits(distance);
            }
        }
        else
        {
            arbitraryMapSrs = true;
        }

        //Create/Modify layer definition
        MgByteReader layerDefContent = BuildLayerDefinitionContent();
        resourceSrvc.SetResource(layerDefId, layerDefContent, null);

        if(layer == null)
        {
            newBuffer = true;
            //Targetting a new layer. create a data source for it
            //
            MgClassDefinition classDef = new MgClassDefinition();

            classDef.SetName(featureName);
            classDef.SetDescription(MgLocalizer.GetString("BUFFERCLASSDESCR", locale));
            classDef.SetDefaultGeometryPropertyName("GEOM");

            //Set KEY property
            MgDataPropertyDefinition propKey = new MgDataPropertyDefinition("KEY");
            propKey.SetDataType(MgPropertyType.Int32);
            propKey.SetAutoGeneration(true);
            propKey.SetReadOnly(true);
            classDef.GetIdentityProperties().Add(propKey);
            classDef.GetProperties().Add(propKey);

            //Set ID property. Hold this segment ID
            MgDataPropertyDefinition propID = new MgDataPropertyDefinition("ID");
            propID.SetDataType(MgPropertyType.Int32);
            classDef.GetProperties().Add(propID);

            //Set geometry property
            MgGeometricPropertyDefinition geomProp = new MgGeometricPropertyDefinition("GEOM");
            //geomProp.SetGeometryTypes(MgFeatureGeometricType.mfgtSurface); //TODO use the constant when exposed
            geomProp.SetGeometryTypes(4);
            classDef.GetProperties().Add(geomProp);

            //Create the schema
            MgFeatureSchema schema = new MgFeatureSchema("BufferSchema", MgLocalizer.GetString("BUFFERSCHEMADESCR", locale));
            schema.GetClasses().Add(classDef);

            //finally, creation of the feature source
            MgCreateSdfParams sdfParams = new MgCreateSdfParams("LatLong", srs, schema);
            featureSrvc.CreateFeatureSource(dataSourceId, sdfParams);

            //Add layer to map
            layer = new MgLayer(layerDefId, resourceSrvc);
            layer.SetName(bufferName);
            layer.SetLegendLabel(bufferName);
            layer.SetDisplayInLegend(true);
            layer.SetSelectable(true);
            layers.Insert(0, layer);
        }
        else
        {
            //data source already exist. clear its content
            //
            ClearDataSource(featureSrvc, dataSourceId, featureName);
        }

        MgSelection sel = new MgSelection(map, selText);
        MgReadOnlyLayerCollection selLayers = sel.GetLayers();

        MgAgfReaderWriter agfRW = new MgAgfReaderWriter();
        MgGeometryCollection bufferGeometries = new MgGeometryCollection();
        MgGeometry geomBuffer;

        MgFeatureCommandCollection commands = new MgFeatureCommandCollection();
        int featId = 0;

        MgBatchPropertyCollection propCollection = new MgBatchPropertyCollection();

        int excludedLayers = 0;
        MgCoordinateSystem srsDs = null;
        MgGeometryCollection inputGeometries = new MgGeometryCollection();

        int bufferFeatures = 0;
        boolean allCompatible = false;
        String prevArbSrs = "";
        MgCoordinateSystem arbSrs = null;

        for(int li =0; li < selLayers.GetCount(); li++)
        {
            MgLayer selLayer = selLayers.GetItem(li);
            boolean inputLayer = false;
            String selLayerName = selLayer.GetName();
            for(int il = 0; il < layerNames.length; il++)
            {
                if(layerNames[il].equals(selLayerName))
                {
                    inputLayer = true;
                    break;
                }
            }
            if(inputLayer == false)
            {
                continue;
            }

            // get the data source SRS
            //
            MgResourceIdentifier featSourceId = new MgResourceIdentifier(selLayer.GetFeatureSourceId());
            MgSpatialContextReader ctxs = featureSrvc.GetSpatialContexts(featSourceId, true);
            String srsDefDs = "";
            if(ctxs != null)
            {
                ctxs.ReadNext();
                srsDefDs = ctxs.GetCoordinateSystemWkt();
                if(srsDefDs == null || srsDefDs.length() == 0)
                {
                    excludedLayers++;
                    continue;
                }
            }
            else
            {
                excludedLayers++;
                continue;
            }

            srsDs = srsFactory.Create(srsDefDs);
            boolean arbitraryDsSrs = (srsDs.GetType() == MgCoordinateSystemType.Arbitrary);
            if(arbitraryDsSrs)
            {
                if(prevArbSrs != null && prevArbSrs.length() > 0 && !prevArbSrs.equals(srsDefDs) && arbitraryMapSrs && merge == 1)
                {
                    throw new Exception(MgLocalizer.GetString("BUFFERDIFFARBXY", locale));
                }
                prevArbSrs = srsDefDs;
                if(arbSrs == null)
                {
                    arbSrs = srsDs;
                }
            }

            if(arbitraryDsSrs != arbitraryMapSrs)
            {
                //exclude this layer because its srs is incompatible with the map srs
                excludedLayers++;
                continue;
            }

            // calculate great circle unless data source srs is arbitrary
            MgCoordinateSystemMeasure measure;
            if(arbitraryDsSrs == true)
                 measure = new MgCoordinateSystemMeasure(srsDs);
            else
                 measure = null;

            // create a SRS transformer if necessary
            MgCoordinateSystemTransform srsXform;
            if((arbitraryMapSrs == false) && (arbitraryDsSrs == false) && !srsDefDs.equals(srsDefMap))
                srsXform = new MgCoordinateSystemTransform(srsDs, srsMap);
            else
                srsXform = null;

            String featureClassName = selLayer.GetFeatureClassName();
            String filter = sel.GenerateFilter(selLayer, featureClassName);
            if(filter == null || filter.length() == 0)
                continue;

            MgFeatureQueryOptions query = new MgFeatureQueryOptions();
            query.SetFilter(filter);

            MgResourceIdentifier featureSource = new MgResourceIdentifier(selLayer.GetFeatureSourceId());

            MgFeatureReader features = featureSrvc.SelectFeatures(featureSource, featureClassName, query);

            if(features.ReadNext())
            {
                MgClassDefinition classDef = features.GetClassDefinition();
                String geomPropName = classDef.GetDefaultGeometryPropertyName();

                do
                {
                    MgByteReader geomReader = features.GetGeometry(geomPropName);
                    MgGeometry geom = agfRW.Read(geomReader);

                    MgGeometry geomDest;
                    if(srsXform != null)
                    {
                        //$wkt = new MgWktReaderWriter();
                        geomDest = (MgGeometry)geom.Transform(srsXform);
                    }
                    else
                        geomDest = geom;

                    if(merge == 0)
                    {
                        geomBuffer = geomDest.Buffer(distance, measure);
                        AddFeatureToCollection(propCollection, agfRW, featId++, geomBuffer);
                        bufferFeatures++;
                    }
                    else
                    {
                        inputGeometries.Add(geomDest);
                    }
                }
                while(features.ReadNext());

                features.Close();
            }
        }

        if(merge == 1)
        {
            if(inputGeometries.GetCount() > 0)
            {
                MgCoordinateSystemMeasure measure;
                if(arbitraryMapSrs)
                    measure = new MgCoordinateSystemMeasure(arbSrs);
                else
                    measure = null;

                MgGeometryFactory geomFactory = new MgGeometryFactory();
                geomBuffer = geomFactory.CreateMultiGeometry(inputGeometries).Buffer(distance, measure);
                AddFeatureToCollection(propCollection, agfRW, featId, geomBuffer);
                bufferFeatures = 1;
            }
        }

        if(propCollection.GetCount() > 0)
        {
            commands.Add(new MgInsertFeatures(featureName, propCollection));

            //Insert the features in the temporary data source
            //
            ReleaseReader(featureSrvc.UpdateFeatures(dataSourceId, commands, false), commands);
        }

        // Save the new map state
        //
        layer.ForceRefresh();
        map.Save(resourceSrvc);

        //build report message
        String title = MgLocalizer.GetString("BUFFERREPORTTITLE", locale);
        String createdUpdatedFmt = newBuffer ? MgLocalizer.GetString("BUFFERREPORTCREATED", locale) : MgLocalizer.GetString("BUFFERREPORTUPDATED", locale);
        String createdUpdatedStr = Substitute(createdUpdatedFmt, new String[] { bufferName } );
        String featuresFmt = bufferFeatures > 1 ? MgLocalizer.GetString("BUFFERREPORTFEATURESPLURAL", locale) : MgLocalizer.GetString("BUFFERREPORTFEATURESSINGULAR", locale);
        String featuresStr = Substitute(featuresFmt, new String[] { String.valueOf(bufferFeatures) } );
        String msg = createdUpdatedStr + "<p><p>"  + featuresStr;

        if(excludedLayers > 0) {
            String warningFmt = excludedLayers > 1 ? MgLocalizer.GetString("BUFFERREPORTWARNINGSINGULAR", locale) : MgLocalizer.GetString("BUFFERREPORTWARNINGPLURAL", locale);
            String warningStr = Substitute(warningFmt, new String[] { String.valueOf(excludedLayers) } );
            msg = msg + "<p><p>" + warningStr;
        }

        // return the report page
        String templ = MgLocalizer.Localize(LoadTemplate("/viewerfiles/bufferreport.templ"), locale, GetClientOS(request));
        String[] vals = {
                    String.valueOf(popup),
                    title,
                    msg};
        outStream.write(Substitute(templ, vals));
    }
    catch(MgException exc)
    {
        OnError(MgLocalizer.GetString("BUFFERREPORTERRORTITLE", locale), exc.GetDetails(), outStream, request);
        return;
    }
    catch(Exception ne)
    {
        OnError(MgLocalizer.GetString("BUFFERREPORTERRORTITLE", locale), ne.getMessage(), outStream, request);
        return;
    }
%>

<%!
void GetRequestParameters(HttpServletRequest request)
{
    mapName = GetParameter(request, "MAPNAME");
    sessionId = GetParameter(request, "SESSION");
    popup = GetIntParameter(request, "POPUP");
    bufferName = GetParameter(request, "BUFFER");
    layersParam = GetParameter(request, "LAYERS");
    lcolor = GetParameter(request, "LCOLOR");
    ffcolor = GetParameter(request, "FFCOLOR");
    fbcolor = GetParameter(request, "FBCOLOR");
    foretrans = GetIntParameter(request, "FORETRANS");
    transparent = GetIntParameter(request, "TRANSPARENT");
    distance = GetDoubleParameter(request, "DISTANCE");
    units = GetParameter(request, "UNITS");
    linestyle = GetParameter(request, "LINESTYLE");
    fillstyle = GetParameter(request, "FILLSTYLE");
    thickness = GetParameter(request, "THICKNESS");
    selText = GetParameter(request, "SELECTION");
    if(IsParameter(request, "MERGE"))
         merge = 1;
    locale = GetParameter(request, "LOCALE");

    if(foretrans < 0 || foretrans > 100)
    {
        foretrans = 50;
    }
}


MgLayer FindLayer(MgLayerCollection layers, String layerName) throws MgException
{
    MgLayer layer = null;
    int i;
    for(i = 0; i < layers.GetCount(); i++)
    {
        MgLayer layer1 = layers.GetItem(i);
        if(layer1.GetName().equals(layerName))
        {
            layer = layer1;
            break;
        }
    }
    return layer;
}

MgByteReader BuildLayerDefinitionContent() throws MgException, Exception
{
    String layerTempl = LoadTemplate("/viewerfiles/arealayerdef.templ");
    String xtrans = String.format("%02x", new Object[]{new Integer(255 * foretrans / 100)});
    String[] vals = {
                dataSource,
                featureName,
                "GEOM",
                fillstyle,
                xtrans + ffcolor,
                (0 != transparent? ("ff" + fbcolor): ("00" + fbcolor)),
                linestyle,
                thickness,
                lcolor };
    layerTempl = Substitute(layerTempl, vals);
    byte[] bytes = layerTempl.getBytes();

    MgByteSource src = new MgByteSource(bytes, bytes.length);
    return src.GetReader();
}

void ClearDataSource(MgFeatureService featureSrvc, MgResourceIdentifier dataSourceId, String featureName)  throws MgException
{
    MgDeleteFeatures deleteCmd = new MgDeleteFeatures(featureName, "ID >= 0");
    MgFeatureCommandCollection commands = new MgFeatureCommandCollection();
    commands.Add(deleteCmd);
    featureSrvc.UpdateFeatures(dataSourceId, commands, false);
}

void OnError(String title, String msg, PrintWriter outStream, HttpServletRequest request) throws FileNotFoundException, IOException
{
    String templ = MgLocalizer.Localize(LoadTemplate("/viewerfiles/errorpage.templ"), locale, GetClientOS(request));
    String[] vals = { String.valueOf(popup), title, msg };
    outStream.write(Substitute(templ, vals));
}

void ReleaseReader(MgPropertyCollection res, MgFeatureCommandCollection commands) throws MgException
{
    if(res == null)
        return;

    for(int i = 0; i < res.GetCount(); i++)
    {
        MgFeatureCommand cmd = commands.GetItem(i);
        if(cmd instanceof MgInsertFeatures)
        {
            MgFeatureProperty resProp = (MgFeatureProperty)res.GetItem(i);
            if(resProp != null)
            {
                MgFeatureReader reader = (MgFeatureReader)resProp.GetValue();
                if(reader == null)
                    return;
                reader.Close();
            }
        }
    }
}

void AddFeatureToCollection(MgBatchPropertyCollection propCollection, MgAgfReaderWriter agfRW, int featureId, MgGeometry featureGeom) throws MgException
{
    MgPropertyCollection bufferProps = new MgPropertyCollection();
    MgInt32Property idProp = new MgInt32Property("ID", featureId);
    bufferProps.Add(idProp);
    MgByteReader geomReader = agfRW.Write(featureGeom);
    MgGeometryProperty geomProp = new MgGeometryProperty("GEOM", geomReader);
    bufferProps.Add(geomProp);
    propCollection.Add(bufferProps);
}

%>
