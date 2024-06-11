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
void checkCollisionPaddle();
void initPowerUpsArray();
void nextAnimation(entities *powerups, SDL_Rect slowSurfaces[]);
void handlePowerUpCollision(entities *powerUp);
void initMonsterArray();
void createMonster();
void updateMonsters();
void initExplosionsArray();
void generateExplosion(int x, int y);
void updateExplosions();
void checkBallMonsterCollision();

#endif
