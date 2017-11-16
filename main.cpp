#include "Game.h"
#include <Windows.h>

Game* g_game = 0;


int main(int argc, char* argv[])
{
	g_game = new Game();

	g_game->init("Chapter 1", 100, 100, 1366, 778, 0);

	AllocConsole();


	while (g_game->running())
	{
		g_game->handleEvents();
		g_game->update();
		g_game->render();
	}

	g_game->clean();

	return 0;
}