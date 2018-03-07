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

int app(Arguments *args);

void *subscribe_to_notifications(Arguments * args)
{
  zsock_t *client = zsock_new(ZMQ_SUB);
  zsock_connect(client, "tcp://127.0.0.1:%s", args->pub_port);
  printf("Client connected to 127.0.0.1:%s\n", args->pub_port);
  zsock_set_subscribe(client, "");

  while (!zsys_interrupted) {
    char *message = zstr_recv(client);
    printf("%s", message);
    zstr_free(&message);
  }
  zsock_destroy(&client);
  return NULL;
}

int main(int argc, char *argv[])
{
  if (argc < 2) {
    printf("[Port number]\n");
    return 0;
  }

  Arguments arguments;
  arguments.pub_port = argv[1];
  arguments.rep_port = argv[2];
  pthread_t notifications;
  pthread_create (&notifications, NULL, subscribe_to_notifications, &arguments);
  app(&arguments);
  pthread_join (notifications, NULL);
  return 0;
}
