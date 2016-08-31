#include "cRenderUtils.h"
#include "window.h"
#include "Vertex.h"
#include "Gallery.h"

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

	Gallery sphere, cube, shaders;

	sphere.makeObject("sphere", vert, 3, tris, 3);
	shaders.makeShader("test", "../res/shaders/simpleVert.txt", 
					"../res/shaders/simpleFrag.txt");
	cube.makeObject("cube", vert, 3, tris, 3);

	sphere.loadOBJ("sphere", "../res/models/sphere.obj");
	cube.loadOBJ("cube", "../res/models/cube.obj");

	shaders.loadShader("test", "../res/shaders/simpleVert.txt",
					"../res/shaders/simpleFrag.txt");

	float time = 0.0f;

	while (window.step())
	{
		time += 0.2354f;
		// UNIFORM!
		draw(cube.getObject("test"), shaders.getShader("test"), time);
	}
	/*freeGeometry(geometry1);
	freeGeometry(geometry2);
	freeShader(shader);*/
	cube.term();
	sphere.term();
	window.term();
	return 0;
}