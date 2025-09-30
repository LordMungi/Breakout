#include "Character.h"
#include <sl.h>
#include "Config.h"
#include "RenderManager.h"

namespace character
{
	static double slidingTime = 0.3;
	static double slidingCooldown = 0.3;

	const utilities::Vector2 defaultSize = { 40, 50 };

	Character init()
	{
		Character character;
		character.size = defaultSize;
		character.position = { config::gameWidth / 2 , character.size.y / 2 };
		character.paddle = paddle::init();
		character.paddle.position.y = character.position.y + character.size.y / 2 + character.paddle.size.y / 2;
		character.speed = 150;
		character.lives = 3;
		character.isLookingAt = Side::Front;
		character.hasSlide = false;
		character.slidingTimer = 0;
		character.slidingCooldownTimer = 0;
		character.state = State::Neutral;
		return character;
	}

	void moveRight(Character& character)
	{
		character.isLookingAt = Side::Right;
		if (character.position.x + (character.paddle.size.x / 2) <= config::gameWidth)
		{			
			character.position.x += character.speed * slGetDeltaTime();
			character.paddle.position.x += character.speed * slGetDeltaTime();
		}
	}
	void moveLeft(Character& character)
	{
		character.isLookingAt = Side::Left;
		if (character.position.x - (character.paddle.size.x / 2) >= 0)
		{
			character.position.x -= character.speed * slGetDeltaTime();
			character.paddle.position.x -= character.speed * slGetDeltaTime();
		}
	}

	void slide(Character& character)
	{
		if (character.hasSlide)
		{
			if (character.state != State::Sliding && slGetTime() - character.slidingCooldownTimer > slidingCooldown)
			{
				character.size = { defaultSize.x * 1.2, defaultSize.y * 0.8 };
				character.position = { character.position.x , character.size.y / 2 };
				character.paddle.position.y = character.position.y + character.size.y / 2 + character.paddle.size.y / 2;
				character.state = State::Sliding;
				character.slidingTimer = slGetTime();
			}

			if (character.state == State::Sliding && slGetTime() - character.slidingTimer < slidingTime)
			{
				switch (character.isLookingAt)
				{
				case Side::Front:
					break;
				case Side::Right:
					if (character.position.x + (character.paddle.size.x / 2) <= config::gameWidth)
					{
						character.position.x += character.speed * slGetDeltaTime() * 2;
						character.paddle.position.x += character.speed * slGetDeltaTime() * 2;
					}
					break;
				case Side::Left:
					if (character.position.x - (character.paddle.size.x / 2) >= 0)
					{
						character.position.x -= character.speed * slGetDeltaTime() * 2;
						character.paddle.position.x -= character.speed * slGetDeltaTime() * 2;
					}
					break;
				}
			}
			else
			{
				character.size = defaultSize;
				character.position = { character.position.x , character.size.y / 2 };
				character.paddle.position.y = character.position.y + character.size.y / 2 + character.paddle.size.y / 2;
				character.state = State::Neutral;
				character.slidingCooldownTimer = slGetTime();
			}
		}
	}

	void draw(Character character)
	{
		render::drawSprite(textures::maid, character.position, character.size);
		//render::drawRectangle(character.position, character.size, utilities::RED);
	}
}