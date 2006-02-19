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
#include "ServerFeatureConnection.h"
#include "FeatureManipulationCommand.h"
#include "ServerUpdateCommand.h"
#include "FeatureCommand.h"
#include "ServerFeatureUtil.h"
#include "ServerFeatureReader.h"

MgServerUpdateCommand::MgServerUpdateCommand()
{
    m_srvrFeatConn = NULL;
    m_featCommand = NULL;
}

MgServerUpdateCommand::MgServerUpdateCommand(MgFeatureCommand* command, MgServerFeatureConnection* connection, INT32 cmdId)
{
    CHECKNULL(command, L"MgServerUpdateCommand.MgServerUpdateCommand");
    CHECKNULL(connection, L"MgServerUpdateCommand.MgServerUpdateCommand");

    m_srvrFeatConn = connection;
    m_featCommand = SAFE_ADDREF((MgUpdateFeatures*)command);
    m_cmdId = cmdId;
}

MgServerUpdateCommand::~MgServerUpdateCommand()
{
    m_srvrFeatConn = NULL; // It is deleted in MgServerUpdateFeatures class
}

MgProperty* MgServerUpdateCommand::Execute()
{
    STRING clsName = m_featCommand->GetFeatureClassName();
    STRING filterText = m_featCommand->GetFilterText();
    Ptr<MgPropertyCollection> propCol = m_featCommand->GetPropertyValues();

    GisPtr<FdoIConnection> fdoConn = m_srvrFeatConn->GetConnection();

    // Create the SQL command
    GisPtr<FdoIUpdate> fdoCommand = (FdoIUpdate*)fdoConn->CreateCommand(FdoCommandType_Update);
    CHECKNULL((FdoIUpdate*)fdoCommand, L"MgServerUpdateCommand.Execute");

    fdoCommand->SetFeatureClassName(clsName.c_str());
    fdoCommand->SetFilter(filterText.c_str());

    GisPtr<FdoPropertyValueCollection> paramValCol = fdoCommand->GetPropertyValues();
    MgServerFeatureUtil::FillFdoPropertyCollection(propCol, paramValCol);

    INT32 recordsUpdated = fdoCommand->Execute();

    char buff[32];
    sprintf(buff, "%d", m_cmdId);
    STRING str = MgUtil::MultiByteToWideChar(string(buff));

    Ptr<MgInt32Property> prop = new MgInt32Property(str, recordsUpdated);

    return SAFE_ADDREF((MgInt32Property*)prop);
}
