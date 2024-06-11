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
extern entities balls[64];

extern int x_vault;

extern SDL_Rect SlowSurfaces[8];
extern SDL_Rect CatchSurfaces[8];
extern SDL_Rect ExpandSurfaces[8];
extern SDL_Rect DivideSurfaces[8];
extern SDL_Rect LaserSurfaces[8];
extern SDL_Rect BreakSurfaces[8];
extern SDL_Rect PlayerSurfaces[8];

extern SDL_Rect nasser[8];
extern SDL_Rect farah[11];
extern SDL_Rect leyna[24];

extern SDL_Rect explosionsSurface[6];

void initGame();
void initBricks();
void readTextFile(const char* filename, char array[MAX_ROWS][MAX_COLS * 2 + 1], char endChar);
void loadHighScore();
void saveHighScore();
void loadNextLevel();
void initPowerUps();
void initPowerUpsArray();
void initMonsterArray();
void initExplosionsArray();

#endif
