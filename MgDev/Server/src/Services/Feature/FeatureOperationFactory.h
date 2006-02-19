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

#ifndef MGFEATUREOPERATIONFACTORY_H
#define MGFEATUREOPERATIONFACTORY_H

///////////////////////////////////////////////////////////////////////////
//  The MgFeatureOperationFactory class is an object that allows one to get
//  an IOperation object that corresponds to given ID and version
//  parameters.  It currently is merely a wrapper object for one static
//  function.
//
//  TODO:  there could be several operation factories dependent on
//  id, version, and service, so this static function will have to
//  be replaced.
class MgFeatureOperationFactory
{
    ///////////////////////////////////////////////////////////////////////////
    /// Constructors/Destructor
    protected :
        MgFeatureOperationFactory();

    ///////////////////////////////////////////////////////////////////////////
    /// Methods
    public :
        static IMgOperationHandler* GetOperation(ACE_UINT32 operationId,
            ACE_UINT32 operationVersion);
};

#endif  //  MGFEATUREOPERATIONFACTORY_H
