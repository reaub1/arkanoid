#ifndef UPDATE_H
#define UPDATE_H

#include <stdbool.h>
#include "SDL.h"
#include "init.h"
#include "game_state.h"
#include "draw.h"


void updateGame();
bool processInput();
void checkBallBrickCollision();
void generatePowerUp(int powerUp, int x, int y);
void updatePowerUps();

#endif
