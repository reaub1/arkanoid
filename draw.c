#include "draw.h"
#include "block.h"
#include "game_state.h"
#include <SDL.h>
#include <SDL_ttf.h>

void drawMenuBar() {
    SDL_Surface* menu_surf = SDL_CreateRGBSurface(0, win_surf->w, MENU_HEIGHT, 32, 0, 0, 0, 0);
    if (menu_surf == NULL) {
        SDL_Log("Error creating menu bar surface: %s", SDL_GetError());
        return;
    }

    SDL_Rect menuRect = {0, 0, menu_surf->w, MENU_HEIGHT};
    SDL_FillRect(menu_surf, &menuRect, SDL_MapRGB(menu_surf->format, 0, 0, 0));

    char scoreText[20];
    snprintf(scoreText, sizeof(scoreText), "Score: %d", score);

    char livesText[20];
    snprintf(livesText, sizeof(livesText), "Lives: %d", lives);

    int scoreX = 20;
    int scoreY = 20;
    int livesX = win_surf->w - 100;
    int livesY = 20;

    // Draw score
    for (int i = 0; scoreText[i] != '\0'; i++) {
        char currentDigit = scoreText[i];
        SDL_Rect srcRect;
        switch (currentDigit) {
            case '0': srcRect = zero; break;
            case '1': srcRect = un; break;
            case '2': srcRect = deux; break;
            case '3': srcRect = trois; break;
            case '4': srcRect = quatre; break;
            case '5': srcRect = cinq; break;
            case '6': srcRect = six; break;
            case '7': srcRect = sept; break;
            case '8': srcRect = huit; break;
            case '9': srcRect = neuf; break;
            default: continue;
        }
        SDL_Rect dstRect = {scoreX, scoreY, 100, 100};
        SDL_BlitSurface(plancheSpritesAscii, &srcRect, win_surf, &dstRect);
        scoreX += srcRect.w;
    }

    // Draw lives
    for (int i = 0; livesText[i] != '\0'; i++) {
        char currentDigit = livesText[i];
        SDL_Rect srcRect;
        switch (currentDigit) {
            case '0': srcRect = zero; break;
            case '1': srcRect = un; break;
            case '2': srcRect = deux; break;
            case '3': srcRect = trois; break;
            case '4': srcRect = quatre; break;
            case '5': srcRect = cinq; break;
            case '6': srcRect = six; break;
            case '7': srcRect = sept; break;
            case '8': srcRect = huit; break;
            case '9': srcRect = neuf; break;
            default: continue;
        }
        SDL_Rect dstRect = {livesX, livesY, 100, 100};
        SDL_BlitSurface(plancheSpritesAscii, &srcRect, win_surf, &dstRect);
        livesX += srcRect.w;
    }

    SDL_UpdateWindowSurface(pWindow);
}


void drawGame(TTF_Font* font) {

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

     if (currentState == WAITING_TO_RESTART) {
        drawWaitingMessage(win_surf, font);
    } else if (currentState == GAME_OVER) {
        drawGameOverMessage(win_surf, font);
    }

    SDL_UpdateWindowSurface(pWindow);
}

void drawBricks(SDL_Surface* win_surf) {
    for (int i = 0; i < BRICK_ROWS; i++) {
        for (int j = 0; j < BRICK_COLUMNS; j++) {
            if (!bricks[i][j].active) {
                continue;
            }

            if (turn % 20 == 0) {
                SDL_Rect* currentColor = &bricks[i][j].color;
                SDL_Surface* brickSurface = plancheSpritesBricks;

                if (SDL_RectEquals(currentColor, &goldbrick1)) {
                    *currentColor = goldbrick2;
                } else if (SDL_RectEquals(currentColor, &goldbrick2)) {
                    *currentColor = goldbrick3;
                } else if (SDL_RectEquals(currentColor, &goldbrick3)) {
                    *currentColor = goldbrick4;
                } else if (SDL_RectEquals(currentColor, &goldbrick4)) {
                    *currentColor = goldbrick5;
                } else if (SDL_RectEquals(currentColor, &goldbrick5)) {
                    *currentColor = goldbrick6;
                } else if (SDL_RectEquals(currentColor, &goldbrick6)) {
                    *currentColor = goldbrick1;
                } else if (SDL_RectEquals(currentColor, &silverbrick1)) {
                    *currentColor = silverbrick2;
                } else if (SDL_RectEquals(currentColor, &silverbrick2)) {
                    *currentColor = silverbrick3;
                } else if (SDL_RectEquals(currentColor, &silverbrick3)) {
                    *currentColor = silverbrick4;
                } else if (SDL_RectEquals(currentColor, &silverbrick4)) {
                    *currentColor = silverbrick5;
                } else if (SDL_RectEquals(currentColor, &silverbrick5)) {
                    *currentColor = silverbrick6;
                } else if (SDL_RectEquals(currentColor, &silverbrick6)) {
                    *currentColor = silverbrick1;
                } else if (SDL_RectEquals(currentColor, &ball1)) {
                    *currentColor = ball2;
                } else if (SDL_RectEquals(currentColor, &ball2)) {
                    *currentColor = ball3;
                } else if (SDL_RectEquals(currentColor, &ball3)) {
                    *currentColor = ball4;
                } else if (SDL_RectEquals(currentColor, &ball4)) {
                    *currentColor = ball5;
                } else if (SDL_RectEquals(currentColor, &ball5)) {
                    *currentColor = ball6;
                } else if (SDL_RectEquals(currentColor, &ball6)) {
                    *currentColor = ball1;
                }

                SDL_BlitSurface(brickSurface, currentColor, win_surf, &bricks[i][j].rect);
            } else {
                SDL_BlitSurface(plancheSpritesBricks, &bricks[i][j].color, win_surf, &bricks[i][j].rect);
            }
        }
    }
}

void renderText(SDL_Surface* surface, const char* message, int x, int y, TTF_Font* font) {
    SDL_Color color = {255, 255, 255}; 
    SDL_Surface* textSurface = TTF_RenderText_Solid(font, message, color);
    if (textSurface == NULL) {
        SDL_Log("TTF_RenderText_Solid Error: %s", TTF_GetError());
        return;
    }

    SDL_Rect textRect = {x, y, textSurface->w, textSurface->h};
    SDL_BlitSurface(textSurface, NULL, surface, &textRect);
    SDL_FreeSurface(textSurface);
}

int getTextWidth(TTF_Font* font, const char* message) {
    int textWidth;
    TTF_SizeText(font, message, &textWidth, NULL);
    return textWidth;
}

int getTextHeight(TTF_Font* font, const char* message) {
    int textHeight;
    TTF_SizeText(font, message, NULL, &textHeight);
    return textHeight;
}

void drawWaitingMessage(SDL_Surface* surface, TTF_Font* font) {
    const char* message = "Press space to continue playing";
    int x = (surface->w - getTextWidth(font, message)) / 2;
    int y = (surface->h - getTextHeight(font, message)) / 2;
    renderText(surface, message, x, y, font);
}

void drawGameOverMessage(SDL_Surface* surface, TTF_Font* font) {
    const char* message = "Game Over! Press SPACE !";
    int x = (surface->w - getTextWidth(font, message)) / 2;
    int y = (surface->h - getTextHeight(font, message)) / 2;
    renderText(surface, message, x, y, font);
}
