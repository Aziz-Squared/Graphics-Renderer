#include "GLFW\glfw3.h"
#include "Input.h"
#include "window.h"
#include <cstring>

bool Input::init(const Window &window)
{
	memset(keys, 0, 350 * sizeof(KEY_STATE));
	winHandle = window.winHandle;

	glfwSetInputMode(winHandle, GLFW_CURSOR, GLFW_CURSOR_NORMAL);

	return true;
}

bool Input::step()
{
	for (int i = 0; i < 350; ++i)
	{
		// GLFW_PRESS, GLFW_RELEASE
		int res = glfwGetKey(winHandle, i);

		if ((keys[i] == UP || keys[i] == RELEASE) && res == GLFW_PRESS)
			keys[i] = PRESS;
		else if ((keys[i] == DOWN || keys[i] == PRESS) && res == GLFW_RELEASE)
			keys[i] = RELEASE;
		else if (keys[i] == PRESS)
			keys[i] = DOWN;
		else if (keys[i] == RELEASE)
			keys[i] = UP;

		keys[i];
	}

	double prevX = mouseX;
	double prevY = mouseY;

	mouseHorz = mouseX - prevX;
	mouseVert = mouseY - prevY;

	glfwGetCursorPos(winHandle, &mouseX, &mouseY);

	return true;
}

bool Input::term()
{
	return false;
}
