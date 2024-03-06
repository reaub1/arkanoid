#include <SDL.h>
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>


#define BRICK_SPRITE_WIDTH 191
#define BRICK_SPRITE_HEIGHT 63

#define BRICK_WIDTH BRICK_SPRITE_WIDTH  
#define BRICK_HEIGHT BRICK_SPRITE_HEIGHT 

#define BRICK_ROWS 4
#define BRICK_COLUMNS 6
#define INDIVIDUAL_BRICK_WIDTH 30
#define INDIVIDUAL_BRICK_HEIGHT 14
#define BRICK_PADDING 0 


struct Brick {
    SDL_Rect rect; 
    bool active;   
} bricks[BRICK_ROWS][BRICK_COLUMNS];


const int FPS=160.0;
//struct { double x; double y; } ball_speed;
struct { double x; double y;  double vx; double vy;} ball;

Uint64 prev, now; // timers
double delta_t;  // durée frame en ms
int x_vault;

SDL_Window* pWindow = NULL;
SDL_Surface* win_surf = NULL;
SDL_Surface* plancheSprites = NULL;
SDL_Surface* plancheSpritesBricks = NULL;


SDL_Rect srcBg = { 0,128, 96,128 }; // x,y, w,h (0,0) en haut a gauche
SDL_Rect srcBall = { 0,96,24,24 };
SDL_Rect scrVaiss = { 128,0,128,32 };
SDL_Rect srcBrick = {0, 0, BRICK_SPRITE_WIDTH, BRICK_SPRITE_HEIGHT};


const int paddleWidth = 128; 
const int paddleHeight = 32; 

void initBricks() {
    int startX = (win_surf->w - BRICK_WIDTH) / 2;
    int startY = (win_surf->h - BRICK_HEIGHT) / 2 - 150;

    bricks[0][0].rect.x = startX;
    bricks[0][0].rect.y = startY;
    bricks[0][0].rect.w = BRICK_WIDTH;
    bricks[0][0].rect.h = BRICK_HEIGHT;
    bricks[0][0].active = true;
}



void drawBricks(SDL_Surface* win_surf) {
    for (int i = 0; i < BRICK_ROWS; i++) {
        for (int j = 0; j < BRICK_COLUMNS; j++) {
            if (bricks[i][j].active) {
                SDL_BlitSurface(plancheSpritesBricks, &srcBrick, win_surf, &bricks[i][j].rect);
            }
        }
    }
}

void checkBallBrickCollision() {
    for (int i = 0; i < BRICK_ROWS; i++) {
        for (int j = 0; j < BRICK_COLUMNS; j++) {
            SDL_Rect brick;
            brick.x = bricks[0][0].rect.x + j * INDIVIDUAL_BRICK_WIDTH;
            brick.y = bricks[0][0].rect.y + i * INDIVIDUAL_BRICK_HEIGHT;
            brick.w = INDIVIDUAL_BRICK_WIDTH;
            brick.h = INDIVIDUAL_BRICK_HEIGHT;

            if (ball.x < brick.x + brick.w &&
                ball.x + 24 > brick.x &&
                ball.y < brick.y + brick.h &&
                ball.y + 24 > brick.y) {

                ball.vy = -ball.vy; 

				//gérer la disparition de la brique quand elle est touchée par la balle


                return; 
            }
        }
    }
}


void init()
{
	pWindow = SDL_CreateWindow("Arknoid", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, 600, 600, SDL_WINDOW_SHOWN);
	win_surf = SDL_GetWindowSurface(pWindow);
	plancheSprites = SDL_LoadBMP("./sprites.bmp");
	plancheSpritesBricks = SDL_LoadBMP("./arkanoid_sprites.bmp");
	SDL_SetColorKey(plancheSprites, true, 0);  // 0: 00/00/00 noir -> transparent

	ball.x = win_surf->w / 2;
	ball.y = win_surf->h / 2;
	ball.vx = 1.0;
	ball.vy = 1.4;

	now = SDL_GetPerformanceCounter();

	initBricks(); 
}

// fonction qui met à jour la surface de la fenetre "win_surf"
void draw()
{
	// remplit le fond 
	SDL_Rect dest = { 0,0,0,0 };
	for (int j = 0; j < win_surf->h; j+=128)
		for (int i = 0; i < win_surf->w; i += 96)
		{
			dest.x = i;
			dest.y = j;
			SDL_BlitSurface(plancheSprites, &srcBg, win_surf, &dest);
		}

	
	// affiche balle
	SDL_Rect dstBall = {ball.x, ball.y, 0, 0};
	SDL_BlitSurface(plancheSprites, &srcBall, win_surf, &dstBall);

	// dedplacement
	ball.x += ball.vx;// / delta_t;
	ball.y += ball.vy;// / delta_t;

	// collision bord
	if ((ball.x < 1) || (ball.x > (win_surf->w - 25)))
		ball.vx *= -1;
	if ((ball.y < 1) || (ball.y > (win_surf->h - 25)))
		ball.vy *= -1;

	// touche bas -> rouge
	if (ball.y >(win_surf->h - 25))
		srcBall.y = 64;
	// touche bas -> vert
	if (ball.y < 1)
		srcBall.y = 96;

	// vaisseau
	dest.x = x_vault;
	dest.y = win_surf->h - 32;
	SDL_BlitSurface(plancheSprites, &scrVaiss, win_surf, &dest);



	int paddleX = x_vault;
	int paddleY = win_surf->h - paddleHeight;

	if ((ball.x + 24 > paddleX) &&               
		(ball.x < paddleX + paddleWidth) &&      
		(ball.y + 24 > paddleY) &&               
		(ball.y < paddleY + paddleHeight)) {     
		ball.vy *= -1;

		ball.y = paddleY - 24;
	}

	drawBricks(win_surf);
}




int main(int argc, char** argv)
{
    if (SDL_Init(SDL_INIT_VIDEO | SDL_INIT_AUDIO ) != 0 )
    {
		return 1;
    }

	init();
    
	bool quit = false;
	while (!quit)
	{	
		SDL_PumpEvents();
        const Uint8* keys = SDL_GetKeyboardState(NULL);
        if (keys[SDL_SCANCODE_LEFT])
            x_vault -= 10;
        if (keys[SDL_SCANCODE_RIGHT])
            x_vault += 10;
        if (keys[SDL_SCANCODE_ESCAPE])
            quit=true;

		checkBallBrickCollision();	

		draw();
		SDL_UpdateWindowSurface(pWindow);
		now = SDL_GetPerformanceCounter();
		delta_t = 1.0/FPS - (double)(now - prev) / (double)SDL_GetPerformanceFrequency();
		prev = now;
		if (delta_t > 0)
             SDL_Delay((Uint32)(delta_t*1000));
		printf("dt = %lf\n",delta_t*1000);
		prev = SDL_GetPerformanceCounter();

				
		if (keys[SDL_SCANCODE_LEFT]) {
			x_vault -= 10;
			if (x_vault < 0) { 
				x_vault = 0;
			}
		}
		if (keys[SDL_SCANCODE_RIGHT]) {
			x_vault += 10;
			if (x_vault > win_surf->w - paddleWidth) {  
				x_vault = win_surf->w - paddleWidth;
			}
		}

	}

    SDL_Quit();
    return 0;
}
