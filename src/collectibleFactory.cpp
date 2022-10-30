#include <collectibleFactory.h>

Collectible::Collectible(Texture2D& objectTexture, Vector2 texturePos,int objectValue, float objectWeight, float timebonus)
	: position(Vector2{ (float)(GetRandomValue(30, 1250)), (float)(GetRandomValue(300, 685)) })
	, texturePosition(texturePos)
	, texture(objectTexture)
	, value(objectValue)
	, weight(objectWeight)
	, timeBonus(timebonus)
{
}

void Collectible::draw()
{
	DrawTextureEx(texture, position - texturePosition, 0.0f, 1.0f, WHITE);
}

void Collectible::drawCollision()
{
	DrawCircle(position.x, position.y, 21.0f, WHITE);
}

Collectible generateCollectible(collectibleType type)
{
	static Texture2D stoneTexture = LoadTexture("collectibles/stone.png");
	static Texture2D goldTexture = LoadTexture("collectibles/gold.png");
	static Texture2D diamondTexture = LoadTexture("collectibles/diamond.png");
	static Texture2D rubyTexture = LoadTexture("collectibles/ruby.png");

	switch (type)
	{
	case stone: return Collectible(stoneTexture, Vector2{ 17.0f, 15.0f }, 10, 2.0f, 1.0f);
		break;
	case gold: return Collectible(goldTexture, Vector2{ 16.0f, 13.0f }, 30, 2.0f, 2.0f);
		break;
	case diamond: return Collectible(diamondTexture, Vector2{ 13.0f, 9.0f }, 40, 4.0f, 3.0f);
		break;
	case ruby: return Collectible(rubyTexture, Vector2{ 16.0f, 9.0f }, 50, 4.0f, 3.5f);
		break;
	}
}