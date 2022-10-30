#pragma once
#include <player.h>

class Shop
{
public:
	Shop(std::shared_ptr<Player> Player, std::shared_ptr<gameData> gamedata);

	void draw();
	void controls();
	void reset();

	inline bool isShopOpen() const { return shopIsOpen; }

private:
	bool wasHookBought;
	bool wasCartBought;
	bool shopIsOpen;
	bool hasLeftShop;

	const Texture2D shopTexture;
	const Sound buy;

	const Rectangle buyButton;
	const Rectangle buyButton2;
	const Rectangle continueButton;

	std::shared_ptr<Player> player;
	std::shared_ptr<gameData> data;
};