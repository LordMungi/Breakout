#include "HUD.h"
#include "RenderManager.h"
#include <sl.h>

namespace hud
{
	bool isMouseCollidingText(utilities::Vector2 position, double fontSize, std::string text)
	{
		slSetFontSize(fontSize);
		utilities::Vector2 size = { slGetTextWidth(text.c_str()), slGetTextHeight(text.c_str()) };

		return (slGetMouseX() >= position.x &&
			slGetMouseX() <= position.x + size.x &&
			slGetMouseY() >= position.y &&
			slGetMouseY() <= position.y + size.y);
	}

	void drawExit(utilities::Vector2 position, double size, bool isSelected)
	{
		utilities::Color color = utilities::WHITE;
		if (isSelected)
			color = utilities::GREY;
		render::drawText(position, size, "Exit", color);
	}

	void drawGlassesCaught(glass::Glass glasses[glass::max], int levelGlasses)
	{
		utilities::Vector2 position = { render::gameResolution.x + render::resolution.x * 0.05, render::resolution.y * 0.2 };
		double size = render::resolution.y * 0.05;

		render::drawText(position, size, "Caught " + std::to_string(glass::getGlassesCaught(glasses)) + "/" + std::to_string(levelGlasses), utilities::WHITE);
	}

	void drawLives(character::Character character)
	{
		utilities::Vector2 position = { render::gameResolution.x + render::resolution.x * 0.05, render::resolution.y * 0.1 };
		double size = render::resolution.y * 0.05;

		render::drawText(position, size, "Lives " + std::to_string(character.lives), utilities::WHITE);
	}

	void drawGameOver()
	{
		utilities::Vector2 position = { render::gameResolution.x / 2, render::resolution.y / 2 };
		double size = render::resolution.y * 0.07;
		
		render::drawText(position, size, "GAME OVER", utilities::WHITE, SL_ALIGN_CENTER);
	}
	void drawPaused()
	{
		utilities::Vector2 position = { render::gameResolution.x / 2, render::resolution.y / 2 };
		double size = render::resolution.y * 0.07;

		render::drawText(position, size, "PAUSED", utilities::WHITE, SL_ALIGN_CENTER);
	}
	void drawWin()
	{
		{
			utilities::Vector2 position = { render::gameResolution.x / 2, render::resolution.y / 2 };
			double size = render::resolution.y * 0.07;

			render::drawText(position, size, "WINNER", utilities::WHITE, SL_ALIGN_CENTER);
		}
	}
}