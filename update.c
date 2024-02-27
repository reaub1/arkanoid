#include "update.h"
#include "init.h"
#include <stdbool.h>
#include "constants.h"
#include "game_state.h"

Uint64 prev, now;
double delta_t;  

void updateGame() {
    ball.x += ball.vx;
    ball.y += ball.vy;

    if ((ball.x < 1) || (ball.x > (win_surf->w - 25)))
        ball.vx *= -1;
    if ((ball.y < 1) || (ball.y > (win_surf->h - 25)))
        ball.vy *= -1;
    
    // Si la balle touche la raquette, on la renvoie
    if ((ball.y > (win_surf->h - 50)) && (ball.x > x_vault) && (ball.x < x_vault + 100))
        ball.vy *= -1;


    if (ball.y > (win_surf->h - 25)){
        srcBall.y = 64;
        ball.vy = 0;
        ball.vx = 0;
    }
        
    if (ball.y < 1)
        srcBall.y = 96;

    const Uint8* keys = SDL_GetKeyboardState(NULL);
    if (keys[SDL_SCANCODE_LEFT])
        if(x_vault > 0){
            x_vault -= 10;
        }
    if (keys[SDL_SCANCODE_RIGHT])
        if(x_vault < win_surf->w - 100){
            x_vault += 10;
        }
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
            if (event.key.keysym.sym == SDLK_RETURN && currentState == MENU) {
                currentState = GAME;
            } else if (event.key.keysym.sym == SDLK_ESCAPE) {
                return true;
            }
        }
    }
    return false;
}

