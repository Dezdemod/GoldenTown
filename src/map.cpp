#include <map.h>

Map::Map(std::shared_ptr<gameData> gamedata, std::shared_ptr<Player> Player)
	: data(gamedata)
	, player(Player)
	, cloudSpeed(0.05f)
	, clouds
	({
		{std::make_pair(Texture2D(LoadTexture("map/cloud.png")), Vector2{ 100.0f, 5.0f })}
		,{std::make_pair(Texture2D(LoadTexture("map/cloud2.png")), Vector2{ 550.0f, 20.0f })}
		,{std::make_pair(Texture2D(LoadTexture("map/cloud3.png")), Vector2{ 900.0f, 10.0f })}
	})
{
}

void Map::draw()
{
	if (!IsCursorHidden()) HideCursor();
	data->timer -= GetFrameTime();
	BeginDrawing();
	{
		ClearBackground(WHITE);
		DrawTexture(data->background, 0, 0, WHITE);
		for (int i = 0; i < data->collectibleCount; i++)
		{
			if (data->collectibles[i].getPosition().y < 750.0f) data->collectibles[i].draw();
		}
		for (int i = 0; i < data->enemyCount; i++)
		{
			if (data->enemies[i].getPosition().y < 750.0f) data->enemies[i].draw();
		}
		if (data->level % 2 == 1) this->drawClouds();
		player->draw();
		DrawText(TextFormat("%i", data->money), 55, 3, 30, WHITE);
		DrawText(TextFormat("%i", (int)(data->timer)), 56, 51, 34, WHITE);
		DrawText(TextFormat("%i", player->getLives()), 1234, 3, 28, WHITE);
	}
	EndDrawing();
}

void Map::drawClouds()
{
	for (auto& cloud : clouds)
	{
		DrawTextureEx(cloud.first, cloud.second, 0.0f, 1.0f, WHITE);
		cloud.second.x += cloudSpeed;
		if (cloud.second.x > data->screenWidth - cloud.first.width)
		{
			DrawTexture(cloud.first, cloud.second.x - data->screenWidth, cloud.second.y, WHITE);
		}
		if (cloud.second.x > data->screenWidth) cloud.second.x = 0.0f;
	}
}

void Map::reset()
{
	if (data->level % 2 == 1)
	{
		clouds[0].second.x = 200.0f;
		clouds[1].second.x = 800.0f;
	}
}