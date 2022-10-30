#include <mainMenu.h>

mainMenu::mainMenu()
	: hasStarted(false)
	, select(LoadSound("audio/select.wav"))
	, menu(LoadTexture("menu.png"))
	, arrow(std::make_pair(Texture2D(LoadTexture("arrow.png")), Vector2{305.0f, 385.0f}))
{
	HideCursor();
}

mainMenu::~mainMenu()
{
	if (!hasStarted) CloseWindow();
	UnloadSound(select);
	UnloadTexture(menu);
	UnloadTexture(arrow.first);
}

void mainMenu::drawMenu()
{
	while (!WindowShouldClose() && !hasStarted)
	{
		BeginDrawing();
		{
			DrawTexture(menu, 0, 0, WHITE);
			DrawTextureEx(arrow.first, arrow.second, 0.0f, 1.0f, WHITE);
			this->controls();
		}
		EndDrawing();
	}
}

void mainMenu::controls()
{
	if (IsKeyPressed(KEY_ENTER)) hasStarted = true;

	if (IsKeyPressed(KEY_W) || IsKeyPressed(KEY_UP))
	{
		if (arrow.second.y == 385.0f)
		{
			PlaySound(select);
			arrow.second.x = 360.0f;
			arrow.second.y = 565.0f;
			SetExitKey(KEY_ENTER);
		}
		else
		{
			PlaySound(select);
			arrow.second.x = 305.0f;
			arrow.second.y = 385.0f;
			SetExitKey(KEY_ESCAPE);
		}
	}

	if (IsKeyPressed(KEY_S) || IsKeyPressed(KEY_DOWN))
	{
		if (arrow.second.y == 565.0f)
		{
			PlaySound(select);
			arrow.second.x = 305.0f;
			arrow.second.y = 385.0f;
			SetExitKey(KEY_ESCAPE);
		}
		else
		{
			PlaySound(select);
			arrow.second.x = 360.0f;
			arrow.second.y = 565.0f;
			SetExitKey(KEY_ENTER);
		}
	}
}