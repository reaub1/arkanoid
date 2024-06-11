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

typedef enum {
    NORMAL_BRICK,
    TOUGH_BRICK,
    SPECIAL_BRICK
} BrickType;

typedef struct {
    SDL_Rect rect; 
    bool active;
    SDL_Rect color;  
    bool isDestructible; 
    bool update;
    int points;
    int life;
    int powerUp;
    int transform;
    BrickType type;
} Brick;

typedef struct {
    int x, y;
    int w, h;
    int vx, vy;
    SDL_Rect surface;
    int state; 
    float time;
    char type;
    int max_state;
} entities;

extern Brick bricks[BRICK_ROWS][BRICK_COLUMNS];

extern entities powerUps[POWERUPS_MAX];
extern entities monsters[MONSTERS_MAX];
extern entities explosions[EXPLOSIONS_MAX];

extern int x_vault;

void initGame();
void initBricks();
void readTextFile(const char* filename, char array[MAX_ROWS][MAX_COLS * 2 + 1], char endChar);
void loadHighScore();
void saveHighScore();
void initPowerUps();

#endif
