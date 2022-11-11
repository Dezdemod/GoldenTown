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
			DrawTextEx(data->mainFont, TextFormat("%i", data->totalMoney), Vector2{ 720.0f, 199.0f }, 60.0f, 0.0f, WHITE);
			DrawTextEx(data->mainFont, TextFormat("%i", data->totalCollectibles), Vector2{ 840.0f, 359.0f }, 60.0f, 0.0f, WHITE);
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