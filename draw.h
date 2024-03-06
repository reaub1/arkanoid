#ifndef DRAW_H
#define DRAW_H

#include <SDL.h>
#include "init.h"
#include "constants.h"

void drawGame();
void initBricks();
void drawBricks(SDL_Surface* win_surf);

#endif
