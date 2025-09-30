#pragma once
#include <string>
#include "Character.h"
#include "Glass.h"

namespace hud
{
	bool isMouseCollidingTextLeft(utilities::Vector2 position, double fontSize, std::string text);
	bool isMouseCollidingTextRight(utilities::Vector2 position, double fontSize, std::string text);
	void drawButton(std::string text, utilities::Vector2 position, double size, bool isSelected);
	void drawGlassesCaught(glass::Glass glasses[glass::max], int levelGlasses);
	void drawLives(character::Character character);
	void drawGameOver();
	void drawPaused();
	void drawWin();
}