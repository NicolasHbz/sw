#include "server.h"

Options argument_parsing(int argc, char **argv)
{
  int               c;
  const char        *short_opt = "h:p:r:";
  char              *pub_port;
  char              *rep_port;
  Options           options;
  struct option     long_opt[] =
  {
    {"help",        no_argument,       NULL, 'h'},
    {"pub-port",    required_argument, NULL, 'p'},
    {"rep-port",    required_argument, NULL, 'r'},
    {"size",        required_argument, NULL, 's'},
    {NULL,          0,                 NULL,  0 }
  };
  options.pub_port = PUB_PORT;
  options.rep_port = REP_PORT;
  options.size = MAP_SIZE;

   while((c = getopt_long(argc, argv, short_opt, long_opt, NULL)) != -1)
   {
      switch(c)
      {
        case 'p':
          options.pub_port = optarg;
          printf("publication port: \"%s\"\n", options.pub_port);
        break;

        case 'r':
          options.rep_port = optarg;
          printf("rep port: \"%s\"\n", options.rep_port);
        break;

        case 's':
          options.size = atoi(optarg);
          printf("map size: \"%d\"\n", options.size);
        break;

        case 'h':
          printf("Usage: %s [OPTIONS] [ARGUMENTS]\n", argv[0]);
          printf("--rep-port [PORT] port used to receive client request and respond\n");
          printf("--pub-port [PORT] port used to send notifications to clients\n");
          printf("--help print this help and exit\n");
          printf("\n");
        break;

        case ':':
        case '?':
          fprintf(stderr, "Try `%s --help' for more information.\n", argv[0]);
        return options;

        default:
          fprintf(stderr, "%s: invalid option -- %c\n", argv[0], c);
          fprintf(stderr, "Try `%s --help' for more information.\n", argv[0]);
        return options;
      }
   }
    return options;
}