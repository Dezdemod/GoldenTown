#include <enemy.h>

Enemy::Enemy()
	: speed((float)(GetRandomValue(1, 3)))
	, goLeft(false)
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

	if (!goLeft) DrawTextureRec
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

void Enemy::movement()
{
	if (!goLeft && position.x >= 1250.0f) goLeft = true;
	else if (!goLeft) position.x += speed;

	if (goLeft && position.x <= 5.0f) goLeft = false;
	else if (goLeft) position.x -= speed;
}