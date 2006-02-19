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

#ifndef _MG_SERVER_GET_PROVIDER_CAPABILITIES_H_
#define _MG_SERVER_GET_PROVIDER_CAPABILITIES_H_

#include "Common.h"
#include "XmlDefs.h"
#include "XmlUtil.h"
#include "Fdo.h"

class MgServerGetProviderCapabilities
{
public:
    MgServerGetProviderCapabilities(CREFSTRING providerName);
    ~MgServerGetProviderCapabilities();
    MgByteReader* GetProviderCapabilities();

private:

    void CreateCapabilitiesDocument();
    void CreateConnectionCapabilities();
    void CreateSchemaCapabilities();
    void CreateCommandCapabilities();
    void CreateFilterCapabilities();
    void CreateExpressionCapabilities();
    void CreateRasterCapabilities();
    void CreateTopologyCapabilities();
    void CreateGeometryCapabilities();

    bool IsConnectionOpen();
    static bool Initialize();

    IConnectionManager*     m_connManager;
    MgXmlUtil*              m_xmlUtil;
    STRING                  m_providerName;
    FdoIConnection*         m_fdoConn;
    MgXmlUtil*              m_xmlCap;
    static bool             m_isInitialized;

};

#endif
