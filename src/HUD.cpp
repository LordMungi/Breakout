#include "HUD.h"
#include "RenderManager.h"
#include <string>

namespace hud
{
	void drawLives(character::Character character)
	{
		render::drawText({ render::resolution.x * 0.8, render::resolution.y * 0.2 }, 30, "Vidas " + std::to_string(character.lives));
	}
}