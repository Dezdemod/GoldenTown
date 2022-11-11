#include <map.h>

Map::Map(std::shared_ptr<gameData> gamedata, std::shared_ptr<Player> Player)
	: data(gamedata)
	, player(Player)
	, cloudSpeed(0.03f)
	, clouds
	({
		{std::make_pair(Texture2D(LoadTexture("map/cloud.png")), Vector2{ 200.0f, 5.0f })}
		,{std::make_pair(Texture2D(LoadTexture("map/cloud2.png")), Vector2{ 800.0f, 10.0f })}
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
		DrawTextEx(data->mainFont, TextFormat("%i", data->money), Vector2{54.0f, 8.0f}, 21.0f, 0.0f, WHITE);
		DrawTextEx(data->mainFont, TextFormat("00:%02i", (int)(data->timer)), Vector2{ 56.0f, 58.0f }, 21.0f, 0.0f, WHITE);
		DrawTextEx(data->mainFont, TextFormat("%i", player->getLives()), Vector2{ 1230.0f, 6.0f }, 22.0f, 0.0f, WHITE);
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