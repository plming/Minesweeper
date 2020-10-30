#pragma once

enum color
{
	COLOR_BLACK = 0,
	COLOR_YELLOW = 14,
	COLOR_WHITE = 15
};

void show_controls();
void set_color(int foreground, int background);