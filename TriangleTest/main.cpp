#include "cRenderUtils.h"
#include "window.h"
#include "Vertex.h"

// This is the dev branch

int main()
{
	Window window;
	window.init();

	Vertex vert[3] =
	{
		{{  0.0f,    .5f,  0.0f, 1.0f },{ 1.0f,1.0f,0.0f,1.0f }},
		{{ .5f,  -.5f,  0.0f, 1.0f },{ 0.4f,0.0f,0.6f,1.0f }},
		{{ -.5f, -.5f,  0.0f, 1.0f },{ 1.0f,1.0f,1.0f,1.0f }},
	};

	unsigned tris[6] = {0, 1, 2, 3, 4, 5};

	Geometry geometry1 = loadOBJ("../res/models/cube.obj");
	Geometry geometry2 = loadOBJ("../res/models/sphere.obj");

	Shader shader = loadShader("../res/shaders/simpleVert.txt",
								"../res/shaders/simpleFrag.txt");

	while (window.step())
	{
		draw(geometry2, shader);
		draw(geometry1, shader);
	}
	freeGeometry(geometry1);
	freeGeometry(geometry2);
	freeShader(shader);
	window.term();
	return 0;
}