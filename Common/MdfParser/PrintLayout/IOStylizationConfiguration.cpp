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

#include "../stdafx.h"
#include "../IOUnknown.h"
#include "IOStylizationConfiguration.h"

CREATE_ELEMENT_MAP;
// Start Elements
ELEM_MAP_ENTRY(1, Stylization);
// Local Elements
ELEM_MAP_ENTRY(2, ResourceId);
ELEM_MAP_ENTRY(3, ExtendedData1);

IOStylizationConfiguration::IOStylizationConfiguration(StylizationConfiguration* stylizationConf, Version& version) :
    SAX2ElementHandler(version),
    m_stylizationConf(stylizationConf)
{
    // The parser will update all the data of the object pointed by the following assigned pointer.
    _ASSERT(NULL != m_stylizationConf);
}

IOStylizationConfiguration::~IOStylizationConfiguration()
{
}

void IOStylizationConfiguration::StartElement(const wchar_t* name, HandlerStack* handlerStack)
{
    m_currElemName = name;
    m_currElemId = _ElementIdFromName(name);

    switch (m_currElemId)
    {
    case eStylization:
        m_startElemName = name;
        break;

    case eExtendedData1:
        m_procExtData = true;
        break;

    case eUnknown:
        ParseUnknownXml(name, handlerStack);
        break;
    }
}

void IOStylizationConfiguration::ElementChars(const wchar_t* ch)
{
    switch (m_currElemId)
    {
    case eResourceId:
        m_stylizationConf->SetResourceId(ch);
        break;
    }
}

void IOStylizationConfiguration::EndElement(const wchar_t* name, HandlerStack* handlerStack)
{
    if (m_startElemName == name)
    {
        m_stylizationConf->SetUnknownXml(m_unknownXml);

        m_startElemName = L"";
        handlerStack->pop();
        delete this;
    }
    else if (eExtendedData1 == _ElementIdFromName(name))
    {
        m_procExtData = false;
    }
}

void IOStylizationConfiguration::Write(MdfStream& fd, StylizationConfiguration* stylizationConf, Version* version)
{
    _ASSERT(NULL != stylizationConf);

    fd << tab() << startStr(sStylization) << std::endl;
    inctab();

    // Property: ResourceId
    fd << tab() << startStr(sResourceId);
    fd << EncodeString(stylizationConf->GetResourceId());
    fd << endStr(sResourceId) << std::endl;

    // Write any unknown XML / extended data
    IOUnknown::Write(fd, stylizationConf->GetUnknownXml(), version);

    dectab();
    fd << tab() << endStr(sStylization) << std::endl;
}