/** \file time01.c
   \brief POSIX time functions for q/kdb using GNUlib

Provide some UTC support for q/kdb.

\author Walter.Eaves@bigfoot.com

*/

#include <config.h>

#include <stdio.h>
#include <stdlib.h>

#include <string.h>

#include <strings.h> /* String utility functions */
#include <errno.h> /* Handle errors */
#include <memory.h> /* Handle errors */

#include "mcast0.h"

/* Check if using time.h */
#if defined(HAVE_TIME_H)
#include "time.h"
#else
#error "no time.h found"
#endif

/* Check if using time.h */
#if defined(HAVE_SYS_TIME_H)
#include "sys/time.h"
#else
#error "no sys/time.h found"
#endif


/* #undef NDEBUG */

/** \addtogroup mcast
   Multicast alert
   @{
*/

K q_umcast0(K x) {
  time_t now1;
  time(&now1);
  unsigned int t2 = *((unsigned int *)&now1);

  return kj(t2);
}

/*
  @}
*/
