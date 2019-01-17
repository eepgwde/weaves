/* \file egex0.c
   \brief Regular expression interface - utility regular expressions for q/kdb using GNUlib

Provide regular expression function for q/kdb.

\author Walter.Eaves@bigfoot.com

*/

#include <config.h>

#include "error.h"

#include "mcast0.h"

#include <ctype.h>
#include <fcntl.h>
#include <errno.h>

static struct sockaddr_in addr;
static int addrlen, sock, cnt;
static struct ip_mreq mreq;
static char message[50];

static char group0[50] = "224.1.1.1";
static short port0 = 6000;

void mcast_setup(const char* group1, const short port1) {
  if (port1) port0 = port1;
  if (group1) strcpy(group0, group1);
}

static char report0[60] = "";

const char * mcast_report() {
  sprintf(report0, "group: %s ; port: %d", group0, port0);
  return(report0);
}

int mcast_socket() {
  /* set up socket */
  addrlen = 0;
  sock = socket(AF_INET, SOCK_DGRAM, 0);
  if (sock < 0) {
    perror("socket");
    return(1);
  }
  fcntl(sock, F_SETFL, O_NONBLOCK);

  memset((char *)&addr, 0, sizeof(addr));
  addr.sin_family = AF_INET;
  addr.sin_addr.s_addr = htonl(INADDR_ANY);
  addr.sin_port = htons(port0);
  addrlen = sizeof(addr);

  return(0);
}

int mcast_send(const char *mesj, const size_t nlen) {
  if (addrlen == 0 && mcast_socket() > 0) return(1);

  addr.sin_addr.s_addr = inet_addr(group0);

  cnt = sendto(sock, mesj, nlen, 0,
               (struct sockaddr *) &addr, addrlen);
  if (cnt < 0) {
    perror("sendto");
    addrlen = 0;                /* try a reset */
    return(1);
  }
  return(0);
}

static short bound = 0;

static int mcast_bind() {
  if (bound > 0) return(0);
  if (addrlen == 0 && mcast_socket() > 0) return(1);

  /* receive */
  if (bind(sock, (struct sockaddr *) &addr, sizeof(addr)) < 0) {        
    perror("bind");
    return(1);
  }
  
  mreq.imr_multiaddr.s_addr = inet_addr(group0);         
  mreq.imr_interface.s_addr = htonl(INADDR_ANY);         
  if (setsockopt(sock, IPPROTO_IP, IP_ADD_MEMBERSHIP,
                 &mreq, sizeof(mreq)) < 0) {
    perror("setsockopt mreq");
    return(1);
  }
  bound = 1;
  return(0);
}

int mcast_recv(struct sockaddr_in *addr0, char *mesj, size_t *n) {
  mcast_bind();

  socklen_t nlen = sizeof(struct sockaddr_in);
  cnt = recvfrom(sock, mesj, *n, 0, (struct sockaddr *) addr0, &nlen);
  if (cnt < 0) {
    if (errno == EWOULDBLOCK || errno == EAGAIN) return(1);
    bound = 0;                  /* force a re-bind */
    return(-1);
  }
  *n = cnt;

  return(0);
}

/* #undef NDEBUG */

