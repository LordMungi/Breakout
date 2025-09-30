#include "Menu.h"
#include <sl.h>
#include "Textures.h"
#include "Config.h"

namespace menu
{
	enum class Options
	{
		Null,
		Play,
		Arcade,
		Exit
	};

	namespace title
	{
		struct Title
		{
			utilities::Vector2 position;
			double size;
		};

		const Title title = { { render::resolution.x * 0.05, render::resolution.y * 0.8 }, render::resolution.y * 0.1 };
		const Title play = { {render::resolution.x * 0.05, render::resolution.y * 0.4}, render::resolution.y * 0.1 };
		const Title arcade = { {render::resolution.x * 0.05, render::resolution.y * 0.3}, render::resolution.y * 0.1 };
		const Title exit = { {render::resolution.x * 0.05, render::resolution.y * 0.1}, render::resolution.y * 0.1 };

	}

	Options optionSelected = Options::Null;

	static void drawMainMenu()
	{
		utilities::Vector2 position = title::title.position;
		double size = title::title.size;
		utilities::Color color = utilities::WHITE;

		render::drawText(position, size, "GlassBreaker", color);

		position = title::play.position;
		size = title::play.size;
		if (optionSelected == Options::Play)
			color = utilities::GREY;
		else
			color = utilities::WHITE;
		render::drawText(position, size, "Play", color);

		position = title::arcade.position;
		size = title::arcade.size;
		if (optionSelected == Options::Arcade)
			color = utilities::GREY;
		else
			color = utilities::WHITE;
		render::drawText(position, size, "Arcade", color);

		position = title::exit.position;
		size = title::exit.size;
		if (optionSelected == Options::Exit)
			color = utilities::GREY;
		else
			color = utilities::WHITE;
		render::drawText(position, size, "Exit", color);

	}

	static void selectOption()
	{
		
		slSetFont(textures::font, title::play.size);
		if (hud::isMouseCollidingText(title::play.position, title::play.size, "Play"))
		{
			optionSelected = Options::Play;
			if (slGetMouseButton(SL_MOUSE_BUTTON_LEFT))
			{
				game::run(game::Mode::Normal);
			}
		}
		else if (hud::isMouseCollidingText(title::arcade.position, title::arcade.size, "Arcade"))
		{
			optionSelected = Options::Arcade;
			if (slGetMouseButton(SL_MOUSE_BUTTON_LEFT))
			{
				game::run(game::Mode::Arcade);
			}

		}
		else if (hud::isMouseCollidingText(title::exit.position, title::exit.size, "Exit"))
		{
			optionSelected = Options::Exit;
			if (slGetMouseButton(SL_MOUSE_BUTTON_LEFT))
			{
				config::programEnded = true;
			}
		}
		else 
			optionSelected = Options::Null;
	}

	void run()
	{
		render::initWindow();
		render::loadTextures();

		while (!render::windowShouldClose() && !config::programEnded)
		{
			render::drawBackground();
			drawMainMenu();
			selectOption();
			render::endDraw();
		}

		render::closeWindow();
	}
}
