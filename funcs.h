#pragma once

#include <stdio.h>
#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdarg.h>
#include <stdbool.h>

// Structs
typedef struct {
    float x;
    float y;
} point;

typedef struct {
    point center;
    float radius;
} circle;

typedef struct {
    circle *circles;
    int count;
} circle_arr;

// Functions
bool in_bounds(point *p, int screen_width, int screen_height);
bool collides_pc(point *p, circle *c);
bool collides_cc(circle *c1, circle *c2);
point *get_collision(circle_arr *circles, point *p, float theta, int screen_width, int screen_height);