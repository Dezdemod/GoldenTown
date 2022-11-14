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
	void inline movement();

	float speed;
	bool canMove;

	Vector2 position;
	Texture2D enemy, reverseEnemy;
	std::vector<Color> colors;
	Color color;;

	float frameWidth, timer;
	int frame, maxFrames;
};

