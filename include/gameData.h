#pragma once
#include <collectibleFactory.h>
#include <enemy.h>
#include <memory>

struct gameData
{
	gameData();

	void update();
	void reset();

	const int screenWidth;
	const int screenHeight;
	int level;
	int money;
	int totalMoney;
	int expenses;
	int enemyCount;
	int collectibleCount;
	int gatheredCollectibles;
	int totalCollectibles;
	float timer;
	float timerBonus;

	const Sound collect;
	const Sound damage;
	const Sound select;

	Texture2D background;
	Music backgroundMusic;
	Font mainFont;

	const collectibleType type[4] = { stone, gold, diamond, ruby };
	std::vector<Collectible> collectibles;
	std::vector<Enemy> enemies;
};