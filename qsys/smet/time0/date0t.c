/* \file date0t.c
   \brief Extra date functions: day of week and week of year

Test program to check linkage. The format strings for strftime can be checked with Python.

\author Walter.Eaves@bigfoot.com

*/

#include "config.h"

#include "stdlib.h"
#include "stdio.h"

#include "strftime.h"

#include "time0.h"

int main(int argc, char **argv) {
  time_t t ; 
  struct tm *tmp ; 
  char date0[256]; 
  time( &t ); 
      
  //localtime() uses the time pointed by t , 
  // to fill a tm structure with the  
  // values that represent the  
  // corresponding local time. 
      
  tmp = localtime( &t ); 
      
  // using strftime to display time 
  strftime(date0, sizeof(date0), "%x - %I:%M%p %V %u", tmp); 
      
  printf("Formatted date & time : %s\n", date0 ); 
  return(0); 
}
