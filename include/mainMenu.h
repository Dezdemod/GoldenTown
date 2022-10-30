#pragma once
#include <raylib/raylib.h>
#include <utility>

class mainMenu
{
public:
	mainMenu();
	~mainMenu();

	void drawMenu();

private:
	void controls();

	bool hasStarted;
	const Sound select;
	const Texture2D menu;
	std::pair<const Texture2D, Vector2> arrow;
};