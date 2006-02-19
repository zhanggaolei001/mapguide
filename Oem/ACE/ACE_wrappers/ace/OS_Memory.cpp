// OS_Memory.cpp,v 4.4 2003/11/01 11:15:14 dhinton Exp

#include "ace/OS_Memory.h"

ACE_RCSID(ace, OS_Memory, "OS_Memory.cpp,v 4.4 2003/11/01 11:15:14 dhinton Exp")

#if !defined (ACE_HAS_INLINED_OSCALLS)
# include "ace/OS_Memory.inl"
#else /* !ACE_HAS_INLINED_OSCALLS */
#if defined (__hpux) && !defined (__GNUG__)
static int shut_up_aCC = 0;
#endif /* HPUX && !g++ */
#endif /* !ACE_HAS_INLINED_OS_CALLS */

#include "ace/os_include/os_stdlib.h"

