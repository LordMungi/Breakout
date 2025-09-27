#include "Menu.h"

namespace menu
{
	void run()
	{
		render::initWindow();
		render::loadTextures();

		game::run();

		render::closeWindow();
	}
}
