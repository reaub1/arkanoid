#include "init.h"
#include "game_state.h"
#include "block.h"

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
    if(plancheSpritesBricks == NULL) {
        SDL_Log("Erreur lors du chargement de Arkanoid_sprites.bmp : %s", SDL_GetError());
        SDL_DestroyWindow(pWindow);
        SDL_Quit();
        exit(1);
    }
    SDL_SetColorKey(plancheSpritesBricks, SDL_TRUE, 0);

    plancheSpritesAscii = SDL_LoadBMP("./Arkanoid_ascii.bmp");
    if(plancheSpritesAscii == NULL) {
        SDL_Log("Erreur lors du chargement de Arkanoid_ascii.bmp : %s", SDL_GetError());
        SDL_DestroyWindow(pWindow);
        SDL_Quit();
        exit(1);
    }
    //SDL_SetColorKey(plancheSpritesAscii, SDL_TRUE, 0);
    
    ball.x = win_surf->w / 2;
    ball.y = win_surf->h / 2;
    ball.vx = 100.0;
    ball.vy = 140.0;

    x_vault = win_surf->w / 2;

    initBricks();
    loadHighScore();
    initPowerUps();
}

void initPowerUps(){
    memset(powerUps, 0, sizeof(powerUps));
}

void initBricks() {
    // Clear the bricks array
    memset(bricks, 0, sizeof(bricks));

    char level[MAX_ROWS][MAX_COLS * 2 + 1];  // Adjusted to read two characters per column
    readTextFile("./level/lvl4.txt", level, '#');

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
                printf("Brick at (%d, %d): Type: %c, Power: %d, Active: %d, Color: (%d, %d, %d, %d), Points: %d\n",
                       i, j, brickType, powerUp, active, color.x, color.y, color.w, color.h, points);
            }
        }
    }
}

void readTextFile(const char* filename, char array[MAX_ROWS][MAX_COLS * 2 + 1], char endChar) {
    // Clear the level array
    memset(array, '\0', sizeof(char) * MAX_ROWS * (MAX_COLS * 2 + 1));

    FILE* file = fopen(filename, "r");
    if (file == NULL) {
        printf("Erreur: Impossible d'ouvrir le fichier %s\n", filename);
        exit(EXIT_FAILURE);
    }

    int row = 0;
    char line[MAX_COLS * 2 + 2]; // +2 to handle '\n' and '\0'

    while (fgets(line, sizeof(line), file) != NULL) {
        if (line[0] == endChar) {
            break;
        }

        if (row >= MAX_ROWS) {
            printf("Avertissement: Nombre de lignes dépasse la limite, seules les %d premières lignes seront lues.\n", MAX_ROWS);
            break;
        }

        int col = 0;
        for (int i = 0; line[i] != '\0' && line[i] != '\n'; i += 2) { // Increment by 2 to read pairs of characters
            if (col >= MAX_COLS * 2) {
                printf("Avertissement: Nombre de colonnes dépasse la limite, seules les %d premières colonnes seront lues pour la ligne %d.\n", MAX_COLS, row + 1);
                break;
            }
            array[row][col] = line[i];
            array[row][col + 1] = line[i + 1];
            col += 2;
        }
        array[row][col] = '\0';
        printf("Loaded line %d: %s\n", row, array[row]);
        row++;
    }

    fclose(file);
}