/** \file date01.c
   \brief POSIX date functions for q/kdb using GNUlib

Provide some day of week, week of year and access to strftime.

\author Walter.Eaves@bigfoot.com

*/

#include <inttypes.h>

#include "config.h"

#include "stdio.h"
#include "stdlib.h"

#include "strings.h" /* String utility functions */
#include "errno.h" /* Handle errors */

#include "strftime.h"

#include "kish0.h"

#include "time0.h"

/* #undef NDEBUG */

static char qbuffer[1000] = "";
static char qfmt[50] = "";

static char *kstrcpy(K k1) {
  int tsz=0;
  if (k1->t != 10) return 0;
  tsz = k1->n ? k1->n : 1; 
  char * r = strncpy(qfmt, (const char *)kC(k1), (size_t) tsz);
  return r;
}

/** \addtogroup dttm0
    Date and time methods.
    @{
*/

/**
 * Display K date object as a strftime string.
 *
 * Annoyingly, I have to use kstrcpy.
 *
 * @return string formatted string.
 */
K q_strftime(K x, K opts, K fmt) {
  struct tm tm1;
  char *fmt0;

  if (x->t != 6) return tm0_err(TM0_ERR);

  int is_dst = 0;
  if (opts->t == -6) {
    is_dst = (int) opts->i;
  }

  strncpy(qfmt, "", sizeof(qfmt));
  fmt0 = kstrcpy(fmt);

  int x0[TM0_N];
  for (int i=0; i < TM0_N; i++)
    x0[i] = 0;

  for (int i=0; i < x->n; i++)
    x0[i] = kI(x)[i];

  tm0_empty0(x0);
  double r0 = tm0_tm2utc0(x0, is_dst, &tm1);

  strncpy(qbuffer, "", sizeof(qbuffer));
  size_t n = strftime(qbuffer, sizeof(qbuffer), fmt0, &tm1);

  return kp(qbuffer);
}

static volatile J v;

K q_seq(K x){
  K y;J j=1;
  P(xt!=101&&xt!=-7,krr("type"))
  j=__sync_fetch_and_add(&v,xt==-7?xj:j);
  P(xt==101,kj(j))
  y=ktn(KJ,xj);DO(xj,kJ(y)[i]=j++)
  R y;
}

#define NFMTS  3
static const char fmts[NFMTS][4] = { "%U", "%V", "%W" };

/**
 * Given a date object returns the extra parts: day-of-week and week-of-year (3 styles)
 *
 * @return string formatted string.
 */
K q_xparts(K x, K opts) {
  struct tm tm1;
  char *fmt0;
  int is_list = 0;
  I xpart = 0;
  struct tm time_str;
  K r0 = tm0_err(TM0_ERR);
  int idx;
  I *pdts;

  if (opts->t == -6 || opts->t == -7) {
    xpart = (int) opts->i;
  }

  if (x->t == 14) {
    I *dts = kI(x);
    pdts = (I *) malloc(x->n * sizeof(I));
    for (int i=0; i<x->n; i++) {
      *(pdts + i) = dj(*(dts+i));
    }
    for (int i=0; i<x->n; i++) {
      (void )dt0_to(pdts+i);
      *(pdts+i) = dt0_part(xpart);
      fprintf(stderr, "%d ", *(pdts+i));
    }
    fprintf(stderr, "\n");
    free(pdts);
    return r0;
  }

  if (x->t != -14) 
    return r0;

  // This is an atomic access
  I dt1 = x->i;
  I dt0 = dj(dt1);
  int y = (int) (dt0 / 10000) ;
  dt0 = dt0 - 10000 * y;
  int m = (int) dt0 / 100 ;
  dt0 = dt0 - 100 * m;
  int d = (int) dt0;

  /* notice you don't have to put in weekday or year day */
  time_str.tm_year = y - 1900;
  time_str.tm_mon = m - 1;    /* month */
  time_str.tm_mday = d;       /* day of month */
  time_str.tm_hour = 0;
  time_str.tm_min = 0;
  time_str.tm_sec = 1;
  time_str.tm_isdst = -1;

  if (mktime(&time_str) == -1)
    return r0;
  else {
    switch (xpart) {
    case 0:
      r0 = ki(time_str.tm_wday);
      break;
    case 1:
      r0 = ki(time_str.tm_yday);
      break;
    case 2:
      r0 = ki(time_str.tm_isdst);
      break;
    default:
      idx = xpart - 3;
      if (idx >= NFMTS) {
        return r0;
      }
      strncpy(qbuffer, "", sizeof(qbuffer));
      strftime(qbuffer, sizeof(qbuffer), fmts[idx], &time_str);
      r0 = ki(atoi(qbuffer));
    }
  }

  return r0;
}


/** @} */
