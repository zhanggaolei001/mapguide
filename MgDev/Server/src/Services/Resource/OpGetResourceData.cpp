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

#include "ResourceServiceDefs.h"
#include "OpGetResourceData.h"
#include "ServerResourceService.h"
#include "LogManager.h"

///----------------------------------------------------------------------------
/// <summary>
/// Constructs the object.
/// </summary>
///----------------------------------------------------------------------------

MgOpGetResourceData::MgOpGetResourceData()
{
}

///----------------------------------------------------------------------------
/// <summary>
/// Destructs the object.
/// </summary>
///----------------------------------------------------------------------------

MgOpGetResourceData::~MgOpGetResourceData()
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

void MgOpGetResourceData::Execute()
{
    ACE_DEBUG((LM_DEBUG, ACE_TEXT("  (%t) MgOpGetResourceData::Execute()\n")));
    ACE_ASSERT(0 != m_data);

    bool operationCompleted = false;
    bool argsRead = false;
    Ptr<MgStream> stream;

    MG_LOG_OPERATION_MESSAGE(L"GetResourceData");

    MG_RESOURCE_SERVICE_TRY()

    MG_LOG_OPERATION_MESSAGE_INIT(m_packet.m_OperationVersion, m_packet.m_NumArguments);

    stream = new MgStream(m_data->GetStreamHelper());

    if (3 == m_packet.m_NumArguments)
    {
        STRING dataName;
        STRING preProcessTags;
        Ptr<MgResourceIdentifier> resource =
            (MgResourceIdentifier*)stream->GetObject();
        stream->GetString(dataName);
        stream->GetString(preProcessTags);

        argsRead = true;

        MG_LOG_OPERATION_MESSAGE_PARAMETERS_START();
        MG_LOG_OPERATION_MESSAGE_ADD_STRING(L"MgResourceIdentifier");
        MG_LOG_OPERATION_MESSAGE_ADD_SEPARATOR();
        MG_LOG_OPERATION_MESSAGE_ADD_STRING(dataName.c_str());
        MG_LOG_OPERATION_MESSAGE_ADD_SEPARATOR();
        MG_LOG_OPERATION_MESSAGE_ADD_STRING(preProcessTags.c_str());
        MG_LOG_OPERATION_MESSAGE_PARAMETERS_END();

        Authenticate();

        Ptr<MgByteReader> byteReader =
            m_service->GetResourceData(resource, dataName, preProcessTags);

        // Encrypt the document if Substitution pre-processing is required.

        if (MgResourcePreProcessingType::Substitution == preProcessTags
            && byteReader != NULL)
        {
            STRING mimeType = byteReader->GetByteSource()->GetMimeType();
            STRING plainText = byteReader->ToString();

            MgCryptographyManager cryptoManager;
            STRING cipherText = cryptoManager.EncryptString(plainText);

            string document;
            MgUtil::WideCharToMultiByte(cipherText, document);
            Ptr<MgByteSource> byteSource = new MgByteSource(
                (unsigned char*)document.c_str(), (INT32)document.length());

            byteSource->SetMimeType(mimeType);
            byteReader = byteSource->GetReader();
        }

        operationCompleted = true;
        WriteResponseStream(*stream, byteReader);
    }
    else
    {
        MG_LOG_OPERATION_MESSAGE_PARAMETERS_START();
        MG_LOG_OPERATION_MESSAGE_PARAMETERS_END();
    }

    if ( !argsRead )
    {
        throw new MgOperationProcessingException(L"MgOpGetResourceData.Execute",
            __LINE__, __WFILE__, NULL, L"", NULL);
    }

    // Successful operation
    MG_LOG_OPERATION_MESSAGE_ADD_STRING(MgResources::Success.c_str());

    MG_RESOURCE_SERVICE_CATCH(L"MgOpGetResourceData.Execute")

    if (mgException != 0 && !operationCompleted && stream != 0)
    {
        WriteResponseStream(*stream, mgException);

        // Failed operation
        MG_LOG_OPERATION_MESSAGE_ADD_STRING(MgResources::Failure.c_str());
    }

    // Add access log entry for operation
    MG_LOG_OPERATION_MESSAGE_ACCESS_ENTRY();

    MG_RESOURCE_SERVICE_THROW()
}
