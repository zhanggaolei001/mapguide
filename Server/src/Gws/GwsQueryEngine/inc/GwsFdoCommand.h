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

//////////////////////////////////////////////////////////////////////////////////////////
//
// Definitions
//
/////////////////////////////////////////////////////////////////////////////////////////
#define FETCH_SIZE 50   // fetch size for multi-feature commands


//////////////////////////////////////////////////////////////////////////////////////////
//
// Forward declarations
//
/////////////////////////////////////////////////////////////////////////////////////////
class CGwsMutableFeature;

//////////////////////////////////////////////////////////////////////////////////////////
//
// Typedefs
//
/////////////////////////////////////////////////////////////////////////////////////////
// failed status
typedef std::map<GWSFeatureId,CGwsStatus>   GwsFailedStatus;
typedef GwsFailedStatus::iterator           GwsFailedStatusIterator;


class CGwsCSQueryProcessor: public FdoIFilterProcessor
{
public:
                 CGwsCSQueryProcessor (
                        IGWSCoordinateSystemConverter  *pConverter);
    virtual      ~CGwsCSQueryProcessor ();
    virtual void ProcessSpatialCondition(FdoSpatialCondition& filter);
    virtual void ProcessBinaryLogicalOperator(FdoBinaryLogicalOperator& filter);
    virtual void ProcessUnaryLogicalOperator(FdoUnaryLogicalOperator& filter);
    virtual void ProcessComparisonCondition(FdoComparisonCondition& filter);
    virtual void ProcessInCondition(FdoInCondition& filter);
    virtual void ProcessNullCondition(FdoNullCondition& filter);
    virtual void ProcessDistanceCondition(FdoDistanceCondition& filter);
    virtual void Dispose();

    EGwsStatus   Status() const;

private:
    GisPtr<IGWSCoordinateSystemConverter> m_converter;
    EGwsStatus          m_status;
};


//////////////////////////////////////////////////////////////////////////////////////////
//
// Fdo data manipulation command wrapper
// class CGwsFdoCommand
//
/////////////////////////////////////////////////////////////////////////////////////////
class CGwsFdoCommand : public CGwsObject
{
public:

    typedef enum _CommandType {
        eUndefined,
        eInsert,
        eUpdate,
        eDelete,
        eLock,
        eUnlock,
        eLockInfo,
        eSelect
    } EFdoCommandType;

    typedef std::vector<WSTR> ObjectPropNames;
    typedef std::map<WSTR, CGwsFdoCommand*> ObjectPropCommands;

protected:
    // Construction/desctruction
    //
    GWS_QUERYENGINE_API     CGwsFdoCommand (FdoIConnection          *connection,
                                            const GWSQualifiedName   &classname);
    GWS_QUERYENGINE_API     CGwsFdoCommand  ();
public:
    GWS_QUERYENGINE_API
    virtual                 ~CGwsFdoCommand ();

    // Initialization
    // Should be called: Init(), Prepare (), Execute ()
    GWS_QUERYENGINE_API
    virtual EGwsStatus      Init            (const wchar_t* pFDOCommandClass = NULL);

    // set the caller coordinate system converter
    // If Converter destination coordinate system must be intialized, than
    // in case of select command fs geometry will be converted to it;
    // in case of insert and update geometry will be converted from it to
    // the fs geometry
    GWS_QUERYENGINE_API
    void                    SetCSConverter (IGWSCoordinateSystemConverter * converter);

    GWS_QUERYENGINE_API
    void                    GetCSConverter (IGWSCoordinateSystemConverter ** converter);

    // just do basic preparation (
    //  - get properties and key descriptors
    //  - call PrepareInternal
    //  - Call IFdoCommand->Prepare ()
    GWS_QUERYENGINE_API
    virtual EGwsStatus      Prepare         ();

    GWS_QUERYENGINE_API
    virtual EGwsStatus      Execute         (IGWSMutableFeature * feature);
    GWS_QUERYENGINE_API
    virtual EGwsStatus      Execute         (CGwsMutableFeature & feature);
    GWS_QUERYENGINE_API
    virtual EGwsStatus      Execute         (const GWSFeatureId & featid);
    GWS_QUERYENGINE_API
    virtual EGwsStatus      Execute         (const GwsFeaturesIdVector & featids);
    GWS_QUERYENGINE_API
    virtual EGwsStatus      Execute         (const GwsFeaturesIdVector & featids, int lbound, int ubound);
    GWS_QUERYENGINE_API
    virtual CGwsFdoCommand::EFdoCommandType Type   () const = 0;

