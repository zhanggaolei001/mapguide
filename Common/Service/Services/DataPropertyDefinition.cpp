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

#include "AceCommon.h"
#include "FeatureService.h"
#include "DataPropertyDefinition.h"

IMPLEMENT_CREATE_OBJECT(MgDataPropertyDefinition)

MgDataPropertyDefinition::MgDataPropertyDefinition()
{
    Initialize();
}


//////////////////////////////////////////////////////////////////
/// <summary>
/// Constructs a MgDataPropertyDefinition object
/// </summary>
/// <param name="name">Name of the property</param>
MgDataPropertyDefinition::MgDataPropertyDefinition(CREFSTRING name) : MgPropertyDefinition(name, MgFeaturePropertyType::DataProperty)
{
    Initialize();
}

void MgDataPropertyDefinition::Initialize()
{
    m_dataType = 0;
    m_readOnly = false;
    m_length = 0;
    m_precision = 0;
    m_scale = 0;
    m_nullable = false;
    m_defaultValue = L"";
    m_autogenerated = false;
    m_serializedXml = L"";
}

//////////////////////////////////////////////////////////////////
/// <summary>
/// Gets the data type of this property.
/// </summary>
/// <returns>
/// Returns the data type of this property.
/// </returns>
INT32 MgDataPropertyDefinition::GetDataType()
{
    return m_dataType;
}

//////////////////////////////////////////////////////////////////
/// <summary>
/// Gets the length of a String, BLOB, or CLOB data property.
/// This value does not apply to any other data type.</summary>
/// <returns>
/// Returns the length of a String, BLOB, or CLOB data property
/// </returns>
INT32 MgDataPropertyDefinition::GetLength()
{
    return m_length;
}

//////////////////////////////////////////////////////////////////
/// <summary>
/// Gets the precision (total number of digits) of a decimal data property.
/// This value does not apply to any other data type.
/// </summary>
/// <returns>Returns the precision</returns>
INT32 MgDataPropertyDefinition::GetPrecision()
{
    return m_precision;
}

//////////////////////////////////////////////////////////////////
/// <summary>
/// Gets the scale (number of digits to the right of the decimal point) of a
/// decimal data property. This value does not apply to any other data type.
/// </summary>
/// <returns>Returns the scale</returns>
INT32 MgDataPropertyDefinition::GetScale()
{
    return m_scale;
}

/// <summary>
/// Returns a Boolean value that indicates if this
/// is an autogenerated property.
/// </summary>
/// <returns>Returns a Boolean value.</returns>
bool MgDataPropertyDefinition::IsAutoGenerated()
{
    return m_autogenerated;
}

/// <summary>
/// Gets the default value for this property.
/// </summary>
/// <returns>Returns the default value</returns>
STRING MgDataPropertyDefinition::GetDefaultValue()
{
    return m_defaultValue;
}

///<summary>
/// Returns a Boolean value that indicates if this property's value can be null.
/// </summary>
/// <returns>Returns a Boolean value</returns>
bool MgDataPropertyDefinition::GetNullable()
{
    return m_nullable;
}

///<summary>
/// Returns a Boolean value that indicates if this property is read-only.
/// </summary>
/// <returns>Returns a Boolean value</returns>
bool MgDataPropertyDefinition::GetReadOnly()
{
    return m_readOnly;
}

//////////////////////////////////////////////////////////////////
/// <summary>
/// Sets the data type of this property.
/// </summary>
/// <param name="type">data type of this property.</param>
void MgDataPropertyDefinition::SetDataType(INT32 type)
{
    m_dataType = type;
}

/// <summary>
/// Sets a Boolean value that indicates if this property is read-only
/// </summary>
/// <param name="value">
/// Input a Boolean value that indicates if this property is read-only
/// </param>
/// <returns>
/// Returns nothing
/// </returns>
void MgDataPropertyDefinition::SetReadOnly(bool value)
{
    m_readOnly = value;
}

//////////////////////////////////////////////////////////////////
/// <summary>
/// Sets the length of a String, BLOB, or CLOB data property.
/// This value does not apply to any other data type.</summary>
/// <param name="len">length of this String, BLOB, or CLOB data property</param>
void MgDataPropertyDefinition::SetLength(INT32 len)
{
    m_length = len;
}

//////////////////////////////////////////////////////////////////
/// <summary>
/// Sets the precision (total number of digits) of a decimal data property.
/// This value does not apply to any other data type.
/// </summary>
/// <param name="precision">precision of this decimal property</param>
void MgDataPropertyDefinition::SetPrecision(INT32 precision)
{
    m_precision = precision;
}

//////////////////////////////////////////////////////////////////
/// <summary>
/// Sets the scale (number of digits to the right of the decimal point) of a
/// decimal data property. This value does not apply to any other data type.
/// </summary>
/// <param name="scale">scale of this decimal property</returns>
void MgDataPropertyDefinition::SetScale(INT32 scale)
{
    m_scale = scale;
}

/// <summary>
/// Sets a Boolean value that indicates if this property's value can be null.
/// </summary>
/// <param name="value">
/// Input a Boolean value that indicates if this property's value can be null
/// </param>
/// <returns>Returns nothing</returns>
void MgDataPropertyDefinition::SetNullable(bool value)
{
    m_nullable = value;
}

/// <summary>
/// Sets the default value for this property
/// </summary>
/// <param name="value">
/// Input the default value
/// </param>
/// <returns>Returns nothing</returns>
void MgDataPropertyDefinition::SetDefaultValue(CREFSTRING value)
{
    m_defaultValue = value;
}

/// <summary>
/// Sets a boolean value that indicates if this is an autogenerated property.
/// </summary>
/// <param name="value">
/// true  - autogenerated and read-only
/// false - not autogenerated
/// <returns>Returns nothing</returns>
void MgDataPropertyDefinition::SetAutoGeneration(bool value)
{
    m_autogenerated = value;
}

void MgDataPropertyDefinition::Serialize(MgStream* stream)
{
    MgPropertyDefinition::Serialize(stream);
    stream->WriteInt32(m_dataType);
    stream->WriteBoolean(m_readOnly);
    stream->WriteInt32(m_length);
    stream->WriteInt32(m_precision);
    stream->WriteInt32(m_scale);
    stream->WriteBoolean(m_nullable);
    stream->WriteString(m_defaultValue);
    stream->WriteBoolean(m_autogenerated);
    stream->WriteString(m_serializedXml);
}

void MgDataPropertyDefinition::Deserialize(MgStream* stream)
{
    MgPropertyDefinition::Deserialize(stream);
    stream->GetInt32(m_dataType);
    stream->GetBoolean(m_readOnly);
    stream->GetInt32(m_length);
    stream->GetInt32(m_precision);
    stream->GetInt32(m_scale);
    stream->GetBoolean(m_nullable);
    stream->GetString(m_defaultValue);
    stream->GetBoolean(m_autogenerated);
    stream->GetString(m_serializedXml);
}

void MgDataPropertyDefinition::ToXml(string& xmlStr, bool includeType)
{
}
