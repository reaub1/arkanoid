#ifndef GAME_STATE_H
#define GAME_STATE_H

extern int score;
extern int lives;
extern int highScore;
extern const char* highScoreFile;
extern int turn; // Add this line

typedef enum {
    MENU,
    GAME,
    GAME_OVER,
    NEXT_LEVEL
} GameState;

extern GameState currentState;
extern const char* levelFiles[];
extern int currentLevelIndex;
extern int totalLevels;

#endif
