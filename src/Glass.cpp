#include "Glass.h"
#include <sl.h>
#include "RenderManager.h"
#include "Config.h"

namespace glass
{
	static int levels[config::maxLevels] = { 6, 10, 12, 15, 15, 16, 20, 20, 25, 30 };

	void initArray(Glass glasses[max], int levelGlasses)
	{
		for (int i = 0; i < max; i++)
		{
			glasses[i].position = { 0, 0 };
			glasses[i].offset = 0;
			glasses[i].type = Type::Normal;
			if (i < levelGlasses)
				glasses[i].state = State::InTable;
			else
				glasses[i].state = State::Null;
		}
	}
	void setPowerups(Glass glasses[max], int levelGlasses)
	{
		bool isThereSlide = false;
		bool isThereDouble = false;
		bool isThereLong = false;

		while (!isThereDouble || !isThereSlide || !isThereLong)
		{
			for (int i = 0; i < levelGlasses; i++)
			{
				if (rand() % 1000 < 10 && glasses[i].type == Type::Normal)
				{
					if (!isThereDouble)
					{
						isThereDouble = true;
						glasses[i].type = Type::Double;
					}
					else if (!isThereSlide)
					{
						isThereSlide = true;
						glasses[i].type = Type::Slide;
					}
					else if (!isThereLong)
					{
						isThereLong = true;
						glasses[i].type = Type::Long;
					}
				}
			}
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
	int getGlassesFallen(Glass glasses[max])
	{
		int counter = 0;
		for (int i = 0; i < max; i++)
		{
			if (glasses[i].state == State::InTray || glasses[i].state == State::Broken)
				counter++;
		}
		return counter;
	}
	int getGlassesCaught(Glass glasses[max])
	{
		int counter = 0;
		for (int i = 0; i < max; i++)
		{
			if (glasses[i].state == State::InTray)
				counter++;
		}
		return counter;
	}
	int getGlassesInLevel(int level)
	{
		if (level > config::maxLevels)
			level = config::maxLevels - 1;

		return levels[level];
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
			case State::InTray:
			{
				switch (glasses[i].type)
				{
				case Type::Normal:
					render::drawRectangle(glasses[i].position, size, utilities::BLUE);
					break;
				case Type::Slide:
					render::drawRectangle(glasses[i].position, size, utilities::RED);
					break;
				case Type::Double:
					render::drawRectangle(glasses[i].position, size, utilities::GREEN);
					break;
				case Type::Long:
					render::drawRectangle(glasses[i].position, size, utilities::YELLOW);
					break;
				}
				break;
			}
			case State::Broken:
				render::drawRectangle(glasses[i].position, size, { 0, 0, 0.6, 1 });
				break;
			}
		}
	}

}