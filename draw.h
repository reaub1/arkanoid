#ifndef DRAW_H
#define DRAW_H

#include <SDL.h>
#include <SDL_ttf.h>
#include "init.h"
#include "constants.h"
#include "game_state.h"

//void drawGame();
void initBricks();
void drawMenuBar();
void drawBricks(SDL_Surface* win_surf);
void renderText(SDL_Surface* surface, const char* message, int x, int y, TTF_Font* font);
int getTextWidth(TTF_Font* font, const char* message);
int getTextHeight(TTF_Font* font, const char* message);
void drawWaitingMessage(SDL_Surface* surface, TTF_Font* font);
void drawGame(TTF_Font* font); 
void drawGameOverMessage(SDL_Surface* surface, TTF_Font* font);


#endif
