// OS_TLI.cpp,v 4.1 2000/06/07 03:07:29 coryan Exp

#include "ace/OS_TLI.h"

ACE_RCSID(ace, OS_TLI, "OS_TLI.cpp,v 4.1 2000/06/07 03:07:29 coryan Exp")

#if !defined (ACE_HAS_INLINED_OSCALLS)
# include "ace/OS_TLI.inl"
#else /* !ACE_HAS_INLINED_OSCALLS */
#if defined (__hpux) && !defined (__GNUG__)
static int shut_up_aCC = 0;
#endif /* HPUX && !g++ */
#endif /* !ACE_HAS_INLINED_OS_CALLS */
