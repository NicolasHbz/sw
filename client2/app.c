#include <czmq.h>
#include <unistd.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <pthread.h>
#include <time.h>
#include <getopt.h>

typedef struct {
    char    *pub_port;
    char    *rep_port;
}           Arguments;

void app(Arguments *args)
{
  printf("Connecting to echo...\n");
  zsock_t *req = zsock_new(ZMQ_REQ);
  zsock_connect(req, "tcp://localhost:%s", args->rep_port);
    printf("%s", args->rep_port);

  int request_nbr;
  // for (request_nbr = 0; request_nbr != 10; request_nbr++) {
    zstr_sendf(req, "Identify|Player2");

    char *message = zstr_recv(req);
    printf("Received : %s\n", message);
    zstr_free(&message);
  // }
  zsock_destroy(&req);
}