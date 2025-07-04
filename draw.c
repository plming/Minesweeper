#include "draw.h"
#include "minesweeper.h"

void draw()
{
	int row, col;
	system("cls");
	for (row = 0; row < SIZE_ROW; row++)
	{
		for (col = 0; col < SIZE_COL; col++)
		{
			if (g_player.row == row && g_player.col == col)
			{
				set_color(COLOR_BLACK, COLOR_YELLOW);
			}

			if (g_cell[row][col].has_flag)
			{
				printf("※");
			}
			else if (!g_cell[row][col].is_uncovered)
			{
				printf("□");
			}
			else
			{
				printf("%2d", g_cell[row][col].num_around_mine);
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

void set_color(color_t foreground, color_t background)
{
	int color = foreground + background * 16;
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), color);
}
