#include "cRenderUtils.h"
#include "window.h"
// This is the dev branch

int main()
{
	Window window;
	window.init();

	while (window.step())
	{
		//window.term();
	}

	return 0;
}