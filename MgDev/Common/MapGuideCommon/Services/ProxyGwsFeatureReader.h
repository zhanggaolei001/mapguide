//
//  Copyright (C) 2004-2010 by Autodesk, Inc.
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

#ifndef _MG_PROXY_GWS_FEATURE_READER_H
#define _MG_PROXY_GWS_FEATURE_READER_H


#ifndef FEATURESET_TEMPL
#define FEATURESET_TEMPL
class MgFeatureSet;
template class MG_MAPGUIDE_API Ptr<MgFeatureSet>;
#endif

class MgFeatureReader;

class MgProxyGwsFeatureReader;
template class MG_MAPGUIDE_API Ptr<MgProxyGwsFeatureReader>;

/// \cond INTERNAL
/////////////////////////////////////////////////////////////////
/// \brief
/// The GwsFeatureReader interface provides a forward-only, read-only
/// iterator for reading data from a GwsQuery.
/// The initial position of the GwsFeatureReader interface is prior to the first item.
/// Thus, you must call ReadNext to begin accessing any data..
class MG_MAPGUIDE_API  MgProxyGwsFeatureReader : public MgFeatureReader
{
    MG_DECL_DYNCREATE();

EXTERNAL_API:

    //////////////////////////////////////////////////////////////////
    /// \brief
    /// Advances the reader to the next item and returns true if there is
    /// another object to read or false if reading is complete. The default
    /// position of the reader is prior to the first item. Thus you must
    /// call ReadNext to begin accessing any data.
    ///
    /// \return
    /// Returns true if there is a next item.
    ///
    bool ReadNext();

    //////////////////////////////////////////////////////////////////
    /// \brief
    /// Gets the definition of the object currently being read. If the user
    /// has requested only a subset of the class properties, the class
    /// definition reflects what the user has asked, rather than the full class
    /// definition.
    ///
    /// \return
    /// A MgClassDefinition representing the current object
    ///
    MgClassDefinition* GetClassDefinition();

    //////////////////////////////////////////////////////////////////
    /// \brief
    ///  Returns true if the value of the specified property is null.
    ///
    /// \param propertyName
    /// Property name.
    ///
    /// \return
    /// Returns true if the value is null.
    ///
    bool IsNull(CREFSTRING propertyName);

    //////////////////////////////////////////////////////////////////
    /// \brief
    /// Gets the Boolean value of the specified property. No conversion is
    /// performed, thus the property must be a of boolean type the result
    /// is undetermined
    ///
    /// \param propertyName
    /// Property name.
    ///
    /// \return
    /// Returns the Boolean value.
    ///
    bool GetBoolean(CREFSTRING propertyName);

    //////////////////////////////////////////////////////////////////
    /// \brief
    /// Gets the Byte value of the specified property. No conversion is
    /// performed, thus the property must be a of byte type or the result
    /// is undetermined
    ///
    /// \param propertyName
    /// Property name.
    ///
    /// \return
    /// Returns the Byte value.
    ///
    BYTE GetByte(CREFSTRING propertyName);

    //////////////////////////////////////////////////////////////////
    /// \brief
    /// Gets the DTime value of the specified property. No conversion is
    /// performed, thus the property must be a of date type or the result
    /// is NULL
    ///
    /// \param propertyName
    /// Property name.
    ///
    /// \return
    /// Returns the DTime value.
    ///
    MgDateTime* GetDateTime(CREFSTRING propertyName);

    //////////////////////////////////////////////////////////////////
    /// \brief
    /// Gets the Single value of the specified property. No conversion is
    /// performed, thus the property must be a of type single or the result
    /// is undetermined
    ///
    /// \param propertyName
    /// Property name.
    ///
    /// \return
    /// Returns the single value.
    ///
    float GetSingle(CREFSTRING propertyName);

