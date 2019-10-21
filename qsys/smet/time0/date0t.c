/* \file date0t.c
   \brief Extra date functions: day of week and week of year

Test program to check linkage. The format strings for strftime can be checked with Python.

\author Walter.Eaves@bigfoot.com

*/

#include "config.h"

#include "stdlib.h"
#include "stdio.h"
#include "string.h"

#include "strftime.h"

#include "time0.h"

int main(int argc, char **argv) {
  time_t t ; 
  struct tm *tmp ; 
  char date0[256];

  {
    struct tm time_str;
    char daybuf[20];

    /* notice you don't have to put in weekday or year day */
    time_str.tm_year = 2001 - 1900;
    time_str.tm_mon = 7 - 1;    /* month */
    time_str.tm_mday = 4;       /* day of month */
    time_str.tm_hour = 0;
    time_str.tm_min = 0;
    time_str.tm_sec = 1;
    time_str.tm_isdst = -1;
    if (mktime(&time_str) == -1)
      (void)puts("-unknown-");
    else {
      printf("tm_wday: %d ; tm_yday: %d\n", time_str.tm_wday, time_str.tm_yday);

      (void)strftime(daybuf, sizeof(daybuf), "%A", &time_str);
      (void)puts(daybuf);

      (void)strftime(daybuf, sizeof(daybuf), "%x - %I:%M%p", &time_str);
      (void)puts(daybuf);
    }
  }

  time( &t );
      
  //localtime() uses the time pointed by t , 
  // to fill a tm structure with the  
  // values that represent the  
  // corresponding local time. 
      
  tmp = localtime( &t ); 
      
  // using strftime to display time 
  strftime(date0, sizeof(date0), "%x - %I:%M%p %V %u", tmp);
  printf("Formatted date & time : %s\n", date0 ); 

  strcpy(date0, "6 Dec 2001 12:33:45");
  printf("processing: %s\n", date0);
  if (strptime(date0, "%d %b %Y %H:%M:%S", tmp) == NULL)
    /* Handle error */;

  printf("year: %d; month: %d; day: %d;\n",
         tmp->tm_year, tmp->tm_mon, tmp->tm_mday);
  printf("hour: %d; minute: %d; second: %d\n",
         tmp->tm_hour, tmp->tm_min, tmp->tm_sec);
  printf("week day: %d; year day: %d\n", tmp->tm_wday, tmp->tm_yday);

  tmp->tm_isdst = -1;      /* Not set by strptime(); tells mktime()
                            to determine whether daylight saving time
                            is in effect */
  t = mktime(tmp);
  if (t == -1)
    /* Handle error */;
  printf("seconds since the Epoch: %ld\n", (long) t);
      
  return(0); 
}
