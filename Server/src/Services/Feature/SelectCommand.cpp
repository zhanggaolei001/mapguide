//
//  Copyright (C) 2004-2008 by Autodesk, Inc.
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
#include "MapGuideCommon.h"
#include "Services/FeatureService.h"
#include "FeatureServiceCommand.h"
#include "SelectCommand.h"
#include "SelectAggregateCommand.h"
#include "ServerFeatureReader.h"
#include "ServerFeatureReaderIdentifier.h"
#include "ServerFeatureConnection.h"
#include "FdoFeatureReader.h"
#include "FdoFilterCollection.h"
#include "FdoReaderCollection.h"

// The maximum size of the subfilter for a selection query.  Tune this value for optimal selection perfomance.
#define MG_MAX_SUBFILTER_SIZE  1000

MgSelectCommand::MgSelectCommand(MgResourceIdentifier* resource) : m_filter(NULL)
{
    CHECKNULL((MgResourceIdentifier*)resource, L"MgSelectCommand.MgSelectCommand");

    // Connect to provider
    m_connection = new MgServerFeatureConnection(resource);
    if ( m_connection->IsConnectionOpen() )
    {
        m_providerName = m_connection->GetProviderName();
    }
    else
    {
        throw new MgConnectionFailedException(L"MgServerSelectFeatures::SelectFeatures()", __LINE__, __WFILE__, NULL, L"", NULL);
    }
    // Create FdoISelect command
    FdoPtr<FdoIConnection> fdoConn = m_connection->GetConnection();
    m_command = (FdoISelect*)fdoConn->CreateCommand(FdoCommandType_Select);
    CHECKNULL((FdoISelect*)m_command, L"MgSelectCommand.MgSelectCommand");
}

MgSelectCommand::~MgSelectCommand()
{
    FDO_SAFE_RELEASE(m_command);
    FDO_SAFE_RELEASE(m_filter);
}

FdoIdentifierCollection* MgSelectCommand::GetPropertyNames()
{
    CHECKNULL((FdoISelect*)m_command, L"MgSelectCommand.GetPropertyNames");
    return m_command->GetPropertyNames();
}

void MgSelectCommand::SetDistinct(bool value)
{
    CHECKNULL((FdoISelect*)m_command, L"MgSelectCommand.GetPropertyNames");
    // This operation is not supported by FdoISelect
    // m_command->SetDistinct(value);

    // throw new MgInvalidOperationException(L"MgSelectCommand.SetDistinct", __LINE__, __WFILE__, NULL, L"", NULL);
}

bool MgSelectCommand::GetDistinct()
{
    CHECKNULL((FdoISelect*)m_command, L"MgSelectCommand.GetDistinct");
    // This operation is not supported by FdoISelect
    // return m_command->GetDistinct();

    // throw new MgInvalidOperationException(L"MgSelectCommand.SetDistinct", __LINE__, __WFILE__, NULL, L"", NULL);

    return false;
}

FdoIdentifierCollection* MgSelectCommand::GetOrdering()
{
    CHECKNULL((FdoISelect*)m_command, L"MgSelectCommand.GetOrdering");
    return m_command->GetOrdering();
}

void MgSelectCommand::SetOrderingOption(FdoOrderingOption option)
{
    CHECKNULL((FdoISelect*)m_command, L"MgSelectCommand.GetOrdering");
    m_command->SetOrderingOption(option);
}

FdoOrderingOption MgSelectCommand::GetOrderingOption()
{
    CHECKNULL((FdoISelect*)m_command, L"MgSelectCommand.GetOrdering");
    return m_command->GetOrderingOption();
}

FdoIdentifierCollection* MgSelectCommand::GetGrouping()
{
    CHECKNULL((FdoISelect*)m_command, L"MgSelectCommand.GetDistinct");
    // This operation is not supported by FdoISelect
    // return m_command->GetGrouping();

    // throw new MgInvalidOperationException(L"MgSelectCommand.SetDistinct", __LINE__, __WFILE__, NULL, L"", NULL);
    return NULL;
}

void MgSelectCommand::SetGroupingFilter(FdoFilter* filter)
{
    CHECKNULL((FdoISelect*)m_command, L"MgSelectCommand.GetDistinct");
    // This operation is not supported by FdoISelect
    // m_command->SetGroupingFilter(filter);

    // throw new MgInvalidOperationException(L"MgSelectCommand.SetGroupingFilter", __LINE__, __WFILE__, NULL, L"", NULL);
}

