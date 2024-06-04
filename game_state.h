#ifndef GAME_STATE_H
#define GAME_STATE_H

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
extern int highScore;
extern const char* highScoreFile;

#endif
