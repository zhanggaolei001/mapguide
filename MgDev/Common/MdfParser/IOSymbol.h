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

#ifndef _IOSYMBOL_H
#define _IOSYMBOL_H

#include "SAX2ElementHandler.h"
#include "Symbol.h"

using namespace XERCES_CPP_NAMESPACE;
using namespace MDFMODEL_NAMESPACE;

BEGIN_NAMESPACE_MDFPARSER

class IOSymbol : public SAX2ElementHandler
{
    protected:
        Symbol * m_symbol;

    public:
        virtual void ElementChars(const wchar_t *ch);

        Symbol* GetSymbol();

        static void Write(MdfStream &fd, Symbol *symbol);
};

END_NAMESPACE_MDFPARSER
#endif // _IOSYMBOL_H
