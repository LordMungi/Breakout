#include "RenderManager.h"
#include "Paddle.h"

int main()
{
	render::initWindow();
	paddle::Paddle paddle = paddle::init();

	while (!render::windowShouldClose())
	{
		render::drawBackground({ 0,0,0,1 });
		paddle::draw(paddle);

		render::endDraw();
	}
	render::closeWindow();

	return 0;
}