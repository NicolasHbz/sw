#include <czmq.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <time.h>

int main(int argc, char *argv[])
{
  if (argc < 2) {
    printf("Port number is mandatory\n");
    return 0;
  }

  zsock_t *chat_srv_socket = zsock_new(ZMQ_PUB);
  zsock_bind(chat_srv_socket, "tcp://127.0.0.1:%s", argv[1]);
  printf("Server listening on tcp://*:%s", argv[1]);

  while (!zsys_interrupted) {
    char message[1024] = "test\n";
    zstr_sendf(chat_srv_socket, "%s", message);
    sleep(2);   
  }
  zsock_destroy(&chat_srv_socket);
  return 0;
}

