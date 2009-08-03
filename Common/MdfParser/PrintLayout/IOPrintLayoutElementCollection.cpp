//
//  Copyright (C) 2004-2009 by Autodesk, Inc.
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
#include "../Common/IOPoint3D.h"
#include "../Common/IOStringObjectCollection.h"
#include "IOPrintLayoutElementCollection.h"

CREATE_ELEMENT_MAP;
// Start Elements
ELEM_MAP_ENTRY(1, LayoutElement);
// Local Elements
ELEM_MAP_ENTRY(2, Name);
ELEM_MAP_ENTRY(3, ResourceId);
ELEM_MAP_ENTRY(4, Center);
ELEM_MAP_ENTRY(5, Width);
ELEM_MAP_ENTRY(6, Height);
ELEM_MAP_ENTRY(7, Rotation);
ELEM_MAP_ENTRY(8, Units);
ELEM_MAP_ENTRY(9, Visible);
ELEM_MAP_ENTRY(10, Opacity);
ELEM_MAP_ENTRY(11, References);
ELEM_MAP_ENTRY(12, ExtendedData1);

IOPrintLayoutElementCollection::IOPrintLayoutElementCollection(PrintLayoutElementCollection* layoutElems, Version& version) :
    SAX2ElementHandler(version),
    m_layoutElems(layoutElems)
{
    // The parser will update all the data of the object pointed by the following assigned pointer.
    _ASSERT(NULL != m_layoutElems);
}

IOPrintLayoutElementCollection::~IOPrintLayoutElementCollection()
{
}

void IOPrintLayoutElementCollection::StartElement(const wchar_t* name, HandlerStack* handlerStack)
{
    m_currElemName = name;
    m_currElemId = _ElementIdFromName(name);

    switch (m_currElemId)
    {
    case eLayoutElement:
        m_startElemName = name;
        m_currElem.reset(new PrintLayoutElement());
        break;

    case eCenter:
        {
            IOPoint3D* IO = new IOPoint3D(m_currElem->GetCenter(), m_version);
            handlerStack->push(IO);
            IO->StartElement(name, handlerStack);
        }
        break;
    
    case eReferences:
        {
            IOStringObjectCollection* IO = new IOStringObjectCollection(m_currElem->GetReferences(), m_version, sReferences, sName);
            handlerStack->push(IO);
            IO->StartElement(name, handlerStack);
        }
        break;
    
    case eExtendedData1:
        m_procExtData = true;
        break;

    case eUnknown:
        ParseUnknownXml(name, handlerStack);
    }
}

void IOPrintLayoutElementCollection::ElementChars(const wchar_t* ch)
{
    switch (m_currElemId)
    {
    case eName:
        m_currElem->SetName(ch);
        break;

    case eResourceId:
        m_currElem->SetResourceId(ch);
        break;

    case eWidth:
        m_currElem->SetWidth(wstrToDouble(ch));
        break;

    case eHeight:
        m_currElem->SetHeight(wstrToDouble(ch));
        break;

    case eRotation:
        m_currElem->SetRotation(wstrToDouble(ch));
        break;

    case eUnits:
        m_currElem->SetUnits(ch);
        break;

    case eVisible:
        m_currElem->SetIsVisible(wstrToBool(ch));
        break;

    case eOpacity:
        m_currElem->SetOpacity(wstrToDouble(ch));
        break;
    }
}

void IOPrintLayoutElementCollection::EndElement(const wchar_t* name, HandlerStack* handlerStack)
{
    if (m_startElemName == name)
    {
        m_currElem->SetUnknownXml(m_unknownXml);
        m_layoutElems->Adopt(m_currElem.release());

        m_startElemName = L"";
        handlerStack->pop();
        delete this;
    }
    else if (eExtendedData1 == _ElementIdFromName(name))
    {
        m_procExtData = false;
    }
}

void IOPrintLayoutElementCollection::Write(MdfStream& fd, PrintLayoutElementCollection* layoutElems, Version* version, const std::string& name)
{
    _ASSERT(NULL != layoutElems);

    fd << tab() << startStr(name) << std::endl;
    inctab();

    for (int i = 0; i < layoutElems->GetCount(); ++i)
    {
       fd << tab() << startStr(sLayoutElement) << std::endl;
       inctab();

        PrintLayoutElement* layoutElem = dynamic_cast<PrintLayoutElement*>(layoutElems->GetAt(i));
        _ASSERT(NULL != layoutElem);

        // Property: Name
        fd << tab() << startStr(sName);
        fd << EncodeString(layoutElem->GetName());
        fd << endStr(sName) << std::endl;

        // Property: ResourceId
        fd << tab() << startStr(sResourceId);
        fd << EncodeString(layoutElem->GetResourceId());
        fd << endStr(sResourceId) << std::endl;

        // Property: Center
        IOPoint3D::Write(fd, layoutElem->GetCenter(), version, sCenter);

        // Property: Width
        fd << tab() << startStr(sWidth);
        fd << DoubleToStr(layoutElem->GetWidth());
        fd << endStr(sWidth) << std::endl;

        // Property: Height
        fd << tab() << startStr(sHeight);
        fd << DoubleToStr(layoutElem->GetHeight());
        fd << endStr(sHeight) << std::endl;

        // Property: Rotation
        fd << tab() << startStr(sRotation);
        fd << DoubleToStr(layoutElem->GetRotation());
        fd << endStr(sRotation) << std::endl;

        // Property: Units
        fd << tab() << startStr(sUnits);
        fd << EncodeString(layoutElem->GetUnits());
        fd << endStr(sUnits) << std::endl;

        // Property: Visible
        fd << tab() << startStr(sVisible);
        fd << BoolToStr(layoutElem->GetIsVisible());
        fd << endStr(sVisible) << std::endl;

        // Property: Opacity
        fd << tab() << startStr(sOpacity);
        fd << DoubleToStr(layoutElem->GetOpacity());
        fd << endStr(sOpacity) << std::endl;

        // Property: References
        IOStringObjectCollection::Write(fd, layoutElem->GetReferences(), version, sReferences, sName);
    
        // Write any unknown XML / extended data
        IOUnknown::Write(fd, layoutElem->GetUnknownXml(), version);

        dectab();
        fd << tab() << endStr(sLayoutElement) << std::endl;
    }

    dectab();
    fd << tab() << endStr(name) << std::endl;
}
