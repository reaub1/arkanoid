#include "draw.h"
#include "block.h"
#include "game_state.h"

void drawMenuBar() {

    SDL_Surface* menu_surf = SDL_CreateRGBSurface(0, win_surf->w, MENU_HEIGHT, 32, 0, 0, 0, 0);
    if (menu_surf == NULL) {
        SDL_Log("Erreur lors de la création de la surface temporaire pour la barre de menu : %s", SDL_GetError());
        return;
    }

    SDL_Rect menuRect = {0, 0, menu_surf->w, MENU_HEIGHT};
    SDL_FillRect(menu_surf, &menuRect, SDL_MapRGB(menu_surf->format, 0, 0, 0));

    char scoreText[20];
    snprintf(scoreText, sizeof(scoreText), "Score: %d", score);

    int scoreX = 20;
    int scoreY = 20; 
    
    for (int i = 0; scoreText[i] != '\0'; i++) {
        char currentDigit = scoreText[i];

        SDL_Rect srcRect;
        switch (currentDigit) {
            case '0':
                srcRect = zero;
                break;
            case '1':
                srcRect = un;
                break;
            case '2':
                srcRect = deux;
                break;
            case '3':
                srcRect = trois;
                break;
            case '4':
                srcRect = quatre;
                break;
            case '5':
                srcRect = cinq;
                break;
            case '6':
                srcRect = six;
                break;
            case '7':
                srcRect = sept;
                break;
            case '8':
                srcRect = huit;
                break;
            case '9':
                srcRect = neuf;
                break;
            default:
                continue;
        }
        
        SDL_Rect dstRect = {scoreX, scoreY, 100, 100};

        SDL_BlitSurface(plancheSpritesAscii, &srcRect, win_surf, &dstRect);

        SDL_UpdateWindowSurface(pWindow);

        scoreX += srcRect.w;        
    }
}

void drawGame() {

    SDL_Surface* menu_surf = SDL_CreateRGBSurface(0, win_surf->w, MENU_HEIGHT, 32, 0, 0, 0, 0);
    if (menu_surf == NULL) {
        SDL_Log("Erreur lors de la création de la surface temporaire pour la barre de menu : %s", SDL_GetError());
        return;
    }

    //drawMenuBar(menu_surf);

    SDL_Rect dest = { 0, MENU_HEIGHT, 0, 0 };
    for (int j = 0; j < win_surf->h - MENU_HEIGHT; j += 64)
        for (int i = 0; i < win_surf->w; i += 64) {
            dest.x = i;
            dest.y = j + MENU_HEIGHT;
            SDL_BlitSurface(plancheSpritesBricks, &darkbackground6, win_surf, &dest);
        }

    SDL_Rect dstBall = { (int)ball.x, (int)ball.y + MENU_HEIGHT, 24, 24 };
    SDL_BlitSurface(plancheSprites, &srcBall, win_surf, &dstBall);

    SDL_Rect dstVaiss = { x_vault, win_surf->h - 32, 128, 32 };
    SDL_BlitSurface(plancheSprites, &scrVaiss, win_surf, &dstVaiss);

    SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
    SDL_RenderFillRect(renderer, &block);

    drawBricks(win_surf);
    drawPowerUps(win_surf);

    SDL_UpdateWindowSurface(pWindow);
}

void drawBricks(SDL_Surface* win_surf) {
    for (int i = 0; i < BRICK_ROWS; i++) {
        for (int j = 0; j < BRICK_COLUMNS; j++) {
            if (!bricks[i][j].active) {
                continue;
            }
            SDL_Rect* currentColor = &bricks[i][j].color;
            SDL_Surface* brickSurface = plancheSpritesBricks;
            SDL_BlitSurface(brickSurface, currentColor, win_surf, &bricks[i][j].rect);            
        }
    }
}

void drawPowerUps(SDL_Surface* win_surf) {
    for (int i = 0; i < POWERUPS_MAX; i++) {
        if (!powerUps[i].surface.w) {
            continue;
        }
        SDL_BlitSurface(plancheSpritesBricks, &powerUps[i].surface, win_surf, &powerUps[i].surface);
    }
}
