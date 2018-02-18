#include <czmq.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <time.h>
int app();

struct arg_struct {
    char** argv;
    int number;
};

void *send_notification_to_all_clients (void* arguments)
{
  struct arg_struct *args = arguments;
  zsock_t *notification_socket = zsock_new(ZMQ_PUB);
  zsock_bind(notification_socket, "tcp://127.0.0.1:%s", args->argv[1]);
  printf("Server listening on tcp://*:%s", args->argv[1]);

  while (!zsys_interrupted) {
    char message[1024] = "test\n";
    zstr_sendf(notification_socket, "%s", message);
    sleep(2);   
  }
  zsock_destroy(&notification_socket);
  return NULL;
}

int main(int argc, char *argv[])
{
  if (argc < 3) {
    printf("[NOTIFICATION-PORT] [REP-PORT]\n");
    return 0;
  }

  pthread_t notifications;
  struct arg_struct arguments;
  arguments.argv = argv;
  arguments.number = 7;
  pthread_create (&notifications, NULL, send_notification_to_all_clients, (void *) &arguments);
  app(argv);
  pthread_join (notifications, NULL);
  return 0;
}

