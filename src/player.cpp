#include <player.h>

Player::Player(std::shared_ptr<gameData> gamedata)
	: lives(3)
	, canMove(true)
	, ascend(false)
	, cartSpeed(3.0f)
	, hookSpeed(4.0f)
	, bonusHookSpeed(0.0f)
	, reel(LoadSound("audio/reel.mp3"))
	, playerTexture(LoadTexture("player/player.png"))
	, claw(LoadTexture("player/claw.png"))
	, position(Vector2{605.0f, 125.0f})
	, ropeStart(Vector2{ 622.0f, 150.0f })
	, ropeEnd(Vector2{ 622.0f, 200.0f })
	, data(gamedata)
{
}

void Player::draw()
{
	DrawTexture(playerTexture, position.x, position.y, WHITE);
	DrawLineEx(ropeStart, ropeEnd, 3.0f, BROWN);
	DrawTexture(claw, ropeEnd.x - 10.0f, ropeEnd.y, WHITE);

	canMove ? this->movement() : this->useHook();
}

void Player::movement()
{
	position.x += cartSpeed;
	ropeStart.x = position.x + 18.0f;
	ropeEnd.x = position.x + 18.0f;
	if (position.x >= 1243.0f || position.x <= 4.0f) cartSpeed *= -1;

	if (IsKeyPressed(KEY_SPACE))
	{
		canMove = false;
		PlaySound(reel);
	}
}

void Player::useHook()
{
	if (!ascend)
	{
		hookSpeed = 4.0f + bonusHookSpeed;
		ropeEnd.y >= 700.0f ? ascend = true : ropeEnd.y += hookSpeed;
	}
	else
	{
		if (ropeEnd.y <= 200.0f)
		{
			ascend = false;
			canMove = true;
			StopSound(reel);
		}
		else ropeEnd.y -= hookSpeed;
	}
	this->checkCollectibleCollision();
	this->checkEnemyCollision();
}

void Player::checkCollectibleCollision()
{
	for (int i = 0; i < data->collectibleCount; i++)
	{
		if (CheckCollisionPointCircle(ropeEnd, data->collectibles[i].getPosition(), 21.0f))
		{
			ascend = true;
			hookSpeed = data->collectibles[i].getWeight() + bonusHookSpeed;
			data->collectibles[i].setX(ropeEnd.x);
			data->collectibles[i].setY(ropeEnd.y + 10.0f);
			if (ropeEnd.y <= 200.0f)
			{
				PlaySound(data->collect);
				data->collectibles[i].setY(750.0f);
				data->timer += data->collectibles[i].getTimeBonus();
				data->money += data->collectibles[i].getValue();
				data->totalMoney += data->collectibles[i].getValue();
				hookSpeed = 4.0f + bonusHookSpeed;
				data->gatheredCollectibles++;
				data->totalCollectibles++;
			}
		}
	}
}

void Player::checkEnemyCollision()
{
	for (int i = 0; i < data->enemyCount; i++)
	{
		if (CheckCollisionPointCircle(ropeEnd, data->enemies[i].getPosition(), 19.0f))
		{
			ascend = true;
			data->enemies[i].stopMovement();
			hookSpeed = 4.0f + bonusHookSpeed;
			data->enemies[i].setX(ropeEnd.x);
			data->enemies[i].setY(ropeEnd.y + 10.0f);
			if (ropeEnd.y <= 200.0f)
			{
				PlaySound(data->damage);
				lives--;
				data->enemies[i].setY(750.0f);
			}
		}
	}
}

void Player::changeHook(const char* textureName, float speed)
{
	UnloadTexture(claw);
	claw = LoadTexture(textureName);
	bonusHookSpeed = speed;
}

void Player::changePlayer(const char* textureName, float speed)
{
	UnloadTexture(playerTexture); 
	playerTexture = LoadTexture(textureName);
	cartSpeed = speed;
}

void Player::resetPosition()
{
	position.x = 605.0f;
	ropeStart = { 622.0f, 150.0f };
	ropeEnd = { 622.0f, 200.0f };
	canMove = true;
	ascend = false;
}

void Player::reset()
{
	this->resetPosition();
	this->stopSound();
	bonusHookSpeed = 0.0f;
	cartSpeed = 3.0f;
	lives = 3;

	UnloadTexture(playerTexture);
	playerTexture = LoadTexture("player/player.png");

	UnloadTexture(claw);
	claw = LoadTexture("player/claw.png");
}