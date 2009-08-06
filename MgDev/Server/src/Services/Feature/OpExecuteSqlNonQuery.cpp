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

#include "ServerFeatureServiceDefs.h"
#include "OpExecuteSqlNonQuery.h"
#include "ServerFeatureService.h"
#include "LogManager.h"
#include "ServerFeatureTransactionPool.h"


///----------------------------------------------------------------------------
/// <summary>
/// Constructs the object.
/// </summary>
///----------------------------------------------------------------------------
MgOpExecuteSqlNonQuery::MgOpExecuteSqlNonQuery()
{
}


///----------------------------------------------------------------------------
/// <summary>
/// Destructs the object.
/// </summary>
///----------------------------------------------------------------------------
MgOpExecuteSqlNonQuery::~MgOpExecuteSqlNonQuery()
{
}


///----------------------------------------------------------------------------
/// <summary>
/// Executes the operation.
/// </summary>
///
/// <exceptions>
/// MgException
/// </exceptions>
///----------------------------------------------------------------------------
void MgOpExecuteSqlNonQuery::Execute()
{
    ACE_DEBUG((LM_DEBUG, ACE_TEXT("  (%t) MgOpExecuteSqlNonQuery::Execute()\n")));

    MG_LOG_OPERATION_MESSAGE(L"ExecuteSqlNonQuery");

    MG_FEATURE_SERVICE_TRY()

    MG_LOG_OPERATION_MESSAGE_INIT(m_packet.m_OperationVersion, m_packet.m_NumArguments);

    ACE_ASSERT(m_stream != NULL);

    if (2 == m_packet.m_NumArguments)
    {
        // Get the feature source
        Ptr<MgResourceIdentifier> resource = (MgResourceIdentifier*)m_stream->GetObject();

        // Get the schema name
        STRING sqlNonSelectStatement;
        m_stream->GetString(sqlNonSelectStatement);

        BeginExecution();

        MG_LOG_OPERATION_MESSAGE_PARAMETERS_START();
        MG_LOG_OPERATION_MESSAGE_ADD_STRING((NULL == resource) ? L"MgResourceIdentifier" : resource->ToString().c_str());
        MG_LOG_OPERATION_MESSAGE_ADD_SEPARATOR();
        MG_LOG_OPERATION_MESSAGE_ADD_STRING(sqlNonSelectStatement.c_str());
        MG_LOG_OPERATION_MESSAGE_PARAMETERS_END();

        Validate();

        // Execute the operation
        INT32 rowsUpdated = m_service->ExecuteSqlNonQuery(resource, sqlNonSelectStatement);

        // Write the response
        EndExecution(rowsUpdated);
    }
    else if (3 == m_packet.m_NumArguments)
    {
        // Get the feature source
        Ptr<MgResourceIdentifier> resource = (MgResourceIdentifier*)m_stream->GetObject();

        // Get the schema name
        STRING sqlNonSelectStatement;
        m_stream->GetString(sqlNonSelectStatement);

        // Get the transaction id
        STRING transactionId;
        m_stream->GetString(transactionId);

        BeginExecution();

        MG_LOG_OPERATION_MESSAGE_PARAMETERS_START();
        MG_LOG_OPERATION_MESSAGE_ADD_STRING((NULL == resource) ? L"MgResourceIdentifier" : resource->ToString().c_str());
        MG_LOG_OPERATION_MESSAGE_ADD_SEPARATOR();
        MG_LOG_OPERATION_MESSAGE_ADD_STRING(sqlNonSelectStatement.c_str());
        MG_LOG_OPERATION_MESSAGE_ADD_SEPARATOR();
        MG_LOG_OPERATION_MESSAGE_ADD_STRING(transactionId.c_str());
        MG_LOG_OPERATION_MESSAGE_PARAMETERS_END();

        Validate();

        MgServerFeatureTransactionPool* transactionPool = MgServerFeatureTransactionPool::GetInstance();
        CHECKNULL(transactionPool, L"MgOpExecuteSqlNonQuery.Execute")

        transactionPool->ValidateTimeout(transactionId);

        // Get the MgTransaction instance from the pool if one has been started for this resource.
        Ptr<MgServerFeatureTransaction> transaction = transactionPool->GetTransaction(transactionId);

        // Execute the operation
        INT32 rowsUpdated = m_service->ExecuteSqlNonQuery(resource, sqlNonSelectStatement, (MgTransaction*)transaction.p);

        // Write the response
        EndExecution(rowsUpdated);
    }
    else
    {
        MG_LOG_OPERATION_MESSAGE_PARAMETERS_START();
        MG_LOG_OPERATION_MESSAGE_PARAMETERS_END();
    }

    if (!m_argsRead)
    {
        throw new MgOperationProcessingException(L"MgOpExecuteSqlNonQuery.Execute",
            __LINE__, __WFILE__, NULL, L"", NULL);
    }

    // Successful operation
    MG_LOG_OPERATION_MESSAGE_ADD_STRING(MgResources::Success.c_str());

    MG_FEATURE_SERVICE_CATCH(L"MgOpExecuteSqlNonQuery.Execute")

    if (mgException != NULL)
    {
        // Failed operation
        MG_LOG_OPERATION_MESSAGE_ADD_STRING(MgResources::Failure.c_str());
    }

    // Add access log entry for operation
    MG_LOG_OPERATION_MESSAGE_ACCESS_ENTRY();

    MG_FEATURE_SERVICE_THROW()
}
