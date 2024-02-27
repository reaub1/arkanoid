#ifndef GAME_STATE_H
#define GAME_STATE_H

typedef enum {
    MENU,
    GAME,
    GAME_OVER
} GameState;

extern GameState currentState;

#endif
