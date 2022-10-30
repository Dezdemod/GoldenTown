#include <game.h>

Game::Game()
	: pause(false)
	, data(std::make_shared<gameData>())
	, player(std::make_shared<Player>(data))
	, map(data, player)
	, shop(player, data)
	, scoreboard(data)
	, gameState(data)
{
}

void Game::menu()
{
	mainMenu mainmenu;
	Tutorial tutorial;

	mainmenu.drawMenu();
	PlaySound(data->select);
	tutorial.draw();
	PlaySound(data->select);
}

void Game::start()
{
	this->menu();
	PlayMusicStream(data->backgroundMusic);
	SetMusicVolume(data->backgroundMusic, 0.2f);
	data->backgroundMusic.looping = true;
	while(!WindowShouldClose())
	{
		if(!gameState.isGameOver()) this->playGame();
		gameState.gameOverScreen();
		data->reset();
		player->reset();
	}
}

void Game::playGame()
{
	while(!WindowShouldClose() && player->getLives() > 0 && data->money >= 0)
	{
		UpdateMusicStream(data->backgroundMusic);
		if(data->timer > 0.0f && data->gatheredCollectibles != data->collectibleCount)
		{
			if(IsKeyPressed(KEY_P)) pause = true, this->pauseGame();
			map.draw();
		}
		else
		{
			this->resetLevel();
			scoreboard.draw();
			shop.isShopOpen() ? shop.draw() : data->update();
		}
	}
	shop.reset();
	this->resetLevel();
	gameState.gameIsOver();
}

void Game::pauseGame()
{
	player->pauseSound();
	while(pause)
	{
		BeginDrawing();
		{
			ClearBackground(BLACK);
			DrawText("PAUSED", 450, 310, 100, WHITE);
		}
		EndDrawing();
		if (IsKeyPressed(KEY_P)) pause = false;
		if (IsKeyPressed(KEY_M)) data->money = 500;
	}
	player->resumeSound();
}

void Game::resetLevel()
{
	map.reset();
	player->stopSound();
	player->resetPosition();
}