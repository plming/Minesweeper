#include "minesweeper.h"

// Place mine as many as NUM_MINE
void initialize()
{
	g_game = STATE_IDLE;
	unsigned int row, col;
	int mine_count = 0;
	srand((unsigned int)time(NULL));
	while (mine_count < NUM_MINE)
	{
		row = rand() % SIZE_ROW;
		col = rand() % SIZE_COL;

		if (g_cell[row][col].has_mine == false)
		{
			g_cell[row][col].has_mine = true;
			increase_cell_num(row, col);
			mine_count++;
		}
	}
}

void increase_cell_num(int row, int col)
{
	// Up
	if (row != 0)
	{
		g_cell[row - 1][col].num_around_mine++;
	}
	// Down
	if (row != SIZE_ROW - 1)
	{
		g_cell[row + 1][col].num_around_mine++;
	}
	// Left
	if (col != 0)
	{
		g_cell[row][col - 1].num_around_mine++;
	}
	// Right
	if (col != SIZE_COL - 1)
	{
		g_cell[row][col + 1].num_around_mine++;
	}
	// Left up
	if (row != 0 && col != 0)
	{
		g_cell[row - 1][col - 1].num_around_mine++;
	}
	// Right up
	if (row != 0 && col != SIZE_COL - 1)
	{
		g_cell[row - 1][col + 1].num_around_mine++;
	}
	// Left down
	if (row != SIZE_ROW - 1 && col != 0)
	{
		g_cell[row + 1][col - 1].num_around_mine++;
	}
	// Right down
	if (row != SIZE_ROW - 1 && col != SIZE_COL - 1)
	{
		g_cell[row + 1][col + 1].num_around_mine++;
	}
	return;
}

char get_input()
{
	char key;
	key = _getch();
	return key;
}

bool is_all_uncovered(void)
{
	int row, col;
	for (row = 0; row < SIZE_ROW; row++)
	{
		for (col = 0; col < SIZE_COL; col++)
		{
			if (g_cell[row][col].has_mine == false)
			{
				if (g_cell[row][col].is_uncovered == false)
				{
					return false;
				}
			}
		}
	}
	return true;
}

