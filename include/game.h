#pragma once
#include <mainMenu.h>
#include <map.h>
#include <shop.h>
#include <scoreboard.h>
#include <gameState.h>
#include <tutorial.h>

class Game
{
public:
	Game();

	void start();

private:
	void menu();
	void playGame();
	void resetLevel();
	void pauseGame();

	bool pause;

	std::shared_ptr<gameData> data;
	std::shared_ptr<Player> player;

	Map map;
	Shop shop;
	Scoreboard scoreboard;
	GameState gameState;
};