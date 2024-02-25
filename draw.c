#include "draw.h"
#include "init.h"

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

    SDL_UpdateWindowSurface(pWindow);
}
