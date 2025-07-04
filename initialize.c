
#include "minesweeper.h"
#include "initialize.h"

// Place mine as many as NUM_MINE
void initialize()
{
	g_game = STATE_IDLE;
	srand((unsigned int)time(NULL));

	g_cell = generate_cells_malloc(9, 9);

	int mine_count = 0;
	while (mine_count < NUM_MINE)
	{
		unsigned int row = rand() % SIZE_ROW;
		unsigned int col = rand() % SIZE_COL;

		if (g_cell[row][col].has_mine == false)
		{
			g_cell[row][col].has_mine = true;
			increase_cell_num(row, col);
			mine_count++;
		}
	}
}

cell_t** generate_cells_malloc(int row, int col)
{
	cell_t** pa_cells = malloc(sizeof(cell_t*) * 9);
	assert(pa_cells != NULL);
	for (int i = 0; i < 9; i++)
	{
		pa_cells[i] = malloc(sizeof(cell_t) * 9);
		assert(pa_cells[i] != NULL);
		for (int j = 0; j < 9; j++)
		{
			pa_cells[i][j].has_mine = false;
			pa_cells[i][j].has_flag = false;
			pa_cells[i][j].is_uncovered = false;
			pa_cells[i][j].num_around_mine = 0;
		}
	}
	return pa_cells;
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
