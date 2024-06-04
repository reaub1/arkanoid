#include "game_state.h"

int score = 0;
int lives = 3;
int highScore = 0;
int turn = 0; 
const char* highScoreFile = "highscore.txt";

GameState currentState = MENU;

const char* levelFiles[] = {
    "./level/lvl1.txt",
    "./level/lvl2.txt",
    "./level/lvl3.txt",

};

int currentLevelIndex = 0;
int totalLevels = sizeof(levelFiles) / sizeof(levelFiles[0]);
