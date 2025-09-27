#pragma once
#include "Color.h"
#include "Vector.h"

namespace render
{
	void initWindow();
	void closeWindow();
	bool windowShouldClose();

	void drawBackground();
	void drawRectangle(utilities::Vector2 position, utilities::Vector2 size, utilities::Color color);
	void drawCircle(utilities::Vector2 position, double radius, utilities::Color color);
	void endDraw();
}