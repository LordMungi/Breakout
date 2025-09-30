#pragma once
#include "Vector.h"

namespace glass
{

	enum class State
	{
		Null,
		InTable,
		Falling,
		InTray,
		Broken
	};

	enum class Type
	{
		Normal,
		Slide,
		Double,
		Long
	};

	struct Glass
	{
		utilities::Vector2 position;
		Type type;
		State state;
		double offset;
	};

	const int max = 30;
	const utilities::Vector2 size = { 4, 8 };
	const double speed = 100;

	void initArray(Glass glasses[max], int levelGlasses);
	void setPowerups(Glass glasses[max], int levelGlasses);

	int getGlassInTable(Glass glasses[max]);
	int getGlassesFallen(Glass glasses[max]);
	int getGlassesCaught(Glass glasses[max]);
	int getGlassesInLevel(int level);

	bool fall(Glass& glass);
	void drawArray(Glass glasses[max]);
}