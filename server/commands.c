#include "server.h"

char    *get_command(zframe_t *input) {
  char  *command;
  int   i;

  char *content = zframe_strdup(input);
  command = malloc(sizeof(content));
  for (i = 0; content[i] != '|'; i++) {
    command[i] = content[i];
  }
  command[i] = '\0';
  return command;
}