    //////////////////////////////////////////////////////////////////
    /// \brief
    /// Gets the Double value of the specified property. No conversion is
    /// performed, thus the property must be a of type double or the result
    /// is undetermined
    ///
    /// \param propertyName
    /// Property name.
    ///
    /// \return
    /// Returns the double value.
    ///
    double GetDouble(CREFSTRING propertyName);

    //////////////////////////////////////////////////////////////////
    /// \brief
    /// Gets the integer 16 bits value of the specified property. No conversion is
    /// performed, thus the property must be a of type integer 16 bits or the result
    /// is undetermined
    ///
    /// \param propertyName
    /// Property name.
    ///
    /// \return
    /// Returns the integer 16 bits value.
    ///
    INT16 GetInt16(CREFSTRING propertyName);

    //////////////////////////////////////////////////////////////////
    /// \brief
    /// Gets the integer 32 bits value of the specified property. No conversion is
    /// performed, thus the property must be a of type integer 32 bits or the result
    /// is undetermined
    ///
    /// \param propertyName
    /// Property name.
    ///
    /// \return
    /// Returns the integer 32 bits value.
    ///
    INT32 GetInt32(CREFSTRING propertyName);

    //////////////////////////////////////////////////////////////////
    /// \brief
    /// Gets the integer 64 bits value of the specified property. No conversion is
    /// performed, thus the property must be a of type integer 64 bits or the result
    /// is NULL
    ///
    /// \param propertyName
    /// Property name.
    ///
    /// \return
    /// Returns the integer 64 bits value.
    /// Note: INT64 is actually a pointer to an Integer64 object
    ///
    INT64 GetInt64(CREFSTRING propertyName);

    //////////////////////////////////////////////////////////////////
    /// \brief
    /// Gets the string value of the specified property. No conversion is
    /// performed, thus the property must be a of type string or the result
    /// is NULL
    ///
    /// \param propertyName
    /// Property name.
    ///
    /// \return
    /// Returns the string value.
    ///
    STRING GetString(CREFSTRING propertyName);

    //////////////////////////////////////////////////////////////////
    /// \brief
    /// Gets the BLOB value of the specified property. No conversion is
    /// performed, thus the property must be a of type BLOBs or the result
    /// is NULL
    ///
    /// \param propertyName
    /// Property name.
    ///
    /// \return
    /// Returns the BLOB value.
    ///
    MgByteReader* GetBLOB(CREFSTRING propertyName);

    //////////////////////////////////////////////////////////////////
    /// \brief
    /// Gets the CLOB value of the specified property. No conversion is
    /// performed, thus the property must be a of type CLOB or the result
    /// is NULL
    ///
    /// \param propertyName
    /// Property name.
    ///
    /// \return
    /// Returns the CLOB value.
    ///
    MgByteReader* GetCLOB(CREFSTRING propertyName);

    //////////////////////////////////////////////////////////////////
    /// \brief
    /// Gets the FeatureReader to access this object value.
    /// The property must be of an object type; otherwise, the result is NULL.
    ///
    /// \param propertyName
    /// Input the property name.
    ///
    /// \return
    /// Returns the feature reader to access this object.
    ///
    /// \exception MgInvalidArgumentException if the property type is not a feature
    ///
    MgFeatureReader* GetFeatureObject(CREFSTRING propertyName);

    //////////////////////////////////////////////////////////////////
    /// \brief
    /// Gets the Geometry for the specified property. No conversion is
    /// performed, thus the property must be a of type Geometry or the result
    /// is NULL
    ///
    /// \param propertyName
    /// Property name.
    ///
    /// \return
    /// Returns a ByteReader object
    ///
    MgByteReader* GetGeometry(CREFSTRING propertyName);

    /// \brief
    /// Gets the raster object of the specified property.
    /// the property must be of Raster type; otherwise, an exception is thrown.
    ///
    /// \param propertyName
    /// Input the property name.
    ///
    /// \return
    /// Returns the raster object.
    ///
    /// \exception MgConnectionNotOpenException
    /// \exception MgNullPropertyValueException
    /// \exception MgFdoException
    /// \exception MgInvalidPropertyTypeException
    ///
    MgRaster* GetRaster(CREFSTRING propertyName);