    GWS_QUERYENGINE_API
    const GWSQualifiedName& ClassName() const { return m_classname; }
    GWS_QUERYENGINE_API
    FdoClassDefinition *    ClassDefinition ()
    {
        if (m_classDef != NULL)
            m_classDef.p->AddRef ();
        return m_classDef;
    }

    const WSTR&             RevisionPropertyName() const { return m_revisionprop; }
    const WSTR&             GeometryPropertyName() const { return m_geometricprop; }
    // returns long transaction name in context of which command is executed
    const WSTR &            LongTransactionName () const { return m_activelt;}
    const WSTR&             ActiveSpatialContext() const { return m_geometricSC;}
    WSTR                    QualifiedClassName();
    // return property definition
    FdoPropertyDefinition * GetPropertyDefinition (GisString * propname);

    // Implementation
    //

    // build filter for the special case of the single integer identity property
    // fails for all other cases
    GWS_QUERYENGINE_API
    EGwsStatus              BuildFilter (IGWSLongFeatureIdSet* idSet,
                                         FdoFilter  *  & pOutFilter);
    GWS_QUERYENGINE_API
    EGwsStatus              BuildFilter    (const GwsFeaturesIdVector & featIds,
                                            int                       lbound,
                                            int                       ubound,
                                            FdoFilter              *& pOutFilter);
    // build filter from feature id
    GWS_QUERYENGINE_API
    EGwsStatus              BuildFilter     (const GWSFeatureId      & featId,
                                             FdoFilter              *& pOutFilter);
    // build filter on any type of identity property
    GWS_QUERYENGINE_API
    static EGwsStatus       BuildFilter    (FdoIConnection          * connection,
                                            FdoDataPropertyDefinitionCollection* identity,
                                            const GwsFeaturesIdVector & featIds,
                                            int                       lbound,
                                            int                       ubound,
                                            FdoFilter              *& pOutFilter);

    GWS_QUERYENGINE_API
    FdoIConnection  *       GetFdoConnection ()
    {
        FdoIConnection * conn = m_connection;
        if (conn != NULL)
            conn->AddRef ();
        return conn;
    }

    GWS_QUERYENGINE_API
    void                    SetFeatureCommandFilter (FdoFilter * filter);

protected:
    // this method discovers name of the revision number property
    void                    DiscoverRevisionProperty ();

    // discover active long transaction. Long transaction is set by the calling code
    // and command is using it to construct CGwsFdoFeatureIds
    void                    DiscoverActiveLongTransaction ();

    // prepare comamd internal. This virtual method is called by Command::Prepare to facilitate
    // prepare of derived commands
    GWS_QUERYENGINE_API
    virtual void            PrepareInternal         ();
    GWS_QUERYENGINE_API
    virtual FdoPropertyValueCollection *  GetPropertyValues ();
    GWS_QUERYENGINE_API
    virtual void            ReleasePropertyValues   ();

    virtual void            SetFilterInternal (FdoFilter * filter) = 0;

    EGwsStatus              SetProperties (CGwsMutableFeature & feature);

    // prepare none-key propeties. Throws GisException that is supposed to be caught by
    // the public Prepare method
    void                    PrepareNonKeyProperties ();
    void                    PrepareKeyProperties ();
    void                    PrepareObjectProperties ();

    //static methods for building identity filters on arbitrary identity metadata
    GWS_QUERYENGINE_API
    static EGwsStatus       BuildFilter     (FdoDataPropertyDefinitionCollection* identity,
                                             const GWSFeatureId      & featId,
                                             FdoFilter              *& pOutFilter);
    GWS_QUERYENGINE_API
    static EGwsStatus       BuildInFilter   (FdoDataPropertyDefinitionCollection* identity,
                                             const GwsFeaturesIdVector & featIds,
                                             int                         lbound,
                                             int                         ubound,
                                             FdoFilter              *&   pOutFilter);

    // process lock conflicts returned in lock conflict reader.
    EGwsStatus              ProcessLockConflicts (
                                                  FdoILockConflictReader      * pReader,
                                                  GwsFailedStatus             & failed
                                                 ) const;

     // Prepares filter by applying cs conversions to spatial predicates
    void                    PrepareFilter (FdoFilter * ifiler);

private:
    void                    SetValue (FdoPropertyValue      *  pPropVal);

    // converts geometry property backwards.
    FdoPropertyValue *      ConvertGeometryProperty (
                                const GWSCoordinateSystem & csname,
                                FdoPropertyValue * val);

