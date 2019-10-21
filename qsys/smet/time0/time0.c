/* \file egex0.c
   \brief Regular expression interface - utility regular expressions for q/kdb using GNUlib

Provide regular expression function for q/kdb.

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

int tm0_print(struct tm *now10) {
  return fprintf(stderr, "now1: %04d.%02d.%02dT%02d:%02d:%02d.%03d +%02d #%d\n",
		 1900 + now10->tm_year, 1 + now10->tm_mon, now10->tm_mday,
		 now10->tm_hour, now10->tm_min, now10->tm_sec, 0,
		 now10->tm_isdst, now10->tm_yday);
}

/* These are the offsets from the K representation of dates */
static int base0[7] = { -1900, -1, 0, 0, 0, 0, 0 };

/* This adjusts the K dates to internal values. */
int* tm0_empty0(int *p) {
  int i;
  int *p0 = p;

  for (i=0; i<TM0_N; i++, p++)
    *p = *p + base0[i];
  return p0;
}

/**
 * Given an array of integers specifying a date-time return a UTC.
 *
 * 
 */
double tm0_tm2utc(int *x, int is_dst) {
  return tm0_tm2utc0(x, is_dst, NULL);
}

/**
 * Given an array of integers specifying a date-time return a UTC and complete the time structure.
 *
 * 
 */
double tm0_tm2utc0(int *x, int is_dst, struct tm *tm1) {
  struct tm tm0;

  tm0.tm_year = x[0];
  tm0.tm_mon = x[1]; 
  tm0.tm_mday = x[2];
  tm0.tm_hour = x[3];
  tm0.tm_min = x[4];
  tm0.tm_sec = x[5];

  tm0.tm_wday = -1;
  tm0.tm_yday = -1;
  tm0.tm_isdst = is_dst;

  time_t time0 = mktime(&tm0);
  if (tm1 != NULL) {
    *tm1 = tm0;
  }

  double tv1 = (double) time0;
  double tv10 = (double) x[6] / (double) 1000.0;
  double tv2 = tv1 + tv10;

  return tv2;
}
