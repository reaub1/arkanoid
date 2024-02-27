#include "init.h"
#include "game_state.h"

SDL_Window* pWindow = NULL;
SDL_Surface* win_surf = NULL;
SDL_Surface* plancheSprites = NULL;

SDL_Rect srcBg = { 0, 128, 96, 128 };
SDL_Rect srcBall = { 0, 96, 24, 24 };
SDL_Rect scrVaiss = { 128, 0, 128, 32 };

Ball ball;

int x_vault = 0;

void initGame() {

    currentState = MENU;

    pWindow = SDL_CreateWindow("Arkanoid", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, 600, 600, SDL_WINDOW_SHOWN);
    if (pWindow == NULL) {
        SDL_Log("Erreur lors de la création de la fenêtre : %s", SDL_GetError());
        SDL_Quit();
        exit(1);
    }

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

    ball.x = win_surf->w / 2;
    ball.y = win_surf->h / 2;
    ball.vx = 1.0;
    ball.vy = 1.4;

    x_vault = win_surf->w / 2;
}
