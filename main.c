#include "minesweeper.h"
#include "initialize.h"
#include "draw.h"
#include "update.h"

state_t g_game;
position_t g_player = { 0, 0 };
cell_t** g_cell = NULL;

int main(void)
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

	switch (g_game)
	{
	case STATE_GAME_OVER:
		printf("GAME OVER !!\n");
		system("pause");
		break;

	case STATE_VICTORY:
		printf("VICTORY !!\n");
		system("pause");
		break;

	default:
		assert(0);
		break;
	}
	return 0;
}
