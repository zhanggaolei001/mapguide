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

#ifndef MGSITEREPOSITORYMANAGER_H_
#define MGSITEREPOSITORYMANAGER_H_

#include "SystemRepositoryManager.h"
#include "SiteRepository.h"
#include "SiteResourceContentManager.h"

class MgResourceContentManager;

class MgSiteRepositoryManager : public MgSystemRepositoryManager
{
/// Constructors/Destructor

    public:

        explicit MgSiteRepositoryManager(MgSiteRepository& repository);
        virtual ~MgSiteRepositoryManager();

    private:

        // Unimplemented Constructors/Methods

        MgSiteRepositoryManager();
        MgSiteRepositoryManager(const MgSiteRepositoryManager&);
        MgSiteRepositoryManager& operator=(const MgSiteRepositoryManager&);

/// Methods

    public:

        // Repository Management APIs

        virtual void CreateRepository(MgResourceIdentifier* resource,
            MgByteReader* content, MgByteReader* header);

        // User Management APIs

        MgByteReader* EnumerateUsers(CREFSTRING group, CREFSTRING role,
            bool includePassword, bool includeGroups);
        void AddUser(CREFSTRING userId, CREFSTRING username,
            CREFSTRING password, CREFSTRING description);
        void DeleteUsers(MgStringCollection* users);
        void UpdateUser(CREFSTRING userId, CREFSTRING newUserId,
            CREFSTRING newUsername, CREFSTRING newPassword,
            CREFSTRING newDescription);
        void GrantGroupMembershipsToUsers(MgStringCollection* groups,
            MgStringCollection* users);
        void GrantRoleMembershipsToUsers(MgStringCollection* roles,
            MgStringCollection* users);
        void RevokeGroupMembershipsFromUsers(MgStringCollection* groups,
            MgStringCollection* users);
        void RevokeRoleMembershipsFromUsers(MgStringCollection* roles,
            MgStringCollection* users);

        // Group Management APIs

        MgByteReader* EnumerateGroups(CREFSTRING user, CREFSTRING role);
        void AddGroup(CREFSTRING group, CREFSTRING description);
        void DeleteGroups(MgStringCollection* groups);
        void UpdateGroup(CREFSTRING group, CREFSTRING newGroup,
            CREFSTRING newDescription);
        void GrantRoleMembershipsToGroups(MgStringCollection* roles,
            MgStringCollection* groups);
        void RevokeRoleMembershipsFromGroups(MgStringCollection* roles,
            MgStringCollection* groups);

        // Role Management APIs

        MgStringCollection* EnumerateRoles(CREFSTRING user, CREFSTRING group);

        // Helper Methods

        virtual MgResourceContentManager* GetResourceContentManager();

    private:

        void AddUser(MgResourceIdentifier& resource, CREFSTRING fullName,
            CREFSTRING password, CREFSTRING description);
        void AddRole(MgResourceIdentifier& resource, CREFSTRING description,
            const MgStringCollection& users, const MgStringCollection& groups);

/// Data Members

    private:

        MgSiteResourceContentManager* m_resourceContentMan;
};

/// Inline Methods

inline MgResourceContentManager* MgSiteRepositoryManager::GetResourceContentManager()
{
    return m_resourceContentMan;
}

#endif
