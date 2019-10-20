/* \file egext.c
   \brief Regular expression interface - utility regular expressions for q/kdb using GNUlib

Test program.

\author Walter.Eaves@bigfoot.com

*/

#include "config.h"

#include "stdlib.h"
#include "stdio.h"
#include "string.h"
#include "crc.h"

#include <string.h>

int main(int argc, char **argv) {
  int i;
  uint32_t r;

  const char str[] = "walter";
  const char str0[] = "eaves";

  printf("crcs %d\n", strlen(str));

  r = crc32(str, strlen(str));
  printf("crcs %d\n", r);

  r = crc32_update(r, str, strlen(str));
  printf("crcs %d\n", r);

  return 0;
}
