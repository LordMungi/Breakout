#include "GameManager.h"
#include <iostream>
#include <sl.h>
#include <ctime>
#include "Config.h"
#include "Paddle.h"
#include "Ball.h"
#include "Block.h"
#include "Character.h"
#include "Glass.h"
#include "HUD.h"

namespace game
{
	const int ballStartPoint = 70;


	struct Game
	{
		character::Character character;
		ball::Ball ball;
		block::Block blocks[block::maxWidth][block::maxHeight];
		glass::Glass glasses[glass::max];
		int levelGlasses;
	};

	static Game init()
	{
		srand(time(0));
		Game game;
		game.character = character::init();
		game.ball = ball::init();
		game.ball.position = { game.character.position.x, ballStartPoint };
		game.levelGlasses = 10;
		block::initArray(game.blocks);
		block::setGlasses(game.blocks, game.levelGlasses);
		glass::initArray(game.glasses, game.levelGlasses);

		return game;
	}

	static void inputUpdate(Game& game)
	{
		if (slGetKey(SL_KEY_RIGHT))
			character::moveRight(game.character);
		if (slGetKey(SL_KEY_LEFT))
			character::moveLeft(game.character);
		if (slGetKey(' ') && game.ball.direction.x == 0 && game.ball.direction.y == 0)
			ball::launchUp(game.ball);

	}

	static void breakBlock(block::Block& block, glass::Glass glasses[glass::max])
	{
		block.state = block::State::Broken;
		if (block.hasGlass)
		{
			int glassIndex = glass::getGlassInTable(glasses);
			glasses[glassIndex].state = glass::State::Falling;
			glasses[glassIndex].position = block.position;				
		}
	}

	static block::Side isBallCollidingWall(ball::Ball ball)
	{
		if (ball.position.y + ball.radius / 2 >= config::gameHeight)
			return block::Side::Top;
		if (ball.position.y - ball.radius / 2 <= 0)
			return block::Side::Bottom;
		if (ball.position.x + ball.radius / 2 >= config::gameWidth)
			return block::Side::Right;
		if (ball.position.x - ball.radius / 2 <= 0)
			return block::Side::Left;
		return block::Side::Null;
	}
	static bool isBallCollidingPaddle(ball::Ball ball, paddle::Paddle paddle)
	{
		return (ball.position.x + ball.radius / 2 >= paddle.position.x - paddle.size.x / 2 &&
			ball.position.x - ball.radius / 2 <= paddle.position.x + paddle.size.x / 2 &&
			ball.position.y + ball.radius / 2 >= paddle.position.y - paddle.size.y / 2 &&
			ball.position.y - ball.radius / 2 <= paddle.position.y + paddle.size.y / 2);
	}
	static bool isBallCollidingCharacter(ball::Ball ball, character::Character character)
	{
		return (ball.position.x + ball.radius / 2 >= character.position.x - character.size.x / 2 &&
			ball.position.x - ball.radius / 2 <= character.position.x + character.size.x / 2 &&
			ball.position.y + ball.radius / 2 >= character.position.y - character.size.y / 2 &&
			ball.position.y - ball.radius / 2 <= character.position.y + character.size.y / 2);
	}
	static block::Side isBallCollidingBlock(ball::Ball ball, block::Block block)
	{
		if (ball.position.x + ball.radius / 2 >= block.position.x - block::size.x / 2 &&
			ball.position.x - ball.radius / 2 <= block.position.x + block::size.x / 2 &&
			ball.position.y + ball.radius / 2 >= block.position.y - block::size.y / 2 &&
			ball.position.y - ball.radius / 2 <= block.position.y + block::size.y / 2)
		{
			double distanceLeft =	abs((block.position.x - block::size.x / 2) - (ball.position.x + ball.radius / 2));
			double distanceRight =	abs((block.position.x + block::size.x / 2) - (ball.position.x - ball.radius / 2));
			double distanceBottom = abs((block.position.y - block::size.y / 2) - (ball.position.y + ball.radius / 2));
			double distanceTop =	abs((block.position.y + block::size.y / 2) - (ball.position.y - ball.radius / 2));
			double minDistance = std::min({ distanceLeft, distanceRight, distanceTop, distanceBottom });

			if (minDistance == distanceLeft) return block::Side::Left;
			if (minDistance == distanceRight) return block::Side::Right;
			if (minDistance == distanceBottom) return block::Side::Bottom;
			if (minDistance == distanceTop) return block::Side::Top;
		}
		return block::Side::Null;
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
		if (game.ball.isInGame)
		{
			if (game.ball.direction.x == 0 && game.ball.direction.y == 0)
				game.ball.position.x = game.character.position.x;
			else
				ball::move(game.ball);

			if (isBallCollidingPaddle(game.ball, game.character.paddle))
				bounceBallPaddle(game.ball, game.character.paddle);

			if (isBallCollidingCharacter(game.ball, game.character))
			{
				game.ball.isInGame = false;
				game.ball.respawnTimer = slGetTime();
				game.character.lives--;

			}

			switch (isBallCollidingWall(game.ball))
			{
			case block::Side::Top:
				ball::bounceVertical(game.ball);
				game.ball.position.y = config::gameHeight - game.ball.radius / 2;
				break;
			case block::Side::Bottom:
				ball::bounceVertical(game.ball);
				game.ball.position.y = 0 + game.ball.radius / 2;
				break;
			case block::Side::Right:
				ball::bounceHorizontal(game.ball);
				game.ball.position.x = config::gameWidth - game.ball.radius / 2;
				break;
			case block::Side::Left:
				ball::bounceHorizontal(game.ball);
				game.ball.position.x = 0 + game.ball.radius / 2;
				break;
			}

			bool hasCollided = false;
			for (int i = 0; i < block::maxWidth; i++)
			{
				for (int j = 0; j < block::maxHeight; j++)
				{
					if (game.blocks[i][j].state == block::State::Undamaged && !hasCollided)
					{
						switch (isBallCollidingBlock(game.ball, game.blocks[i][j]))
						{
						case block::Side::Top:
							ball::bounceVertical(game.ball);
							game.ball.position.y = game.blocks[i][j].position.y + block::size.y / 2 + game.ball.radius / 2;
							breakBlock(game.blocks[i][j], game.glasses);							
							hasCollided = true;
							break;
						case block::Side::Bottom:
							ball::bounceVertical(game.ball);
							game.ball.position.y = game.blocks[i][j].position.y - block::size.y / 2 - game.ball.radius / 2;
							breakBlock(game.blocks[i][j], game.glasses);
							hasCollided = true;
							break;
						case block::Side::Left:
							ball::bounceHorizontal(game.ball);
							game.ball.position.x = game.blocks[i][j].position.x - block::size.x / 2 - game.ball.radius / 2;
							breakBlock(game.blocks[i][j], game.glasses);
							hasCollided = true;
							break;
						case block::Side::Right:
							ball::bounceHorizontal(game.ball);
							game.ball.position.x = game.blocks[i][j].position.x + block::size.x / 2 + game.ball.radius / 2;
							breakBlock(game.blocks[i][j], game.glasses);
							hasCollided = true;
							break;
						}
					}
				}
			}
		}
		else if (slGetTime() - game.ball.respawnTimer > 2)
		{
			game.ball = ball::init();
			game.ball.position = { game.character.position.x, ballStartPoint };
		}
	}

