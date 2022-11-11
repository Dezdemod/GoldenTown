#pragma once
#include <gameData.h>

class Player
{
public:
	Player(std::shared_ptr<gameData> gamedata);

	void draw();
	inline int getLives() const { return lives; }
	inline void pauseSound() { PauseSound(reel); }
	inline void resumeSound() { ResumeSound(reel); }
	inline void stopSound() { StopSound(reel); }
	void changeHook(const char* textureName, float speed);
	void changePlayer(const char* textureName, float speed);
	void resetPosition();
	void reset();

private:
	void movement();
	void useHook();
	void checkCollectibleCollision();
	void checkEnemyCollision();

	int lives;

	bool canMove;
	bool ascend;

	float cartSpeed;
	float hookSpeed;
	float bonusHookSpeed;

	const Sound reel;

	Texture2D playerTexture;
	Texture2D claw;
	Vector2 position;
	Vector2 ropeStart;
	Vector2 ropeEnd;

	std::shared_ptr<gameData> data;
};