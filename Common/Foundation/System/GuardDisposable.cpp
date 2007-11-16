//
//  Copyright (C) 2004-2007 by Autodesk, Inc.
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

#include "Foundation.h"


//////////////////////////////////////////////////////////////
INT32 MgGuardDisposable::GetRefCount()
{
    ACE_MT(ACE_GUARD_RETURN(ACE_Recursive_Thread_Mutex, ace_mon, m_mutex, -1));

    return m_refCount;
}


//////////////////////////////////////////////////////////////
INT32 MgGuardDisposable::AddRef()
{
    ACE_MT(ACE_GUARD_RETURN(ACE_Recursive_Thread_Mutex, ace_mon, m_mutex, -1));

    m_refCountFlag = true;

    if (0 == m_refCount)
    {
#ifdef _DEBUG
        ACE_DEBUG((LM_DEBUG, ACE_TEXT("(%t) ************ Error in MgGuardDisposable::Addref(). Class Name: %W. Called with Reference Count = 0.\n"), GetClassName().c_str()));
#endif

        throw new MgLogicException(L"MgGuardDisposable.AddRef", __LINE__, __WFILE__, NULL, L"", NULL);
    }

    return ++m_refCount;
}


//////////////////////////////////////////////////////////////
INT32 MgGuardDisposable::Release()
{
    {
        ACE_MT(ACE_GUARD_RETURN(ACE_Recursive_Thread_Mutex, ace_mon, m_mutex, -1));
        m_refCountFlag = true;

        if (0 == m_refCount)
        {
#ifdef _DEBUG
            ACE_DEBUG((LM_DEBUG, ACE_TEXT("(%t) ************ Error in MgGuardDisposable::Release(). Class Name: %W. Called with Reference Count = 0.\n"), GetClassName().c_str()));
#endif

            throw new MgLogicException(L"MgGuardDisposable.Release", __LINE__, __WFILE__, NULL, L"", NULL);
        }

        --m_refCount;
    }

    if (0 != m_refCount)
    {
        return m_refCount;
    }
    else
    {
        Dispose();
        return 0;
    }
}


//////////////////////////////////////////////////////////////
MgGuardDisposable::MgGuardDisposable()
{
}


//////////////////////////////////////////////////////////////
MgGuardDisposable::~MgGuardDisposable()
{
}
