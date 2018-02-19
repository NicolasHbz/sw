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

#define PUB_PORT "12345"
#define REP_PORT "4242"

typedef struct {
    char    *pub_port;
    char    *rep_port;
}           Arguments;

typedef struct {
    char    *rep_port;
    char    *pub_port;
}           Options;

int app(char *rep_port);
void *send_notification_to_all_clients (Arguments *args);
Options argument_parsing(int argc, char **argv);

#endif