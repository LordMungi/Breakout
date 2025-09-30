#pragma once
#include "RenderManager.h"
#include "HUD.h"

namespace game
{
	enum class Mode
	{
		Normal,
		Arcade
	};

	void run(Mode mode);
}