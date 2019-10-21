/** \file date01.c
   \brief POSIX date functions for q/kdb using GNUlib

Provide some day of week, week of year and access to strftime.

\author Walter.Eaves@bigfoot.com

*/

#include "config.h"

#include "stdio.h"
#include "stdlib.h"

#include "strings.h" /* String utility functions */
#include "errno.h" /* Handle errors */

#include "strftime.h"

#include "kish0.h"

#include "time0.h"

/* #undef NDEBUG */

/** \addtogroup dttm0
    Date and time methods.
    @{
*/

/**
 * Display K date object as a strftime string.
 *
 * @return string formatted string.
 */
K q_strftime(K x, K opts) {
  struct tm tm1;

  if (x->t != 6) return tm0_err(TM0_ERR);

  int is_dst = 0;
  if (opts->t == -6) {
    is_dst = (int) opts->s;
  }

  int x0[TM0_N];
  for (int i=0; i < TM0_N; i++)
    x0[i] = 0;

  for (int i=0; i < x->n; i++)
    x0[i] = kI(x)[i];

  tm0_empty0(x0);
  double r0 = tm0_tm2utc0(x0, is_dst, &tm1);

  char date0[256];
  strftime(date0, sizeof(date0), "%x - %I:%M%p %V %u", &tm1);

  return kf(r0);
}

/** @} */
