/** \file time01.c
   \brief POSIX time functions for q/kdb using GNUlib

Provide some UTC support for q/kdb.

\author Walter.Eaves@bigfoot.com

*/

#include <config.h>

#include <stdio.h>
#include <stdlib.h>

#include <string.h>

#include <strings.h> /* String utility functions */
#include <errno.h> /* Handle errors */
#include <memory.h> /* Handle errors */

#include "mcast0.h"

/* #undef NDEBUG */


/* Copy a char array to a string. A problem with zero-length strings */
static char *kstrdup(K k1) {
  int tsz=0;
  if (k1->t != 10) return 0;
  tsz = k1->n ? k1->n : 1; 
  char * r = strndup((const char *)kC(k1), (size_t) tsz);
  return r;
}

/** \addtogroup mcast
   Multicast alert
   @{
*/

K q_mc_report(K x) {
  K results;
  char *results1 = (char *)mcast_report();
  results = kpn(results1, strlen(results1));
  return results;
}

K q_mc_setup(K group1, K port1) {
  /* One string required */
  if (group1->t != 10) return kj(-1);

  if (port1->t != -5) return kj(-2);

  char *group2 = kstrdup(group1);

  mcast_setup(group2, port1->h);
  free(group2);

  return q_mc_report(kj(0));
}

K q_mc_send(K mesj) {
  if (mesj->t != 10) return kj(-1);

  return kj(mcast_send(kC(mesj), mesj->n));
}

#define BUFSZ 1024
static char buffer[BUFSZ] = "";

K q_mc_recv(K x) {
  struct sockaddr_in addr;

  size_t nlen0 = BUFSZ;
  int chk = mcast_recv(&addr, buffer, &nlen0);
  if (chk < 0) {
    perror("recvfrom");     /* it should rebind */
    return kj(-1);
  }
  if (chk == 1) {
    return kj(1);
  }

  K syms=ktn(KS,0);
  S sym;
  sym=ss("IBM");
  js(&syms, sym);
  sym=ss("GOOG");
  js(&syms, sym);

  // printf("%s: message = %d \"%s\"\n", inet_ntoa(addr.sin_addr), nlen0, buffer);
  
  return syms;
}

/*
  @}
*/
