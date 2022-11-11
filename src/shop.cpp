#include <shop.h>

Shop::Shop(std::shared_ptr<Player> Player, std::shared_ptr<gameData> gamedata)
	: player(Player)
	, data(gamedata)
	, wasHookBought(false)
	, wasCartBought(false)
	, hasLeftShop(true)
	, shopIsOpen(true)
	, shopTexture(LoadTexture("shop/shop.png"))
	, buy(LoadSound("audio/buy.mp3"))
	, buyButton(Rectangle{ 200.0f, 480.0f, 240.0f, 100.0f })
	, buyButton2(Rectangle{ 860.0f, 480.0f, 240.0f, 100.0f })
	, continueButton(Rectangle{ 369.0f, 633.0f, 543.0f, 64.0f })
{
}

void Shop::draw()
{
	if (IsCursorHidden()) ShowCursor();
	hasLeftShop = false;
	while(!hasLeftShop && data->money >= 0)
	{
		UpdateMusicStream(data->backgroundMusic);
		BeginDrawing();
		{
			DrawTexture(shopTexture, 0, 0, WHITE);
			DrawTextEx(data->mainFont, TextFormat("%i", data->money), Vector2{ 115.0f, 12.0f }, 40.0f, 0.0f, Color{ 75, 105, 47, 255 });
			!wasHookBought ? DrawTextEx(data->mainFont, "$500", Vector2{ 208.0f, 510.0f }, 55.0f, 0.0f, GREEN) : DrawTextEx(data->mainFont, "SOLD", Vector2{ 212.0f, 510.0f }, 55.0f, 0.0f, RED);
			!wasCartBought ? DrawTextEx(data->mainFont, "$500", Vector2{ 868.0f, 510.0f }, 55.0f, 0.0f, GREEN) : DrawTextEx(data->mainFont, "SOLD", Vector2{ 872.0f, 510.0f }, 55.0f, 0.0f, RED);
		}
		EndDrawing();
		this->controls();
	}
	PlaySound(data->select);
	data->update();
	if (wasHookBought && wasCartBought) shopIsOpen = false;
}

void Shop::controls()
{
	if (CheckCollisionPointRec(GetMousePosition(), continueButton) && IsMouseButtonPressed(MOUSE_BUTTON_LEFT) || IsKeyPressed(KEY_ENTER))
	{
		hasLeftShop = true;
	}

	if (CheckCollisionPointRec(GetMousePosition(), buyButton) && IsMouseButtonPressed(MOUSE_BUTTON_LEFT) && data->money >= 500 && !wasHookBought)
	{
		PlaySound(buy);
		player->changeHook("shop/bronzeClaw.png", 1.0f);
		data->money -= 500;
		wasHookBought = true;
	}

	if (CheckCollisionPointRec(GetMousePosition(), buyButton2) && IsMouseButtonPressed(MOUSE_BUTTON_LEFT) && data->money >= 950 && !wasCartBought)
	{
		PlaySound(buy);
		player->changePlayer("shop/bronzeCart.png", 4.0f);
		data->money -= 950;
		wasCartBought = true;
	}
}

void Shop::reset()
{
	wasHookBought = false;
	wasCartBought = false;
	shopIsOpen = true;
}