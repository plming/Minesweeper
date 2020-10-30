#include "minesweeper.h"

state_t g_game;
position_t g_player = { 0, 0 };
cell_t g_cell[SIZE_ROW][SIZE_COL] = { 0, };

int main()
{
	char key_input;

	initialize();
	while (g_game == STATE_IDLE)
	{
		// TODO: getinput, update, draw 순으로 바꾸기
		draw();
		key_input = get_input();
		g_game = update(key_input);
	}

	if (g_game == STATE_GAME_OVER)
	{
		printf("GAME OVER !!\n");
		system("pause");
	}
	else if (g_game == STATE_VICTORY)
	{
		printf("VICTORY !!\n");
		system("pause");
	}
	return 0;
}