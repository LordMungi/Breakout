#include "GameManager.h"
#include <iostream>
#include <sl.h>
#include <ctime>
#include "Config.h"

namespace game
{
	struct Game
	{
		paddle::Paddle paddle;
		ball::Ball ball;
	};

	static Game init()
	{
		srand(time(0));
		Game game;
		game.paddle = paddle::init();
		game.ball = ball::init();
		game.ball.position = { game.paddle.position.x, game.paddle.position.y + game.paddle.size.y * 2};

		return game;
	}

	static void inputUpdate(Game& game)
	{
		if (slGetKey(SL_KEY_RIGHT))
			paddle::moveRight(game.paddle);
		if (slGetKey(SL_KEY_LEFT))
			paddle::moveLeft(game.paddle);
		if (slGetKey(' ') && game.ball.direction.x == 0 && game.ball.direction.y == 0)
			ball::launchUp(game.ball);

	}

	static bool isBallCollidingWallHorizontal(ball::Ball ball)
	{
		return (ball.position.y + ball.radius / 2 >= config::gameHeight ||
			ball.position.y - ball.radius / 2 <= 0);
	}
	static bool isBallCollidingWallVertical(ball::Ball ball)
	{
		return (ball.position.x + ball.radius / 2 >= config::gameWidth ||
			ball.position.x - ball.radius / 2 <= 0);
	}
	static bool isBallCollidingPaddle(ball::Ball ball, paddle::Paddle paddle)
	{
		return (ball.position.x + ball.radius / 2 >= paddle.position.x - paddle.size.x / 2 &&
			ball.position.x - ball.radius / 2 <= paddle.position.x + paddle.size.x / 2 &&
			ball.position.y + ball.radius / 2 >= paddle.position.y - paddle.size.y / 2 &&
			ball.position.y - ball.radius / 2 <= paddle.position.y + paddle.size.y / 2);
	}

	static void bounceBallPaddle(ball::Ball& ball, paddle::Paddle paddle)
	{
		double ballHit = ball.position.x - paddle.position.x;
		double angle = ballHit * 40 / (paddle.size.x / 2);
		ball.direction.x = sin(angle * 3.141592 / 180.0);
		ball.direction.y = cos(angle * 3.141592 / 180.0);
		ball.position.y = paddle.position.y + paddle.size.y / 2 + ball.radius / 2;
	}

	static void updateBall(Game& game)
	{
		if (game.ball.direction.x == 0 && game.ball.direction.y == 0)
			game.ball.position.x = game.paddle.position.x;
		else
			ball::move(game.ball);

		if (isBallCollidingWallVertical(game.ball))
			ball::bounceHorizontal(game.ball);
		if (isBallCollidingWallHorizontal(game.ball))
			ball::bounceVertical(game.ball);
		if (isBallCollidingPaddle(game.ball, game.paddle))
			bounceBallPaddle(game.ball, game.paddle);
	}

	void run()
	{
		Game game = init();

		while (!render::windowShouldClose())
		{
			render::drawBackground();

			inputUpdate(game);
			updateBall(game);

			paddle::draw(game.paddle);
			ball::draw(game.ball);

			render::endDraw();
		}
	}
}