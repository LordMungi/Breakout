#pragma once
#include <string>
#include "Character.h"
#include "Glass.h"

namespace hud
{
	bool isMouseCollidingText(utilities::Vector2 position, double fontSize, std::string text);
	void drawExit(utilities::Vector2 position, double size, bool isSelected);
	void drawGlassesCaught(glass::Glass glasses[glass::max], int levelGlasses);
	void drawLives(character::Character character);
	void drawGameOver();
	void drawPaused();
	void drawWin();
}