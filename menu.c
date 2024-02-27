#include "menu.h"
#include "SDL.h"
#include "game_state.h"

#define COLOR_BACKGROUND SDL_MapRGB(surface->format, 0, 0, 0)
#define COLOR_MENU SDL_MapRGB(surface->format, 255, 255, 255)

void showMenu(SDL_Window* window) {
    SDL_Renderer* renderer = SDL_GetRenderer(window);
    if (!renderer) {
        renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
    }

    SDL_Color whiteColor = {255, 255, 255};
    SDL_Color borderColor = {173, 216, 230};
    SDL_Color backgroundColor = {0, 0, 139};

    int windowWidth, windowHeight;
    SDL_GetWindowSize(window, &windowWidth, &windowHeight);

    SDL_Rect menuBackground = {windowWidth / 4, windowHeight / 4, windowWidth / 2, windowHeight / 2};

    SDL_SetRenderDrawColor(renderer, backgroundColor.r, backgroundColor.g, backgroundColor.b, 255);
    SDL_RenderClear(renderer);

    const int numButtons = 3;
    int buttonHeight = 50;
    int padding = 10;
    int buttonWidth = menuBackground.w - 2 * padding;

    for (int i = 0; i < numButtons; i++) {
        int buttonX = menuBackground.x + padding;
        int buttonY = menuBackground.y + padding + i * (buttonHeight + padding);

        SDL_Rect borderRect = {buttonX - 3, buttonY - 3, buttonWidth + 6, buttonHeight + 6};
        SDL_SetRenderDrawColor(renderer, borderColor.r, borderColor.g, borderColor.b, 255);
        SDL_RenderFillRect(renderer, &borderRect);

        SDL_Rect buttonRect = {buttonX, buttonY, buttonWidth, buttonHeight};
        SDL_SetRenderDrawColor(renderer, whiteColor.r, whiteColor.g, whiteColor.b, 255);
        SDL_RenderFillRect(renderer, &buttonRect);
    }

    SDL_RenderPresent(renderer);

    SDL_Event event;
    while (SDL_WaitEvent(&event)) {
        if (event.type == SDL_QUIT) {
            exit(0);
        } else if (event.type == SDL_KEYDOWN) {
            if (event.key.keysym.sym == SDLK_RETURN) {
                currentState = GAME;
                return;
            }
        }
    }
}