	static bool isGlassCollidingBlock(glass::Glass glass, block::Block blocks[block::maxWidth][block::maxHeight])
	{
		int blockColumn = 0;
		for (int i = 0; i < block::maxWidth; i++)
		{
			if (blocks[i][0].position.x == glass.position.x)
				blockColumn = i;
		}

		for (int i = 0; i < block::maxHeight; i++)
		{
			if (blocks[blockColumn][i].state == block::State::Undamaged)
			{
				if (glass.position.y - glass::size.y / 2 <= blocks[blockColumn][i].position.y + block::size.y / 2 &&
					glass.position.y + glass::size.y / 2 >= blocks[blockColumn][i].position.y - block::size.y / 2)
					return true;
			}
		}
		return false;
	}
	static bool isGlassCollidingPaddle(glass::Glass glass, paddle::Paddle paddle)
	{
		return (glass.position.x + glass::size.x / 2 >= paddle.position.x - paddle.size.x / 2 &&
			glass.position.x - glass::size.x / 2 <= paddle.position.x + paddle.size.x / 2 &&
			glass.position.y - glass::size.y / 2 <= paddle.position.y + paddle.size.y / 2 &&
			glass.position.y >= paddle.position.y);
	}

	static void updateGlasses(Game& game)
	{
		for (int i = 0; i < game.levelGlasses; i++)
		{
			if (game.glasses[i].state == glass::State::Falling && !isGlassCollidingBlock(game.glasses[i], game.blocks))
			{
				if (!glass::fall(game.glasses[i]))
					game.character.lives--;

				if (isGlassCollidingPaddle(game.glasses[i], game.character.paddle))
				{
					game.glasses[i].state = glass::State::InTray;
					game.glasses[i].position.y = game.character.paddle.position.y + game.character.paddle.size.y / 2 + glass::size.y / 2;
					game.glasses[i].offset = game.character.position.x - game.glasses[i].position.x;
				}
			}
			if (game.glasses[i].state == glass::State::InTray)
			{
				game.glasses[i].position.x = game.character.position.x - game.glasses[i].offset;
			}
		}
	}

	void run()
	{
		Game game = init();

		while (!render::windowShouldClose() && game.character.lives > 0)
		{
			render::drawBackground();

			inputUpdate(game);
			updateBall(game);
			updateGlasses(game);

			character::draw(game.character);
			paddle::draw(game.character.paddle);
			ball::draw(game.ball);
			block::drawArray(game.blocks);
			glass::drawArray(game.glasses);

			hud::drawLives(game.character);

			render::endDraw();
		}
	}
}