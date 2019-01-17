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

void mcast_report() {
  fprintf(stderr, "group: %s ; port: %d", group0, port0);
}

int mcast_socket(const short port0) {
  /* set up socket */
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

int mcast_send(const char *mesj) {
  addr.sin_addr.s_addr = inet_addr(group0);

  time_t t = time(0);
  sprintf(message, "time is %-24.24s", ctime(&t));

  cnt = sendto(sock, message, sizeof(message), 0,
               (struct sockaddr *) &addr, addrlen);
  if (cnt < 0) {
    perror("sendto");
    return(1);
  }
  return(0);
}

int mcast_bind() {
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
  return(0);
}

int mcast_recv(const char *mesj) {
  cnt = recvfrom(sock, message, sizeof(message), 0, 
                 (struct sockaddr *) &addr, &addrlen);
  if (cnt < 0) {
    if (errno == EWOULDBLOCK || errno == EAGAIN) return(1);

    return(-1);
  }
  fprintf(stderr, "%s: message = \"%s\"\n", inet_ntoa(addr.sin_addr), message);

  return(0);
}

/* #undef NDEBUG */

