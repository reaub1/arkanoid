#include "init.h"
#include "draw.h"
#include "update.h"
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include "menu.h"
#include <SDL.h>
#include <SDL_ttf.h>
#include "game_state.h"

int main(int argc, char** argv) {
    if (SDL_Init(SDL_INIT_VIDEO | SDL_INIT_AUDIO) != 0) {
        SDL_Log("SDL_Init Error: %s", SDL_GetError());
        return 1;
    }

    if (TTF_Init() == -1) {
        SDL_Log("TTF_Init Error: %s", TTF_GetError());
        SDL_Quit();
        return 1;
    }

    TTF_Font* font = TTF_OpenFont("../arkanoid/Outwrite.ttf", 24);
    if (!font) {
        SDL_Log("TTF_OpenFont Error: %s", TTF_GetError());
        TTF_Quit();
        SDL_Quit();
        return 1;
    }

    initGame();

    bool quit = false;
    while (!quit) {
        switch (currentState) {
            case MENU:
                showMenu(pWindow);
                break;
            case GAME:
                updateGame();
                drawGame(font); 
                break;
            case WAITING_TO_RESTART:
                drawGame(font);
                SDL_UpdateWindowSurface(pWindow); 
                break;
            case GAME_OVER:
                drawGame(font); 
                SDL_UpdateWindowSurface(pWindow); 
                break;
        }
        quit = processInput();
        if (turn == 1000) turn = 0;
    }

    TTF_CloseFont(font);
    TTF_Quit();
    
    return 0;
}
