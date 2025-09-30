#pragma once
#include "Vector.h"
#include "Paddle.h"

namespace character
{
	enum class State
	{
		Neutral,
		Sliding,
		Win,
		Lose
	};

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
		State state;

		double speed;
		int lives;

		bool hasSlide;
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