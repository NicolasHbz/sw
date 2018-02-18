#include <czmq.h>

int app(char *argv[])
{
  printf("Connecting to echo...\n");
  zsock_t *req = zsock_new(ZMQ_REQ);
  zsock_connect(req, "tcp://localhost:%s", argv[2]);

  int request_nbr;
  for (request_nbr = 0; request_nbr != 10; request_nbr++) {
    zstr_sendf(req, "Hello world !");

    char *message = zstr_recv(req);
    printf("Received : %s\n", message);
    zstr_free(&message);
  }
  zsock_destroy(&req);
  return 0;
}