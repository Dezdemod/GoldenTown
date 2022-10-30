#include <gameData.h>

gameData::gameData()
	: screenWidth(1280)
	, screenHeight(720)
	, level(1)
	, money(0)
	, totalMoney(0)
	, expenses(50)
	, enemyCount(1)
	, collectibleCount(5)
	, gatheredCollectibles(0)
	, totalCollectibles(0)
	, timer(25.0f)
	, timerBonus(0.0f)
	, collect(LoadSound("audio/collect.mp3"))
	, damage(LoadSound("audio/damage.mp3"))
	, select(LoadSound("audio/select.wav"))
	, background(LoadTexture("map/day.png"))
	, backgroundMusic(LoadMusicStream("audio/music.mp3"))
	, collectibles(20, generateCollectible(stone))
	, enemies(5)

{
	SetSoundVolume(damage, 0.5f);
	for (int i = 0; i < collectibleCount; i++) collectibles[i] = generateCollectible(type[GetRandomValue(0, 3)]);
}

void gameData::update()
{
	level++;
	gatheredCollectibles = 0;
	timer = 25.0f + timerBonus;

	if (level % 3 == 0 && expenses < 500) expenses += 90;
	if (collectibleCount < 20)
	{
		timerBonus += 0.34f;
		collectibleCount++;
		if (level % 3 == 0 && enemyCount < 5) enemyCount++;
	}

	for (int i = 0; i < collectibleCount; i++) collectibles[i] = generateCollectible(type[GetRandomValue(0, 3)]);
	for (int i = 0; i < enemyCount; i++) enemies[i] = Enemy();

	if (level % 2 == 0)
	{
		UnloadTexture(background);
		background = LoadTexture("map/night.png");
	}
	else
	{
		UnloadTexture(background);
		background = LoadTexture("map/day.png");
	}
}

void gameData::reset()
{
	level = 1;
	money = 0;
	totalMoney = 0;
	expenses = 100;
	enemyCount = 1;
	collectibleCount = 5;
	gatheredCollectibles = 0;
	totalCollectibles = 0;
	timer = 25.0f;
	timerBonus = 0.0f;
	UnloadTexture(background);
	background = LoadTexture("map/day.png");
	StopMusicStream(backgroundMusic);
	PlayMusicStream(backgroundMusic);
	for (int i = 0; i < collectibleCount; i++) collectibles[i] = generateCollectible(type[GetRandomValue(0, 3)]);
	for (int i = 0; i < enemyCount; i++) enemies[i] = Enemy();
}