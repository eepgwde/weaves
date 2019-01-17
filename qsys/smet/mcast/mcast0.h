#if !defined(MCAST0_H)
#define MCAST0_H

#include "config.h"

#include "stdlib.h"
#include "string.h"
#include "unistd.h"
#include "stdio.h"

#include "sys/types.h"

#include "k.h"

/* Check if using time.h */
#if defined(HAVE_TIME_H)
#include "time.h"
#else
#error "no time.h found"
#endif

/* Check if using time.h */
#if defined(HAVE_SYS_TIME_H)
#include "sys/time.h"
#else
#error "no sys/time.h found"
#endif


#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>

extern void mcast_setup(const char* group1, const short port1);
extern const char *mcast_report();
extern int mcast_send(const char *mesj, const size_t nlen);
extern int mcast_recv(struct sockaddr_in *addr, char *mesj, size_t *n);

#endif
