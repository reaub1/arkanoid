#ifndef DRAW_H
#define DRAW_H

#include <SDL.h>
#include "init.h"
#include "constants.h"
#include "game_state.h"

void drawGame();
void initBricks();
void drawMenuBar();
void drawBricks(SDL_Surface* win_surf);
void drawPowerUps(SDL_Surface* win_surf);
void showGameOver();
void drawText(SDL_Surface* surface, const char* message, int x, int y);
void drawWaitingMessage();
void drawGameOverMessage();


#endif
