#include "minesweeper.h"

int update(char keyInput)
{
	if (keyInput == LEFT)
	{
		playerPosition.col = (playerPosition.col - 1) % SIZE_COL;
	}
	else if (keyInput == RIGHT)
	{
		playerPosition.col = (playerPosition.col + 1) % SIZE_COL;
	}
	else if (keyInput == UP)
	{
		playerPosition.row = (playerPosition.row - 1) % SIZE_ROW;
	}
	else if (keyInput == DOWN)
	{
		playerPosition.row = (playerPosition.row + 1) % SIZE_ROW;
	}
	// set flag
	else if (keyInput == 'm' && cell[playerPosition.row][playerPosition.col].hasUncovered == false)
	{
		if (cell[playerPosition.row][playerPosition.col].flagExists)
		{
			cell[playerPosition.row][playerPosition.col].flagExists = false;
		}
		else
		{
			cell[playerPosition.row][playerPosition.col].flagExists = true;
		}
	}
	// uncover cell
	else if (keyInput == SPACE && cell[playerPosition.row][playerPosition.col].flagExists == false)
	{
		if (cell[playerPosition.row][playerPosition.col].mineExists)
		{
			return GAMEOVER;
		}
		else
		{
			if (cell[playerPosition.row][playerPosition.col].numAround != 0)
			{
				cell[playerPosition.row][playerPosition.col].hasUncovered = true;
			}
			else
			{
				autoUncover(playerPosition.row, playerPosition.col);
			}

			if (checkAllCells() == true)
			{
				return VICTORY;
			}
		}
	}
	return IDLE;
}

void autoUncover(int row, int col)
{
	if (cell[row][col].hasUncovered == true)
	{
		return;
	}
	cell[row][col].hasUncovered = true;
	if (cell[row][col].numAround > 0)
	{
		return;
	}
	//check 8 directions for out of index
	if (row != 0)	//UP
	{
		autoUncover(row - 1, col);
	}
	if (row != SIZE_ROW - 1)	//DOWN
	{
		autoUncover(row + 1, col);
	}
	if (col != 0)	//LEFT
	{
		autoUncover(row, col - 1);
	}
	if (col != SIZE_COL - 1)	//RIGHT
	{
		autoUncover(row, col + 1);
	}
	if (row != 0 && col != 0)	//LEFT UP
	{
		autoUncover(row - 1, col - 1);
	}
	if (row != 0 && col != SIZE_COL - 1)	//RIGHT UP
	{
		autoUncover(row - 1, col + 1);
	}
	if (row != SIZE_ROW - 1 && col != 0)	//LEFT DOWN
	{
		autoUncover(row + 1, col - 1);
	}
	if (row != SIZE_ROW - 1 && col != SIZE_COL - 1)	//LEFT DOWN
	{
		autoUncover(row + 1, col + 1);
	}
	return;
}