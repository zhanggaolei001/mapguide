// -*- C++ -*-

//=============================================================================
/**
 *  @file    os_float.h
 *
 *  floating types
 *
 *  os_float.h,v 1.2 2003/07/19 19:04:15 dhinton Exp
 *
 *  @author Don Hinton <dhinton@dresystems.com>
 *  @author This code was originally in various places including ace/OS.h.
 */
//=============================================================================

#ifndef ACE_OS_INCLUDE_OS_FLOAT_H
#define ACE_OS_INCLUDE_OS_FLOAT_H

#include /**/ "ace/pre.h"

#include "ace/config-all.h"

#if !defined (ACE_LACKS_PRAGMA_ONCE)
# pragma once
#endif /* ACE_LACKS_PRAGMA_ONCE */

#if !defined (ACE_LACKS_FLOAT_H)
# include /**/ <float.h>
#endif /* !ACE_LACKS_FLOAT_H */

// Place all additions (especially function declarations) within extern "C" {}
#ifdef __cplusplus
extern "C"
{
#endif /* __cplusplus */

#ifdef __cplusplus
}
#endif /* __cplusplus */

#include /**/ "ace/post.h"
#endif /* ACE_OS_INCLUDE_OS_FLOAT_H */
