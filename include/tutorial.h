#pragma once
#include <raylib/raylib.h>

class Tutorial
{
public:
	Tutorial();
	~Tutorial();

	void draw();

private:
	const Texture2D tutorialScreen;
	const Sound select;
};