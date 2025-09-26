#include "Paddle.h"
#include <sl.h>
#include "Config.h"
#include "RenderManager.h"

namespace paddle
{
	Paddle init()
	{
		Paddle paddle;
		paddle.position.x = config::gameWidth / 2;
		paddle.position.y = 0.0;
		paddle.size.x = 50.0;
		paddle.size.y = 30.0;
		return paddle;
	}
	void moveRight(Paddle& paddle)
	{
		
	}
	void moveLeft(Paddle& paddle)
	{

	}
	void draw(Paddle paddle)
	{
		render::drawRectangle(paddle.position, paddle.size, { 1,1,1,1 });
	}
}