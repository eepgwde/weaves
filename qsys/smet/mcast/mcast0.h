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

#endif
