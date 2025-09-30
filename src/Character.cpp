#include "Character.h"
#include <sl.h>
#include "Config.h"
#include "RenderManager.h"

namespace character
{
	static double slidingTime = 0.3;
	static double slidingCooldown = 0.3;

	Character init()
	{
		Character character;
		character.size = { 40.0, 40.0 };
		character.position = { config::gameWidth / 2 , character.size.y / 2 };
		character.paddle = paddle::init();
		character.paddle.position.y = character.position.y + character.size.y / 2 + character.paddle.size.y / 2;
		character.speed = 200;
		character.lives = 3;
		character.isLookingAt = Side::Front;
		character.hasSlide = false;
		character.isSliding = false;
		character.slidingTimer = 0;
		character.slidingCooldownTimer = 0;
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
			if (!character.isSliding && slGetTime() - character.slidingCooldownTimer > slidingCooldown)
			{
				character.size = { 60.0, 30.0 };
				character.position = { character.position.x , character.size.y / 2 };
				character.paddle.position.y = character.position.y + character.size.y / 2 + character.paddle.size.y / 2;
				character.isSliding = true;
				character.slidingTimer = slGetTime();
			}

			if (character.isSliding && slGetTime() - character.slidingTimer < slidingTime)
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
				character.size = { 40.0, 40.0 };
				character.position = { character.position.x , character.size.y / 2 };
				character.paddle.position.y = character.position.y + character.size.y / 2 + character.paddle.size.y / 2;
				character.isSliding = false;
				character.slidingCooldownTimer = slGetTime();
			}
		}
	}

	void draw(Character character)
	{
		render::drawRectangle(character.position, character.size, utilities::RED);
	}
}