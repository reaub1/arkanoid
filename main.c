#include "init.h"
#include "draw.h"
#include "update.h"
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include "menu.h"
#include "game_state.h"

int main(int argc, char** argv) {
    if (SDL_Init(SDL_INIT_VIDEO | SDL_INIT_AUDIO ) != 0 ) {
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
                quit = processInput();
                updateGame();
                drawGame();
                turn++;
                if (turn == 1000)
                    turn = 0;
                break;
            case GAME_OVER:
                showGameOver();
                break;
        }
    }

    SDL_Quit();
    return 0;
}
