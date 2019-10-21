#if !defined(EGEX0_H)
#define EGEX0_H

#include "config.h"

/* Check if using a POSIX regex. */
#if defined(HAVE_REGMATCH_T_RM_SP)
#include "/usr/include/regex.h" 
#else
#include "regex.h"
#endif

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

extern int tm0_print(struct tm *);

/* This takes a 7 integer array, first is a year, last is milliseconds */
#define TM0_N 7
extern double tm0_tm2utc(int *x, int is_dst);
extern double tm0_tm2utc0(int *x, int is_dst, struct tm *);
extern int* tm0_empty0(int *x);

extern struct tm const * dt0_to(const int *);
extern int dt0_part(const int);

#endif
