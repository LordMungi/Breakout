#include "Glass.h"
#include <sl.h>
#include "RenderManager.h"

namespace glass
{
	void initArray(Glass glasses[max], int levelGlasses)
	{
		for (int i = 0; i < max; i++)
		{
			glasses[i].position = { 0, 0 };
			glasses[i].offset = 0;
			if (i < levelGlasses)
				glasses[i].state = State::InTable;
			else
				glasses[i].state = State::Null;
		}
	}

	int getGlassInTable(Glass glasses[max])
	{
		for (int i = 0; i < max; i++)
		{
			if (glasses[i].state == State::InTable)
				return i;
		}
		return 999;
	}

	bool fall(Glass& glass)
	{
		if (glass.position.y - size.y / 2 > 0)
		{
			glass.position.y -= speed * slGetDeltaTime();
			return true;
		}
		glass.state = State::Broken;
		return false;
	}

	void drawArray(Glass glasses[max])
	{
		for (int i = 0; i < max; i++)
		{
			switch (glasses[i].state)
			{
			case State::Falling:
				render::drawRectangle(glasses[i].position, size, utilities::BLUE);
				break;
			case State::InTray:
				render::drawRectangle(glasses[i].position, size, utilities::BLUE);
				break;
			case State::Broken:
				render::drawRectangle(glasses[i].position, size, { 0, 0, 0.6, 1 });
				break;
			}
		}
	}

}