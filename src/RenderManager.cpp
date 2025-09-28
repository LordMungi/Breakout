#include "RenderManager.h"
#include <sl.h>
#include "Config.h"
#include "Textures.h"

namespace render
{
	static int resWidth = 1080;
	static int resHeight = 720;

	static utilities::Vector2 posToScreen(utilities::Vector2 position)
	{
		int gameResWidth = config::gameWidth * resHeight / config::gameHeight;
		int marginWidth = resWidth - gameResWidth;
		return { position.x * gameResWidth / config::gameWidth, position.y * resHeight / config::gameHeight };
	}
	static utilities::Vector2 sizeToScreen(utilities::Vector2 size)
	{
		int gameResWidth = config::gameWidth * resHeight / config::gameHeight;
		return { size.x * gameResWidth / config::gameWidth, size.y * resHeight / config::gameHeight};
	}

	void initWindow()
	{		
		slWindow(resWidth, resHeight, "Simple SIGIL Example", false);
	}
	void closeWindow()
	{
		slClose();
	}
	void loadTextures()
	{
		textures::loadMaid();
		textures::loadTray();
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
	void drawSprite(int texture, utilities::Vector2 position, utilities::Vector2 size)
	{
		position = posToScreen(position);
		size = sizeToScreen(size);
		slSetForeColor(1, 1, 1, 1);
		slSprite(texture, position.x, position.y, size.x, size.y);
	}

	void endDraw()
	{
		slRender();
	}


}