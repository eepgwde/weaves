/** \file date01.c
   \brief POSIX date functions for q/kdb using GNUlib

Provide some day of week, week of year and access to strftime.

There are some problems with initialization. See q_init0()

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

static int q_init0_ = -1;
static volatile J v = 0;

/** Static buffers are pointers to something in the data segment.
 * and can't return sizeof.
 */

#define NQBUFFER 256
static char qbuffer[NQBUFFER] = "";
#define NQFMT 10
static char qfmt[NQFMT] = "";

/** Module initialization.
 *
 * The statics weren't being initialized.
 * But then I realized the buffers were not returning the right sizeof.
 * I believe this is corrected now.
 */
K q_init0(K x){
  fprintf(stderr, "%d %d\n", q_init0_, v);
  q_init0_ = -1;
  v = 0;
  tm0_init();

  return ks("time0init");
}

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

  strncpy(qfmt, "", NQFMT);     /* use the buffer size, it should sizeof to char. */
  fmt0 = kstrcpy(fmt);

  int x0[TM0_N];
  for (int i=0; i < TM0_N; i++)
    x0[i] = 0;

  for (int i=0; i < x->n; i++)
    x0[i] = kI(x)[i];

  tm0_empty0(x0);
  double r0 = tm0_tm2utc0(x0, is_dst, &tm1);

  strncpy(qbuffer, "", NQBUFFER);
  size_t n = strftime(qbuffer, NQBUFFER, fmt0, &tm1);

  return kp(qbuffer);
}

/** Thread-safe sequence.
 *
 * An example who to use a vector fill.
 * Bit cryptic!
 */
K q_seq(K x){
  K y;J j=1;
  P(xt!=101&&xt!=-7,krr("type")) /* there error return */
  j=__sync_fetch_and_add(&v,xt==-7?xj:j); /* thread-safe method */
  P(xt==101,kj(j))                        /* 101 is a unary primitive, I've never seen this, must be f[] */
  y=ktn(KJ,xj);DO(xj,kJ(y)[i]=j++)        /* make a vector and copy into it */
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

    r0=ktn(KI,xi);              /* make the vector, implicitly uses the parameter K x and sizes it to that */

    // Re-use this buffer for workspace

    // Their cryptic example is this, I re-work this as for-loops and write it in their style.
    /*

    DO(xi,kI(r0)[i]=*(pdts+i))

    Their DO doesn't need a semi-colon, but I put one in, because it help emacs format.

    My loops

    for (int i=0; i<xn; i++) {
      kI(r0)[i] = dj(*(dts+i));
    }

    for (int i=0; i<xn; i++) {
      (void )dt0_to(kI(r0)+i);
      kI(r0)[i] = dt0_part(xpart);
    }
    */

    DO(xi,kI(r0)[i]=dj(*(dts+i))) ;
    DO(xi,(void )dt0_to(kI(r0)+i); kI(r0)[i]=dt0_part(xpart)) ;
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
      strftime(qbuffer, NQBUFFER, fmts[idx], &time_str);
      r0 = ki(atoi(qbuffer));
    }
  }

  return r0;
}

/** @} */
