#ifndef GAME_STATE_H
#define GAME_STATE_H

typedef enum {
    MENU,
    GAME,
    WAITING_TO_RESTART,
    GAME_OVER
} GameState;

extern GameState currentState;

extern int score;
extern int lives;
extern int level;
extern int turn;

#endif
