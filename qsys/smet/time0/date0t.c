/* \file egext.c
   \brief Regular expression interface - utility regular expressions for q/kdb using GNUlib

Test program.

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
  char MY_TIME[Size]; 
  time( &t ); 
      
  //localtime() uses the time pointed by t , 
  // to fill a tm structure with the  
  // values that represent the  
  // corresponding local time. 
      
  tmp = localtime( &t ); 
      
  // using strftime to display time 
  strftime(MY_TIME, sizeof(MY_TIME), "%x - %I:%M%p", tmp); 
      
  printf("Formatted date & time : %s\n", MY_TIME ); 
  return(0); 
}
