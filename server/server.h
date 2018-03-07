#ifndef SERVER_H
#define SERVER_H

#include <czmq.h>
#include <unistd.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <pthread.h>
#include <time.h>
#include <getopt.h>
#include <jansson.h>

#include "notification.h"

#define PUB_PORT "12345"
#define REP_PORT "4242"
#define MAP_SIZE 5
#define NBR_OF_PLAYERS 2

typedef struct {
    char        *pub_port;
    char        *rep_port;
    int         size;
}               Arguments;

typedef struct {
    char        *rep_port;
    char        *pub_port;
    int         size;
}               Options;

typedef struct
{
    char        *command;
    void        (*func)();
}               CommandList;

typedef struct {
    char        *command;
    char        *data; 
}               Command;

typedef struct {
    char        *name;
    zframe_t    *identity;  
}               PlayerList;

int app(Arguments *arguments);
void *send_notification_to_all_clients (Arguments *args);
Options argument_parsing(int argc, char **argv);
Command get_command_and_data(zframe_t *input);

#endif