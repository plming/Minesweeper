#pragma once

#include <assert.h>
#include <stdlib.h>
#include <stdbool.h>

#include <Windows.h>

typedef enum state
{
	STATE_IDLE,
	STATE_GAME_OVER,
	STATE_VICTORY
} state_t;

typedef struct position
{
	unsigned int row;
	unsigned int col;
} position_t;

typedef struct cell
{
	bool has_mine;
	bool has_flag;
	bool is_uncovered;
	unsigned int num_around_mine;
} cell_t;

#define SIZE_ROW (9)
#define SIZE_COL (9)
#define NUM_MINE (10)

extern state_t g_game;
extern position_t g_player;
extern cell_t** g_cell;

char get_input();
