#include "cRenderUtils.h"
#include "window.h"
#include "Vertex.h"
// This is the dev branch

int main()
{
	Window window;
	window.init();

	Vertex vert[3] = { {  0,     .5f,  0,  1}, 
					   { .5f,   .5f,  0,  1},
					   {-.5f,  -.5f,  0,  1} };

	unsigned tris[3] = {0, 1, 2};

	const char vsource[] =
		"#version 150\n"
		"in vec4 position;"
		"void main() {gl_Position = position;}";
	
	const char fsource[] =
		"#version 350\n"
		"out vec4 outColor;"
		"void main() {outColor = vec4(1.0,0.0,0.0,1.0);}";

	Geometry geometry = makeGeometry(vert, 3, tris, 3);
	Shader shader = makeShader(vsource, fsource);

	while (window.step())
	{
		draw(geometry, shader);
	}

	return 0;
}