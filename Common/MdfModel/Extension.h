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

#ifndef EXTENSION_H_
#define EXTENSION_H_

#include "MdfModel.h"
#include "AttributeRelate.h"
#include "CalculatedProperty.h"
#include "MdfRootObject.h"

BEGIN_NAMESPACE_MDFMODEL

//-------------------------------------------------------------------------
// DESCRIPTION:
// Extension class defines the joins between feature classes
//-------------------------------------------------------------------------
class MDFMODEL_API Extension : public MdfRootObject
    {
    public:
         // Construction, destruction, initialization
        Extension();
        virtual ~Extension();

        // Operations
        // Property : AttributeRelates
        AttributeRelateCollection* GetAttributeRelates();

        // Property : CalculatedProperty
        CalculatedPropertyCollection* GetCalculatedProperties();

        // Property : Name
        const MdfString& GetName() const;
        void SetName(const MdfString &name);

        // Property : FeatureClass
        const MdfString& GetFeatureClass() const;
        void SetFeatureClass(const MdfString&  strFeatureClass);

    private:
        // Hidden copy constructor and assignment operator.
        Extension(const Extension&);
        Extension& operator=(const Extension&);

        // AttributeRelateCollection
        AttributeRelateCollection m_collAttributeRelates;

        // CalculatedPropertyCollection
        CalculatedPropertyCollection m_collCalculatedProperties;

        // Name
        MdfString m_strName;

        // Feature Class
        MdfString m_strFeatureClass;
    };

    typedef MdfOwnerCollection<Extension> ExtensionCollection;
    EXPIMP_TEMPLATE template
        class MDFMODEL_API MdfOwnerCollection<Extension>;

END_NAMESPACE_MDFMODEL
#endif // EXTENSION_H_