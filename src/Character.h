#pragma once
#include "Vector.h"
#include "Paddle.h"

namespace character
{
	struct Character
	{
		utilities::Vector2 position;
		utilities::Vector2 size;
		paddle::Paddle paddle;
		double speed;
		int lives;
	};

	Character init();
	void moveRight(Character& character);
	void moveLeft(Character& character);
	void draw(Character character);
}