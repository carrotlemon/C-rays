#include "funcs.h"

#include <SDL2/SDL.h>
#include <stdarg.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

bool in_bounds(point *p, int screen_width, int screen_height) {
    if (p->x < 0 || p->x > (float)screen_width || p->y < 0 || p->y > (float)screen_height) {
        return false;
    } else {
        return true;
    }
}

bool collides_pc(point *p, circle *c) {
    int distanceSq = (c->center.x - p->x) * (c->center.x - p->x) + (c->center.y - p->y) * (c->center.y - p->y);
    return distanceSq <= c->radius * c->radius;
}
bool collides_cc(circle *c1, circle *c2) {
    int distanceSq = (c2->center.x - c1->center.x) * (c2->center.x - c1->center.x) +
                     (c2->center.y - c1->center.y) * (c2->center.y - c1->center.y);
    if (distanceSq >= c1->radius * c2->radius + c1->radius * c2->radius) {
        return true;
    } else {
        return false;
    }
}

point *get_collision(circle_arr *circles, point *p, float theta, int screen_width, int screen_height) {
    point *res = malloc(sizeof(point));
    res->x = p->x;
    res->y = p->y;
    float dx = cos(theta), dy = sin(theta);
    // printf("dx: %f dy: %f\n", dx, dy);
    while (in_bounds(res, screen_width, screen_height)) {
        bool collided = false;
        for (int i = 0; i < circles->count; ++i) {
            if (collides_pc(res, &circles->circles[i])) {
                collided = true;
            }
        }
        if (collided) {
            break;
        }
        res->x += dx;
        res->y += dy;
    }
    return res;
}
