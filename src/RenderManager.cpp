#include "RenderManager.h"
#include <sl.h>
#include "Config.h"
#include "Textures.h"

namespace render
{
	utilities::Vector2 resolution = { 1080, 720 };
	utilities::Vector2 gameResolution = {};

	static void setGameResolution()
	{
		gameResolution = gameSizeToScreen({ config::gameWidth, config::gameHeight });
	}

	static utilities::Vector2 gamePosToScreen(utilities::Vector2 position)
	{
		int gameResWidth = config::gameWidth * resolution.y / config::gameHeight;
		return { position.x * gameResWidth / config::gameWidth, position.y * resolution.y / config::gameHeight };
	}
	static utilities::Vector2 gameSizeToScreen(utilities::Vector2 size)
	{
		int gameResWidth = config::gameWidth * resolution.y / config::gameHeight;
		return { size.x * gameResWidth / config::gameWidth, size.y * resolution.y / config::gameHeight};
	}

	void initWindow()
	{		
		slWindow(resolution.x, resolution.y, "Simple SIGIL Example", false);
		setGameResolution();
	}
	void closeWindow()
	{
		slClose();
	}
	void loadTextures()
	{
		textures::loadMaid();
		textures::loadTray();
		textures::loadFont();
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
		position = gamePosToScreen(position);
		size = gameSizeToScreen(size);
		slSetForeColor(color.r, color.g, color.b, color.a);
		slRectangleFill(position.x, position.y, size.x, size.y);
	}
	void drawCircle(utilities::Vector2 position, double radius, utilities::Color color)
	{
		position = gamePosToScreen(position);
		slSetForeColor(color.r, color.g, color.b, color.a);
		slCircleFill(position.x, position.y, radius, 100);
	}
	void drawSprite(int texture, utilities::Vector2 position, utilities::Vector2 size)
	{
		position = gamePosToScreen(position);
		size = gameSizeToScreen(size);
		slSetForeColor(1, 1, 1, 1);
		slSprite(texture, position.x, position.y, size.x, size.y);
	}
	void drawText(utilities::Vector2 position, double size, std::string text, utilities::Color color)
	{
		slSetTextAlign(SL_ALIGN_LEFT);
		slSetForeColor(color.r, color.g, color.b, color.a);
		slSetFont(textures::font, size);
		slText(position.x, position.y, text.c_str());
	}
	void drawText(utilities::Vector2 position, double size, std::string text, utilities::Color color, int align)
	{
		slSetTextAlign(align);
		slSetForeColor(color.r, color.g, color.b, color.a);
		slSetFont(textures::font, size);
		slText(position.x, position.y, text.c_str());
	}

	void endDraw()
	{
		slRender();
	}
}