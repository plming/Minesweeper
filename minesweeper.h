#pragma once

#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <conio.h>
#include <time.h>
#include <Windows.h>

typedef enum game_state
{
	IDLE,
	GAMEOVER,
	VICTORY
} game_state_t;

typedef struct position
{
	unsigned int row;
	unsigned int col;
} position_t;

typedef struct cell
{
	bool mineExists;
	bool flagExists;
	bool hasUncovered;
	unsigned int numAround;
} cell_t;

#define SIZE_ROW (9)
#define SIZE_COL (9)
#define NUM_MINE (10)

#define UP ('w')
#define DOWN ('s')
#define LEFT ('a')
#define RIGHT ('d')
#define SPACE (32)

extern game_state_t GameState;
extern position_t playerPosition;
extern cell_t cell[SIZE_ROW][SIZE_COL];

void init();
void increaseNum(int row, int col);
void draw();

char get_input();
int update(char keyInput);
bool checkAllCells(void);
void autoUncover(int row, int col);