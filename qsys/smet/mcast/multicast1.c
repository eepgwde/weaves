/* 

   multicast1.c

   The following program sends or receives multicast packets. If invoked
   with one argument, it sends a packet containing the current time to an
   arbitrarily chosen multicast group and UDP port. If invoked with no
   arguments, it receives and prints these packets. Start it as a sender on
   just one host and as a receiver on all the other hosts

*/

#include "config.h"

#include "mcast0.h"

#include <time.h>

#define EXAMPLE_PORT 6000
#define EXAMPLE_GROUP "224.1.1.1"

#define BUFSZ 60

int main(int argc, const char **argv)
{
  char buffer[BUFSZ] = "";

  mcast_setup(EXAMPLE_GROUP, EXAMPLE_PORT);
  printf("%s\n", mcast_report());

  if (argc > 1) {
    /* send */
    while (1) {
      time_t t = time(0);
      sprintf(buffer, "time is %-24.24s", ctime(&t));
      printf("sending: %d: %s\n", BUFSZ, buffer);
      mcast_send(buffer, BUFSZ);
      sleep(2);
    }
  } else {
    /* receive */
    struct sockaddr_in addr;
    while (1) {
      size_t nlen0 = BUFSZ;
      int chk = mcast_recv(&addr, buffer, &nlen0);
      if (chk < 0) {
        perror("recvfrom");     /* it should rebind */
        continue;
      }
      if (chk == 1) {
        sleep(2);
        continue;     /* wait a bit */
      }

      printf("%s: message = %d \"%s\"\n", inet_ntoa(addr.sin_addr), nlen0, buffer);
      // printf("%s: message = %d \"%s\"\n", "none", nlen0, buffer);
    }
  }
}