FdoFilter* MgSelectCommand::GetGroupingFilter()
{
    CHECKNULL((FdoISelect*)m_command, L"MgSelectCommand.GetGroupingFilter");
    // This operation is not supported by FdoISelect
    // return m_command->GetGroupingFilter(filter);

    // throw new MgInvalidOperationException(L"MgSelectCommand.GetGroupingFilter", __LINE__, __WFILE__, NULL, L"", NULL);
    return NULL;
}

void MgSelectCommand::SetFeatureClassName(FdoString* value)
{
    CHECKNULL((FdoISelect*)m_command, L"MgSelectCommand.SetFeatureClassName");
    m_command->SetFeatureClassName(value);
}

void MgSelectCommand::SetFilter(FdoString* value)
{
    CHECKNULL((FdoISelect*)m_command, L"MgSelectCommand.SetFilter");
    m_command->SetFilter(value);
}

void MgSelectCommand::SetFilter(FdoFilter* value)
{
    CHECKNULL((FdoISelect*)m_command, L"MgSelectCommand.SetFilter");
    m_command->SetFilter(value);

    FDO_SAFE_RELEASE(m_filter);
    m_filter = FDO_SAFE_ADDREF(value);
}

MgReader* MgSelectCommand::Execute()
{
    FdoPtr<FdoIFeatureReader> reader = NULL;

    printf("MgSelectCommand::Execute()\n");

    // Break up the filter into smaller chunks
    FdoPtr<MgFdoFilterCollection> subFilters = this->GetSubFilters();

    CHECKNULL((FdoISelect*)m_command, L"MgSelectCommand.MgSelectCommand");

    // Execute queries using the smaller filters and collect the results of the queries into a reader collection.
    FdoPtr<MgFdoReaderCollection> frc = MgFdoReaderCollection::Create();
    
    for (FdoInt32 filterIndex = 0; filterIndex < subFilters->GetCount(); filterIndex++)
    {
        FdoFilter* filter = subFilters->GetItem(filterIndex);
        m_command->SetFilter(filter);
        reader = m_command->Execute();

        frc->Add(reader);
    }

    FdoPtr<MgFdoFeatureReader> featureReader = CreateFdoFeatureReader(frc);
    CHECKNULL((FdoIFeatureReader*)featureReader, L"MgSelectCommand.Execute");

    // Create a feature reader identifier
    Ptr<MgServerFeatureReaderIdentifier> featReaderId = new MgServerFeatureReaderIdentifier(featureReader);

    // TODO: This needs to be tied back to the original FDO connection that is cached so that if the original
    //       FDO connection is ever removed from the cache then the associated MgServerFeatureReaderIdentifier
    //       is also removed from it's cache.


    // TODO: Add this identifier to FdoConnectionPool along with connection for next fetch, if required.
    // TODO: MgServerGetFeatures will tell us that whether we need to cache this or not based on if there
    // TODO: can be possible more record available. Need to look into FdoConnectionPoolManager to find out
    // TODO: how can we pool the connections and MgServerFeatureReaderIdentifier

    return new MgServerFeatureReader(featReaderId);
}

bool MgSelectCommand::IsSupportedFunction(FdoFunction* fdoFunc)
{
    FdoPtr<FdoIConnection> fdoConn = m_connection->GetConnection();
    return this->IsFdoSupportedFunction(fdoConn, fdoFunc);
}

bool MgSelectCommand::SupportsSelectGrouping()
{
    FdoPtr<FdoIConnection> fdoConn = m_connection->GetConnection();
    return MgFeatureServiceCommand::SupportsSelectGrouping(fdoConn);
}

bool MgSelectCommand::SupportsSelectOrdering()
{
    FdoPtr<FdoIConnection> fdoConn = m_connection->GetConnection();
    return MgFeatureServiceCommand::SupportsSelectOrdering(fdoConn);
}

bool MgSelectCommand::SupportsSelectDistinct()
{
    FdoPtr<FdoIConnection> fdoConn = m_connection->GetConnection();
    return MgFeatureServiceCommand::SupportsSelectDistinct(fdoConn);
}

FdoFilter* MgSelectCommand::GetFilter()
{
    return FDO_SAFE_ADDREF(m_filter);
}

