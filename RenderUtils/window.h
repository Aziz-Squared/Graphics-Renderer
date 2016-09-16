#pragma once
#include "GLFW\glfw3.h"

class Window
{
	friend class Input;

private:
	int width, height;
	char title[64];
	bool isInitialized = false;
	// forward declare
	GLFWwindow *winHandle = nullptr;

public:
	bool init(int a_width = 800, int a_height = 600, char *a_title = "Zyzz Renderer"); // Setup/start/initialize
	bool step();										 // Update/refresh
	bool term();										 // Kill/terminate/DIEDIEDIE/POTG




};