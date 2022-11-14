#include <enemy.h>

Enemy::Enemy()
	: speed((float)(GetRandomValue(1, 3)))
	, canMove(true)
	, position(Vector2{ (float)(GetRandomValue(5, 1250)), (float)(GetRandomValue(300, 685)) })
	, enemy(LoadTexture("enemy/enemy.png"))
	, reverseEnemy(LoadTexture("enemy/enemyReverse.png"))
	, colors({ LIME, ORANGE, BROWN, GRAY, VIOLET})
	, color(colors[GetRandomValue(0, 4)])
	, frameWidth((float)(enemy.width / 2))
	, timer(0.0f)
	, frame(0)
	, maxFrames((int)enemy.width / (int)frameWidth)
{
}

void Enemy::draw()
{
	timer += GetFrameTime();
	if (timer > 0.2f) timer = 0.0f, frame++;
	frame %= maxFrames;

	if (speed > 0) DrawTextureRec
	(
		enemy,
		Rectangle{ frameWidth * frame, 0, frameWidth, (float)enemy.height },
		Vector2{ position.x - 16.0f, position.y - 5.0f },
		color
	);
	else DrawTextureRec
	(
		reverseEnemy,
		Rectangle{ frameWidth * frame, 0, frameWidth, (float)enemy.height },
		Vector2{ position.x - 16.0f, position.y - 5.0f },
		color
	);

	if (canMove) this->movement();
}

void inline Enemy::movement()
{
	if (position.x >= 1265.0f || position.x <= 10.0f) speed *= -1;
	position.x += speed;
}