MgFdoFilterCollection* MgSelectCommand::GetSubFilters()
{
    // Break up a filter into a bunch of smaller filters

    // For now we just reduce a simple case with datastore limitations in handling the number of OR conditions.
    // This is the case where a filter has only OR spatial conditions that can be broken up into a collection
    // of smaller OR filters.

    class FdoCommonFilterFragmenter :  public virtual FdoIFilterProcessor
    {
    private:
        FdoPtr<FdoFilter>	 m_newFilter;
        FdoPtr<FdoIGeometry> m_geomRight;
        FdoPtr<FdoIGeometry> m_geomLeft;

        int m_OrCount;
        std::vector<FdoFilter*> m_filters;
        bool m_isFragmented;

    protected:
        void HandleFilter( FdoFilter *filter )
        {
            filter->Process( this );
        }
    public:

        FdoCommonFilterFragmenter( ):m_isFragmented(true)
        {
            m_OrCount = 0;
            m_filters.clear();
        }

        int GetOrCount() { return m_OrCount; }
        std::vector<FdoFilter*> GetFilters() { return m_filters; }
        bool IsFragmented() { return m_isFragmented; }

        virtual void Dispose() { delete this; }
       
        virtual void ProcessBinaryLogicalOperator(FdoBinaryLogicalOperator& filter)
        {
            if( filter.GetOperation() != FdoBinaryLogicalOperations_Or )
            {
                m_isFragmented = false;
                return;
            }
            if (m_OrCount < 2)
            {
                HandleFilter( FdoPtr<FdoFilter>(filter.GetLeftOperand()) );
                HandleFilter( FdoPtr<FdoFilter>(filter.GetRightOperand()) );
            }
            m_OrCount++;
        }
        virtual void ProcessComparisonCondition(FdoComparisonCondition& filter)
        {
            // Add filter to collection
            m_filters.push_back(&filter);
            return;
        }
        virtual void ProcessDistanceCondition(FdoDistanceCondition& filter)
        {  
            m_isFragmented = false;
            return;
        }

        virtual void ProcessInCondition(FdoInCondition& filter)
        {
            m_isFragmented = false;
            return;
        }
        virtual void ProcessNullCondition(FdoNullCondition& filter)
        {
            m_isFragmented = false;
            return;
        }
        virtual void ProcessSpatialCondition(FdoSpatialCondition& filter)
        {  
            m_isFragmented = false;
            return;
        }

        virtual void ProcessUnaryLogicalOperator(FdoUnaryLogicalOperator& filter)
        {
            m_isFragmented = false;
            return;
        }
    };


    FdoCommonFilterFragmenter  fragmenter;
    if (m_filter)
        m_filter->Process( &fragmenter ); 

#ifdef _DEBUG
    int nCount = fragmenter.GetOrCount();
    if ( nCount > 0)
    {
        char temp[1024];
        sprintf(temp, "Or_Count = %d", nCount);  // NOXLATE
        printf("%s\n", temp);
    }
#endif

    FdoPtr<MgFdoFilterCollection> filters = MgFdoFilterCollection::Create();

    if (fragmenter.IsFragmented() && fragmenter.GetOrCount() > 0)
    {
        int nSelectionCount = 0;

        std::vector<FdoFilter*>::iterator filterIter;
        bool bFirst = true;

        FdoStringP filterString;
        std::vector<FdoFilter*> fragmentedFilters = fragmenter.GetFilters();


        bool bIsAddedToCollection = false;

        for (filterIter = fragmentedFilters.begin(); filterIter != fragmentedFilters.end(); filterIter++)
        {
            FdoStringP tempString = (*filterIter)->ToString();
            FdoStringP orString = L" OR ";  // NOXLATE
            if (bFirst)
            {
                filterString = tempString;
                bFirst = false;
            }
            else
            {
                filterString = filterString + orString + tempString;
                nSelectionCount++;
            }

            if (nSelectionCount >= MG_MAX_SUBFILTER_SIZE)
            {
                filters->Add(FdoFilter::Parse(filterString));
                bFirst = true;
                filterString = L"";
                nSelectionCount = 0;
                bIsAddedToCollection = true;
            }
            else
            {
                bIsAddedToCollection = false;
            }
        }

        if ( !bIsAddedToCollection )
        {
            filters->Add(FdoFilter::Parse(filterString));
        }

    }
    else
    {
        filters->Add(m_filter);
    }

    return FDO_SAFE_ADDREF(filters.p);
}

MgFdoFeatureReader* MgSelectCommand::CreateFdoFeatureReader(MgFdoReaderCollection *readerCollection)
{
    FdoPtr<MgFdoFeatureReader> featureReader = new MgFdoFeatureReader(readerCollection);

    return FDO_SAFE_ADDREF(featureReader.p);
}

