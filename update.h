#pragma once
#include <stdbool.h>
#include "minesweeper.h"

enum control
{
	CONTROL_UP = 'w',
	CONTROL_DOWN = 's',
	CONTROL_LEFT = 'a',
	CONTROL_RIGHT = 'd',
	CONTROL_FLAG = 'm',
	CONTROL_SPACE = ' '
};

state_t update(char key_input);
bool is_all_uncovered(void);
void uncover_recursive(int row, int col);
void set_flag(int row, int col);