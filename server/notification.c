#include "server.h"

void *send_notification_to_all_clients (Arguments *args)
{
  zsock_t *notification_socket = zsock_new(ZMQ_PUB);
  zsock_bind(notification_socket, "tcp://*:%s", args->pub_port);
  
  while (!zsys_interrupted) {
    char *json = malloc(sizeof(1024));
    json_t *root = json_pack("{s:i, s:i}", "foo", 42, "bar", 7);
    json = json_dumps(root, 0);
    strcat(json, "\n");
    zstr_sendf(notification_socket, "%s", json);
    json_decref(root);
    free(json);
    sleep(2);
  }
  zsock_destroy(&notification_socket);
  return NULL;
}

void init_notifications(){

}