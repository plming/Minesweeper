#include "minesweeper.h"

// Place mine as many as NUM_MINE
void init()
{
	unsigned int row, col;
	int mineCounter = 0;
	srand((unsigned int)time(NULL));
	while (mineCounter < NUM_MINE)
	{
		row = rand() % SIZE_ROW;
		col = rand() % SIZE_COL;

		if (cell[row][col].mineExists == false)
		{
			cell[row][col].mineExists = true;
			increaseNum(row, col);
			mineCounter++;
		}
	}
}

void increaseNum(int row, int col)
{
	// Up
	if (row != 0)
	{
		cell[row - 1][col].numAround++;
	}
	// Down
	if (row != SIZE_ROW - 1)
	{
		cell[row + 1][col].numAround++;
	}
	// Left
	if (col != 0)
	{
		cell[row][col - 1].numAround++;
	}
	// Right
	if (col != SIZE_COL - 1)
	{
		cell[row][col + 1].numAround++;
	}
	// Left up
	if (row != 0 && col != 0)
	{
		cell[row - 1][col - 1].numAround++;
	}
	// Right up
	if (row != 0 && col != SIZE_COL - 1)
	{
		cell[row - 1][col + 1].numAround++;
	}
	// Left down
	if (row != SIZE_ROW - 1 && col != 0)
	{
		cell[row + 1][col - 1].numAround++;
	}
	// Right down
	if (row != SIZE_ROW - 1 && col != SIZE_COL - 1)
	{
		cell[row + 1][col + 1].numAround++;
	}
}

char get_input()
{
	char keyInput;
	keyInput = _getch();
	return keyInput;
}

bool checkAllCells(void)
{
	int row, col;
	for (row = 0; row < SIZE_ROW; row++)
	{
		for (col = 0; col < SIZE_COL; col++)
		{
			if (cell[row][col].mineExists == false)
			{
				if (cell[row][col].hasUncovered == false)
				{
					return false;
				}
			}
		}
	}
	return true;
}

