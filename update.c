#include "minesweeper.h"

int update(char keyInput)
{
	switch (keyInput)
	{
	case CONTROL_LEFT:
		g_player.col += SIZE_COL - 1;
		g_player.col %= SIZE_COL;
		break;
	case CONTROL_RIGHT:
		g_player.col = (g_player.col + 1) % SIZE_COL;
		break;
	case CONTROL_UP:
		g_player.row += SIZE_ROW - 1;
		g_player.row %= SIZE_ROW;
		break;
	case CONTROL_DOWN:
		g_player.row = (g_player.row + 1) % SIZE_ROW;
		break;
	case CONTROL_FLAG:
		set_flag(g_player.row, g_player.col);
		break;
	case CONTROL_SPACE:
		if (g_cell[g_player.row][g_player.col].has_flag == true)
		{
			break;
		}
		if (g_cell[g_player.row][g_player.col].has_mine)
		{
			return STATE_GAME_OVER;
		}

		if (g_cell[g_player.row][g_player.col].num_around_mine != 0)
		{
			g_cell[g_player.row][g_player.col].is_uncovered = true;
		}
		else
		{
			uncover_recursive(g_player.row, g_player.col);
		}

		if (is_all_uncovered() == true)
		{
			return STATE_VICTORY;
		}
		break;
	default:
		break;
	}
	return STATE_IDLE;
}

void set_flag(int row, int col)
{
	if (g_cell[row][col].is_uncovered)
	{
		return;
	}

	g_cell[row][col].has_flag = !g_cell[row][col].has_flag;
	return;
}

void uncover_recursive(int row, int col)
{
	if (g_cell[row][col].is_uncovered == true)
	{
		return;
	}
	g_cell[row][col].is_uncovered = true;
	if (g_cell[row][col].num_around_mine > 0)
	{
		return;
	}
	// Check 8 directions for out of index

	// Up
	if (row != 0)
	{
		uncover_recursive(row - 1, col);
	}
	// Down
	if (row != SIZE_ROW - 1)
	{
		uncover_recursive(row + 1, col);
	}
	// Left
	if (col != 0)
	{
		uncover_recursive(row, col - 1);
	}
	// Right
	if (col != SIZE_COL - 1)
	{
		uncover_recursive(row, col + 1);
	}
	// Left up
	if (row != 0 && col != 0)
	{
		uncover_recursive(row - 1, col - 1);
	}
	// Right up
	if (row != 0 && col != SIZE_COL - 1)
	{
		uncover_recursive(row - 1, col + 1);
	}
	// Left down
	if (row != SIZE_ROW - 1 && col != 0)
	{
		uncover_recursive(row + 1, col - 1);
	}
	// Right down
	if (row != SIZE_ROW - 1 && col != SIZE_COL - 1)
	{
		uncover_recursive(row + 1, col + 1);
	}
	return;
}