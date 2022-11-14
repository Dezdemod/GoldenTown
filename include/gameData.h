#pragma once
#include <collectibleFactory.h>
#include <enemy.h>
#include <memory>

struct gameData
{
	gameData();

	void update();
	void reset();

	const int screenWidth, screenHeight;
	int level;
	int enemyCount;
	int money, totalMoney, expenses;
	int collectibleCount, gatheredCollectibles, totalCollectibles;
	float timer, timerBonus;

	const Sound collect, damage, select;

	Texture2D background;
	Music backgroundMusic;
	const Font mainFont;

	const collectibleType type[4];
	std::vector<Collectible> collectibles;
	std::vector<Enemy> enemies;
};