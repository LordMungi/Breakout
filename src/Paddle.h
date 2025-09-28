#pragma once
#include "Vector.h"

namespace paddle
{
	struct Paddle
	{
		utilities::Vector2 position;
		utilities::Vector2 size;
	};

	Paddle init();

	void draw(Paddle paddle);
}