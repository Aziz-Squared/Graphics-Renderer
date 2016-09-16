#include "cRenderUtils.h"

int main()
{
	Window window;
	window.init();

	Framebuffer screen = { 0,1280,720 };

	Geometry quad = makeGeometry(quad_verts, 4, quad_tris, 6);

	Shader simple = loadShader("simpleFrag.glsl", "simpleVert.glsl");



	while (window.step())
	{
		tdraw(simple, quad, screen);
	}

	window.term();
}




//#include "cRenderUtils.h"
//#include "window.h"
//#include "Vertex.h"
//#include "Gallery.h"
//#include "Timer.h"
//#include "Input.h"
//#include "Camera.h"
//#include "procgen.h"
//
//#include "GLM\glm.hpp"
//#include "GLM\ext.hpp"
//
//// This is the dev branch
//
//int main()
//{
//	Window window;
//	window.init();
//	Gallery gallery, shaders;
//	Time time;
//	Input input;
//	input.init(window);
//
//	unsigned char pixels[] = { 255, 255, 0 };
//
//	Texture tex = loadTexture("../res/texture/pants.jpg");
//
//	Vertex vert[3] =
//	{
//		{ { 0.0f,    .5f,  0.0f, 1.0f },{ 1.0f,1.0f,0.0f,1.0f } },
//		{ { .5f,  -.5f,  0.0f, 1.0f },{ 0.4f,0.0f,0.6f,1.0f } },
//		{ { -.5f, -.5f,  0.0f, 1.0f },{ 1.0f,1.0f,1.0f,1.0f } },
//	};
//
//	unsigned tris[6] = { 0, 1, 2, 3, 4, 5 };
//
//	
//	gallery.makeObject("sphere", vert, 3, tris, 3);
//	gallery.makeObject("cube", vert, 3, tris, 3);
//	gallery.makeObject("ship", vert, 3, tris, 3);
//	
//	shaders.makeShader("test", "../res/shaders/simpleVert.txt",
//		"../res/shaders/simpleFrag.txt");
//
//	gallery.loadShader("CAMERA", "../res/shaders/cameraVert.txt",
//		"../res/shaders/cameraFrag.txt");
//	gallery.loadShader("TEXTURE", "../res/shaders/textureVert.txt",
//		"../res/shaders/textureFrag.txt");
//
//	gallery.loadOBJ("sphere", "../res/models/sphere.obj");
//	gallery.loadOBJ("cube", "../res/models/cube.obj");
//	gallery.loadOBJ("ship", "../res/models/flyingdick.obj");
//
//	shaders.loadShader("test", "../res/shaders/simpleVert.txt",
//		"../res/shaders/simpleFrag.txt");
//
//	float ct = 0.0f;
//
//	float IDENTITIY[16] = { 1,0,0,0,
//						  0,1,0,0,
//						  0,0,1,0,
//						  0,0,0,1 };
//
//	glm::mat4 proj, view, model;
//	model = glm::scale(glm::vec3(5.0f, 5.0f, 5.0f));
//	genGrid(4, 2);
//	//proj = glm::ortho<float>(-10, 10, -10, 10, -10, 10);
//
//	FlyCamera cam;
//	cam.jumpTo(glm::vec3(10, 0, 0));
//	cam.lookAt(glm::vec3(0, 0, 0));
//	
//	while (window.step())
//	{
//		time.step();
//		input.step();	
//
//		view = cam.getView();
//		proj = cam.getProjection();
//
//		cam.update(input, time);
//
//		model = glm::rotate(ct, glm::vec3(0, 1, 0));
//
//		draw(gallery.getObject("cube"), gallery.getShader("CAMERA"),
//			glm::value_ptr(model),
//			glm::value_ptr(view),
//			glm::value_ptr(proj), ct);
//
//		draw(gallery.getObject("cube"), gallery.getShader("TEXTURE"), tex,
//			glm::value_ptr(model),
//			glm::value_ptr(view),
//			glm::value_ptr(proj), ct);
//	}
//
//	freeTexture(tex);
//	
//	input.term();
//	time.term();
//	gallery.term();
//	window.term();
//	return 0;
//
//	}
//	
//
