#include <scoreboard.h>

Scoreboard::Scoreboard(std::shared_ptr<gameData> gamedata)
	: texture(LoadTexture("scoreboard.png"))
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
			DrawText(TextFormat("%i", data->money), 560, 207, 45, DARKGREEN);
			DrawText(TextFormat("+%i", timeBonus), 730, 271, 45, DARKGREEN);
			DrawText(TextFormat("-%i", data->expenses), 655, 330, 45, Color{ 186, 7, 7, 255 });
			DrawText(TextFormat("%i", (data->money + timeBonus - data->expenses)), 735, 392, 45, DARKGREEN);
		}
		EndDrawing();
	}
	PlaySound(data->select);
	data->money += timeBonus - data->expenses;
	data->totalMoney += timeBonus - data->expenses;
}