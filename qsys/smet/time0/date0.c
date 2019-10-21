/* \file date0.c
   \brief Some extra date functions.

Provide some day of the week and week number methods. A generic interface to strftime.

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

static char qbuffer[1024] = "";

