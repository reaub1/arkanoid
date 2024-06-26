#include "update.h"
#include "init.h"
#include <stdbool.h>
#include "constants.h"
#include "game_state.h"
#include "block.h"

Uint64 prev, now;
double delta_t = 0.0;  
bool firstTurn = true;

char activePowerUp = 'n';
int catchBall = 0;
int catched = 0;

void updateGame() {
    if (firstTurn) 
        prev = SDL_GetPerformanceCounter();
        initPowerUpsArray();
        initMonsterArray();
        initExplosionsArray();
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
    checkBallMonsterCollision();
    updateMonsters();
    updateExplosions();
    updateBalls();

    if (rand() % 100 == 0) {
        createMonster();
    }

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

    if (checkAllBricksDestroyed()) {
        loadNextLevel();
    }

    const Uint8* keys = SDL_GetKeyboardState(NULL);
    if (keys[SDL_SCANCODE_LEFT])
        if  (x_vault > 0)  {
            if(catched){
                ball.x -= 1000 * delta_t;
            }
            x_vault -= 1000 * delta_t;
        }
    if (keys[SDL_SCANCODE_RIGHT])
        if  (x_vault < win_surf->w - 140)  {
            if(catched){
                ball.x += 1000 * delta_t;
            }
            x_vault += 1000 * delta_t;
        }
    if( keys[SDL_SCANCODE_SPACE] && catched){
        catched = 0;
        catchBall = 0;
        ball.vx = 100.0;
        ball.vy = 140.0;
    }

    if(keys[SDL_SCANCODE_B]){
        generateBallExplosion(ball.x, ball.y);
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

void checkBallMonsterCollision(){
    for (int i = 0; i < MONSTERS_MAX; i++) {
        if (monsters[i].surface.w == 0) {
            continue;
        }

        SDL_Rect monsterRect;
        monsterRect.x = monsters[i].x;
        monsterRect.y = monsters[i].y-50;
        monsterRect.w = monsters[i].w;
        monsterRect.h = monsters[i].h;

        SDL_Rect ballRect;
        ballRect.x = ball.x;
        ballRect.y = ball.y;
        ballRect.w = 24;
        ballRect.h = 24;

        if (SDL_HasIntersection(&ballRect, &monsterRect)) {
            generateExplosion(monsterRect.x, monsterRect.y+32);
            score += 150;
            monsters[i] = (entities){0};
            drawMenuBar();
        }
    }
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
                    //printf("block destoyed with this powerup : %d\n", bricks[i][j].powerUp);
                    if(bricks[i][j].powerUp != 0){
                        //printf("enter in the if statement: %d\n", bricks[i][j].powerUp);
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

bool checkAllBricksDestroyed() {
    for (int i = 0; i < BRICK_ROWS; i++) {
        for (int j = 0; j < BRICK_COLUMNS; j++) {
            if (bricks[i][j].active) {
                return false;
            }
        }
    }
    return true;
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

    powerUpEntity.max_state = 7;


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
            //printf("error in powerUp generation : the powerUp integer is not in acceptable value\n");
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
                continue;
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

            if(catchBall){
                catched = 1;
                ball.vx = 0;
                ball.vy = 0;
            }
        }
    }
    for (int i = 0; i < POWERUPS_MAX; i++) {
        if (powerUps[i].surface.w == 0) {
            continue;
        }

        SDL_Rect powerUpRect;
        powerUpRect.x = powerUps[i].x;
        powerUpRect.y = powerUps[i].y-20;
        powerUpRect.w = powerUps[i].w;
        powerUpRect.h = powerUps[i].h;

        if (SDL_HasIntersection(&paddle, &powerUpRect)) {
            handlePowerUpCollision(&powerUps[i]);
            powerUps[i].surface.w = 0;
        }
    }

    for (int i = 0; i < MONSTERS_MAX; i++) {
        if (monsters[i].surface.w == 0) {
            continue;
        }

        SDL_Rect monsterRect;
        monsterRect.x = monsters[i].x;
        monsterRect.y = monsters[i].y-50;
        monsterRect.w = monsters[i].w;
        monsterRect.h = monsters[i].h;

        if (SDL_HasIntersection(&paddle, &monsterRect)) {
            generateExplosion(monsterRect.x, monsterRect.y+32);
            drawMenuBar();
            score += 150;
            monsters[i] = (entities){0};
        }
    }

}


void nextAnimation(entities *powerups, SDL_Rect Surfaces[]) {
    
    powerups->surface = Surfaces[powerups->state];
    if(powerups->state == powerUps->max_state)
        powerups->state = 0;
    else
        powerups->state++;
}

void handlePowerUpCollision(entities *powerUp) {

    if(activePowerUp != 'n'){
        deactivatePowerUp(powerUp->type);
        return;
    }
    switch (powerUp->type) {
        case 's':
            // Slow ball
            ball.vx = ball.vx/2;
            ball.vy = ball.vy/2;
            activePowerUp = 's';
            break;
        case 'c':
            // Catch ball (example effect)
            catchBall = 1;
            activePowerUp = 'c';
            break;
        case 'e':
            // Expand paddle
            //paddle.w += 50;
            break;
        case 'd':
            // Divide
            //generateBallExplosion(ball.x, ball.y);

            break;
        case 'l':
            //laser
            break;
        case 'b':
            // Break 
            lives++;
            drawMenuBar();
            break;
        default:
            //printf("Unknown power-up type: %c\n", powerUp->type);
            break;
    }
}

void createMonster(){
        int monsterType = rand() % 3;
        int xPos = rand() % (win_surf->w - 64);
        int yPos = 0;

        entities monster;
        monster.x = xPos;
        monster.y = yPos;
        monster.h = 32;
        monster.w = 32;
        monster.vx = 100;
        monster.vy = 100;
        monster.state = 0;
        monster.time = 0;
        
        switch (monsterType) {
            case 0:
                monster.surface = nasser[0];
                monster.type = 'n';
                monster.max_state = 7;
                break;
            case 1:
                monster.surface = farah[0];
                monster.type = 'f';
                monster.max_state = 11;
                break;
            case 2:
                monster.surface = leyna[0];
                monster.type = 'l';
                monster.max_state = 24;
                break;
            default:
                printf("Unknown monster type: %d\n", monsterType);
                return;
        }

        for (int i = 0; i < MONSTERS_MAX; i++) {
            if (monsters[i].surface.w == 0) {
                monsters[i] = monster;
                break;
            }
        }
}

void updateMonsters(){
    const float TIME_RESET = 0.1;

    for (int i = 0; i < MONSTERS_MAX; i++){
       
            if(monsters[i].y > win_surf->h){
                monsters[i].surface.w = 0;
                continue;
            }

            monsters[i].time -= delta_t;

            if ((rand() / (float)RAND_MAX) < MOVE_PROBABILITY) {
                monsters[i].vx = -monsters[i].vx;
            }

            monsters[i].x += monsters[i].vx * delta_t;
            monsters[i].y += monsters[i].vy * delta_t;

            if(monsters[i].time < 0.0){

                switch (monsters[i].type)
                {  
                    case 'n':
                        nextAnimation(&monsters[i], nasser);
                        break;
                    case 'f':
                        nextAnimation(&monsters[i], farah);
                        break;
                    case 'l':
                        nextAnimation(&monsters[i], leyna);
                        break;
                    default:
                        break;
                }
                monsters[i].time = TIME_RESET;
            }
    }
}

void generateExplosion(int x, int y){

    entities explosion;
    explosion.x = x;
    explosion.y = y;
    explosion.h = 32;
    explosion.w = 32;
    explosion.vx = 0;
    explosion.vy = 0;
    explosion.state = 0;
    explosion.time = 0.1;
    explosion.max_state = 5;
    explosion.surface = explosionsSurface[0];

    for (int i = 0; i < EXPLOSIONS_MAX; i++){
        if(explosions[i].surface.w == 0){
            explosions[i] = explosion;
            break;
        }
    }
}

void updateExplosions(){
    const float TIME_RESET = 0.1;
    for (int i = 0; i < EXPLOSIONS_MAX; i++){
        if(explosions[i].surface.w != 0){
            explosions[i].time -= delta_t;
            if(explosions[i].time < 0){
                nextAnimation(&explosions[i], explosionsSurface);
                explosions[i].time = TIME_RESET;
            }
            if(explosions[i].state == explosions[i].max_state){
                explosions[i] = (entities){0};
            }
        }
    }
}

void deactivatePowerUp(char type){
    printf("desactive powerups");
    switch (type)
    {
        case 's':
            ball.vx = ball.vx*2;
            ball.vy = ball.vy*2;
            break;
        case 'e':
            //paddle.w = 50;
            break;
        case 'c':
            catchBall = 0;
            break;
        
        default:
            break;
    }
}

void generateBallExplosion(int x, int y){
    entities ball;
    ball.x = x;
    ball.y = y;
    ball.h = 24;
    ball.w = 24;
    ball.vx = rand() % 200 - 100;
    ball.vy = rand() % 200 - 100;

    ball.surface = srcBall;

    for(int i = 0; i<64; i++){
        if(balls[i].surface.w == 0){
            balls[i] = ball;
            break;
        }
    }
}

void updateBalls(){
    for (int i = 0; i < 64; i++){
        if(balls[i].surface.w != 0){
            balls[i].x += balls[i].vx * delta_t;
            balls[i].y += balls[i].vy * delta_t;
        }
    }
}