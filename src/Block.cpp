#include "Block.h"
#include "Config.h"
#include "RenderManager.h"

namespace block
{
	void initArray(Block blocks[maxWidth][maxHeight])
	{
		utilities::Vector2 initialPos = { size.x / 2, config::gameHeight - size.y * 2 };
		utilities::Vector2 position = { initialPos.x, initialPos.y};

		for (int i = 0; i < maxWidth; i++)
		{
			for (int j = 0; j < maxHeight; j++)
			{
				blocks[i][j].state = State::Undamaged;

				blocks[i][j].position = position;
				position = { position.x, position.y - size.y};
			}
			position.y = initialPos.y;
			position.x += size.x;
		}
	}

	void drawArray(Block blocks[maxWidth][maxHeight])
	{
		utilities::Color color;
		for (int i = 0; i < maxWidth; i++)
		{

			for (int j = 0; j < maxHeight; j++)
			{
				if (blocks[i][j].state == State::Undamaged)
				{
					if ((i + j) % 2)
						color = { 1,1,1,1 };
					else
						color = { 0.8,0.8,0.8,1 };
					render::drawRectangle(blocks[i][j].position, size, color);

				}
			}
		}
	}
}