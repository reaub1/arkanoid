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
            case 'S':
                srcRect = s;
                break;
            case 'c':
                srcRect = c;
                break;
            case 'o':
                srcRect = o;
                break;
            case 'r':
                srcRect = r;
                break;
            case 'e':
                srcRect = e;
                break;
            default:
                continue;
        }
        
        SDL_Rect dstRect = {scoreX, scoreY, 100, 100};

        SDL_BlitSurface(plancheSpritesAscii, &srcRect, win_surf, &dstRect);

        SDL_UpdateWindowSurface(pWindow);

        scoreX += srcRect.w;        
    }

    // Display lives
    char livesText[20];
    snprintf(livesText, sizeof(livesText), "Lives: %d", lives);

    int livesX = win_surf->w - 100;
    int livesY = 20;

    for (int i = 0; livesText[i] != '\0'; i++) {
        char currentDigit = livesText[i];

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
        
        SDL_Rect dstRect = {livesX, livesY, 100, 100};

        SDL_BlitSurface(plancheSpritesAscii, &srcRect, win_surf, &dstRect);

        SDL_UpdateWindowSurface(pWindow);

        livesX += srcRect.w;        
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


// Existing functions like drawMenuBar, drawGame, drawBricks...

void showGameOver() {
    SDL_Surface* surface = SDL_GetWindowSurface(pWindow);
    SDL_Color backgroundColor = {0, 0, 0};
    Uint32 background_color = SDL_MapRGB(surface->format, backgroundColor.r, backgroundColor.g, backgroundColor.b);
    SDL_FillRect(surface, NULL, background_color);

    const char* gameOverText = "game over";
    int wordLength = strlen(gameOverText);
    int wordX = (surface->w - wordLength * LETTER_SPRITE_WIDTH) / 2;
    int wordY = surface->h / 2;

    for (int ii = 0; ii < wordLength; ii++) {
        char currentLetter = gameOverText[ii];
        SDL_Rect src;

        switch (currentLetter) {
            case 'a': src = a; break;
            case 'b': src = b; break;
            case 'c': src = c; break;
            case 'd': src = d; break;
            case 'e': src = e; break;
            case 'f': src = f; break;
            case 'g': src = g; break;
            case 'h': src = h; break;
            case 'i': src = i; break;
            case 'j': src = j; break;
            case 'k': src = k; break;
            case 'l': src = l; break;
            case 'm': src = m; break;
            case 'n': src = n; break;
            case 'o': src = o; break;
            case 'p': src = p; break;
            case 'q': src = q; break;
            case 'r': src = r; break;
            case 's': src = s; break;
            case 't': src = t; break;
            case 'u': src = u; break;
            case 'v': src = v; break;
            case 'w': src = w; break;
            case 'x': src = x; break;
            case 'y': src = y; break;
            case 'z': src = z; break;
            case ' ': 
                wordX += LETTER_SPRITE_WIDTH; // Add space between words
                continue;
            default: 
                continue; // Skip any unrecognized characters
        }

        SDL_Rect letterDestRect = { wordX, wordY, LETTER_SPRITE_WIDTH, LETTER_SPRITE_HEIGHT };
        SDL_BlitSurface(plancheSpritesAscii, &src, surface, &letterDestRect);

        wordX += LETTER_SPRITE_WIDTH;
    }

    SDL_UpdateWindowSurface(pWindow);

    SDL_Event event;
    while (SDL_WaitEvent(&event)) {
        if (event.type == SDL_QUIT) {
            exit(0);
        } else if (event.type == SDL_KEYDOWN) {
            if (event.key.keysym.sym == SDLK_RETURN) {
                // Restart game
                lives = 3;
                score = 0;
                initBricks();
                ball.x = win_surf->w / 2;
                ball.y = win_surf->h / 2;
                ball.vx = 100.0;
                ball.vy = 140.0;
                currentState = GAME;
                return;
            }
        }
    }
}


void drawPowerUps(SDL_Surface* win_surf) {
    for (int i = 0; i < POWERUPS_MAX; i++) {
        if (!powerUps[i].surface.w) {
            continue;
        }

        SDL_Rect dstPowerUp = { powerUps[i].x, powerUps[i].y + MENU_HEIGHT, 16, 32 };

        SDL_BlitSurface(plancheSpritesBricks, &powerUps[i].surface, win_surf, &dstPowerUp);
    }
}
