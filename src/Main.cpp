#include <sl.h>
#include "Config.h"

int main()
{
	slWindow(config::resWidth, config::resHeight, "Simple SIGIL Example", false);

	while (!slShouldClose() && !slGetKey(SL_KEY_ESCAPE))
	{
		slSetBackColor(0.5, 0.75, 1.0);

		slSetForeColor(1, 0, 0, 0.5);
		slRectangleFill(config::resWidth * 0.5, config::resHeight * 0.5, 100, 100);

		slRender();
	}

	slClose();

	return 0;
}