#include "server.h"

int main(int argc, char *argv[])
{
  Options options = argument_parsing(argc, argv);
  Arguments arguments;
  arguments.pub_port = options.pub_port;
  arguments.rep_port = options.rep_port;
  arguments.size = options.size;

  pthread_t notifications;
  pthread_create (&notifications, NULL, send_notification_to_all_clients, &arguments);
  app(&arguments);
  pthread_join (notifications, NULL);
  return 0;
}

