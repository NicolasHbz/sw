#include "server.h"

// static const Command    orders_command[] =
// {
//     {"test|", test},
//     {NULL, NULL}
// };

int app(Arguments *args)
{
  zsock_t *router = zsock_new(ZMQ_ROUTER);
  zsock_bind(router, "tcp://*:%s", args->rep_port);

  while (!zsys_interrupted) {
    zmsg_t *message = zmsg_recv(router);

    zframe_t *identity = zmsg_pop(message);
    zframe_t *empty = zmsg_pop(message);
    zframe_t *content = zmsg_pop(message);

    char *cpy = get_command(content);

    zframe_t *caca = zframe_from (cpy);

    zmsg_destroy(&message);
    printf("Your identity  is : %s\n", cpy);
    sleep(1);

    zmsg_t *response = zmsg_new();

    zmsg_prepend(response, &identity);
    zmsg_append(response, &empty);
    zmsg_append(response, &caca);

    zmsg_send(&response, router);
    zmsg_destroy(&response);

    zframe_destroy(&identity);
    zframe_destroy(&empty);
    zframe_destroy(&content);
  }
  zsock_destroy(&router);
  return 0;
}