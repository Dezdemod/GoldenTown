#pragma once
#include <gameData.h>

class Scoreboard
{
public:
	Scoreboard(std::shared_ptr<gameData> gamedata);

	void draw();

private:
	const float textSize;

	const Texture2D texture;
	std::shared_ptr<gameData> data;
};