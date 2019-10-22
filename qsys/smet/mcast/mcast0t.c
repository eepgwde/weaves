/* \file mcast0t.c
   \brief Check out some casting issues with the time structures.

   This has to build under 32 bit and I'm checking the type sizes in use.

\author Walter.Eaves@bigfoot.com

*/

#include "config.h"

#include "stdlib.h"
#include "stdio.h"

#include "mcast0.h"

int main(int argc, char **argv) {

  {
    /* Check structure sizes */
    unsigned int now0;
    time_t now1;
    struct timeval tv0;

    fprintf(stderr, "sizeof: unsigned int %u time_t %u struct timeval %u\n", sizeof(now0),
	    sizeof(now1), sizeof(tv0));
  }

  /* from unsigned int, compare to time_t */
  unsigned int now0;
  time_t t0 = time((time_t *)&now0);
  
  time_t now1;
  time_t t1 = time(&now1);
  
  fprintf(stderr, "time_t now1 %u ; time_t t1 %u\n", now1, t1);

  struct tm now10;
  gmtime_r(&now1, &now10);

  /* And check the values returned against the struct tm structure call. */
  struct timeval tv0;

  int retval = gettimeofday(&tv0, NULL);
  fprintf(stderr, "retval %d\n", retval);
  fprintf(stderr, "tv0.tv_sec: %u; tv0.tv_usec: %u\n", tv0.tv_sec, tv0.tv_usec);

  struct tm now2;
  now2.tm_sec = 0;
  now2.tm_min = 0;
  now2.tm_hour = 0;
  now2.tm_mday = now10.tm_mday;
  now2.tm_mon = now10.tm_mon;
  now2.tm_year = now10.tm_year;
  /* now2.tm_wday = 0; */
  /* now2.tm_yday = 0; */
  now2.tm_isdst = 0;

  time_t now20 = mktime(&now2);

  fprintf(stderr, "now20: %d\n", now20);

  return 0;
}
