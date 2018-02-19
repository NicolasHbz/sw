#include "server.h"

int main(int argc, char *argv[])
{
  Options options = argument_parsing(argc, argv);
  char **map = build_map();
  
  Arguments arguments;
  arguments.pub_port = options.pub_port;
  pthread_t notifications;
  pthread_create (&notifications, NULL, send_notification_to_all_clients, &arguments);
  app(options.rep_port);
  pthread_join (notifications, NULL);
  return 0;
}

