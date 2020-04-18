#include <stdio.h>
#include <stdlib.h>
#include <conio.h>
#include <Windows.h>

#pragma warning(disable: 4996)

#define SIZE_ROW 10
#define SIZE_COL 10

#define UP 119
#define DOWN 115
#define LEFT 97
#define RIGHT 100

#define SPACE 32

int isMine[10][10] = { 0, };	//0 means there's "no" mine, 1 means there's a mine
int statusCell[10][10] = { 0, };	//0 means hidden, 1 means flag, 2 means opened
int numMineAround[10][10] = { 0, };	//number of mine around

typedef struct _position
{
	int x;
	int y;
}position;

position cursor;

void increaseMineNum(int row, int col)
{
	if (row != 0)	//UP
	{
		numMineAround[row - 1][col]++;
	}
	if (row != SIZE_ROW - 1)	//DOWN
	{
		numMineAround[row + 1][col]++;
	}
	if (col != 0)	//LEFT
	{
		numMineAround[row][col - 1]++;
	}
	if (col != SIZE_COL - 1)	//RIGHT
	{
		numMineAround[row][col + 1]++;
	}
	if (row != 0 && col != 0)	//LEFT UP
	{
		numMineAround[row - 1][col - 1]++;
	}
	if (row != 0 && col != SIZE_COL - 1)	//RIGHT UP
	{
		numMineAround[row - 1][col + 1]++;
	}
	if (row != SIZE_ROW - 1 && col != 0)	//LEFT DOWN
	{
		numMineAround[row + 1][col - 1]++;
	}
	if (row != SIZE_ROW - 1 && col != SIZE_COL - 1)	//LEFT DOWN
	{
		numMineAround[row + 1][col + 1]++;
	}
}

void init(int percent)	//Create mine according to percent
{
	int row, col;
	srand(time(NULL));

	for (row = 0; row < SIZE_ROW; row++)
	{
		for (col = 0; col < SIZE_COL; col++)
		{
			if ((rand() % 100 + 1) <= percent)	//Here's mine
			{
				isMine[row][col] = 1;	//Place a mine
				increaseMineNum(row, col);	//Increase the number of mine around
			}
		}
	}
	cursor.x = 0;
	cursor.y = 0;
}

void display()//бсбр
{
	int row, col;
	system("cls");	//Clear console
	for (row = 0; row < SIZE_ROW; row++)
	{
		for (col = 0; col < SIZE_COL; col++)
		{
			if (row == cursor.x && col == cursor.y)
			{
				printf("\u001b[43;1m");	//Set text background color to bright yellow
			}
			else
			{
				printf("\u001b[0m");	//reset text background color
			}
			if (statusCell[row][col] == 0)
			{
				printf("бр ", isMine[row][col]);
			}
			else
			{
				printf("%d ", numMineAround[row][col]);
			}
		}
		printf("\n\n");
	}
}

int input()	//if gameover, return 1
{
	char keyBuffer;
	keyBuffer = getch();
	printf("%d\n", keyBuffer);
	if (keyBuffer == SPACE && statusCell[cursor.x][cursor.y] == 0)
	{
		statusCell[cursor.x][cursor.y] = 1;
		if (isMine[cursor.x][cursor.y] == 1)
		{
			return 1;
		}
	}
	else if (keyBuffer == UP && cursor.x != 0)
	{
		cursor.x--;
		printf("\nUP\n");
	}
	else if (keyBuffer == DOWN && cursor.x != SIZE_ROW - 1)
	{
		printf("\nDOWN\n");
		cursor.x++;
	}
	else if (keyBuffer == LEFT && cursor.y != 0)
	{
		printf("\nleft\n");
		cursor.y--;
	}
	else if (keyBuffer == RIGHT && cursor.y != SIZE_COL - 1)
	{
		printf("\nright\n");
		cursor.y++;
	}
	return 0;
}

int main()
{
	int isGameOver = 0;
	init(20);
	while (isGameOver != 1)
	{
		display();
		isGameOver = input();
	}
	printf("Game Over !!\n");
	return 0;
}