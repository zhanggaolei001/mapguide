//
//  Copyright (C) 2003-2010 by Autodesk, Inc.
//
//  By using this code, you are agreeing to the terms and conditions of
//  the License Agreement included in the documentation for this code.
//
//  AUTODESK MAKES NO WARRANTIES, EXPRESS OR IMPLIED,
//  AS TO THE CORRECTNESS OF THIS CODE OR ANY DERIVATIVE
//  WORKS WHICH INCORPORATE IT.
//
//  AUTODESK PROVIDES THE CODE ON AN "AS-IS" BASIS
//  AND EXPLICITLY DISCLAIMS ANY LIABILITY, INCLUDING
//  CONSEQUENTIAL AND INCIDENTAL DAMAGES FOR ERRORS,
//  OMISSIONS, AND OTHER PROBLEMS IN THE CODE.
//
//  Use, duplication, or disclosure by the U.S. Government is subject to
//  restrictions set forth in FAR 52.227-19 (Commercial Computer Software
//  Restricted Rights) and DFAR 252.227-7013(c)(1)(ii) (Rights in Technical
//  Data and Computer Software), as applicable.
//

#ifndef _DWFCORE_STL_H
#define _DWFCORE_STL_H

#include "dwfcore/Core.h"

///
///\file        dwfcore/STL.h
///\brief       This file includes all STL headers required by the library.
///

///
///\page        notes       Notes
///\section     stl         STL Header Files
///             \e xtree based collections generate unreachable code warnings when compiled
///             with Microsoft Visual Studio Compilers in non-Debug build configurations with
///             warning level 4 enabled.  STL.h includes all header files required by the
///             core library and temporarily disables the MSVC \b C4702: \b unreachable \b code warning.
///             It should be included instead of individal STL headers if your build configuration
///             requires a high level of warning notification.
///             

#ifdef  _DWFCORE_WIN32_SYSTEM
#pragma warning(push)
#pragma warning(disable: 4702)
#endif

#include <map>
#include <list>
#include <queue>
#include <vector>
using namespace std;

#ifdef  _DWFCORE_WIN32_SYSTEM
#pragma warning(pop)
#endif


#endif
