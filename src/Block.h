#pragma once
#include "Vector.h"

namespace block
{
	enum class State
	{
		Null,
		Undamaged,
		Broken
	};

	enum class Side
	{
		Null,
		Top,
		Left,
		Right,
		Bottom
	};

	struct Block
	{
		utilities::Vector2 position;
		State state;
		bool hasGlass;
	};

	const utilities::Vector2 size = { 50, 15 };

	const int maxWidth = 8;
	const int maxHeight = 12;


	void initArray(Block blocks[maxWidth][maxHeight]);
	void setGlasses(Block blocks[maxWidth][maxHeight], int levelGlasses);

	void drawArray(Block blocks[maxWidth][maxHeight]);
}