#include "init.h"
#include "game_state.h"

SDL_Window* pWindow = NULL;
SDL_Surface* win_surf = NULL;
SDL_Surface* plancheSprites = NULL;
SDL_Surface* plancheSpritesBricks = NULL;

SDL_Rect srcBg = { 0, 128, 96, 128 };
SDL_Rect srcBall = { 0, 96, 24, 24 };
SDL_Rect scrVaiss = { 128, 0, 128, 32 };
SDL_Rect srcBrick = {0, 0, BRICK_SPRITE_WIDTH, BRICK_SPRITE_HEIGHT};

SDL_Renderer* renderer = NULL;
Brick bricks[BRICK_ROWS][BRICK_COLUMNS] = {0};

SDL_Rect block;

Ball ball;

int x_vault = 0;

void initGame() {

    block.x = 0;   // Initialisation de la position x
    block.y = 0;    // Initialisation de la position y
    block.w = 50;   // Définition de la largeur
    block.h = 50;

    currentState = MENU;

    pWindow = SDL_CreateWindow("Arkanoid", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, 600, 600, SDL_WINDOW_SHOWN);
    if (pWindow == NULL) {
        SDL_Log("Erreur lors de la création de la fenêtre : %s", SDL_GetError());
        SDL_Quit();
        exit(1);
    }

    renderer = SDL_CreateRenderer(pWindow, -1, SDL_RENDERER_SOFTWARE);

    win_surf = SDL_GetWindowSurface(pWindow);
    if (win_surf == NULL) {
        SDL_Log("Erreur lors de l'obtention de la surface de la fenêtre : %s", SDL_GetError());
        SDL_DestroyWindow(pWindow);
        SDL_Quit();
        exit(1);
    }

    plancheSprites = SDL_LoadBMP("./sprites.bmp");
    if (plancheSprites == NULL) {
        SDL_Log("Erreur lors du chargement de sprites.bmp : %s", SDL_GetError());
        SDL_DestroyWindow(pWindow);
        SDL_Quit();
        exit(1);
    }
    SDL_SetColorKey(plancheSprites, SDL_TRUE, 0);

    plancheSpritesBricks = SDL_LoadBMP("./Arkanoid_sprites.bmp");
    if(plancheSpritesBricks == NULL) {
        SDL_Log("Erreur lors du chargement de Arkanoid_sprites.bmp : %s", SDL_GetError());
        SDL_DestroyWindow(pWindow);
        SDL_Quit();
        exit(1);
    }
    //SDL_SetColorKey(plancheSpritesBricks, SDL_TRUE, 0);

    

    ball.x = win_surf->w / 2;
    ball.y = win_surf->h / 2;
    ball.vx = 1.0;
    ball.vy = 1.4;

    x_vault = win_surf->w / 2;

    initBricks();
}

void initBricks() {
    int startX = (win_surf->w - BRICK_WIDTH) / 2;
    int startY = (win_surf->h - BRICK_HEIGHT) / 2 - 150;

    for (int i = 0; i < BRICK_ROWS; i++) {
        for (int j = 0; j < BRICK_COLUMNS; j++) {
            bricks[i][j].rect.x = startX + j * BRICK_WIDTH;
            bricks[i][j].rect.y = startY + i * BRICK_HEIGHT;
            bricks[i][j].rect.w = BRICK_WIDTH;
            bricks[i][j].rect.h = BRICK_HEIGHT;
            bricks[i][j].active = true;
        }
    }
}
