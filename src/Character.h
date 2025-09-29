#pragma once
#include "Vector.h"
#include "Paddle.h"

namespace character
{
	enum class Side
	{
		Front,
		Right,
		Left
	};

	struct Character
	{
		utilities::Vector2 position;
		utilities::Vector2 size;
		Side isLookingAt;

		double speed;
		int lives;

		bool isSliding;
		double slidingTimer;
		double slidingCooldownTimer;
		
		paddle::Paddle paddle;
	};

	Character init();
	void moveRight(Character& character);
	void moveLeft(Character& character);

	void slide(Character& character);

	void draw(Character character);
}