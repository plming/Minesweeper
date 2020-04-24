#define _CRT_SECURE_NO_WARNINGS

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <conio.h>
#include <Windows.h>

#define SIZE_ROW 9
#define SIZE_COL 9

#define UP 119
#define DOWN 115
#define LEFT 97
#define RIGHT 100
#define SPACE 32

enum _gameState
{
	IDLE,
	GAMEOVER,
	VICTORY
};

typedef struct _Position
{
	unsigned int row;
	unsigned int col;
} Position;

typedef struct _Cell
{
	bool mineExists;
	bool flagExists;
	bool hasUncovered;
	unsigned int numAround;
} Cell;

Position playerPosition;
Cell cell[SIZE_ROW][SIZE_COL] = { 0, };

void init(int percent);
void increaseNum(int row, int col);
void render();
void showHowToPlay();
void setColor(int foreground, int background);
char getInput();
int process(char keyInput);
bool checkAllCells(void);
void autoUncover(int row, int col);

int main()
{
	char keyInput;
	int gameState = IDLE;
	init(10);
	while (gameState == IDLE)
	{
		render();
		keyInput = getInput();
		gameState = process(keyInput);
	}

	if (gameState == GAMEOVER)
	{
		printf("GAME OVER !!\n");
		system("pause");
	}
	else if (gameState == VICTORY)
	{
		printf("VICTORY !!\n");
		system("pause");
	}
	return 0;
}

void init(int percent)	//Create mine according to percent
{
	int row, col;
	srand(time(NULL));

	for (row = 0; row < SIZE_ROW; row++)
	{
		for (col = 0; col < SIZE_COL; col++)
		{
			if (rand() % 100 < percent)	//mine exists
			{
				cell[row][col].mineExists = true;
				increaseNum(row, col);
			}
		}
	}

	playerPosition.row = 0;
	playerPosition.col = 0;
}

void increaseNum(int row, int col)
{
	if (row != 0)	//UP
	{
		cell[row - 1][col].numAround++;
	}
	if (row != SIZE_ROW - 1)	//DOWN
	{
		cell[row + 1][col].numAround++;
	}
	if (col != 0)	//LEFT
	{
		cell[row][col - 1].numAround++;
	}
	if (col != SIZE_COL - 1)	//RIGHT
	{
		cell[row][col + 1].numAround++;
	}
	if (row != 0 && col != 0)	//LEFT UP
	{
		cell[row - 1][col - 1].numAround++;
	}
	if (row != 0 && col != SIZE_COL - 1)	//RIGHT UP
	{
		cell[row - 1][col + 1].numAround++;
	}
	if (row != SIZE_ROW - 1 && col != 0)	//LEFT DOWN
	{
		cell[row + 1][col - 1].numAround++;
	}
	if (row != SIZE_ROW - 1 && col != SIZE_COL - 1)	//LEFT DOWN
	{
		cell[row + 1][col + 1].numAround++;
	}
}

void render()
{
	enum color
	{
		BLACK,
		BLUE,
		GREEN,
		CYAN,
		RED,
		MAGENTA,
		BROWN,
		LIGHTGRAY,
		DARKGRAY,
		LIGHTBLUE,
		LIGHTGREEN,
		LIGHTCYAN,
		LIGHTRED,
		LIGHTMAGENTA,
		YELLOW,
		WHITE
	};
	int row, col;
	system("cls");
	for (row = 0; row < SIZE_ROW; row++)
	{
		for (col = 0; col < SIZE_COL; col++)
		{
			if (playerPosition.row == row && playerPosition.col == col)
			{
				setColor(BLACK, YELLOW);
			}

			if (cell[row][col].flagExists)
			{
				printf(" бс ");
			}
			else if (!cell[row][col].hasUncovered)
			{
				printf(" бр ");
			}
			else
			{
				printf(" %02d ", cell[row][col].numAround);
			}

			setColor(WHITE, BLACK);
		}
		printf("\n\n");
	}
	showHowToPlay();
}

void showHowToPlay()
{
	printf("M: flag the room\nSPACE: dig the room\n");

}

void setColor(int foreground, int background)
{
	int color = foreground + background * 16;
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), color);
}


char getInput()
{
	char keyInput;
	keyInput = _getch();
	return keyInput;
}

int process(char keyInput)
{
	if (keyInput == LEFT && playerPosition.col != 0)
	{
		playerPosition.col--;
		printf("LEFT\n");
		return IDLE;
	}
	else if (keyInput == RIGHT && playerPosition.col != SIZE_COL - 1)
	{
		playerPosition.col++;
		printf("RIGHT\n");
		return IDLE;
	}
	else if (keyInput == UP && playerPosition.row != 0)
	{
		playerPosition.row--;
		printf("UP\n");
		return IDLE;
	}
	else if (keyInput == DOWN && playerPosition.row != SIZE_ROW - 1)
	{
		playerPosition.row++;
		printf("DOWN\n");
		return IDLE;
	}
	else if (keyInput == 'm' && cell[playerPosition.row][playerPosition.col].hasUncovered == false)	//flag
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
	else if (keyInput == SPACE && cell[playerPosition.row][playerPosition.col].flagExists == false)	//uncover
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