    //////////////////////////////////////////////////////////////////
    /// <summary>
    ///  Returns true if the value of the property at the specified index is null.
    /// </summary>
    /// <param name="index">Property index.</param>
    /// <returns>Returns true if the value is null.</returns>
    bool IsNull(INT32 index);

    //////////////////////////////////////////////////////////////////
    /// <summary>
    /// Gets the Boolean value of the property at the specified index. No conversion is
    /// performed, thus the property must be a of boolean type the result
    /// is undertermined</summary>
    /// <param name="index">Property index.</param>
    /// <returns>Returns the Boolean value.</returns>
    /// EXCEPTIONS:
    /// MgInvalidArgumentException if the property type is not boolean
    bool GetBoolean(INT32 index);

    //////////////////////////////////////////////////////////////////
    /// <summary>
    /// Gets the Byte value of the property at the specified index. No conversion is
    /// performed, thus the property must be a of byte type or the result
    /// is undertermined</summary>
    /// <param name="index">Property index.</param>
    /// <returns>Returns the Byte value.</returns>
    /// EXCEPTIONS:
    /// MgInvalidArgumentException if the property type is not byte
    BYTE GetByte(INT32 index);

    //////////////////////////////////////////////////////////////////
    /// <summary>
    /// Gets the DTime value of the property at the specified index. No conversion is
    /// performed, thus the property must be a of date type or the result
    /// is NULL</summary>
    /// <param name="index">Property index.</param>
    /// <returns>Returns the DTime value.</returns>
    /// EXCEPTIONS:
    /// MgInvalidArgumentException if the property type is not date/time
    MgDateTime* GetDateTime(INT32 index);

    //////////////////////////////////////////////////////////////////
    /// <summary>
    /// Gets the Single value of the property at the specified index. No conversion is
    /// performed, thus the property must be a of type single or the result
    /// is undetermined</summary>
    /// <param name="index">Property index.</param>
    /// <returns>Returns the single value.</returns>
    /// EXCEPTIONS:
    /// MgInvalidArgumentException if the property type is not float
    float GetSingle(INT32 index);

    //////////////////////////////////////////////////////////////////
    /// <summary>
    /// Gets the Double value of the property at the specified index. No conversion is
    /// performed, thus the property must be a of type double or the result
    /// is undetermined</summary>
    /// <param name="index">Property index.</param>
    /// <returns>Returns the double value.</returns>
    /// EXCEPTIONS:
    /// MgInvalidArgumentException if the property type is not double
    double GetDouble(INT32 index);

    //////////////////////////////////////////////////////////////////
    /// <summary>
    /// Gets the integer 16 bits value of the property at the specified index. No conversion is
    /// performed, thus the property must be a of type integer 16 bits or the result
    /// is undetermined</summary>
    /// <param name="index">Property index.</param>
    /// <returns>Returns the integer 16 bits value.</returns>
    /// EXCEPTIONS:
    /// MgInvalidArgumentException if the property type is not int16
    INT16 GetInt16(INT32 index);

    //////////////////////////////////////////////////////////////////
    /// <summary>
    /// Gets the integer 32 bits value of the property at the specified index. No conversion is
    /// performed, thus the property must be a of type integer 32 bits or the result
    /// is undetermined</summary>
    /// <param name="index">Property index.</param>
    /// <returns>Returns the integer 32 bits value.</returns>
    /// EXCEPTIONS:
    /// MgInvalidArgumentException if the property type is not int32
    INT32 GetInt32(INT32 index);

