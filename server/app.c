#include "server.h"

static PlayerList player_list[] =
{
    {NULL, NULL},
    {NULL, NULL},
};

void    wait_for_clients(zsock_t *router){
  int   i = 0;
  int   j;
  char  *identity_message;

  while(player_list[i].name == NULL) {
    zmsg_t *message = zmsg_recv(router);

    zframe_t *identity = zmsg_pop(message);
    zframe_t *empty = zmsg_pop(message);
    zframe_t *content = zmsg_pop(message);

    Command command = get_command_and_data(content);

    for (j = 0; j < NBR_OF_PLAYERS; j++){
      if (player_list[j].name == NULL){
        player_list[j].name = malloc(sizeof(command.data));
        player_list[j].name = command.data;
        player_list[j].identity = identity;
        i++;
        j++;
      }
    }

    identity_message = malloc(sizeof("Your identity is : "));
    strcpy(identity_message, "Your identity is : ");
    identity_message = strcat(identity_message, command.data);

    zframe_t *msg = zframe_from(identity_message);

    zmsg_destroy(&message);
    printf("Waiting for %d players\n", NBR_OF_PLAYERS);

    zmsg_t *response = zmsg_new();

    zmsg_prepend(response, &identity);
    zmsg_append(response, &empty);
    zmsg_append(response, &msg);

    zmsg_send(&response, router);
    zmsg_destroy(&response);

    zframe_destroy(&identity);
    zframe_destroy(&empty);
    zframe_destroy(&content);
    if (i == NBR_OF_PLAYERS) {
      break;
    }
  }
}

int     app(Arguments *args)
{
  zsock_t *router = zsock_new(ZMQ_ROUTER);
  zsock_bind(router, "tcp://*:%s", args->rep_port);

  wait_for_clients(router);

  pthread_t notifications;
  pthread_create (&notifications, NULL, send_notification_to_all_clients, args);
  pthread_join (notifications, NULL);

  while (!zsys_interrupted) {
    zmsg_t *message = zmsg_recv(router);

    zframe_t *identity = zmsg_pop(message);
    zframe_t *empty = zmsg_pop(message);
    zframe_t *content = zmsg_pop(message);

    Command command = get_command_and_data(content);

    zframe_t *msg = zframe_from(command.data);

    zmsg_destroy(&message);
    printf("Your command is : %s\n", command.command);
    printf("Your data is : %s\n", command.data);
    sleep(1);

    zmsg_t *response = zmsg_new();

    zmsg_prepend(response, &identity);
    zmsg_append(response, &empty);
    zmsg_append(response, &msg);

    zmsg_send(&response, router);
    zmsg_destroy(&response);

    zframe_destroy(&identity);
    zframe_destroy(&empty);
    zframe_destroy(&content);
  }
  zsock_destroy(&router);
  return 0;
}