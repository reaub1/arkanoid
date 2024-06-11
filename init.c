#include "init.h"
#include "game_state.h"
#include "block.h"
#include <SDL.h>
#include <stdio.h>
#include <stdlib.h>

SDL_Window* pWindow = NULL;
SDL_Surface* win_surf = NULL;
SDL_Surface* plancheSprites = NULL;
SDL_Surface* plancheSpritesBricks = NULL;
SDL_Surface* plancheSpritesAscii = NULL;

SDL_Rect srcBall = { 0, 96, 24, 24 };
SDL_Rect scrVaiss = { 128, 0, 128, 32 };

SDL_Renderer* renderer = NULL;
Brick bricks[BRICK_ROWS][BRICK_COLUMNS] = {0};
entities powerUps[POWERUPS_MAX] = {0};
entities monsters[MONSTERS_MAX] = {0};
entities explosions[EXPLOSIONS_MAX] = {0};
entities balls[MAX_BALLS] = {0};

SDL_Rect SlowSurfaces[8];
SDL_Rect CatchSurfaces[8];
SDL_Rect ExpandSurfaces[8];
SDL_Rect DivideSurfaces[8];
SDL_Rect LaserSurfaces[8];
SDL_Rect BreakSurfaces[8];
SDL_Rect PlayerSurfaces[8];

SDL_Rect nasser[8];
SDL_Rect farah[11];
SDL_Rect leyna[24];

SDL_Rect explosionsSurface[6];


SDL_Rect block;

Ball ball;

int x_vault = 0;

extern int highScore;
extern const char* highScoreFile;

void loadHighScore() {
    FILE* file = fopen(highScoreFile, "r");
    if (file) {
        fscanf(file, "%d", &highScore);
        fclose(file);
    }
}

void saveHighScore() {
    FILE* file = fopen(highScoreFile, "w");
    if (file) {
        fprintf(file, "%d", highScore);
        fclose(file);
    }
}

void initGame() {
    block.x = 0;
    block.y = 0;
    block.w = 50; 
    block.h = 50;

    currentState = MENU;

    pWindow = SDL_CreateWindow("Arkanoid", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, 416, 600, SDL_WINDOW_SHOWN);
    if (pWindow == NULL) {
        SDL_Log("Erreur lors de la création de la fenêtre : %s", SDL_GetError());
        SDL_Quit();
        exit(1);
    }

    renderer = SDL_CreateRenderer(pWindow, -1, SDL_RENDERER_SOFTWARE);

    win_surf = SDL_GetWindowSurface(pWindow);
    if (win_surf == NULL) {
        SDL_Log("Erreur lors de l'obtention de la surface de la fenêtre : %s", SDL_GetError());
        SDL_DestroyWindow(pWindow);
        SDL_Quit();
        exit(1);
    }

    plancheSprites = SDL_LoadBMP("./sprites.bmp");
    if (plancheSprites == NULL) {
        SDL_Log("Erreur lors du chargement de sprites.bmp : %s", SDL_GetError());
        SDL_DestroyWindow(pWindow);
        SDL_Quit();
        exit(1);
    }
    SDL_SetColorKey(plancheSprites, SDL_TRUE, 0);

    plancheSpritesBricks = SDL_LoadBMP("./Arkanoid_sprites.bmp");
    if (plancheSpritesBricks == NULL) {
        SDL_Log("Erreur lors du chargement de Arkanoid_sprites.bmp : %s", SDL_GetError());
        SDL_DestroyWindow(pWindow);
        SDL_Quit();
        exit(1);
    }
    SDL_SetColorKey(plancheSpritesBricks, SDL_TRUE, 0);

    plancheSpritesAscii = SDL_LoadBMP("./Arkanoid_ascii.bmp");
    if (plancheSpritesAscii == NULL) {
        SDL_Log("Erreur lors du chargement de Arkanoid_ascii.bmp : %s", SDL_GetError());
        SDL_DestroyWindow(pWindow);
        SDL_Quit();
        exit(1);
    }

    ball.x = win_surf->w / 2;
    ball.y = win_surf->h / 2;
    ball.vx = 100.0;
    ball.vy = 140.0;

    x_vault = win_surf->w / 2;

    initBricks();
    loadHighScore();
}

void loadNextLevel() {
    currentLevelIndex++;
    if (currentLevelIndex >= totalLevels) {
        currentLevelIndex = 0; 
    }
    initBricks();

    ball.x = win_surf->w / 2;
    ball.y = win_surf->h / 2;
    ball.vx = 100.0;
    ball.vy = 140.0;

    x_vault = win_surf->w / 2;
}


