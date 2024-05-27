#include "update.h"
#include "init.h"
#include <stdbool.h>
#include "constants.h"
#include "game_state.h"

Uint64 prev, now;
double delta_t = 0.0;  
bool firstTurn = true;

void updateGame() {
    if (firstTurn) {
        prev = SDL_GetPerformanceCounter();
        firstTurn = false;
    }

    ball.x += ball.vx * delta_t;
    ball.y += ball.vy * delta_t;

    if (ball.x < 1 || ball.x > (win_surf->w - BALL_SPRITE_WIDTH)) {
        ball.vx *= -1;
    }
    if (ball.y < 1) {
        ball.vy *= -1;
    }

    if (ball.y > (win_surf->h - BALL_SPRITE_HEIGHT - MENU_HEIGHT)) {
        lives--;
        if (lives > 0) {
            currentState = WAITING_TO_RESTART;
        } else {
            currentState = GAME_OVER;
        }
    }

    if ((ball.y > (win_surf->h - 50 - MENU_HEIGHT)) && (ball.x > x_vault) && (ball.x < x_vault + 100)) {
        ball.vy *= -1;
    }

    const Uint8* keys = SDL_GetKeyboardState(NULL);
    if (keys[SDL_SCANCODE_LEFT]) {
        if (x_vault > 0) {
            x_vault -= 1;
        }
    }
    if (keys[SDL_SCANCODE_RIGHT]) {
        if (x_vault < win_surf->w - 100) {
            x_vault += 1;
        }
    }

    now = SDL_GetPerformanceCounter();
    delta_t = 1.0 / FPS - ((double)(now - prev) / SDL_GetPerformanceFrequency() * 1000);
    prev = now;
    if (delta_t > 0) {
        SDL_Delay((Uint32)(delta_t * 1000));
    }

    checkBallBrickCollision();
}


bool processInput() {
    SDL_Event event;
    while (SDL_PollEvent(&event)) {
        if (event.type == SDL_QUIT) {
            return true;
        } else if (event.type == SDL_KEYDOWN) {
            if (currentState == MENU) {
                if (event.key.keysym.sym == SDLK_RETURN) {
                    currentState = GAME;
                }
            } else if (currentState == WAITING_TO_RESTART) {
                if (event.key.keysym.sym == SDLK_SPACE) {
                    // Reset ball position and state
                    ball.x = win_surf->w / 2;
                    ball.y = win_surf->h / 2;
                    ball.vx = 0.1;
                    ball.vy = 0.14;
                    currentState = GAME;
                }
            } else if (currentState == GAME_OVER) {
                if (event.key.keysym.sym == SDLK_SPACE) {
                    // Reset game state
                    score = 0;
                    lives = 3;
                    level = 1;
                    turn = 0;
                    currentState = MENU;
                    initGame();
                }
            } else if (event.key.keysym.sym == SDLK_ESCAPE) {
                return true;
            }
        }
    }
    return false;
}

void checkBallBrickCollision() {
    for (int i = 0; i < BRICK_ROWS; i++) {
        for (int j = 0; j < BRICK_COLUMNS; j++) {
            SDL_Rect brick;
            if(!bricks[i][j].active){
                continue;
            }
            brick.x = bricks[0][0].rect.x + j * INDIVIDUAL_BRICK_WIDTH;
            brick.y = bricks[0][0].rect.y + i * INDIVIDUAL_BRICK_HEIGHT - MENU_HEIGHT;
            brick.w = INDIVIDUAL_BRICK_WIDTH;
            brick.h = INDIVIDUAL_BRICK_HEIGHT;

            if (ball.x < brick.x + brick.w &&
                ball.x + 24 > brick.x &&
                ball.y < brick.y + brick.h &&
                ball.y + 24 > brick.y) {

                int ballCenterX = ball.x + 12;
                int ballCenterY = ball.y + 12; 

                int brickCenterX = brick.x + brick.w / 2;
                int brickCenterY = brick.y + brick.h / 2;

                int distX = abs(ballCenterX - brickCenterX);
                int distY = abs(ballCenterY - brickCenterY);

                int combinedHalfWidths = 12 + brick.w / 2;
                int combinedHalfHeights = 12 + brick.h / 2;

                int overlapX = combinedHalfWidths - distX;
                int overlapY = combinedHalfHeights - distY;

                if (overlapX > 0 && overlapY > 0) {
                    if (overlapX > overlapY) {
                        if (ballCenterY < brickCenterY) {
                            ball.y -= overlapY;
                            ball.vy = -ball.vy;
                        } else {
                            ball.y += overlapY;
                            ball.vy = -ball.vy;
                        }
                    } else {
                        ball.x += overlapX;
                        ball.vx = -ball.vx;
                    }

                if(bricks[i][j].isDestructible){
                    bricks[i][j].active = false;
                    score += bricks[i][j].points;
                    //updateMenu
                    drawMenuBar();
                }    
                }
                return; 
            }
        }
    }
}

