#include "Menu.h"

namespace menu
{
	void run()
	{
		render::initWindow();

		game::run();

		render::closeWindow();
	}
}
