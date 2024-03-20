#ifndef INIT_H
#define INIT_H

#include <SDL.h>
#include "constants.h"

extern SDL_Window* pWindow;
extern SDL_Surface* win_surf;
extern SDL_Surface* plancheSprites;
extern SDL_Surface* plancheSpritesBricks;
extern SDL_Surface* plancheSpritesAscii;

extern SDL_Rect srcBall; 
extern SDL_Rect scrVaiss;
extern SDL_Rect srcBrick;

extern SDL_Rect block;

extern SDL_Renderer* renderer;

typedef struct {
    double x, y;
    double vx, vy;
} Ball;

extern Ball ball;

typedef struct {
    SDL_Rect rect; 
    bool active;
    SDL_Rect color;  
    bool isDestructible; 
    bool update;
    int points;
} Brick;

extern Brick bricks[BRICK_ROWS][BRICK_COLUMNS];

extern int x_vault;

void initGame();
void initBricks();
void readTextFile(const char* filename, char array[MAX_ROWS][MAX_COLS + 1]);

#endif
