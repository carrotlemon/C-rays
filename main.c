#include <SDL2/SDL.h>
#include <math.h>
#include <stdbool.h>
#include <stdio.h>

#include "funcs.h"

#define SCREEN_WIDTH 800
#define SCREEN_HEIGHT 600

void drawCircle(SDL_Renderer *renderer, circle *c) {
    int centerX = (int)c->center.x, centerY = (int)c->center.y, radius = (int)c->radius;
    for (int w = 0; w < radius * 2; w++) {
        for (int h = 0; h < radius * 2; h++) {
            int dx = radius - w;
            int dy = radius - h;
            if ((dx * dx + dy * dy) <= (radius * radius)) {
                SDL_RenderDrawPoint(renderer, centerX + dx, centerY + dy);
            }
        }
    }
}

int main(int argc, char *argv[]) {
    // Initialize SDL
    if (SDL_Init(SDL_INIT_VIDEO) < 0) {
        printf("SDL Init Error: %s\n", SDL_GetError());
        return 1;
    }
    // Create SDL Window
    SDL_Window *window = SDL_CreateWindow("SDL2 Basic Shapes", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED,
                                          SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN);
    if (!window) {
        printf("Window Creation Error: %s\n", SDL_GetError());
        SDL_Quit();
        return 1;
    }

    // Create Renderer
    SDL_Renderer *renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
    if (!renderer) {
        printf("Renderer Creation Error: %s\n", SDL_GetError());
        SDL_DestroyWindow(window);
        SDL_Quit();
        return 1;
    }

    bool running = true;
    SDL_Event event;

    // Initialize circle_arr
    int num_circles = 1;
    circle_arr *carr = malloc(sizeof(circle_arr));
    carr->circles = malloc(sizeof(circle) * num_circles);
    carr->count = num_circles;

    carr->circles[0].center.x = 100;
    carr->circles[0].center.y = 400;
    carr->circles[0].radius = 50;

    // Initialize light source
    circle *light = malloc(sizeof(circle));
    int numRays = 80000;
    light->radius = 20;
    light->center.x = SCREEN_WIDTH / 2;
    light->center.y = SCREEN_HEIGHT / 2;
    //printf("light center: %f %f", light->center.x, light->center.y);

    while (running) {
        while (SDL_PollEvent(&event)) {
            if (event.type == SDL_QUIT) {
                running = false;
            }
            // Mouse input
            if (event.type == SDL_MOUSEMOTION && (event.motion.state & SDL_BUTTON_LMASK)) {
                //printf("%d, %d\n", event.motion.x, event.motion.y);
                carr->circles[0].center.x = (float)event.motion.x;
                carr->circles[0].center.y = (float)event.motion.y;
            }
        }

        // Reset Renderer
        SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
        SDL_RenderClear(renderer);

        SDL_SetRenderDrawColor(renderer, 0, 255, 0, 255);
        for (int i = 0; i < carr->count; ++i) {
            drawCircle(renderer, &carr->circles[i]);
        }

        // Draw Rays
        SDL_SetRenderDrawColor(renderer, 255, 0, 255, 255);
        for (double theta = 0; theta <= 2 * M_PI; theta += (2 * M_PI / numRays)) {
            // printf("%f\n", theta);
            point *res = get_collision(carr, &light->center, theta, SCREEN_WIDTH, SCREEN_HEIGHT);
            SDL_RenderDrawLine(renderer, light->center.x, light->center.y, res->x, res->y);
            // printf("x: %f y: %f", res->x, res->y);
        }

        SDL_RenderPresent(renderer);
    }

    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();

    free(carr->circles);
    free(carr);
    free(light);

    return 0;
}

// SDL usage examples

// // Draw a red rectangle
// SDL_Rect rect = {100, 100, 200, 150};
// SDL_SetRenderDrawColor(renderer, 255, 0, 0, 255);
// SDL_RenderFillRect(renderer, &rect);

// // Draw a green outline rectangle
// SDL_Rect outlineRect = {350, 100, 200, 150};
// SDL_SetRenderDrawColor(renderer, 0, 255, 0, 255);
// SDL_RenderDrawRect(renderer, &outlineRect);

// // Draw a blue circle
// SDL_SetRenderDrawColor(renderer, 0, 0, 255, 255);
// drawCircle(renderer, 500, 400, 50);

// // Draw red line
// SDL_SetRenderDrawColor(renderer, 255, 0, 0, 255);
// SDL_RenderDrawLine(renderer, 100, 100, 700, 500);