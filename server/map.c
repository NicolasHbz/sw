#include "server.h"

char **build_map()
{
  int   i;
  int   j;
  char  **map;

  for (i = 0; i < MAP_SIZE; i++)
    {
      map[i] = malloc(sizeof(char*) * MAP_SIZE);
      for (j = 0; j < MAP_SIZE; j++)
        {
        map[i][j] = malloc(sizeof(char) * 5);
        map[i][j] = "empty";
        }
    }
    return map;
}