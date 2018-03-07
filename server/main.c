#include "server.h"

int main(int argc, char *argv[])
{
  Options options = argument_parsing(argc, argv);
  Arguments arguments;
  arguments.pub_port = options.pub_port;
  arguments.rep_port = options.rep_port;
  arguments.size = options.size;

  app(&arguments);
  return 0;
}

