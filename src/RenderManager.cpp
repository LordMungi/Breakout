#include "RenderManager.h"
#include <sl.h>
#include "Config.h"

namespace render
{
	int resWidth = 1080;
	int resHeight = 720;

	void initWindow()
	{		
		slWindow(resWidth, resHeight, "Simple SIGIL Example", false);
	}
	void closeWindow()
	{
		slClose();
	}
	bool windowShouldClose()
	{
		return slShouldClose();
	}
	void drawBackground(utilities::Color color)
	{
		slSetBackColor(color.r, color.g, color.b);
	}
	void drawRectangle(utilities::Vector2 position, utilities::Vector2 size, utilities::Color color)
	{
		position = gameToScreen(position);
		slSetForeColor(color.r, color.g, color.b, color.a);
		slRectangleFill(position.x, position.y, size.x, size.y);
	}
	void drawCircle(utilities::Vector2 position, double radius, utilities::Color color)
	{
		position = gameToScreen(position);
		slSetForeColor(color.r, color.g, color.b, color.a);
		slCircleFill(position.x, position.y, radius, 100);
	}
	void endDraw()
	{
		slRender();
	}

	utilities::Vector2 gameToScreen(utilities::Vector2 vector)
	{
		return { vector.x * resWidth / config::gameWidth, vector.y * (resHeight - resHeight / 5) / config::gameHeight };
	}
}