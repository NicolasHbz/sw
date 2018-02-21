#ifndef NOTIFICATION_H
#define NOTIFICATION_H

typedef enum {
    cycle_info =        0,
    game_started =      1,
    game_finished =     2,
    client_dead =       3,
    client_win =        4,
}                       NotificationType;

typedef struct {
    char                *name;
    unsigned int        x;
    unsigned int        y;
    unsigned int        energy;
    unsigned int        looking; // direction dans laquelle regarde le joueur (left = 0, up = 1, right = 2, down = 3)
}                       Player;

typedef struct {
    unsigned int        x;
    unsigned int        y;
    unsigned int        value;
}                       EnergyCell;

typedef struct {
    unsigned int        map_size;
    unsigned int        game_status;    // 0 => waiting, 1 => started, 2 => finished
    Player              *players;       // tableau de <Player>,
    EnergyCell          *energy_cells;  // tableau de <EnergyCell>
}                       GameInfo;

typedef struct {
    NotificationType    notification_type;
    GameInfo            *game_info;
}                       Notifications;

#endif