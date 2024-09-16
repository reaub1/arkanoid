// game_state.h
#ifndef GAME_STATE_H
#define GAME_STATE_H

#include "SDL.h"

typedef enum {
    MENU,
    GAME,
    GAME_OVER
} GameState;

extern GameState currentState;
extern int score;
extern int lives;
extern int level;
extern int turn;

extern SDL_Rect vausRect;

#endif // GAME_STATE_H
