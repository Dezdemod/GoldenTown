#include <gameState.h>

GameState::GameState(std::shared_ptr<gameData> gamedata)
	: gameOver(false)
	, gameOverTexture(LoadTexture("gameOver.png"))
	, arrow(std::make_pair(Texture2D(LoadTexture("arrow2.png")), Vector2{ 983.0f, 490.0f }))
	, data(gamedata)
	, arrowColor(WHITE)
{
}

void GameState::gameOverScreen()
{
	while(gameOver)
	{
		BeginDrawing();
		{
			DrawTexture(gameOverTexture, 0, 0, WHITE);
			DrawTextureEx(arrow.first, arrow.second, 0, 1.0f, arrowColor);
			DrawText(TextFormat("%i", data->totalMoney), 720, 194, 70, WHITE);
			DrawText(TextFormat("%i", data->totalCollectibles), 840, 354, 70, WHITE);
		}
		EndDrawing();
		this->controls();
	}
}

void GameState::controls()
{
	if (IsKeyPressed(KEY_D) || IsKeyPressed(KEY_RIGHT))
	{
		if (arrow.second.x == 150.0f)
		{
			PlaySound(data->select);
			SetExitKey(KEY_ESCAPE);
			arrow.second.x = 983.0f;
			arrowColor = WHITE;
		}
		else
		{
			PlaySound(data->select);
			SetExitKey(KEY_ENTER);
			arrow.second.x = 150.0f;
			arrowColor = RED;
		}
	}
	if (IsKeyPressed(KEY_A) || IsKeyPressed(KEY_LEFT))
	{
		if (arrow.second.x == 983.0f)
		{
			PlaySound(data->select);
			SetExitKey(KEY_ENTER);
			arrow.second.x = 150.0f;
			arrowColor = RED;
		}
		else
		{
			PlaySound(data->select);
			SetExitKey(KEY_ESCAPE);
			arrow.second.x = 983.0f;
			arrowColor = WHITE;
		}
	}

	if (IsKeyPressed(KEY_ENTER)) PlaySound(data->select), gameOver = false;
}