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

#include "ServerFeatureServiceDefs.h"
#include "AceCommon.h"
#include "FeatureService.h"
#include "FeatureServiceCommand.h"
#include "SelectCommand.h"
#include "SelectAggregateCommand.h"

MgFeatureServiceCommand* MgFeatureServiceCommand::CreateCommand(MgResourceIdentifier* resource, FdoCommandType commandType)
{
    Ptr<MgFeatureServiceCommand> command = (MgFeatureServiceCommand*)NULL;
    switch(commandType)
    {
        case FdoCommandType_Select:
        {
            command = new MgSelectCommand(resource);
            break;
        }
        case FdoCommandType_SelectAggregates:
        {
            command = new MgSelectAggregateCommand(resource);
            break;
        }
    }
    return SAFE_ADDREF((MgFeatureServiceCommand*)command);
}

bool MgFeatureServiceCommand::IsFdoSupportedFunction(FdoIConnection* connection, FdoFunction* fdoFunc)
{
    CHECKNULL(connection, L"MgServerSelectFeatures.SupportsFunction");

    GisPtr<FdoIExpressionCapabilities> fec = connection->GetExpressionCapabilities();
    CHECKNULL((FdoIExpressionCapabilities*)fec, L"MgServerSelectFeatures.SupportsFunction");

    bool supports = false;

    GisPtr<FdoFunctionDefinitionCollection> ffdc = fec->GetFunctions();
    if (NULL != (FdoFunctionDefinitionCollection*)ffdc)
    {
        GisInt32 funcCnt = ffdc->GetCount();
        for (GisInt32 i=0; i < funcCnt; i++)
        {
            GisPtr<FdoFunctionDefinition> ffd = ffdc->GetItem(i);
            CHECKNULL((FdoFunctionDefinition*)ffd, L"MgServerSelectFeatures.SupportsFunction");

            // TODO: Just comparing name is enough?
            // TODO: I think, NOT, because there can be overloaded functions like one function
            // with multiple arguments, differnet datatypes etc.
            //
            // Comparing argument count is not sufficient because, there can be optional arguments
            // as well. Therefore, we should just restrict to name comparision only
            GisString* funcNameAllowed = ffd->GetName();
            GisString* funcNameSupplied = fdoFunc->GetName();
            size_t cmp = _wcsicmp(funcNameAllowed, funcNameSupplied);
            if (cmp == 0)
            {
                supports = true;
                break;
            }
        }
    }
    return supports;
}

bool MgFeatureServiceCommand::SupportsSelectDistinct(FdoIConnection* connection)
{
    CHECKNULL((FdoIConnection*)connection, L"MgServerFeatureConnection.SupportsConfiguration()");

    GisPtr<FdoICommandCapabilities> fcc = connection->GetCommandCapabilities();
    CHECKNULL((FdoICommandCapabilities*)fcc, L"MgFeatureServiceCommand.SupportsSelectDistinct");

    bool supports = fcc->SupportsSelectDistinct();

    return supports;
}


bool MgFeatureServiceCommand::SupportsSelectOrdering(FdoIConnection* connection)
{
    CHECKNULL((FdoIConnection*)connection, L"MgServerFeatureConnection.SupportsConfiguration()");

    GisPtr<FdoICommandCapabilities> fcc = connection->GetCommandCapabilities();
    CHECKNULL((FdoICommandCapabilities*)fcc, L"MgFeatureServiceCommand.SupportsSelectOrdering");

    bool supports = fcc->SupportsSelectOrdering();

    return supports;
}

bool MgFeatureServiceCommand::SupportsSelectGrouping(FdoIConnection* connection)
{
    CHECKNULL((FdoIConnection*)connection, L"MgServerFeatureConnection.SupportsConfiguration()");

    GisPtr<FdoICommandCapabilities> fcc = connection->GetCommandCapabilities();
    CHECKNULL((FdoICommandCapabilities*)fcc, L"MgFeatureServiceCommand.SupportsSelectGrouping");

    bool supports = fcc->SupportsSelectGrouping();

    return supports;
}
