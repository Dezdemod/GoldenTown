#pragma once
#include <player.h>

class GameState
{
public:
	GameState(std::shared_ptr<gameData> gamedata);

	void gameOverScreen();
	void controls();

	inline bool isGameOver() { return gameOver; };
	inline void gameIsOver() { gameOver = true; }

private:
	bool gameOver;
	const Texture2D gameOverTexture;
	std::pair<const Texture2D, Vector2> arrow;
	Color arrowColor;
	
	std::shared_ptr<gameData> data;
};
