#include "cRenderUtils.h"
#include "window.h"
#include "Vertex.h"

// This is the dev branch

int main()
{
	Window window;
	window.init();

	Vertex vert[6] =
	{
		{{  0.0f,    .5f,  0.0f, 1.0f },{ 1.0f,1.0f,0.0f,1.0f }},
		{{ .5f,  -.5f,  0.0f, 1.0f },{ 0.4f,0.0f,0.6f,1.0f }},
		{{ -.5f, -.5f,  0.0f, 1.0f },{ 1.0f,1.0f,1.0f,1.0f }},
		{{ -1.0f, 1.0f, 1.0f, 1.0f },{0.2f,0.2f,0.0f,1.0f}},
		{{1.0f,-1.0f,1.0f,1.0f},{1.0f,0.0f,1.0f,1.0f}},
		{{1.0f,1.0f,1.0f,1.0f},{0.0f,1.0f,1.0f,1.0f}}
	};

	unsigned tris[6] = {0, 1, 2, 3, 4, 5};
	

	const char vsource[] =
		"#version 330\n"
		"layout(location = 0)in vec4 position;"
		"layout(location = 1)in vec4 color;"
		"out vec4 vColor;"
		"void main() { vColor = color; gl_Position = position;}";
	
	const char fsource[] =
		"#version 150\n"
		"in vec4 vColor;"
		"out vec4 outColor;"
		"void main() {outColor = vColor;}";

	Geometry geometry = makeGeometry(vert, 6, tris, 6);
	Shader shader = makeShader(vsource, fsource);

	while (window.step())
	{
		draw(geometry, shader);
	}

	return 0;
}