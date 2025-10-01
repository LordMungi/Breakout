#include "Paddle.h"
#include <sl.h>
#include "Config.h"
#include "RenderManager.h"

namespace paddle
{
	utilities::Vector2 defaultSize = { 50.0, 6.0 };
	Paddle init()
	{
		Paddle paddle;
		paddle.position = { config::gameWidth / 2 , 0.0 };
		paddle.size = defaultSize;
		return paddle;
	}

	void draw(Paddle paddle)
	{
		if (paddle.size.x == defaultSize.x)
			render::drawSprite(textures::trayNormal, paddle.position, paddle.size);
		else
			render::drawSprite(textures::trayGold, paddle.position, paddle.size);
	}
}