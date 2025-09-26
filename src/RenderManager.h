#pragma once
#include "Color.h"
#include "Vector.h"

namespace render
{
	void initWindow();
	void closeWindow();
	bool windowShouldClose();

	void drawBackground(utilities::Color color);
	void drawRectangle(utilities::Vector2 position, utilities::Vector2 size, utilities::Color color);
	void drawCircle(utilities::Vector2 position, double radius, utilities::Color color);
	void endDraw();

	utilities::Vector2 gameToScreen(utilities::Vector2 position);
}