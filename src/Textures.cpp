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
	int slideRight[2];
	int slideLeft[2];
	int win[8];
	int lose[2];

	void load()
	{
		bricks = slLoadTexture("resources/sprites/background/bricks.png");
		cafe = slLoadTexture("resources/sprites/background/cafe.png");
		maid = slLoadTexture("resources/sprites/maid/idle/0000.png");
		tray = slLoadTexture("resources/sprites/tray/1.png");
		font = slLoadFont("resources/fonts/LEMONMILK-Regular.otf");

		runRight[0] = slLoadTexture("resources/sprites/maid/run-right/0000.png");
		runRight[1] = slLoadTexture("resources/sprites/maid/run-right/0001.png");
		runRight[2] = slLoadTexture("resources/sprites/maid/run-right/0002.png");
		runRight[3] = slLoadTexture("resources/sprites/maid/run-right/0003.png");
		runRight[4] = slLoadTexture("resources/sprites/maid/run-right/0004.png");
		runRight[5] = slLoadTexture("resources/sprites/maid/run-right/0005.png");

		runLeft[0] = slLoadTexture("resources/sprites/maid/run-left/0000.png");
		runLeft[1] = slLoadTexture("resources/sprites/maid/run-left/0001.png");
		runLeft[2] = slLoadTexture("resources/sprites/maid/run-left/0002.png");
		runLeft[3] = slLoadTexture("resources/sprites/maid/run-left/0003.png");
		runLeft[4] = slLoadTexture("resources/sprites/maid/run-left/0004.png");
		runLeft[5] = slLoadTexture("resources/sprites/maid/run-left/0005.png");

		slideRight[0] = slLoadTexture("resources/sprites/maid/slide-right/0000.png");
		slideRight[1] = slLoadTexture("resources/sprites/maid/slide-right/0001.png");

		slideLeft[0] = slLoadTexture("resources/sprites/maid/slide-left/0000.png");
		slideLeft[1] = slLoadTexture("resources/sprites/maid/slide-left/0001.png");

		win[0] = slLoadTexture("resources/sprites/maid/win/0000.png");
		win[1] = slLoadTexture("resources/sprites/maid/win/0001.png");
		win[2] = slLoadTexture("resources/sprites/maid/win/0002.png");
		win[3] = slLoadTexture("resources/sprites/maid/win/0003.png");
		win[4] = slLoadTexture("resources/sprites/maid/win/0004.png");
		win[5] = slLoadTexture("resources/sprites/maid/win/0005.png");
		win[6] = slLoadTexture("resources/sprites/maid/win/0006.png");
		win[7] = slLoadTexture("resources/sprites/maid/win/0007.png");

		lose[0] = slLoadTexture("resources/sprites/maid/lose/0000.png");
		lose[1] = slLoadTexture("resources/sprites/maid/lose/0001.png");

	}
}