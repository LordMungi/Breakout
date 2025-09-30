#include "Ball.h"
#include <iostream>
#include <sl.h>
#include "Config.h"
#include "RenderManager.h"

namespace ball
{
	Ball init()
	{
		Ball ball;
		ball.position = { 0.0, 0.0 };
		ball.direction = { 0.0, 0.0 };
		ball.radius = 8;
		ball.speed = 150;
		ball.isInGame = false;
		return ball;
	}

	int getBallsInGame(Ball balls[maxBalls])
	{
		int counter = 0;
		for (int i = 0; i < maxBalls; i++)
		{
			if (balls[i].isInGame)
				counter++;
		}
		return counter;
	}

	void move(Ball& ball)
	{		
		ball.position.x += ball.direction.x * ball.speed * slGetDeltaTime();
		ball.position.y += ball.direction.y * ball.speed * slGetDeltaTime();
	}
	
	void draw(Ball ball)
	{
		if (ball.isInGame)
			render::drawCircle(ball.position, ball.radius, utilities::WHITE);
	}

	void launchUp(Ball& ball)
	{
		ball.direction.x = (double)(rand() % 8000) / 10000.0 - 0.4;
		ball.direction.y = 1.0f - fabs(ball.direction.x);
	}

	void bounceHorizontal(Ball& ball)
	{
		ball.direction.x *= -1;
	}
	void bounceVertical(Ball& ball)
	{
		ball.direction.y *= -1;
	}
}