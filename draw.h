#pragma once
#include <stdio.h>

typedef enum color
{
	COLOR_BLACK = 0,
	COLOR_YELLOW = 14,
	COLOR_WHITE = 15
} color_t;

void draw();
void show_controls();
void set_color(color_t foreground, color_t background);