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
#include "TileOperation.h"
#include "ServiceManager.h"

///----------------------------------------------------------------------------
/// <summary>
/// Constructs the object.
/// </summary>
///
/// <exceptions>
/// MgException
/// </exceptions>
///----------------------------------------------------------------------------

MgTileOperation::MgTileOperation()
{
    MG_TRY()

    MgServiceManager* serviceManager = MgServiceManager::GetInstance();
    assert(NULL != serviceManager);

    m_service = dynamic_cast<MgTileService*>(
        serviceManager->RequestService(MgServiceType::TileService));
    assert(m_service != NULL);

    MG_CATCH_AND_THROW(L"MgTileOperation.MgTileOperation")
}

///----------------------------------------------------------------------------
/// <summary>
/// Destructs the object.
/// </summary>
///----------------------------------------------------------------------------

MgTileOperation::~MgTileOperation()
{
}

///----------------------------------------------------------------------------
/// <summary>
/// Perform validation on the operation
/// </summary>
///----------------------------------------------------------------------------

///----------------------------------------------------------------------------
/// <summary>
/// Perform validation on the operation
/// </summary>
///----------------------------------------------------------------------------

void MgTileOperation::Validate()
{
    CheckLicense();
}