    //////////////////////////////////////////////////////////////////
    /// <summary>
    /// Gets the integer 64 bits value of the property at the specified index. No conversion is
    /// performed, thus the property must be a of type integer 64 bits or the result
    /// is NULL</summary>
    /// <param name="index">Property index.</param>
    /// <returns>Returns the integer 64 bits value.
    /// Note: INT64 is actually a pointer to an Integer64 object
    ///</returns>
    /// EXCEPTIONS:
    /// MgInvalidArgumentException if the property type is not int64
    INT64 GetInt64(INT32 index);

    //////////////////////////////////////////////////////////////////
    /// <summary>
    /// Gets the string value of the property at the specified index. No conversion is
    /// performed, thus the property must be a of type string or the result
    /// is NULL</summary>
    /// <param name="index">Property index.</param>
    /// <returns>Returns the string value.</returns>
    /// EXCEPTIONS:
    /// MgInvalidArgumentException if the property type is not a string
    STRING GetString(INT32 index);

    //////////////////////////////////////////////////////////////////
    /// <summary>
    /// Gets the BLOB value of the property at the specified index. No conversion is
    /// performed, thus the property must be a of type BLOBs or the result
    /// is NULL</summary>
    /// <param name="index">Property index.</param>
    /// <returns>Returns the BLOB value.</returns>
    /// EXCEPTIONS:
    /// MgInvalidArgumentException if the property type is not a BLOB
    MgByteReader* GetBLOB(INT32 index);

    //////////////////////////////////////////////////////////////////
    /// <summary>
    /// Gets the CLOB value of the property at the specified index. No conversion is
    /// performed, thus the property must be a of type CLOB or the result
    /// is NULL</summary>
    /// <param name="index">Property index.</param>
    /// <returns>Returns the CLOB value.</returns>
    /// EXCEPTIONS:
    /// MgInvalidArgumentException if the property type is not a CLOB
    MgByteReader* GetCLOB(INT32 index);

    //////////////////////////////////////////////////////////////////
    /// <summary>
    /// Gets the FeatureReader to access this object value.
    /// The property must be of an object type; otherwise, the result is NULL.
    /// </summary>
    /// <param name="index">Property index.</param>
    /// <returns>Returns the feature reader to access this object.</returns>
    /// EXCEPTIONS:
    /// MgInvalidArgumentException if the property type is not a feature
    MgFeatureReader* GetFeatureObject(INT32 index);

    //////////////////////////////////////////////////////////////////
    /// <summary>
    /// Gets the geometry value of the property at the specified index as a GeometryReader.
    /// Because no conversion is performed, the property must be
    /// of Geometric type; otherwise, the result is NULL.</summary>
    /// <param name="index">Property index.</param>
    /// <returns>Returns the Geometry object.</returns>
    /// EXCEPTIONS:
    /// MgInvalidArgumentException if the property type is not geometry
    MgByteReader* GetGeometry(INT32 index);

    //////////////////////////////////////////////////////////////////
    /// <summary>
    /// </summary>
    /// <param name="index">Property index.</param>
    /// <returns>Returns the Raster object.</returns>
    /// EXCEPTIONS:
    /// MgInvalidArgumentException if the property type is not geometry
    MgRaster* GetRaster(INT32 index);

    //////////////////////////////////////////////////////////////////
    /// \brief
    /// Closes the FeatureReader object, freeing any resources it may be holding.
    ///
    void Close();

    //////////////////////////////////////////////////////////////////
    /// \brief
    /// Serializes all features into an XML.
    /// XML is serialized from the current position of feature reader in the order
    /// data are retrieved.
    ///
    /// \return
    /// MgByteReader holding XML.
    ///
    MgByteReader* ToXml();

INTERNAL_API:

    //////////////////////////////////////////////////////////////////
    /// \brief
    /// Gets the definition of the object currently being read. If the user
    /// has requested only a subset of the class properties, the class
    /// definition reflects what the user has asked, rather than the full class
    /// definition.
    ///
    /// \return
    /// A MgClassDefinition representing the current object
    ///
    //Note: Same as GetClassDefinition, however does not serialize
    //the class definition to XML in the case where our feature
    //reader and its caller are local
    MgClassDefinition* GetClassDefinitionNoXml();

