/* \file date0.c
   \brief Some extra date functions.

Provide some day of the week and week number methods. A generic interface to strftime.

\author Walter.Eaves@bigfoot.com

*/

#include "config.h"

#include "stdio.h"
#include "stdlib.h"
#include "ctype.h"

#include "kish0.h"

#include "error.h"

#include "time0.h"

/* #undef NDEBUG */

static char qbuffer[1024] = "";

static struct tm tm1;

struct tm const * dt0_to(const int *dt0) {
  int y, dt1, m, d;

  y = (int) ((*dt0) / 10000) ;
  dt1 = (*dt0) - 10000 * y;
  m = (int) dt1 / 100 ;
  dt1 = dt1 - 100 * m;
  d = (int) dt1;

  /* notice you don't have to put in weekday or year day */
  tm1.tm_year = y - 1900;
  tm1.tm_mon = m - 1;    /* month */
  tm1.tm_mday = d;       /* day of month */
  tm1.tm_hour = 0;
  tm1.tm_min = 0;
  tm1.tm_sec = 1;
  tm1.tm_isdst = -1;

  return &tm1;
}

