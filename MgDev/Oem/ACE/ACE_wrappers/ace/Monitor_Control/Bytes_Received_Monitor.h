// -*- C++ -*-

//=============================================================================
/**
 * @file Bytes_Received_Monitor.h
 *
 * $Id: Bytes_Received_Monitor.h 82115 2008-06-20 20:43:13Z parsons $
 *
 * @author Jeff Parsons <j.parsons@vanderbilt.edu>
 */
//=============================================================================

#ifndef BYTES_RECEIVED_MONITOR_H
#define BYTES_RECEIVED_MONITOR_H

#include /**/ "ace/pre.h"

#include "ace/Monitor_Base.h"

#if !defined (ACE_LACKS_PRAGMA_ONCE)
#pragma once
#endif /* ACE_LACKS_PRAGMA_ONCE */

#if defined (ACE_HAS_MONITOR_FRAMEWORK) && (ACE_HAS_MONITOR_FRAMEWORK == 1)

#if defined (ACE_HAS_PDH_H) && !defined (ACE_LACKS_PDH_H)
#include "ace/Monitor_Control/Windows_Multi_Instance_Monitor.h"
#elif defined (linux) || defined (AIX)
#include "ace/Monitor_Control/Linux_Network_Interface_Monitor.h"
#elif defined (ACE_HAS_KSTAT)
#include "ace/Monitor_Control/Solaris_Network_Interface_Monitor.h"
#elif defined (__FreeBSD__) || defined (__NetBSD__) || defined (__OpenBSD__) 
#include "ace/Monitor_Control/BSD_Network_Interface_Monitor.h"
#else
#include "ace/Monitor_Control/Null_Network_Interface_Monitor.h"
#endif

#include "ace/Monitor_Control/Monitor_Control_export.h"

ACE_BEGIN_VERSIONED_NAMESPACE_DECL

namespace ACE
{
  namespace Monitor_Control
  {
    /**
     * @class Bytes_Received_Monitor
     *
     * @brief Monitors total bytes received over all network interfaces.
     */
    class MONITOR_CONTROL_Export Bytes_Received_Monitor
      : public Monitor_Base
#if defined (ACE_HAS_WIN32_PDH)
      , public Windows_Multi_Instance_Monitor
#elif defined (linux) || defined (AIX)
      , public Linux_Network_Interface_Monitor
#elif defined (ACE_HAS_KSTAT)
      , public Solaris_Network_Interface_Monitor
#elif defined (__FreeBSD__) || defined (__NetBSD__) || defined (__OpenBSD__)
      , public BSD_Network_Interface_Monitor
#else
      , public Null_Network_Interface_Monitor
#endif
    {
    public:
      Bytes_Received_Monitor (const char* name);

      /// Implementation of the pure virtual method.
      virtual void update (void);

      /// Stores the default name, used if none is supplied by the user.
      static const char* default_name (void);
      
    private:
      /// Overridden reset, calls platform-specific reset.
      virtual void clear_i (void);

    private:
      static const char* default_name_;
    };
  }
}

ACE_END_VERSIONED_NAMESPACE_DECL

#endif /* ACE_HAS_MONITOR_FRAMEWORK==1 */

#include /**/ "ace/post.h"

#endif // BYTES_RECEIVED_MONITOR_H
