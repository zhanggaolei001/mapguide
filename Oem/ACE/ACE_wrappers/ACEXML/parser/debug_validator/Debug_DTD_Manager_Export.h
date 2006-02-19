
// -*- C++ -*-
// Debug_DTD_Manager_Export.h,v 1.2 2002/01/24 21:00:01 nanbor Exp
// Definition for Win32 Export directives.
// This file is generated automatically by generate_export_file.pl -s ACEXML_DEBUG_DTD_MANAGER
// ------------------------------
#ifndef ACEXML_DEBUG_DTD_MANAGER_EXPORT_H
#define ACEXML_DEBUG_DTD_MANAGER_EXPORT_H

#include "ace/config-all.h"

#if defined (ACE_AS_STATIC_LIBS) && !defined (ACEXML_DEBUG_DTD_MANAGER_HAS_DLL)
#  define ACEXML_DEBUG_DTD_MANAGER_HAS_DLL 0
#endif /* ACE_AS_STATIC_LIBS && ACEXML_DEBUG_DTD_MANAGER_HAS_DLL */

#if !defined (ACEXML_DEBUG_DTD_MANAGER_HAS_DLL)
#  define ACEXML_DEBUG_DTD_MANAGER_HAS_DLL 1
#endif /* ! ACEXML_DEBUG_DTD_MANAGER_HAS_DLL */

#if defined (ACEXML_DEBUG_DTD_MANAGER_HAS_DLL) && (ACEXML_DEBUG_DTD_MANAGER_HAS_DLL == 1)
#  if defined (ACEXML_DEBUG_DTD_MANAGER_BUILD_DLL)
#    define ACEXML_DEBUG_DTD_MANAGER_Export ACE_Proper_Export_Flag
#    define ACEXML_DEBUG_DTD_MANAGER_SINGLETON_DECLARATION(T) ACE_EXPORT_SINGLETON_DECLARATION (T)
#    define ACEXML_DEBUG_DTD_MANAGER_SINGLETON_DECLARE(SINGLETON_TYPE, CLASS, LOCK) ACE_EXPORT_SINGLETON_DECLARE(SINGLETON_TYPE, CLASS, LOCK)
#  else /* ACEXML_DEBUG_DTD_MANAGER_BUILD_DLL */
#    define ACEXML_DEBUG_DTD_MANAGER_Export ACE_Proper_Import_Flag
#    define ACEXML_DEBUG_DTD_MANAGER_SINGLETON_DECLARATION(T) ACE_IMPORT_SINGLETON_DECLARATION (T)
#    define ACEXML_DEBUG_DTD_MANAGER_SINGLETON_DECLARE(SINGLETON_TYPE, CLASS, LOCK) ACE_IMPORT_SINGLETON_DECLARE(SINGLETON_TYPE, CLASS, LOCK)
#  endif /* ACEXML_DEBUG_DTD_MANAGER_BUILD_DLL */
#else /* ACEXML_DEBUG_DTD_MANAGER_HAS_DLL == 1 */
#  define ACEXML_DEBUG_DTD_MANAGER_Export
#  define ACEXML_DEBUG_DTD_MANAGER_SINGLETON_DECLARATION(T)
#  define ACEXML_DEBUG_DTD_MANAGER_SINGLETON_DECLARE(SINGLETON_TYPE, CLASS, LOCK)
#endif /* ACEXML_DEBUG_DTD_MANAGER_HAS_DLL == 1 */

#endif /* ACEXML_DEBUG_DTD_MANAGER_EXPORT_H */

// End of auto generated file.
