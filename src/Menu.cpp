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
		Original,
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
		const Title original = { {render::resolution.x * 0.05, render::resolution.y * 0.3}, render::resolution.y * 0.1 };
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

		position = title::original.position;
		size = title::original.size;
		if (optionSelected == Options::Original)
			color = utilities::GREY;
		else
			color = utilities::WHITE;
		render::drawText(position, size, "Original", color);

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
		if (isMouseCollidingText(title::play.position, { slGetTextWidth("Play"), slGetTextHeight("Play") }))
		{
			optionSelected = Options::Play;
			if (slGetMouseButton(SL_MOUSE_BUTTON_LEFT))
			{
				game::run(game::Mode::Normal);
			}
		}
		else if (isMouseCollidingText(title::original.position, { slGetTextWidth("Original"), slGetTextHeight("Original") }))
		{
			optionSelected = Options::Original;
			if (slGetMouseButton(SL_MOUSE_BUTTON_LEFT))
			{
				game::run(game::Mode::Arcade);
			}

		}
		else if (isMouseCollidingText(title::exit.position, { slGetTextWidth("Exit"), slGetTextHeight("Exit") }))
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

	bool isMouseCollidingText(utilities::Vector2 position, utilities::Vector2 size)
	{
		return (slGetMouseX() >= position.x &&
			slGetMouseX() <= position.x + size.x &&
			slGetMouseY() >= position.y &&
			slGetMouseY() <= position.y + size.y);
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
