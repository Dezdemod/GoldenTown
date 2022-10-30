#pragma once
#include <raylib/raylib.h>
#include <vector>

class Enemy
{
public:
	Enemy();

	void draw();
	void drawCollision(){ DrawCircle(position.x, position.y, 19.0f, WHITE); }
	inline void setX(float X) { position.x = X; }
	inline void setY(float Y) { position.y = Y; }
	inline void stopMovement() { canMove = false; }
	inline Vector2 getPosition() const { return position; }

private:
	void movement();

	float speed;
	bool goLeft;
	bool canMove;

	Vector2 position;
	Texture2D enemy;
	Texture2D reverseEnemy;
	std::vector<Color> colors;
	Color color;;

	float frameWidth;
	float timer;
	int frame;
	int maxFrames;
};

