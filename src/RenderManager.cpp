#include "RenderManager.h"
#include <sl.h>
#include "Config.h"

namespace render
{
	static int resWidth = 1080;
	static int resHeight = 720;

	static utilities::Vector2 posToScreen(utilities::Vector2 position)
	{
		int gameResWidth = 4 * resHeight / 3;
		int marginHeight = resHeight / 5;
		int marginWidth = (resWidth - gameResWidth) / 2;
		return { position.x * gameResWidth / config::gameWidth + marginWidth, position.y * (resHeight - marginHeight) / config::gameHeight + marginHeight };
	}
	static utilities::Vector2 sizeToScreen(utilities::Vector2 size)
	{
		int gameResWidth = 4 * resHeight / 3;
		int marginHeight = resHeight / 5;
		int marginWidth = (resWidth - gameResWidth) / 2;
		return { size.x * gameResWidth / config::gameWidth, size.y * (resHeight - marginHeight) / config::gameHeight};
	}

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
	void drawBackground()
	{
		slSetBackColor(0.1, 0.1, 0.1);
		drawRectangle({ config::gameWidth / 2, config::gameHeight / 2 }, { config::gameWidth, config::gameHeight }, { 0, 0, 0, 1 });
	}
	void drawRectangle(utilities::Vector2 position, utilities::Vector2 size, utilities::Color color)
	{
		position = posToScreen(position);
		size = sizeToScreen(size);
		slSetForeColor(color.r, color.g, color.b, color.a);
		slRectangleFill(position.x, position.y, size.x, size.y);
	}
	void drawCircle(utilities::Vector2 position, double radius, utilities::Color color)
	{
		position = posToScreen(position);
		slSetForeColor(color.r, color.g, color.b, color.a);
		slCircleFill(position.x, position.y, radius, 100);
	}
	void endDraw()
	{
		slRender();
	}


}