#include <scoreboard.h>

Scoreboard::Scoreboard(std::shared_ptr<gameData> gamedata)
	: textSize(35.0f)
	, texture(LoadTexture("scoreboard.png"))
	, data(gamedata)
{
}

void Scoreboard::draw()
{
	const int timeBonus = (int)data->timer * 4;
	while(!IsKeyPressed(KEY_ENTER))
	{
		UpdateMusicStream(data->backgroundMusic);
		BeginDrawing();
		{
			ClearBackground(BROWN);
			DrawTexture(texture, texture.width / 2, texture.height / 2, WHITE);
			DrawTextEx(data->mainFont, TextFormat("%i", data->money), Vector2{ 560.0f, 210.0f }, textSize, 0.0f, DARKGREEN);
			DrawTextEx(data->mainFont, TextFormat("+%i", timeBonus), Vector2{ 730.0f, 274.0f }, textSize, 0.0f, DARKGREEN);
			DrawTextEx(data->mainFont, TextFormat("-%i", data->expenses), Vector2{ 655.0f, 333.0f }, textSize, 0.0f, Color{ 186, 7, 7, 255 });
			DrawTextEx(data->mainFont, TextFormat("%i", (data->money + timeBonus - data->expenses)), Vector2{ 735.0f, 395.0f }, textSize, 0.0f, DARKGREEN);
		}
		EndDrawing();
	}
	PlaySound(data->select);
	data->money += timeBonus - data->expenses;
	data->totalMoney += timeBonus - data->expenses;
}