#pragma once
#include <player.h>

class Map
{
public:
	Map(std::shared_ptr<gameData> gamedata, std::shared_ptr<Player> Player);

	void draw();
	void reset();

private:
	void drawClouds();

	const float cloudSpeed;
	std::vector<std::pair<const Texture2D, Vector2>> clouds;
	std::shared_ptr<gameData> data;
	std::shared_ptr<Player> player;
};
