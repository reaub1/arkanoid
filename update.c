#include "update.h"
#include "init.h"
#include <stdbool.h>
#include "constants.h"

Uint64 prev, now;
double delta_t;  

void updateGame() {
    ball.x += ball.vx;
    ball.y += ball.vy;

    if ((ball.x < 1) || (ball.x > (win_surf->w - 25)))
        ball.vx *= -1;
    if ((ball.y < 1) || (ball.y > (win_surf->h - 25)))
        ball.vy *= -1;

    if (ball.y > (win_surf->h - 25))
        srcBall.y = 64;
    if (ball.y < 1)
        srcBall.y = 96;

    const Uint8* keys = SDL_GetKeyboardState(NULL);
    if (keys[SDL_SCANCODE_LEFT])
        x_vault -= 10;
    if (keys[SDL_SCANCODE_RIGHT])
        x_vault += 10;

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
            if (event.key.keysym.sym == SDLK_ESCAPE) {
                return true;
            }
        }
    }
    return false;
}
