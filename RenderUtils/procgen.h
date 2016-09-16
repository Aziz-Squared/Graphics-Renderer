#pragma once

#include "globjects.h"

/*
	Generate a grid
*/

Geometry genGrid(unsigned sqr, float dim);

/*
	Make some noise!
		on a texture...
*/

Texture genNoise(unsigned sqr, unsigned octaves);