void initBricks() {
    memset(bricks, 0, sizeof(bricks));

    char level[MAX_ROWS][MAX_COLS * 2 + 1];
    readTextFile(levelFiles[currentLevelIndex], level, '#');

    for (int i = 0; i < MAX_ROWS; i++) {
        for (int j = 0; j < MAX_COLS; j++) {
            SDL_Rect color = {0};
            bool active = true;
            bool isDestructible = true;
            bool update = false;
            int points = 0;
            int powerUp = 0;
            int life = 1;
            int type = 0; // Assuming NORMAL_BRICK is 0

            char brickType = level[i][j * 2];      // First character for brick type
            char brickPower = level[i][j * 2 + 1]; // Second character for brick power

            if (brickType == '\0' || brickType == '#') {
                active = false;
            } else {
                switch (brickType) {
                    case 'r':
                        color = redbrick;
                        points = 90;
                        break;
                    case 'o':
                        color = orangebrick;
                        points = 60;
                        break;
                    case 'w':
                        color = whitebrick;
                        points = 50;
                        break;
                    case 'b':
                        color = bluebrick;
                        break;
                    case 'm':
                        color = magentabrick;
                        break;
                    case 'l':
                        color = bluelightbrick;
                        points = 70;
                        break;
                    case 'g':
                        color = greenbrick;
                        points = 80;
                        break;
                    case 'n':
                        color = navybrick;
                        points = 100;
                        break;
                    case 'd':
                        color = darkgreenbrick;
                        break;
                    case 'p':
                        color = pinkbrick;
                        points = 110;
                        break;
                    case 'y':
                        color = yellowbrick;
                        points = 120;
                        break;
                    case 'f':
                        color = darkredbrick;
                        break;
                    case 's':
                        color = silverbrick1;
                        life = 3;
                        type = 1; // Assuming SPECIAL_BRICK is 1
                        break;
                    case 'z':
                        color = goldbrick1;
                        isDestructible = false;
                        update = true;
                        type = 1; // Assuming SPECIAL_BRICK is 1
                        break;
                    case 'q':
                        color = ball1;
                        break;
                    default:
                        active = false;
                        break;
                }

                powerUp = brickPower - '0'; // Convert the power character to an integer (assuming '0' to '9')
            }

            bricks[i][j].rect.x = j * BRICK_WIDTH;
            bricks[i][j].rect.y = i * BRICK_HEIGHT + MENU_HEIGHT;
            bricks[i][j].rect.w = BRICK_WIDTH;
            bricks[i][j].rect.h = BRICK_HEIGHT;
            bricks[i][j].active = active;
            bricks[i][j].color = color;
            bricks[i][j].update = update;
            bricks[i][j].life = life;
            bricks[i][j].powerUp = powerUp;
            bricks[i][j].type = type;
            bricks[i][j].isDestructible = isDestructible;
            bricks[i][j].points = points;
            bricks[i][j].transform = 0;

            // Logging for debugging
            if (active) {
                //printf("Brick at (%d, %d): Type: %c, Power: %d, Active: %d, Color: (%d, %d, %d, %d), Points: %d\n",
                //       i, j, brickType, powerUp, active, color.x, color.y, color.w, color.h, points);
            }
        }
    }
}

void readTextFile(const char* filename, char array[MAX_ROWS][MAX_COLS * 2 + 1], char endChar) {
    // Clear the level array
    memset(array, '\0', sizeof(char) * MAX_ROWS * (MAX_COLS * 2 + 1));

    FILE* file = fopen(filename, "r");
    if (file == NULL) {
        //printf("Erreur: Impossible d'ouvrir le fichier %s\n", filename);
        exit(EXIT_FAILURE);
    }

    int row = 0;
    char line[MAX_COLS * 2 + 2]; // +2 to handle '\n' and '\0'

    while (fgets(line, sizeof(line), file) != NULL) {
        if (line[0] == endChar) {
            break;
        }

        if (row >= MAX_ROWS) {
            //printf("Avertissement: Nombre de lignes dépasse la limite, seules les %d premières lignes seront lues.\n", MAX_ROWS);
            break;
        }

        int col = 0;
        for (int i = 0; line[i] != '\0' && line[i] != '\n'; i += 2) { // Increment by 2 to read pairs of characters
            if (col >= MAX_COLS * 2) {
                //printf("Avertissement: Nombre de colonnes dépasse la limite, seules les %d premières colonnes seront lues pour la ligne %d.\n", MAX_COLS, row + 1);
                break;
            }
            array[row][col] = line[i];
            array[row][col + 1] = line[i + 1];
            col += 2;
        }
        array[row][col] = '\0';
        //printf("Loaded line %d: %s\n", row, array[row]);
        row++;
    }

    fclose(file);
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

void initMonsterArray(){
    nasser[0] = nasser1;
    nasser[1] = nasser2;
    nasser[2] = nasser3;
    nasser[3] = nasser4;
    nasser[4] = nasser5;
    nasser[5] = nasser6;
    nasser[6] = nasser7;
    nasser[7] = nasser8;

    farah[0] = farah1;
    farah[1] = farah2;
    farah[2] = farah3;
    farah[3] = farah4;
    farah[4] = farah5;
    farah[5] = farah6;
    farah[6] = farah7;
    farah[7] = farah8;
    farah[8] = farah9;
    farah[9] = farah10;
    farah[10] = farah11;

    leyna[0] = leyna1;
    leyna[1] = leyna2;
    leyna[2] = leyna3;
    leyna[3] = leyna4;
    leyna[4] = leyna5;
    leyna[5] = leyna6;
    leyna[6] = leyna7;
    leyna[7] = leyna8;
    leyna[8] = leyna9;
    leyna[9] = leyna10;
    leyna[10] = leyna11;
    leyna[11] = leyna12;
    leyna[12] = leyna13;
    leyna[13] = leyna14;
    leyna[14] = leyna15;
    leyna[15] = leyna16;
    leyna[16] = leyna17;
    leyna[17] = leyna18;
    leyna[18] = leyna19;
    leyna[19] = leyna20;
    leyna[20] = leyna21;
    leyna[21] = leyna22;
    leyna[22] = leyna23;
    leyna[23] = leyna24;
}

void initExplosionsArray(){
    explosionsSurface[0] = explosion1;
    explosionsSurface[1] = explosion2;
    explosionsSurface[2] = explosion3;
    explosionsSurface[3] = explosion4;
    explosionsSurface[4] = explosion5;
    explosionsSurface[5] = explosion6;
}