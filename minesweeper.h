#pragma once

#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <conio.h>
#include <time.h>
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

enum control
{
	CONTROL_UP = 'w',
	CONTROL_DOWN = 's',
	CONTROL_LEFT = 'a',
	CONTROL_RIGHT = 'd',
	CONTROL_FLAG = 'm',
	CONTROL_SPACE = ' '
};

extern state_t g_game;
extern position_t g_player;
extern cell_t g_cell[SIZE_ROW][SIZE_COL];

void initialize();
void increase_cell_num(int row, int col);
void draw();

char get_input();
int update(char keyInput);
bool is_all_uncovered(void);
void uncover_recursive(int row, int col);
void set_flag(int row, int col);