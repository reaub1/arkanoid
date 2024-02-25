#ifndef INIT_H
#define INIT_H

#include <SDL.h>

extern SDL_Window* pWindow;
extern SDL_Surface* win_surf;
extern SDL_Surface* plancheSprites;

extern SDL_Rect srcBg; 
extern SDL_Rect srcBall; 
extern SDL_Rect scrVaiss;

typedef struct {
    double x, y;
    double vx, vy;
} Ball;

extern Ball ball;


extern int x_vault;

void initGame();

#endif
