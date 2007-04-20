//
//  Copyright (C) 2007 by Autodesk, Inc.
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

#include "stdafx.h"
#include "SE_ExpressionBase.h"
#include "StylizationEngine.h"

#include "SimpleSymbolDefinition.h"

#include <wctype.h>

using namespace MDFMODEL_NAMESPACE;


void SE_ExpressionBase::SetParameterValues(OverrideCollection* overrides)
{
    m_parameters.clear();
    int length = overrides->GetCount();
    for (int i = 0; i < length; i++)
    {
        Override* over = overrides->GetAt(i);
        const wchar_t* name = over->GetParameterIdentifier().c_str();
        const wchar_t* symbol = over->GetSymbolName().c_str();
        const wchar_t* value = over->GetParameterValue().c_str();
        m_parameters[ParamId(symbol, name)] = value;
    }
}


void SE_ExpressionBase::SetDefaultValues(SimpleSymbolDefinition* definition)
{
    m_defaults.clear();

    ParameterCollection* parameters = definition->GetParameterDefinition();
    m_symbol = definition->GetName().c_str();

    int length = parameters->GetCount();
    for (int i = 0; i < length; i++)
    {
        Parameter* param = parameters->GetAt(i);
        const wchar_t* name = param->GetIdentifier().c_str();
        const wchar_t* value = param->GetDefaultValue().c_str();
        m_defaults[name] = value;
    }
}


void SE_ExpressionBase::ReplaceParameters(const MdfModel::MdfString& exprstr, const wchar_t* fallback)
{
    MdfString::size_type startIdx, endIdx, count;
    MdfString::iterator beginIter;
    const wchar_t *name, *value, *trim;

    // trim whitespace from the beginning
    trim = exprstr.c_str();
    while (iswspace(*trim))
        trim++;

    m_buffer.assign(trim);
    startIdx = endIdx = 0;

    for(;;)
    {
        startIdx = m_buffer.find(L'%', startIdx);
        if (startIdx == MdfString::npos)
            break;

        endIdx = m_buffer.find(L'%', startIdx + 1);
        if (endIdx == MdfString::npos)
            break;

        // we have found matched % characters--it must be a parameter
        count = endIdx - startIdx - 1;
        m_param.assign(m_buffer, startIdx + 1, count);
        name = m_param.c_str();

        ParameterMap::const_iterator paramIter = m_parameters.find(ParamId(m_symbol, name));

        if (paramIter == m_parameters.end())
        {
            DefaultMap::const_iterator defIter = m_defaults.find(name);
            if (defIter == m_defaults.end())
                value = fallback;
            else
                value = (*defIter).second;
        }
        else
            value = (*paramIter).second;

        beginIter = m_buffer.begin();
        m_buffer.replace(beginIter + startIdx, beginIter + endIdx + 1, value);
        startIdx += wcslen(value);
    }

    // trim whitespace from the end
    size_t len = m_buffer.size();
    trim = m_buffer.c_str() + len - 1;
    while (iswspace(*trim--))
        len--;
    m_buffer.resize(len);
}


void SE_ExpressionBase::ParseDoubleExpression(const MdfModel::MdfString& exprstr, SE_Double& val, double defaultValue)
{
    wchar_t fallback[64] = { 0 };
    ::swprintf(fallback, 64, L"%.17g", defaultValue);

    ReplaceParameters(exprstr, fallback);
    const wchar_t* cstr = m_buffer.c_str();
    size_t len = m_buffer.size();
    size_t chars = 0;
    val.expression = NULL;
    val = defaultValue;

    if (len == 0)
        return;

    int ret = swscanf(cstr, L"%lf%n", &val.value, &chars);

    if (ret == 1 && chars == len)
        return;

    val.expression = FdoExpression::Parse(cstr);
}


void SE_ExpressionBase::ParseIntegerExpression(const MdfModel::MdfString& exprstr, SE_Integer& val, int defaultValue)
{
    wchar_t fallback[32] = { 0 };
    ::swprintf(fallback, 32, L"%d", defaultValue);

    ReplaceParameters(exprstr, fallback);
    const wchar_t* cstr = m_buffer.c_str();
    size_t len = m_buffer.size();
    size_t chars = 0;
    val.expression = NULL;
    val = defaultValue;

    if (len == 0)
        return;

    int ret = swscanf(cstr, L"%d%n", &val, &chars);

    if (ret == 1 && chars == len)
        return;

    val.expression = FdoExpression::Parse(cstr);
}


void SE_ExpressionBase::ParseBooleanExpression(const MdfModel::MdfString& exprstr, SE_Boolean& val, bool defaultValue)
{
    ReplaceParameters(exprstr, defaultValue? L"true" : L"false");
    const wchar_t* cstr = m_buffer.c_str();
    size_t len = m_buffer.size();
    val.expression = NULL;
    val = defaultValue;

    if (len == 0)
        return;

    if (_wcsicmp(cstr, L"true") == 0)
    {
        val = true;
        return;
    }
    else if (_wcsicmp(cstr, L"false") == 0)
    {
        val = false;
        return;
    }

    val.expression = FdoExpression::Parse(cstr);
}


void SE_ExpressionBase::ParseStringExpression(const MdfModel::MdfString& exprstr, SE_String& val, wchar_t* defaultValue)
{
    ReplaceParameters(exprstr, defaultValue);

    if (exprstr.empty())
    {
        val.expression = NULL;
        val = defaultValue;
    }
    else
    {
        const wchar_t* start = m_buffer.c_str();
        const wchar_t* str = start;

        // literal expression must start with a single quote (after trimming)
        if (*str++ != L'\'')
        {
            try
            {
                val.expression = FdoExpression::Parse(start);
            }
            catch (FdoException* e)
            {
                e->Release();

                // just use the string directly
                val.expression = NULL;
                val = start;
            }
            return;
        }

        while(*str != L'\0' && *str != L'\'')
            str++;

        // literal expression must have a matching closing single quote
        if (*str++ == L'\0')
        {
            try
            {
                val.expression = FdoExpression::Parse(start);
            }
            catch (FdoException* e)
            {
                e->Release();

                // just use the string directly
                val.expression = NULL;
                val = start;
            }
            return;
        }

        // last character of the literal expression should also be a single quote
        if (*str != L'\0')
        {
            try
            {
                val.expression = FdoExpression::Parse(start);
            }
            catch (FdoException* e)
            {
                e->Release();

                // just use the string directly
                val.expression = NULL;
                val = start;
            }
            return;
        }

        size_t len = m_buffer.size() - 2;
        wchar_t* copy = new wchar_t[len + 1];
        memcpy(copy, start + 1, sizeof(wchar_t)*len);
        copy[len] = L'\0';
        val = copy;
    }
}


void SE_ExpressionBase::ParseColorExpression(const MdfModel::MdfString& exprstr, SE_Color& val, unsigned int defaultValue)
{
    wchar_t fallback[9] = { 0 };
    ::swprintf(fallback, 9, L"%08x", defaultValue);

    ReplaceParameters(exprstr, fallback);
    const wchar_t* cstr = m_buffer.c_str();
    size_t len = m_buffer.size();
    size_t chars = 0;
    val.expression = NULL;
    val = defaultValue;

    if (len == 0)
        return;

    int ret = swscanf(cstr, L"%X%n", &val.value.argb, &chars);

    if (ret == 1 && chars == len)
        return;

    val.expression = FdoExpression::Parse(cstr);
}
