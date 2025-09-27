#include "Paddle.h"
#include <sl.h>
#include "Config.h"
#include "RenderManager.h"

namespace paddle
{
	Paddle init()
	{
		Paddle paddle;
		paddle.position = { config::gameWidth / 2 , 20.0 };
		paddle.size = { 50.0, 10.0 };
		paddle.speed = 200;
		return paddle;
	}
	void moveRight(Paddle& paddle)
	{
		if (paddle.position.x + (paddle.size.x / 2) <= config::gameWidth)
			paddle.position.x += paddle.speed * slGetDeltaTime();
	}
	void moveLeft(Paddle& paddle)
	{
		if (paddle.position.x - (paddle.size.x / 2) >= 0)
			paddle.position.x -= paddle.speed * slGetDeltaTime();
	}
	void draw(Paddle paddle)
	{
		render::drawRectangle(paddle.position, paddle.size, { 1,1,1,1 });
	}
}