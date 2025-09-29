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

	struct Glass
	{
		utilities::Vector2 position;
		State state;
		double offset;
	};

	const int max = 20;
	const utilities::Vector2 size = { 5, 10 };
	const double speed = 50;

	void initArray(Glass glasses[max], int levelGlasses);

	int getGlassInTable(Glass glasses[max]);

	bool fall(Glass& glass);
	void drawArray(Glass glasses[max]);
}