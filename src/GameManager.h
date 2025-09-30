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

	enum class OnExit
	{
		Quit,
		Retry,
		Next
	};

	OnExit run(Mode mode, int level);
}