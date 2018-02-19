#include "server.h"

void *send_notification_to_all_clients (Arguments *args)
{
  zsock_t *notification_socket = zsock_new(ZMQ_PUB);
  zsock_bind(notification_socket, "tcp://127.0.0.1:%s", args->pub_port);

  while (!zsys_interrupted) {
    char message[1024] = "test\n";
    zstr_sendf(notification_socket, "%s", message);
    sleep(2);   
  }
  zsock_destroy(&notification_socket);
  return NULL;
}