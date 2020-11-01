#include "update.h"
#include "minesweeper.h"

state_t update(char key_input)
{
	switch (key_input)
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
		if (g_cell[g_player.row][g_player.col].has_flag)
		{
			break;
		}

		if (g_cell[g_player.row][g_player.col].has_mine)
		{
			return STATE_GAME_OVER;
		}

		uncover_recursive(g_player.row, g_player.col);

		if (is_all_uncovered())
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
	if (row < 0 || row >= SIZE_ROW)
	{
		return;
	}

	if (col < 0 || col >= SIZE_COL)
	{
		return;
	}

	if (g_cell[row][col].is_uncovered)
	{
		return;
	}

	g_cell[row][col].is_uncovered = true;
	if (g_cell[row][col].num_around_mine != 0)
	{
		return;
	}

	uncover_recursive(row - 1, col);
	uncover_recursive(row + 1, col);
	uncover_recursive(row, col - 1);
	uncover_recursive(row, col + 1);
	uncover_recursive(row - 1, col - 1);
	uncover_recursive(row - 1, col + 1);
	uncover_recursive(row + 1, col - 1);
	uncover_recursive(row + 1, col + 1);
	return;
}

bool is_all_uncovered(void)
{
	for (int row = 0; row < SIZE_ROW; row++)
	{
		for (int col = 0; col < SIZE_COL; col++)
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