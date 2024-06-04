#include "game_state.h"

GameState currentState = MENU;

int score = 0;
int lives = 3;
int level = 1;
int turn = 0;
int highScore = 0;
const char* highScoreFile = "highscore.txt";