    // build in filer
    EGwsStatus              BuildInFilter   (const GwsFeaturesIdVector & featIds,
                                            int                         lbound,
                                            int                         ubound,
                                            FdoFilter              *&   pOutFilter);
protected:
    // Member Data
    GisPtr<FdoIConnection>                      m_connection;
    GWSQualifiedName                            m_classname;
    WSTR                                        m_activelt;         // active long transaction
    WSTR                                        m_revisionprop;     // revision property name
    WSTR                                        m_geometricprop;    // geometric property name
    WSTR                                        m_geometricSC;      // spatial context name for geometric property

    // caller and fs coordinate systems. used to initialize converter
    GisPtr<IGWSCoordinateSystemConverter>       m_converter;
    bool                                        m_bFilterPrepared;

    GisPtr<FdoICommand>                         m_pCommand;
    GisPtr<FdoPropertyValueCollection>          m_pProperties;

    typedef std::map<std::wstring,FdoPropertyDefinition*> PropertyDefinitionMap;

    // caching class defintion
    GisPtr<FdoFeatureSchema>                    m_schema;
    GisPtr<FdoClassDefinition>                  m_classDef;
    GisPtr<FdoDataPropertyDefinitionCollection> m_identity;
    PropertyDefinitionMap                       m_propdefs;

    // caching values and commands for FDO object properties
    ObjectPropNames                             m_objPropNames;
    ObjectPropCommands                          m_objPropCommands;
    bool                                        m_bIsPrepared;

    // skip setting of the unsupported properties
    bool                                        m_bSkipUnsupportedProperties;

    // some capabilities that we want to examine fast
    bool                                        m_bSupportBlobs;
    bool                                        m_bSupportClobs;

    // supports locking flag
    bool                                        m_bSupportLocking;
};



//////////////////////////////////////////////////////////////////////////////////////////
//
// insert command
//
//////////////////////////////////////////////////////////////////////////////////////////
class CGwsFdoInsertCommand : public CGwsFdoCommand
{
public:
    GWS_QUERYENGINE_API  CGwsFdoInsertCommand (FdoIConnection           *conn,
                                               const GWSQualifiedName   &classname);
    GWS_QUERYENGINE_API
    virtual              ~CGwsFdoInsertCommand ();

    GWS_QUERYENGINE_API
    virtual CGwsFdoCommand::EFdoCommandType    Type () const
    {
        return CGwsFdoCommand::eInsert;
    }
    GWS_QUERYENGINE_API
    virtual EGwsStatus   Init           (const wchar_t* pFDOCommandClass = NULL);

    GWS_QUERYENGINE_API
    virtual EGwsStatus   Execute        (CGwsMutableFeature &  feature);

protected:
    virtual FdoPropertyValueCollection * GetPropertyValues ();
    virtual void         PrepareInternal();
    virtual void         SetFilterInternal (FdoFilter * filter)
    {
        filter; // For "unreferenced formal parameter" warning
    };
};


//////////////////////////////////////////////////////////////////////////////////////////
//
// update command
//
//////////////////////////////////////////////////////////////////////////////////////////
class CGwsFdoUpdateCommand : public CGwsFdoCommand
{
public:
    GWS_QUERYENGINE_API    CGwsFdoUpdateCommand (FdoIConnection          *session,
                                                 const GWSQualifiedName  &classname);
    GWS_QUERYENGINE_API
    virtual                 ~CGwsFdoUpdateCommand ();

    GWS_QUERYENGINE_API
    virtual CGwsFdoCommand::EFdoCommandType     Type () const
    {
        return CGwsFdoCommand::eUpdate;
    }
    GWS_QUERYENGINE_API
    virtual EGwsStatus      Init           (const wchar_t* pFDOCommandClass = NULL);

    GWS_QUERYENGINE_API
    virtual EGwsStatus      Execute        (CGwsMutableFeature & feature);

protected:
    virtual FdoPropertyValueCollection *  GetPropertyValues ();
    virtual void            PrepareInternal();
    virtual void            SetFilterInternal (FdoFilter * filter);
};


//////////////////////////////////////////////////////////////////////////////////////////
//
// delete command
//
//////////////////////////////////////////////////////////////////////////////////////////
class CGwsFdoDeleteCommand : public CGwsFdoCommand
{
public:
    GWS_QUERYENGINE_API   CGwsFdoDeleteCommand (FdoIConnection          * conn,
                                                const GWSQualifiedName   &classname);
    GWS_QUERYENGINE_API
    virtual                ~CGwsFdoDeleteCommand ();

