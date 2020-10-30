#include "minesweeper.h"
#include "draw.h"

void draw()
{
	int row, col;
	system("cls");
	for (row = 0; row < SIZE_ROW; row++)
	{
		for (col = 0; col < SIZE_COL; col++)
		{
			if (playerPosition.row == row && playerPosition.col == col)
			{
				set_color(COLOR_BLACK, COLOR_YELLOW);
			}

			if (cell[row][col].flagExists)
			{
				printf("б╪");
			}
			else if (!cell[row][col].hasUncovered)
			{
				printf("бр");
			}
			else
			{
				printf("%2d", cell[row][col].numAround);
			}

			set_color(COLOR_WHITE, COLOR_BLACK);
		}
		printf("\n");
	}
	show_controls();
	return;
}

void show_controls()
{
	printf("\n");
	printf("M: flag the room\n");
	printf("SPACE: dig the room\n");
	return;
}

void set_color(int foreground, int background)
{
	int color = foreground + background * 16;
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), color);
}