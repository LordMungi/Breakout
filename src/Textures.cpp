#include "Textures.h"
#include <sl.h>
#include <string>

namespace textures
{
	int bricks;
	int cafe;
	int maid;
	int tray;
	int font;
	int runRight[6];
	int runLeft[6];

	void load()
	{
		bricks = slLoadTexture("resources/sprites/background/bricks.png");
		cafe = slLoadTexture("resources/sprites/background/cafe.png");
		maid = slLoadTexture("resources/sprites/maid/idle/0000.png");
		tray = slLoadTexture("resources/sprites/tray/1.png");
		font = slLoadFont("resources/fonts/LEMONMILK-Regular.otf");

		runRight[0] = slLoadTexture("resources/sprites/maid/run-right/0000.bmp");
		runRight[1] = slLoadTexture("resources/sprites/maid/run-right/0001.bmp");
		runRight[2] = slLoadTexture("resources/sprites/maid/run-right/0002.bmp");
		runRight[3] = slLoadTexture("resources/sprites/maid/run-right/0003.bmp");
		runRight[4] = slLoadTexture("resources/sprites/maid/run-right/0004.bmp");
		runRight[5] = slLoadTexture("resources/sprites/maid/run-right/0005.bmp");

		runLeft[0] = slLoadTexture("resources/sprites/maid/run-left/0000.bmp");
		runLeft[1] = slLoadTexture("resources/sprites/maid/run-left/0001.bmp");
		runLeft[2] = slLoadTexture("resources/sprites/maid/run-left/0002.bmp");
		runLeft[3] = slLoadTexture("resources/sprites/maid/run-left/0003.bmp");
		runLeft[4] = slLoadTexture("resources/sprites/maid/run-left/0004.bmp");
		runLeft[5] = slLoadTexture("resources/sprites/maid/run-left/0005.bmp");
	}
}