    //////////////////////////////////////////////////////////////////
    /// \brief
    /// Create reader from a Feature Set
    ///
    MgProxyGwsFeatureReader(MgFeatureSet* featureSet);

    //////////////////////////////////////////////////////////////////
    /// \brief
    /// Gets the Geometry for the specified property. No conversion is
    /// performed, thus the property must be a of type Geometry or the result
    /// is NULL
    ///
    /// \param propertyName
    /// Property name.
    ///
    /// \return
    /// Returns a ByteReader object
    ///
    BYTE_ARRAY_OUT GetGeometry(CREFSTRING propertyName, INT32& length);

    //////////////////////////////////////////////////////////////////
    /// \brief
    /// Gets the Geometry for the specified property. No conversion is
    /// performed, thus the property must be a of type Geometry or the result
    /// is NULL
    ///
    /// \param index
    /// Property index.
    ///
    /// \return
    /// Returns a ByteReader object
    ///
    BYTE_ARRAY_OUT GetGeometry(INT32 index, INT32& length);

    //////////////////////////////////////////////////////////////////
    /// \brief
    /// Gets the string value of the specified property. No conversion is
    /// performed, thus the property must be a of type string or the result
    /// is NULL
    ///
    /// \param propertyName
    /// Property name.
    ///
    /// \return
    /// Returns the string value.
    ///
    const wchar_t* GetString(CREFSTRING propertyName, INT32& length);

    //////////////////////////////////////////////////////////////////
    /// \brief
    /// Gets the string value of the specified property. No conversion is
    /// performed, thus the property must be a of type string or the result
    /// is NULL
    ///
    /// \param index
    /// Property index.
    ///
    /// \return
    /// Returns the string value.
    ///
    const wchar_t* GetString(INT32 index, INT32& length);

    //////////////////////////////////////////////////////////////////
    /// \brief
    /// Serialize data to TCP/IP stream
    ///
    /// \param stream
    /// Stream
    ///
    virtual void Serialize(MgStream* stream);

    //////////////////////////////////////////////////////////////////
    /// \brief
    /// Deserialize data from TCP/IP stream
    ///
    /// \param stream
    /// Stream
    ///
    virtual void Deserialize(MgStream* stream);

    virtual MgFeatureSet* GetFeatures(INT32 count);

    //////////////////////////////////////////////////////////////////
    /// \brief
    /// ASSIGNs feature set
    ///
    /// \param featureSet
    /// feature set to be assigned
    ///
    void AssignFeatureSet(MgFeatureSet* featureSet);

    void ToXml(string &str);

    void SetService(MgFeatureService* service);

protected:

    virtual INT32 GetClassId()
    {
        return m_cls_id;
    }

    virtual void Dispose()
    {
        delete this;
    }

    MgProxyGwsFeatureReader();
    ~MgProxyGwsFeatureReader();

private:

    MgProperty* GetProperty(CREFSTRING propertyName, INT16 expectedType);
    /// Get the property for the specified name
    MgProperty* GetProperty(CREFSTRING propertyName);

    MgProperty* GetProperty(INT32 index, INT16 expectedType);
    /// Get the property for the specified index
    MgProperty* GetProperty(INT32 index);

    //void UpdateCurrentSet(MgBatchPropertyCollection* bpCol);
    void SetServiceForFeatureProperties(MgFeatureService* service);

    //Ptr<MgBatchPropertyCollection> m_set;
    //Ptr<MgPropertyDefinitionCollection> m_propDefCol;

    //STRING m_providerName;
    Ptr<MgFeatureSet> m_set;
    INT32 m_currRecord;
    STRING m_serverGwsFeatureReader;
    MgFeatureService* m_service; // Do not want to implement a default constructor

CLASS_ID:
    static const INT32 m_cls_id = PlatformBase_FeatureService_GwsFeatureReader;

};
/// \endcond

#endif