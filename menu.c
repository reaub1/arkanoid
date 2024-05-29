#include "menu.h"
#include "SDL.h"
#include "game_state.h"
#include "constants.h"
#include "block.h"

void showMenu(SDL_Window* window) {
    SDL_Surface* surface = SDL_GetWindowSurface(window);
    if (!surface) {
        SDL_Log("Erreur lors de l'obtention de la surface de la fenêtre : %s", SDL_GetError());
        SDL_DestroyWindow(window);
        SDL_Quit();
        exit(1);
    }

    SDL_Color blackColor = {30, 30, 30};
    SDL_Color borderColor = {173, 216, 230};
    SDL_Color backgroundColor = {0, 0, 0};

    Uint32 background_color = SDL_MapRGB(surface->format, backgroundColor.r, backgroundColor.g, backgroundColor.b);
    SDL_FillRect(surface, NULL, background_color); 

    const int numButtons = 3;
    int buttonHeight = 50;
    int padding = 10;
    int buttonWidth = 200;
    int windowHeight, windowWidth;
    SDL_GetWindowSize(window, &windowWidth, &windowHeight);

    int buttonY[numButtons];
    for (int i = 0; i < numButtons; i++) {
        buttonY[i] = (windowHeight - (numButtons * (buttonHeight + padding))) / 2 + i * (buttonHeight + padding);
    }

    for (int i = 0; i < numButtons; i++) {
        int buttonX = (windowWidth - buttonWidth) / 2;

        SDL_Rect borderRect = {buttonX - 3, buttonY[i] - 3, buttonWidth + 6, buttonHeight + 6};
        SDL_FillRect(surface, &borderRect, SDL_MapRGB(surface->format, borderColor.r, borderColor.g, borderColor.b));

        SDL_Rect buttonRect = {buttonX, buttonY[i], buttonWidth, buttonHeight};
        SDL_FillRect(surface, &buttonRect, SDL_MapRGB(surface->format, blackColor.r, blackColor.g, blackColor.b));
    }

    const char* words[3] = {"easy", "medium", "hard"};
    int wordLengths[3] = {4, 6, 4};
    int wordX[numButtons];
    for (int i = 0; i < numButtons; i++) {
        wordX[i] = (windowWidth - wordLengths[i] * LETTER_SPRITE_WIDTH) / 2;
    }

    for (int ii = 0; ii < numButtons; ii++) {
    for (int jj = 0; jj < wordLengths[ii]; jj++) {

        char currentLetter = words[ii][jj];

        SDL_Rect src;

        switch (currentLetter) { 
            case 'a':
                src = a;
                break;
            case 'b':
                src = b;
                break;
            case 'c':
                src = c;
                break;
            case 'd':
                src = d;
                break;
            case 'e':
                src = e;
                break;
            case 'f':
                src = f;
                break;
            case 'g':
                src = g;
                break;
            case 'h':
                src = h;
                break;
            case 'i':
                src = i;
                break;
            case 'j':
                src = j;
                break;
            case 'k':   
                src = k;
                break;
            case 'l':
                src = l;
                break;
            case 'm':
                src = m;
                break;
            case 'n':
                src = n;
                break;
            case 'o':
                src = o;
                break;
            case 'p':
                src = p;
                break;
            case 'q':
                src = q;
                break;
            case 'r':
                src = r;
                break;
            case 's':
                src = s;
                break;
            case 't':
                src = t;
                break;
            case 'u':
                src = u;
                break;
            case 'v':
                src = v;
                break;
            case 'w':
                src = w;
                break;
            case 'x':
                src = x;
                break;
            case 'y':
                src = y;
                break;
            case 'z':
                src = z;
                break;
            default:
                src = a;
                break;
            }
        int letterX = wordX[ii] + jj * LETTER_SPRITE_WIDTH;
        int letterY = buttonY[ii];

        SDL_Rect letterDestRect = { letterX, letterY, LETTER_SPRITE_WIDTH, LETTER_SPRITE_HEIGHT };

        SDL_BlitSurface(plancheSpritesAscii, &src, surface, &letterDestRect);
    }
}


    SDL_UpdateWindowSurface(window);

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
