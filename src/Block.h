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

	struct Block
	{
		State state;
	};


}