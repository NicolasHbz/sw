#include <czmq.h>

int app(char *argv[]);

int subscribe_to_notifications(char *argv[]){
  zsock_t *client = zsock_new(ZMQ_SUB);
  zsock_connect(client, "tcp://127.0.0.1:%s", argv[1]);
  printf("Client connected to 127.0.0.1:%s\n", argv[1]);
  zsock_set_subscribe(client, "");

  while (!zsys_interrupted) {
    char *message = zstr_recv(client);
    printf("%s", message);
    zstr_free(&message);
  }
  zsock_destroy(&client);
  return 0;
}

int main(int argc, char *argv[])
{
  if (argc < 2) {
    printf("[Port number]\n");
    return 0;
  }
  pthread_t notifications;
  pthread_create (&notifications, NULL, &subscribe_to_notifications, argv);
  app(argv);
  pthread_join (notifications, NULL);
  return 0;
}
