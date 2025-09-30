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

	const utilities::Vector2 size = { 30, 12 };

	const int maxWidth = 10;
	const int maxHeight = 15;

	void initArray(Block blocks[maxWidth][maxHeight], int level);
	void setGlasses(Block blocks[maxWidth][maxHeight], int levelGlasses);
	bool areAllBlocksDestroyed(Block blocks[maxWidth][maxHeight]);

	void drawArray(Block blocks[maxWidth][maxHeight]);
}