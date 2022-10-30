#include <tutorial.h>

Tutorial::Tutorial()
	: tutorialScreen(LoadTexture("tutorial.png"))
	, select(LoadSound("aduio/select.wav"))
{
}

Tutorial::~Tutorial()
{
	UnloadTexture(tutorialScreen);
	UnloadSound(select);
}

void Tutorial::draw()
{
	while (!IsKeyPressed(KEY_ENTER))
	{
		BeginDrawing();
		{
			DrawTexture(tutorialScreen, 0, 0, WHITE);
		}
		EndDrawing();
	}
	PlaySound(select);
}