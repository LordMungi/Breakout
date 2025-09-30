#include "Textures.h"
#include <sl.h>

namespace textures
{
	int bricks;
	int cafe;
	int maid;
	int tray;
	int font;

	void load()
	{
		bricks = slLoadTexture("resources/sprites/background/bricks.png");
		cafe = slLoadTexture("resources/sprites/background/cafe.png");
		maid = slLoadTexture("resources/sprites/maid/1.png");
		tray = slLoadTexture("resources/sprites/tray/1.png");
		font = slLoadFont("resources/fonts/LEMONMILK-Regular.otf");
	}
}