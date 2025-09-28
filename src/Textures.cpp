#include "Textures.h"
#include <sl.h>

namespace textures
{
	int maid;
	int tray;
	int font;

	void loadMaid()
	{
		maid = slLoadTexture("resources/sprites/maid/1.png");
	}
	void loadTray()
	{
		tray = slLoadTexture("resources/sprites/tray/1.png");
	}
	void loadFont()
	{
		font = slLoadFont("resources/fonts/LEMONMILK-Regular.otf");
	}
}