#include "update.h"
#include "init.h"
#include <stdbool.h>
#include "constants.h"
#include "game_state.h"
#include "block.h"

Uint64 prev, now;
double delta_t = 0.0;  
bool firstTurn = true;

SDL_Rect SlowSurfaces[8];
SDL_Rect CatchSurfaces[8];
SDL_Rect ExpandSurfaces[8];
SDL_Rect DivideSurfaces[8];
SDL_Rect LaserSurfaces[8];
SDL_Rect BreakSurfaces[8];
SDL_Rect PlayerSurfaces[8];


void updateGame() {
    if (firstTurn) 
        prev = SDL_GetPerformanceCounter();
        initPowerUpsArray();
    if (firstTurn) {
        prev = SDL_GetPerformanceCounter();;
        firstTurn = false;
        now = prev;
    }

    prev = now;
    now = SDL_GetPerformanceCounter();
    delta_t = (double)(now - prev) / SDL_GetPerformanceFrequency();

    ball.x += ball.vx * delta_t;
    ball.y += ball.vy * delta_t;

    if ((ball.x < 1) || (ball.x > (win_surf->w - 25)))
        ball.vx *= -1;
    if ((ball.y < 1) || (ball.y > (win_surf->h - 25)))
        ball.vy *= -1;

    checkBallBrickCollision();
    checkCollisionPaddle();

    if (ball.y > (win_surf->h - 25 - MENU_HEIGHT)) {
        srcBall.y = 64;
        ball.vy = 0;
        ball.vx = 0;
    }

    if (ball.y < 1)
        srcBall.y = 96;
    if (ball.y > (win_surf->h - 25 - MENU_HEIGHT)) {
        lives--;
        if (lives <= 0) {
            currentState = GAME_OVER;
            if (score > highScore) {
                highScore = score;
                saveHighScore();
            }
        } else {
            ball.x = win_surf->w / 2;
            ball.y = win_surf->h / 2;
            ball.vx = 100.0;
            ball.vy = 140.0;
        }
    }

    const Uint8* keys = SDL_GetKeyboardState(NULL);
    if (keys[SDL_SCANCODE_LEFT])
        if  (x_vault > 0)  {
            x_vault -= 1000 * delta_t;
        }
    if (keys[SDL_SCANCODE_RIGHT])
        if  (x_vault < win_surf->w - 140)  {
            x_vault += 1000 * delta_t;
        }

    SDL_Delay((Uint32)1000 / 60);
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

    powerUpEntity.state = 1;
    powerUpEntity.time = 0.1;


    switch (powerUp){
        case 1:
            powerUpEntity.surface = slow1;
            powerUpEntity.type = 's';
            break;
        case 2: 
            powerUpEntity.surface = catch1;
            powerUpEntity.type = 'c';
            break;
        case 3: 
            powerUpEntity.surface = expand1;
            powerUpEntity.type = 'e';
            break;
        case 4: 
            powerUpEntity.surface = divide1;
            powerUpEntity.type = 'd';
            break;
        case 5:
            powerUpEntity.surface = laser1;
            powerUpEntity.type = 'l';
            break;
        case 6:
            powerUpEntity.surface = break1;
            powerUpEntity.type = 'b';
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
    const float TIME_RESET = 0.1;

    for (int i = 0; i < POWERUPS_MAX; i++){
        if(powerUps[i].surface.w != 0){
            powerUps[i].y += powerUps[i].vy * delta_t;

            if(powerUps[i].y > win_surf->h){
                powerUps[i].surface.w = 0;
                continue; // Skip to the next power-up since this one is now inactive
            }

            powerUps[i].time -= delta_t;
            if(powerUps[i].time < 0){

                switch (powerUps[i].type)
                {
                    case 's':
                        nextAnimation(&powerUps[i], SlowSurfaces);
                        break;
                    case 'c':
                        nextAnimation(&powerUps[i], CatchSurfaces);
                        break;
                    case 'e':
                        nextAnimation(&powerUps[i], ExpandSurfaces);
                        break;
                    case 'd':
                        nextAnimation(&powerUps[i], DivideSurfaces);
                        break;
                    case 'l':
                        nextAnimation(&powerUps[i], LaserSurfaces);
                        break;
                    case 'b':
                        nextAnimation(&powerUps[i], BreakSurfaces);
                        break;
                    default:
                        break;
                        
                }
                powerUps[i].time = TIME_RESET;
            }
        }
    }
}
void checkCollisionPaddle() {
    SDL_Rect paddle;
    paddle.x = x_vault;
    paddle.y = win_surf->h - 50 - MENU_HEIGHT;
    paddle.w = 100;
    paddle.h = 20;

    int ballCenterX = ball.x + 12;
    int ballCenterY = ball.y + 12;

    int paddleCenterX = paddle.x + paddle.w / 2;
    int paddleCenterY = paddle.y + paddle.h / 2;

    if (ball.x < paddle.x + paddle.w &&
        ball.x > paddle.x &&
        ball.y < paddle.y + paddle.h &&
        ball.y > paddle.y) {

        int distX = abs(ballCenterX - paddleCenterX);
        int distY = abs(ballCenterY - paddleCenterY);

        int combinedHalfWidths = 12 + paddle.w / 2;
        int combinedHalfHeights = 12 + paddle.h / 2;

        int overlapX = combinedHalfWidths - distX;
        int overlapY = combinedHalfHeights - distY;

        if (overlapX > 0 && overlapY > 0) {
            float relativeImpact = (float)(ballCenterX - paddle.x) / (float)paddle.w;
            float angle = (relativeImpact - 0.5f) * 2.0f * MAX_BOUNCE_ANGLE;

            ball.vx = BALL_SPEED * cos(angle);
            ball.vy = -BALL_SPEED * sin(angle);
        }
    }
}
void initPowerUpsArray(){
    SlowSurfaces[0] = slow1;
    SlowSurfaces[1] = slow2;
    SlowSurfaces[2] = slow3;
    SlowSurfaces[3] = slow4;
    SlowSurfaces[4] = slow5;
    SlowSurfaces[5] = slow6;
    SlowSurfaces[6] = slow7;
    SlowSurfaces[7] = slow8;

    CatchSurfaces[0] = catch1;
    CatchSurfaces[1] = catch2;
    CatchSurfaces[2] = catch3;
    CatchSurfaces[3] = catch4;
    CatchSurfaces[4] = catch5;
    CatchSurfaces[5] = catch6;
    CatchSurfaces[6] = catch7;
    CatchSurfaces[7] = catch8;

    ExpandSurfaces[0] = expand1;
    ExpandSurfaces[1] = expand2;
    ExpandSurfaces[2] = expand3;
    ExpandSurfaces[3] = expand4;
    ExpandSurfaces[4] = expand5;
    ExpandSurfaces[5] = expand6;
    ExpandSurfaces[6] = expand7;
    ExpandSurfaces[7] = expand8;

    DivideSurfaces[0] = divide1;
    DivideSurfaces[1] = divide2;
    DivideSurfaces[2] = divide3;
    DivideSurfaces[3] = divide4;
    DivideSurfaces[4] = divide5;
    DivideSurfaces[5] = divide6;
    DivideSurfaces[6] = divide7;
    DivideSurfaces[7] = divide8;

    LaserSurfaces[0] = laser1;
    LaserSurfaces[1] = laser2;
    LaserSurfaces[2] = laser3;
    LaserSurfaces[3] = laser4;
    LaserSurfaces[4] = laser5;
    LaserSurfaces[5] = laser6;
    LaserSurfaces[6] = laser7;
    LaserSurfaces[7] = laser8;

    BreakSurfaces[0] = break1;
    BreakSurfaces[1] = break2;
    BreakSurfaces[2] = break3;
    BreakSurfaces[3] = break4;
    BreakSurfaces[4] = break5;
    BreakSurfaces[5] = break6;
    BreakSurfaces[6] = break7;
    BreakSurfaces[7] = break8;

    PlayerSurfaces[0] = player1;
    PlayerSurfaces[1] = player2;
    PlayerSurfaces[2] = player3;
    PlayerSurfaces[3] = player4;
    PlayerSurfaces[4] = player5;
    PlayerSurfaces[5] = player6;
    PlayerSurfaces[6] = player7;
    PlayerSurfaces[7] = player8;
}

void nextAnimation(entities *powerups, SDL_Rect slowSurfaces[]) {
    
    powerups->surface = slowSurfaces[powerups->state];
    if(powerups->state == 7)
        powerups->state = 0;
    else
        powerups->state++;
}