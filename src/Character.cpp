#include "Character.h"
#include <sl.h>
#include "Config.h"
#include "RenderManager.h"

namespace character
{
	Character init()
	{
		Character character;
		character.position = { config::gameWidth / 2 , 20.0 };
		character.size = { 40.0, 40.0 };
		character.paddle = paddle::init();
		character.speed = 200;
		character.lives = 3;
		return character;
	}

	void moveRight(Character& character)
	{
		if (character.position.x + (character.paddle.size.x / 2) <= config::gameWidth)
		{			
			character.position.x += character.speed * slGetDeltaTime();
			character.paddle.position.x += character.speed * slGetDeltaTime();
		}
	}
	void moveLeft(Character& character)
	{
		if (character.position.x - (character.paddle.size.x / 2) >= 0)
		{
			character.position.x -= character.speed * slGetDeltaTime();
			character.paddle.position.x -= character.speed * slGetDeltaTime();
		}
	}

	void draw(Character character)
	{
		render::drawRectangle(character.position, character.size, { 1, 0, 0, 1 });
	}
}