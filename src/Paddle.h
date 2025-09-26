#pragma once
#include "Vector.h"

namespace paddle
{
	struct Paddle
	{
		utilities::Vector2 position;
		utilities::Vector2 size;
		double speed;
	};

	Paddle init();
	void moveRight(Paddle& paddle);
	void moveLeft(Paddle& paddle);
	void draw(Paddle paddle);
}