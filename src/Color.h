#pragma once

namespace utilities
{
	struct Color
	{
		double r;
		double g;
		double b;
		double a;
	};

	const Color WHITE = { 1, 1, 1, 1 };
	const Color GREY = { 0.5, 0.5, 0.5, 1};
	const Color BLACK = { 0, 0, 0, 1 };
	const Color RED = { 1, 0, 0, 1 };
	const Color GREEN = { 0, 1, 0, 1 };
	const Color BLUE = { 0, 0, 1, 1 };
}

