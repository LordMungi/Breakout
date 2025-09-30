#pragma once
#include "Vector.h"

namespace ball
{
	const int maxBalls = 2;

	struct Ball
	{
		utilities::Vector2 position;
		utilities::Vector2 direction;
		double radius;
		double speed;
		bool isInGame;
		double respawnTimer;
	};

	Ball init();
	int getBallsInGame(Ball balls[maxBalls]);
	void move(Ball& ball);
	void draw(Ball ball);
	void launchUp(Ball& ball);
	void bounceHorizontal(Ball& ball);
	void bounceVertical(Ball& ball);
}