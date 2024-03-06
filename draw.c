#include "draw.h"


void drawGame() {
    

    SDL_Rect dest = { 0, 0, 0, 0 };
    for (int j = 0; j < win_surf->h; j += 128)
        for (int i = 0; i < win_surf->w; i += 96) {
            dest.x = i;
            dest.y = j;
            SDL_BlitSurface(plancheSprites, &srcBg, win_surf, &dest);
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
                if(i%2 == 0 && j%2 == 0) {
                    srcBrick.y = 0;
                } else {
                    srcBrick.y = 16;
                }
                SDL_BlitSurface(plancheSpritesBricks, &bricks[i][j].color, win_surf, &bricks[i][j].rect);
            }
        }
    }
}