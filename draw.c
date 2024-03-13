#include "draw.h"
#include "block.h"


void drawGame() {

    SDL_Rect dest = { 0, 0, 0, 0 };
    for (int j = 0; j < win_surf->h; j += 64)
        for (int i = 0; i < win_surf->w; i += 64) {
            dest.x = i;
            dest.y = j;
            SDL_BlitSurface(plancheSpritesBricks, &darkbackground6, win_surf, &dest);
        }

    SDL_Rect dstBall = { (int)ball.x, (int)ball.y, 24, 24 };
    SDL_BlitSurface(plancheSprites, &srcBall, win_surf, &dstBall);

    SDL_Rect dstVaiss = { x_vault, win_surf->h - 32, 128, 32 };
    SDL_BlitSurface(plancheSprites, &scrVaiss, win_surf, &dstVaiss);

    // on dessine le block
    SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
    SDL_RenderFillRect(renderer, &block);

    //NEW PART

    drawBricks(win_surf);

    /******/

    SDL_UpdateWindowSurface(pWindow);
}


void drawBricks(SDL_Surface* win_surf) {
    for (int i = 0; i < BRICK_ROWS; i++) {
        for (int j = 0; j < BRICK_COLUMNS; j++) {
            if (bricks[i][j].active) {
                
            if(turn%20==0){
                if (bricks[i][j].color.x == goldbrick1.x && bricks[i][j].color.y == goldbrick1.y) {
                bricks[i][j].color = goldbrick2;
                SDL_BlitSurface(plancheSpritesBricks, &bricks[i][j].color, win_surf, &bricks[i][j].rect);
                } else if (bricks[i][j].color.x == goldbrick2.x && bricks[i][j].color.y == goldbrick2.y) {
                    bricks[i][j].color = goldbrick3;
                    SDL_BlitSurface(plancheSpritesBricks, &bricks[i][j].color, win_surf, &bricks[i][j].rect);
                } else if (bricks[i][j].color.x == goldbrick3.x && bricks[i][j].color.y == goldbrick3.y) {
                    bricks[i][j].color = goldbrick4;
                    SDL_BlitSurface(plancheSpritesBricks, &bricks[i][j].color, win_surf, &bricks[i][j].rect);
                } else if (bricks[i][j].color.x == goldbrick4.x && bricks[i][j].color.y == goldbrick4.y) {
                    bricks[i][j].color = goldbrick5;
                    SDL_BlitSurface(plancheSpritesBricks, &bricks[i][j].color, win_surf, &bricks[i][j].rect);
                } else if (bricks[i][j].color.x == goldbrick5.x && bricks[i][j].color.y == goldbrick5.y) {
                    bricks[i][j].color = goldbrick6;
                    SDL_BlitSurface(plancheSpritesBricks, &bricks[i][j].color, win_surf, &bricks[i][j].rect);
                } else if (bricks[i][j].color.x == goldbrick6.x && bricks[i][j].color.y == goldbrick6.y) {
                    bricks[i][j].color = goldbrick1;
                    SDL_BlitSurface(plancheSpritesBricks, &bricks[i][j].color, win_surf, &bricks[i][j].rect);
                }

                if (bricks[i][j].color.x == silverbrick1.x && bricks[i][j].color.y == silverbrick1.y) {
                    bricks[i][j].color = silverbrick2;
                    SDL_BlitSurface(plancheSpritesBricks, &bricks[i][j].color, win_surf, &bricks[i][j].rect);
                } else if (bricks[i][j].color.x == silverbrick2.x && bricks[i][j].color.y == silverbrick2.y) {
                    bricks[i][j].color = silverbrick3;
                    SDL_BlitSurface(plancheSpritesBricks, &bricks[i][j].color, win_surf, &bricks[i][j].rect);
                } else if (bricks[i][j].color.x == silverbrick3.x && bricks[i][j].color.y == silverbrick3.y) {
                    bricks[i][j].color = silverbrick4;
                    SDL_BlitSurface(plancheSpritesBricks, &bricks[i][j].color, win_surf, &bricks[i][j].rect);
                } else if (bricks[i][j].color.x == silverbrick4.x && bricks[i][j].color.y == silverbrick4.y) {
                    bricks[i][j].color = silverbrick5;
                    SDL_BlitSurface(plancheSpritesBricks, &bricks[i][j].color, win_surf, &bricks[i][j].rect);
                } else if (bricks[i][j].color.x == silverbrick5.x && bricks[i][j].color.y == silverbrick5.y) {
                    bricks[i][j].color = silverbrick6;
                    SDL_BlitSurface(plancheSpritesBricks, &bricks[i][j].color, win_surf, &bricks[i][j].rect);
                } else if (bricks[i][j].color.x == silverbrick6.x && bricks[i][j].color.y == silverbrick6.y) {
                    bricks[i][j].color = silverbrick1;
                    SDL_BlitSurface(plancheSpritesBricks, &bricks[i][j].color, win_surf, &bricks[i][j].rect);
                }

                if (bricks[i][j].color.x == ball1.x && bricks[i][j].color.y == ball1.y) {
                    bricks[i][j].color = ball2;
                    SDL_BlitSurface(plancheSpritesBricks, &bricks[i][j].color, win_surf, &bricks[i][j].rect);
                } else if (bricks[i][j].color.x == ball2.x && bricks[i][j].color.y == ball2.y) {
                    bricks[i][j].color = ball3;
                    SDL_BlitSurface(plancheSpritesBricks, &bricks[i][j].color, win_surf, &bricks[i][j].rect);
                } else if (bricks[i][j].color.x == ball3.x && bricks[i][j].color.y == ball3.y) {
                    bricks[i][j].color = ball4;
                    SDL_BlitSurface(plancheSpritesBricks, &bricks[i][j].color, win_surf, &bricks[i][j].rect);
                } else if (bricks[i][j].color.x == ball4.x && bricks[i][j].color.y == ball4.y) {
                    bricks[i][j].color = ball5;
                    SDL_BlitSurface(plancheSpritesBricks, &bricks[i][j].color, win_surf, &bricks[i][j].rect);
                } else if (bricks[i][j].color.x == ball5.x && bricks[i][j].color.y == ball5.y) {
                    bricks[i][j].color = ball6;
                    SDL_BlitSurface(plancheSpritesBricks, &bricks[i][j].color, win_surf, &bricks[i][j].rect);
                } else if (bricks[i][j].color.x == ball6.x && bricks[i][j].color.y == ball6.y) {
                    bricks[i][j].color = ball1;
                    SDL_BlitSurface(plancheSpritesBricks, &bricks[i][j].color, win_surf, &bricks[i][j].rect);
                }
            }
            SDL_BlitSurface(plancheSpritesBricks, &bricks[i][j].color, win_surf, &bricks[i][j].rect);
                SDL_BlitSurface(plancheSpritesBricks, &bricks[i][j].color, win_surf, &bricks[i][j].rect);
            }
        }
    }
}