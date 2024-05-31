#include "update.h"
#include "init.h"
#include <stdbool.h>
#include "constants.h"
#include "game_state.h"
#include "block.h"

Uint64 prev, now;
double delta_t = 0.0;  
bool firstTurn = true;

void updateGame() {

    if(firstTurn){
        prev = SDL_GetPerformanceCounter();;
        firstTurn = false;
        now = prev;
    }

    prev = now;
    now = SDL_GetPerformanceCounter();
    delta_t = (double)(now - prev) / SDL_GetPerformanceFrequency();

    //printf("fps : %f\n", 1/delta_t);

    ball.x += ball.vx * delta_t;
    ball.y += ball.vy * delta_t;

    if ((ball.x < 1) || (ball.x > (win_surf->w - 25)))
        ball.vx *= -1;
    if ((ball.y < 1) || (ball.y > (win_surf->h - 25)))
        ball.vy *= -1;

    //si la balle touche le block
    // Supposons que ballRect représente le rectangle de la balle    
    checkBallBrickCollision();
    
    // Si la balle touche la raquette, on la renvoie
    if ((ball.y > (win_surf->h - 50 - MENU_HEIGHT)) && (ball.x > x_vault) && (ball.x < x_vault + 100))
        ball.vy *= -1;

    if (ball.y > (win_surf->h - 25 - MENU_HEIGHT)){
        srcBall.y = 64;
        ball.vy = 0;
        ball.vx = 0;
    }
        
    if (ball.y < 1)
        srcBall.y = 96;

    const Uint8* keys = SDL_GetKeyboardState(NULL);
    if (keys[SDL_SCANCODE_LEFT])
        if(x_vault > 0){
            x_vault -= 1000 * delta_t;
        }
    if (keys[SDL_SCANCODE_RIGHT])
        if(x_vault < win_surf->w - 140){
            x_vault += 1000 * delta_t;
        }

    SDL_Delay((Uint32)1000/60);
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
    updatePowerUps();
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
                    printf("block destoyed with this powerup : %d\n", bricks[i][j].powerUp);
                    if(bricks[i][j].powerUp != 0){
                        printf("enter in the if statement: %d\n", bricks[i][j].powerUp);
                        generatePowerUp(bricks[i][j].powerUp, brick.x, brick.y);
                    }
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

void generatePowerUp(int powerUp, int x, int y){

    entities powerUpEntity;
    powerUpEntity.x = x;
    powerUpEntity.y = y;

    powerUpEntity.h = 16;
    powerUpEntity.w = 32;     

    powerUpEntity.vx = 0;
    powerUpEntity.vy = 100;


    switch (powerUp){
        case 1:
            powerUpEntity.surface = slow1;
            break;
        case 2: 
            powerUpEntity.surface = catch1;
            break;
        case 3: 
            powerUpEntity.surface = expand1;
            break;
        case 4: 
            powerUpEntity.surface = divide1;
            break;
        case 5:
            powerUpEntity.surface = laser1;
            break;
        case 6:
            powerUpEntity.surface = break1;
            break;
        default :
            printf("error in powerUp generation : the powerUp integer is not in acceptable value\n");
            break;
    }
    for (int i = 0; i < POWERUPS_MAX; i++){
        if(powerUps[i].surface.w == 0){
            powerUps[i] = powerUpEntity;
            break;
        }
    }
}

void updatePowerUps(){
    for (int i = 0; i < POWERUPS_MAX; i++){
        if(powerUps[i].surface.w != 0){
            powerUps[i].y += powerUps[i].vy * delta_t;
            printf("powerUp y : %d\n", powerUps[i].y);
            if(powerUps[i].y > win_surf->h){
                powerUps[i].surface.w = 0;
            }
        }
    }
}
        

