#include "Game.h"

Game::Game()
{
}

void Game::drawInterface()
{
}

void Game::drawMenu(int)
{
}

void Game::drawDialog(string, int)
{
}

void Game::setPlayer(int newPlayer)
{
	player = newPlayer;
}

void Game::changePlayer()
{
	player = player ? 0 : 1;
}

int Game::getPlayer()
{
	return player;
}
