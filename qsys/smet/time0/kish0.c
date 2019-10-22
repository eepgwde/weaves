/* \file kish0.c
   \brief K interfaces

Provide conversion to and from K 

\author Walter.Eaves@bigfoot.com

*/

#include "config.h"

#include "stdio.h"
#include "stdlib.h"

#include "string.h"

#include "errno.h" /* Handle errors */

#include "kish0.h"

static K tm0_err_;

/* Error number shared by modules */
/* errors: 0 none, 1 something else. Not used! */
static int tm0_errno = -1;

K tm0_err(int err_) {
  tm0_errno = err_;
  tm0_init();
  return tm0_err_;
}

/** Initialize and error marker
 *
 * This has a terrifying bug. I can't use static int flag0 = 0.
 */
void tm0_init(void) {
  static int flag0 = -1;

  if (flag0 == -1) {
    flag0 = 0;
    tm0_err_ = ks("time0error");
    /* Not sure if this is needed.
      tm0_err_ = r1(tm0_err_); */
  }
}

/* Copy a char array to a string. A problem with zero-length strings. */
char *kstrdup(K k1) {
  int tsz=0;
  if (k1->t != 10) return 0;
  tsz = k1->n ? k1->n : 1; 
  char * r = strndup((const char *)kC(k1), (size_t) tsz);
  return r;
}

