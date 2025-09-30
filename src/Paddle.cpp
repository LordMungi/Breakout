#include "Paddle.h"
#include <sl.h>
#include "Config.h"
#include "RenderManager.h"

namespace paddle
{
	Paddle init()
	{
		Paddle paddle;
		paddle.position = { config::gameWidth / 2 , 0.0 };
		paddle.size = { 50.0, 6.0 };
		return paddle;
	}

	void draw(Paddle paddle)
	{
		//render::drawSprite(textures::tray, paddle.position, paddle.size);
		render::drawRectangle(paddle.position, paddle.size, utilities::WHITE);
	}
}