    GWS_QUERYENGINE_API
    virtual CGwsFdoCommand::EFdoCommandType Type () const
    {
        return CGwsFdoCommand::eDelete;
    }
    GWS_QUERYENGINE_API
    virtual EGwsStatus     Init           (const wchar_t* pFDOCommandClass = NULL);
    GWS_QUERYENGINE_API
    virtual EGwsStatus     Execute        (const GWSFeatureId & featid);

protected:
    virtual void           PrepareInternal();
    virtual void           SetFilterInternal (FdoFilter * filter);
};


//////////////////////////////////////////////////////////////////////////////////////////
//
// feature locking command base class
// (superclass for lock/unclock commands)
//
//////////////////////////////////////////////////////////////////////////////////////////
class CGwsFdoLockingCommand : public CGwsFdoCommand
{
public:
    GWS_QUERYENGINE_API     CGwsFdoLockingCommand (
                                                   FdoIConnection           * conn,
                                                   const GWSQualifiedName   &classname);
    GWS_QUERYENGINE_API
    virtual                 ~CGwsFdoLockingCommand ();

    GWS_QUERYENGINE_API
    virtual EGwsStatus      Execute        (CGwsMutableFeature &  feature);
    GWS_QUERYENGINE_API
    virtual EGwsStatus      Execute        (const GWSFeatureId & featid);
    GWS_QUERYENGINE_API
    virtual EGwsStatus      Execute        (const GwsFeaturesIdVector & featids, int lbound, int ubound);


    GWS_QUERYENGINE_API
    const std::set<GWSFeatureId>  & Processed () const
    {
        return m_processed;
    }

    GWS_QUERYENGINE_API
    const GwsFailedStatus  & Rejected () const
    {
        return m_rejected;
    }

protected:
    virtual void            PrepareInternal();
    virtual EGwsStatus      ExecuteFilter   (FdoFilter *pFilter) = 0;

protected:
    std::set<GWSFeatureId>  m_processed;
    GwsFailedStatus         m_rejected;
};


//////////////////////////////////////////////////////////////////////////////////////////
//
// lock feature command
//
//////////////////////////////////////////////////////////////////////////////////////////
class CGwsFdoLockCommand : public CGwsFdoLockingCommand
{
public:
    GWS_QUERYENGINE_API     CGwsFdoLockCommand (
                                                FdoIConnection           * conn,
                                                const GWSQualifiedName   & classname);
    GWS_QUERYENGINE_API
    virtual                 ~CGwsFdoLockCommand ();

    GWS_QUERYENGINE_API
    virtual CGwsFdoCommand::EFdoCommandType Type () const
    {
        return CGwsFdoCommand::eLock;
    }
    GWS_QUERYENGINE_API
    virtual EGwsStatus      Init           (const wchar_t* pFDOCommandClass = NULL);

protected:
    virtual void            PrepareInternal();
    virtual void            SetFilterInternal (FdoFilter * filter);
    virtual EGwsStatus      ExecuteFilter  (FdoFilter *pFilter);

protected:
    FdoLockType             m_lockType;
};


//////////////////////////////////////////////////////////////////////////////////////////
//
// unlock command
//
//////////////////////////////////////////////////////////////////////////////////////////
class CGwsFdoUnlockCommand : public CGwsFdoLockingCommand
{
public:
    GWS_QUERYENGINE_API          CGwsFdoUnlockCommand (
                                                       FdoIConnection          * conn,
                                                       const GWSQualifiedName   &classname);
    GWS_QUERYENGINE_API
    virtual                     ~CGwsFdoUnlockCommand ();

    virtual CGwsFdoCommand::EFdoCommandType Type() const {
        return CGwsFdoCommand::eUnlock;
    }

    GWS_QUERYENGINE_API
    virtual EGwsStatus Init (const wchar_t* pFDOCommandClass = NULL);

    GWS_QUERYENGINE_API
    virtual void       SetOwner (GisString * pOwner)
    {
        if (pOwner)
            m_owner = pOwner;
    }
    GWS_QUERYENGINE_API
    virtual GisString * Owner() const
    {
        return m_owner.c_str();
    }

protected:
    virtual void        SetFilterInternal (FdoFilter * filter);
    virtual EGwsStatus  ExecuteFilter (FdoFilter *pFilter);

protected:
    WSTR                m_owner;
};
