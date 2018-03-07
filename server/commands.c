#include "server.h"

Command   get_command_and_data(zframe_t *input) {
  Command command_and_data;
  char    *command;
  char    *data;
  int     i;

  char *content = zframe_strdup(input);
  command = malloc(sizeof(content));
  for (i = 0; content[i] != '|'; i++) {
    command[i] = content[i];
  }
  command[i] = '\0';
  data = strchr(content, '|');
  memmove(data, data + 1, strlen(data));
  command_and_data.command = command;
  command_and_data.data = data;
  return command_and_data;
}