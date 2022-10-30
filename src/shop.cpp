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
			DrawText(TextFormat("%i", data->money), 115, 5, 50, Color{ 75, 105, 47, 255 });
			!wasHookBought ? DrawText("$500", 240, 500, 70, GREEN) : DrawText("SOLD", 230, 500, 70, RED);
			!wasCartBought ? DrawText("$950", 900, 500, 70, GREEN) : DrawText("SOLD", 890, 500, 70, RED);
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