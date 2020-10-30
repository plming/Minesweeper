#include "minesweeper.h"

game_state_t GameState;
position_t playerPosition = { 0, 0 };
cell_t cell[SIZE_ROW][SIZE_COL] = { 0, };

int main()
{
	char keyInput;
	init();
	while (GameState == IDLE)
	{
		// TODO: getinput, update, draw 순으로 바꾸기
		draw();
		keyInput = get_input();
		GameState = update(keyInput);
	}

	if (GameState == GAMEOVER)
	{
		printf("GAME OVER !!\n");
		system("pause");
	}
	else if (GameState == VICTORY)
	{
		printf("VICTORY !!\n");
		system("pause");
	}
	return 0;
}