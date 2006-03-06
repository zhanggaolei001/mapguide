/* -*- c++ -*- */
// SS_State_DONE.h,v 1.1 2003/08/25 07:43:45 kobica Exp

#ifndef TERA_SS_STATE_DONE_H
#define TERA_SS_STATE_DONE_H

#include "ace/OS.h"
#include "ace/Singleton.h"

#include "jaws3/Protocol_Handler.h"

class TeraSS_State_DONE : public JAWS_Protocol_State
{
public:

  int service (JAWS_Event_Completer *, void *data);

  JAWS_Protocol_State * transition ( const JAWS_Event_Result &result
                                   , void *data
                                   , void *act
                                   );

  static JAWS_Protocol_State * instance (void)
  {
    return ACE_Singleton<TeraSS_State_DONE, ACE_SYNCH_MUTEX>::instance ();
  }

};

#endif /* TERA_SS_STATE_DONE_H */
