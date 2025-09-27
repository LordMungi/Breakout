#include "Textures.h"
#include <sl.h>

namespace textures
{
	int maid;
	int tray;

	void loadMaid()
	{
		maid = slLoadTexture("resources/sprites/maid/1.png");
	}
	void loadTray()
	{
		tray = slLoadTexture("resources/sprites/tray/1.png");
	}
}