#include "update.h"
#include "init.h"
#include <stdbool.h>
#include "constants.h"
#include "game_state.h"

Uint64 prev, now;
double delta_t = 0.0;  

void updateGame() {

    ball.x += ball.vx;
    ball.y += ball.vy;

    if ((ball.x < 1) || (ball.x > (win_surf->w - 25)))
        ball.vx *= -1;
    if ((ball.y < 1) || (ball.y > (win_surf->h - 25)))
        ball.vy *= -1;

    //si la balle tocuhe le block
    // Supposons que ballRect représente le rectangle de la balle    
    checkBallBrickCollision();
    
    // Si la balle touche la raquette, on la renvoie
    if ((ball.y > (win_surf->h - 50 - MENU_HEIGHT)) && (ball.x > x_vault) && (ball.x < x_vault + 100))
        ball.vy *= -1;

    if (ball.y > (win_surf->h - 25)){
        srcBall.y = 64;
        ball.vy = 0;
        ball.vx = 0;
    }
        
    if (ball.y < 1)
        srcBall.y = 96;

    const Uint8* keys = SDL_GetKeyboardState(NULL);
    if (keys[SDL_SCANCODE_LEFT])
        if(x_vault > 0){
            x_vault -= 10;
        }
    if (keys[SDL_SCANCODE_RIGHT])
        if(x_vault < win_surf->w - 100){
            x_vault += 10;
        }
    now = SDL_GetPerformanceCounter();
    delta_t = 1.0 / FPS - ((double)(now - prev) / SDL_GetPerformanceFrequency());
    prev = now;
    if (delta_t > 0)
        SDL_Delay((Uint32)(delta_t * 1000));
}

bool processInput() {
    SDL_Event event;
    while (SDL_PollEvent(&event)) {
        if (event.type == SDL_QUIT) {
            return true;
        } else if (event.type == SDL_KEYDOWN) {
            if (event.key.keysym.sym == SDLK_RETURN && currentState == MENU) {
                currentState = GAME;
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
                }    
                }
                return; 
            }
        }
    }
}

