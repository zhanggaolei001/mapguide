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

#include "stdafx.h"
#include "IOVectorScaleRange.h"
#include "IOAreaTypeStyle.h"
#include "IOLineTypeStyle.h"
#include "IOPointTypeStyle.h"
#include "IFeatureTypeStyleVisitor.h"

using namespace XERCES_CPP_NAMESPACE;
using namespace MDFMODEL_NAMESPACE;
using namespace MDFPARSER_NAMESPACE;

IOVectorScaleRange::IOVectorScaleRange()
{
}

IOVectorScaleRange::IOVectorScaleRange(VectorLayerDefinition *layer)
{
    this->layer = layer;
}

IOVectorScaleRange::~IOVectorScaleRange()
{
}

void IOVectorScaleRange::StartElement(const wchar_t *name, HandlerStack *handlerStack)
{
    m_currElemName = name;
    if (m_currElemName == L"VectorScaleRange") // NOXLATE
    {
        m_startElemName = name;
        this->_scaleRange = new VectorScaleRange();
    }
    else if (m_currElemName == L"AreaTypeStyle") // NOXLATE
    {
        IOAreaTypeStyle *IO = new IOAreaTypeStyle(this->_scaleRange);
        handlerStack->push(IO);
        IO->StartElement(name, handlerStack);
    }
    else if (m_currElemName == L"LineTypeStyle") // NOXLATE
    {
        IOLineTypeStyle *IO = new IOLineTypeStyle(this->_scaleRange);
        handlerStack->push(IO);
        IO->StartElement(name, handlerStack);
    }
    else if (m_currElemName == L"PointTypeStyle") // NOXLATE
    {
        IOPointTypeStyle *IO = new IOPointTypeStyle(this->_scaleRange);
        handlerStack->push(IO);
        IO->StartElement(name, handlerStack);
    }
}

void IOVectorScaleRange::ElementChars(const wchar_t *ch)
{
    if (m_currElemName == L"MinScale") // NOXLATE
        (this->_scaleRange)->SetMinScale(wstrToDouble(ch));
    else if (m_currElemName == L"MaxScale") // NOXLATE
        (this->_scaleRange)->SetMaxScale(wstrToDouble(ch));
}

void IOVectorScaleRange::EndElement(const wchar_t *name, HandlerStack *handlerStack)
{
    if (m_startElemName == name)
    {
        this->layer->GetScaleRanges()->Adopt(this->_scaleRange);
        handlerStack->pop();
        this->layer = NULL;
        this->_scaleRange = NULL;
        m_startElemName = L"";
        delete this;
    }
}

void IOVectorScaleRange::Write(MdfStream &fd, VectorScaleRange *scaleRange)
{
    fd << tab() << "<VectorScaleRange>" << std::endl; // NOXLATE
    inctab();

    //Property: MinScale (optional)
    if (scaleRange->GetMinScale() != 0.0)
    {
        fd << tab() << "<MinScale>"; // NOXLATE
        fd << DoubleToStr(scaleRange->GetMinScale());
        fd << "</MinScale>" << std::endl; // NOXLATE
    }

    //Property: MaxScale (optional)
    if (scaleRange->GetMaxScale() != VectorScaleRange::MAX_MAP_SCALE)
    {
        fd << tab() << "<MaxScale>"; // NOXLATE
        fd << DoubleToStr(scaleRange->GetMaxScale());
        fd << "</MaxScale>" << std::endl; // NOXLATE
    }

    //Property: FeatureTypeStyle
    for (int x = 0; x < scaleRange->GetFeatureTypeStyles()->GetCount(); x++)
    {
        if (dynamic_cast<AreaTypeStyle*>(scaleRange->GetFeatureTypeStyles()->GetAt(x)) != 0)
        {
            IOAreaTypeStyle * IO = new IOAreaTypeStyle();
            IO->Write(fd, dynamic_cast<AreaTypeStyle*>(scaleRange->GetFeatureTypeStyles()->GetAt(x)));
            delete IO;
        }
        else if (dynamic_cast<LineTypeStyle*>(scaleRange->GetFeatureTypeStyles()->GetAt(x)) != 0)
        {
            IOLineTypeStyle * IO = new IOLineTypeStyle();
            IO->Write(fd, dynamic_cast<LineTypeStyle*>(scaleRange->GetFeatureTypeStyles()->GetAt(x)));
            delete IO;
        }
        else if (dynamic_cast<PointTypeStyle*>(scaleRange->GetFeatureTypeStyles()->GetAt(x)) != 0)
        {
            IOPointTypeStyle * IO = new IOPointTypeStyle();
            IO->Write(fd, dynamic_cast<PointTypeStyle*>(scaleRange->GetFeatureTypeStyles()->GetAt(x)));
            delete IO;
        }
    }

    dectab();
    fd << tab() << "</VectorScaleRange>" << std::endl; // NOXLATE
}
