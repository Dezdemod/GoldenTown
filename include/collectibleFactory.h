#pragma once
#include <raylib/raylib.h>

class Collectible
{
public:
	Collectible(Texture2D& objectTexture, Vector2 texturePosition, int objectValue, float objectWeight, float timebonus);

	void draw();
	void drawCollision();

	inline void setX(float X) { position.x = X; }
	inline void setY(float Y) { position.y = Y; }
	inline int getValue() const { return value; }
	inline float getWeight() const { return weight; }
	inline float getTimeBonus() const { return timeBonus; }
	inline Vector2 getPosition() const { return position; }

private:

	int value;
	float weight;
	float timeBonus;

	Vector2 position;
	Vector2 texturePosition;

	Texture2D texture;
};

enum collectibleType
{
	stone,
	gold,
	diamond,
	ruby
};

Collectible generateCollectible(collectibleType type);
