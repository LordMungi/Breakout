#pragma once
#include "Vector.h"

namespace ball
{
	struct Ball
	{
		utilities::Vector2 position;
		utilities::Vector2 direction;
		double radius;
		double speed;
	};

	Ball init();
	void move(Ball& ball);
	void draw(Ball ball);
	void launchUp(Ball& ball);
	void bounceHorizontal(Ball& ball);
	void bounceVertical(Ball& ball);
}