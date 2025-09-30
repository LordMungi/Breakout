#pragma once
#include "RenderManager.h"

namespace game
{
	enum class Mode
	{
		Normal,
		Arcade
	};

	void run(Mode mode);
}