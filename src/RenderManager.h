#pragma once
#include "Color.h"
#include <iostream>
#include "Vector.h"

namespace render
{
	extern utilities::Vector2 resolution;

	utilities::Vector2 gamePosToScreen(utilities::Vector2 position);
	utilities::Vector2 gameSizeToScreen(utilities::Vector2 size);

	void initWindow();
	void closeWindow();
	void loadTextures();
	bool windowShouldClose();

	void drawBackground();
	void drawRectangle(utilities::Vector2 position, utilities::Vector2 size, utilities::Color color);
	void drawCircle(utilities::Vector2 position, double radius, utilities::Color color);
	void drawSprite(int texture, utilities::Vector2 position, utilities::Vector2 size);
	void drawText(utilities::Vector2 position, double size, std::string text, utilities::Color color);

	void endDraw();
}