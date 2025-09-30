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

namespace game
{
	const int ballStartPoint = 70;
	double pauseTimer = 0;

	OnExit onExit;

	struct Game
	{
		character::Character character;
		ball::Ball balls[ball::maxBalls];
		block::Block blocks[block::maxWidth][block::maxHeight];
		glass::Glass glasses[glass::max];
		int levelGlasses;
		bool isArcade;
		bool isRunning;
		bool shouldEnd;
	};

	static Game init(Mode mode, int level)
	{
		srand(time(0));
		Game game;

		game.isArcade = mode == Mode::Arcade;

		game.character = character::init();
		game.balls[0] = ball::init();
		game.balls[0].position = { game.character.position.x, ballStartPoint };
		game.balls[0].isInGame = true;

		game.balls[1] = ball::init();

		game.levelGlasses = game.isArcade ? 3 : glass::getGlassesInLevel(level);
		block::initArray(game.blocks, level);
		block::setGlasses(game.blocks, game.levelGlasses);
		glass::initArray(game.glasses, game.levelGlasses);
		glass::setPowerups(game.glasses, game.levelGlasses);

		game.isRunning = true;
		game.shouldEnd = false;

		return game;
	}

	static void inputUpdate(Game& game)
	{
		if (game.isRunning)
		{
			if (slGetKey(SL_KEY_RIGHT) && game.character.state == character::State::Neutral)
				character::moveRight(game.character);
			else if (slGetKey(SL_KEY_LEFT) && game.character.state == character::State::Neutral)
				character::moveLeft(game.character);
			else if (game.character.state == character::State::Neutral)
				game.character.isLookingAt = character::Side::Front;
			if (slGetKey('x') || slGetKey('X') && game.character.state == character::State::Neutral)
				character::slide(game.character);
			if (slGetKey(' ') && game.balls[0].direction.x == 0 && game.balls[0].direction.y == 0)
				ball::launchUp(game.balls[0]);
		}
		if (slGetKey(SL_KEY_ESCAPE) && slGetTime() - pauseTimer > 0.2)
		{
			pauseTimer = slGetTime();
			game.isRunning = !game.isRunning;
			game.character.isPaused = !game.isRunning;
		}
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
		for (int i = 0; i < ball::maxBalls; i++)
		{
			if (game.balls[i].isInGame)
			{
				if (game.balls[i].direction.x == 0 && game.balls[i].direction.y == 0)
					game.balls[i].position.x = game.character.position.x;
				else
					ball::move(game.balls[i]);

				if (isBallCollidingPaddle(game.balls[i], game.character.paddle))
					bounceBallPaddle(game.balls[i], game.character.paddle);

				if (isBallCollidingCharacter(game.balls[i], game.character))
				{
					game.balls[i].isInGame = false;
					game.character.lives--;
					if (ball::getBallsInGame(game.balls) < 1)
						game.balls[0].respawnTimer = slGetTime();
				}

				switch (isBallCollidingWall(game.balls[i]))
				{
				case block::Side::Top:
					ball::bounceVertical(game.balls[i]);
					game.balls[i].position.y = config::gameHeight - game.balls[i].radius / 2;
					break;
				case block::Side::Bottom:
					if (game.isArcade)
					{
						game.balls[i].isInGame = false;
						if (ball::getBallsInGame(game.balls) < 1)
						{
							game.balls[0].respawnTimer = slGetTime();
							game.character.lives--;
						}
					}

					ball::bounceVertical(game.balls[i]);
					game.balls[i].position.y = 0 + game.balls[i].radius / 2;
					break;
				case block::Side::Right:
					ball::bounceHorizontal(game.balls[i]);
					game.balls[i].position.x = config::gameWidth - game.balls[i].radius / 2;
					break;
				case block::Side::Left:
					ball::bounceHorizontal(game.balls[i]);
					game.balls[i].position.x = 0 + game.balls[i].radius / 2;
					break;
				}

				bool hasCollided = false;
				for (int j = 0; j < block::maxWidth; j++)
				{
					for (int k = 0; k < block::maxHeight; k++)
					{
						if (game.blocks[j][k].state == block::State::Undamaged && !hasCollided)
						{
							switch (isBallCollidingBlock(game.balls[i], game.blocks[j][k]))
							{
							case block::Side::Top:
								std::cout << "Ball " << j << " Top\n";
								ball::bounceVertical(game.balls[i]);
								game.balls[i].position.y = game.blocks[j][k].position.y + block::size.y / 2 + game.balls[i].radius / 2;
								breakBlock(game.blocks[j][k], game.glasses);
								hasCollided = true;
								break;
							case block::Side::Bottom:
								std::cout << "Ball " << j << " Bottom\n";
								ball::bounceVertical(game.balls[i]);
								game.balls[i].position.y = game.blocks[j][k].position.y - block::size.y / 2 - game.balls[i].radius / 2;
								breakBlock(game.blocks[j][k], game.glasses);
								hasCollided = true;
								break;
							case block::Side::Left:
								std::cout << "Ball " << j << " Left\n";
								ball::bounceHorizontal(game.balls[i]);
								game.balls[i].position.x = game.blocks[j][k].position.x - block::size.x / 2 - game.balls[i].radius / 2;
								breakBlock(game.blocks[j][k], game.glasses);
								hasCollided = true;
								break;
							case block::Side::Right:
								std::cout << "Ball " << j << " Right\n";
								ball::bounceHorizontal(game.balls[i]);
								game.balls[i].position.x = game.blocks[j][k].position.x + block::size.x / 2 + game.balls[i].radius / 2;
								breakBlock(game.blocks[j][k], game.glasses);
								hasCollided = true;
								break;
							}
						}
					}
				}
			}
			else if (ball::getBallsInGame(game.balls) < 1 && slGetTime() - game.balls[0].respawnTimer > 2)
			{
				game.balls[0] = ball::init();
				game.balls[0].isInGame = true;
				game.balls[0].position = { game.character.position.x, ballStartPoint };
			}
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
					switch (game.glasses[i].type)
					{
					case glass::Type::Slide:
						game.character.hasSlide = true;
						break;
					case glass::Type::Double:
					{
						game.balls[1].isInGame = true;
						game.balls[1].position = game.balls[0].position;
						ball::launchUp(game.balls[1]);
						break;
					}
					case glass::Type::Long:
						game.character.paddle.size.x *= 1.2;
						break;
					}
				}
			}
			if (game.glasses[i].state == glass::State::InTray)
			{
				game.glasses[i].position.x = game.character.position.x - game.glasses[i].offset;
				game.glasses[i].position.y = game.character.paddle.position.y + game.character.paddle.size.y / 2 + glass::size.y / 2;
			}
		}
	}

	static void updateCharacter(Game& game)
	{
		if (game.character.state == character::State::Sliding)
			character::slide(game.character);

		if (game.isArcade)
		{
			if (block::areAllBlocksDestroyed(game.blocks))
			{
				for (int i = 0; i < ball::maxBalls; i++)
				{
					game.balls[i].isInGame = false;
				}
				game.character.state = character::State::Win;
			}
		}
		else if (glass::getGlassesFallen(game.glasses) >= game.levelGlasses)
		{
			for (int i = 0; i < ball::maxBalls; i++)
			{
				game.balls[i].isInGame = false;
			}
			game.character.state = character::State::Win;
		}

		else if (game.character.lives < 1)
		{
			for (int i = 0; i < ball::maxBalls; i++)
			{
				game.balls[i].isInGame = false;
			}
			game.character.state = character::State::Lose;
		}
	}

	static void exitButton(Game& game)
	{
		utilities::Vector2 position = { render::resolution.x * 0.97, render::resolution.y * 0.9 };
		double size = render::resolution.y * 0.05;
		bool isSelected = false;

		if (hud::isMouseCollidingTextRight(position, size, "Exit"))
		{
			isSelected = true;
			if (slGetMouseButton(SL_MOUSE_BUTTON_LEFT))
			{
				game.shouldEnd = true;
				onExit = OnExit::Quit;
			}
		}
		hud::drawButton("Exit", position, size, isSelected);
	}

	static void retryButton(Game& game)
	{
		utilities::Vector2 position = { render::resolution.x * 0.97, render::resolution.y * 0.85 };
		double size = render::resolution.y * 0.05;
		bool isSelected = false;

		if (hud::isMouseCollidingTextRight(position, size, "Retry"))
		{
			isSelected = true;
			if (slGetMouseButton(SL_MOUSE_BUTTON_LEFT))
			{
				game.shouldEnd = true;
				onExit = OnExit::Retry;
			}
		}

		hud::drawButton("Retry", position, size, isSelected);
	}

	static void nextButton(Game& game)
	{
		utilities::Vector2 position = { render::resolution.x * 0.97, render::resolution.y * 0.8 };
		double size = render::resolution.y * 0.05;
		bool isSelected = false;

		if (hud::isMouseCollidingTextRight(position, size, "Next"))
		{
			isSelected = true;
			if (slGetMouseButton(SL_MOUSE_BUTTON_LEFT))
			{
				game.shouldEnd = true;
				onExit = OnExit::Next;
			}
		}

		hud::drawButton("Next", position, size, isSelected);
	}

	static void drawHud(Game& game)
	{

		hud::drawLives(game.character);
		if(!game.isArcade)
			hud::drawGlassesCaught(game.glasses, game.levelGlasses);
		switch (game.character.state)
		{
		case character::State::Win:
			hud::drawWin();
			exitButton(game);
			retryButton(game);
			nextButton(game);
			break;
		case character::State::Lose:
			hud::drawGameOver();
			exitButton(game);
			retryButton(game);
			break;
		default:
			if (!game.isRunning)
			{
				hud::drawPaused();
				exitButton(game);
				retryButton(game);
				nextButton(game);
			}
			break;
		}
	}

	OnExit run(Mode mode, int level)
	{
		Game game = init(mode, level);

		while (!render::windowShouldClose() && !game.shouldEnd)
		{
			render::drawGameBackground();

			inputUpdate(game);
			if (game.isRunning)
			{
				updateBall(game);
				updateGlasses(game);
				updateCharacter(game);
			}

			character::draw(game.character);
			paddle::draw(game.character.paddle);
			ball::draw(game.balls[0]);
			ball::draw(game.balls[1]);
			block::drawArray(game.blocks);
			glass::drawArray(game.glasses);
			drawHud(game);
			render::nextFrame(game.isRunning);

			render::endDraw();
		}

		return onExit;
	}
}