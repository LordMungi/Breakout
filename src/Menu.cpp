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
		Credits,
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
		const Title play = { {render::resolution.x * 0.05, render::resolution.y * 0.5}, render::resolution.y * 0.1 };
		const Title arcade = { {render::resolution.x * 0.05, render::resolution.y * 0.4}, render::resolution.y * 0.1 };
		const Title credits = { {render::resolution.x * 0.05, render::resolution.y * 0.3}, render::resolution.y * 0.1 };
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

		position = title::credits.position;
		size = title::credits.size;
		if (optionSelected == Options::Credits)
			color = utilities::GREY;
		else
			color = utilities::WHITE;
		render::drawText(position, size, "Credits", color);

		position = title::exit.position;
		size = title::exit.size;
		if (optionSelected == Options::Exit)
			color = utilities::GREY;
		else
			color = utilities::WHITE;
		render::drawText(position, size, "Exit", color);

	}

	static bool exitButtonPressed()
	{
		utilities::Vector2 position = { render::resolution.x * 0.95, render::resolution.y * 0.90 };
		double size = render::resolution.y * 0.05;
		bool isSelected = false;

		if (hud::isMouseCollidingTextRight(position, size, "Exit"))
		{
			isSelected = true;
			if (slGetMouseButton(SL_MOUSE_BUTTON_LEFT))
			{
				return true;
			}
		}
		hud::drawButton("Exit", position, size, isSelected);
		return false;
	}

	static void drawCredits()
	{
		bool shouldExit = false;
		do
		{
			render::drawBackground();
			utilities::Vector2 position = title::title.position;
			double size = title::title.size;
			utilities::Color color = utilities::WHITE;

			render::drawText(position, size, "Credits", color);

			size = render::resolution.y * 0.06;
			position = {position.x, render::resolution.y * 0.6};
			render::drawText(position, size, "Programming & Art", color);

			size = render::resolution.y * 0.05;
			position = { position.x + render::resolution.x * 0.05, position.y - render::resolution.y * 0.065 };
			render::drawText(position, size, "Santino Verrua (LordMungi)", color);

			shouldExit = exitButtonPressed();
			render::endDraw();
		} while (!render::windowShouldClose() && !shouldExit);
	}

	static void selectOption()
	{
		
		slSetFont(textures::font, title::play.size);
		if (hud::isMouseCollidingTextLeft(title::play.position, title::play.size, "Play"))
		{
			optionSelected = Options::Play;
			if (slGetMouseButton(SL_MOUSE_BUTTON_LEFT))
			{
				int level = 0;
				game::OnExit onExit;

				do
				{
					onExit = game::run(game::Mode::Normal, level);
					if (onExit == game::OnExit::Next)
						level++;
				} while (onExit != game::OnExit::Quit);
			}
		}
		else if (hud::isMouseCollidingTextLeft(title::arcade.position, title::arcade.size, "Arcade"))
		{
			optionSelected = Options::Arcade;
			if (slGetMouseButton(SL_MOUSE_BUTTON_LEFT))
			{
				int level = 0;
				game::OnExit onExit;

				do
				{
					onExit = game::run(game::Mode::Arcade, level);
					if (onExit == game::OnExit::Next)
						level++;
				} while (onExit != game::OnExit::Quit);
			}
		}
		else if (hud::isMouseCollidingTextLeft(title::credits.position, title::credits.size, "Credits"))
		{
			optionSelected = Options::Credits;
			if (slGetMouseButton(SL_MOUSE_BUTTON_LEFT))
			{
				drawCredits();
			}
		}
		else if (hud::isMouseCollidingTextLeft(title::exit.position, title::exit.size, "Exit"))
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
