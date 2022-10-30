#include <player.h>

Player::Player(std::shared_ptr<gameData> gamedata)
	: canMove(true)
	, goLeft(false)
	, ascend(false)
	, lives(3)
	, positionX(605.0f)
	, positionY(125.0f)
	, cartSpeed(3.0f)
	, hookSpeed(4.0f)
	, bonusHookSpeed(0.0f)
	, reel(LoadSound("audio/reel.mp3"))
	, playerTexture(LoadTexture("player/player.png"))
	, claw(LoadTexture("player/claw.png"))
	, ropeStart(Vector2{ 622.0f, 150.0f })
	, ropeEnd(Vector2{ 622.0f, 200.0f })
	, data(gamedata)
{
}

void Player::draw()
{
	DrawTexture(playerTexture, positionX, positionY, WHITE);
	DrawLineEx(ropeStart, ropeEnd, 3.0f, BROWN);
	DrawTexture(claw, ropeEnd.x - 10.0f, ropeEnd.y, WHITE);

	canMove ? this->movement() : this->useHook();
}

void Player::movement()
{
	if (!goLeft && positionX >= 1243.0f) goLeft = true;
	else if (!goLeft) positionX += cartSpeed;

	if (goLeft && positionX <= 4.0f) goLeft = false;
	else if (goLeft) positionX -= cartSpeed;

	ropeStart.x = positionX + 18.0f;
	ropeEnd.x = positionX + 18.0f;
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
	positionX = 605.0f;
	positionY = 125.0f;
	ropeStart = { 622.0f, 150.0f };
	ropeEnd = { 622.0f, 200.0f };
	canMove = true;
	goLeft = false;
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