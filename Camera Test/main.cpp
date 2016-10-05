#include "crenderutils.h"
#include "window.h"
#include "Input.h"
#include "Vertex.h"

#include "GLM\glm.hpp"
#include "GLM\ext.hpp"

void main()
{
	Window context;
	Input input;
	context.init(1280, 720);
	input.init(context);

	Geometry quad = makeGeometry(quad_verts, 4, quad_tris, 6);
	Geometry spear = loadOBJ("../res/models/soulspear.obj");

	Texture spear_normal = loadTexture("../res/textures/soulspear_normal.tga");
	Texture spear_diffuse = loadTexture("../res/textures/soulspear_diffuse.tga");
	Texture spear_specular = loadTexture("../res/textures/soulspear_specular.tga");


	Shader gpass = loadShader("../res/shaders/gpassVert.glsl",
		"../res/shaders/gpassFrag.glsl", true, true, true);

	Shader lpass = loadShader("../res/shaders/lPassVert.glsl",
		"../res/shaders/lPassFrag.glsl", true, true, true);

	Shader post = loadShader("../res/shaders/quadVert.glsl",
							 "../res/shaders/quadFrag.glsl", true, true, true);
	
	Shader onequad = loadShader("../res/shaders/onequadVert.glsl",
								 "../res/shaders/onequadFrag.glsl", true, true, true);

	Framebuffer screen = { 0, 1280, 720 };
	Framebuffer gframe = makeFramebuffer(1280, 720, 4);
	Framebuffer lframe = makeFramebuffer(1280, 720, 3);

	glm::mat4 model, view, proj;

	model = glm::translate(glm::vec3(0, -1, 0));
	view = glm::lookAt(glm::vec3(0, 0, 4), glm::vec3(0, 0, 0), glm::vec3(0, 1, 0));
	proj = glm::perspective(45.f, 1280.f / 720, 1.f, 100.f);

	float time = 0;

	while (context.step())
	{
	 //	tdraw(quad, onequad, screen);

		time += 0.016f;
		clearFramebuffer(gframe);
		clearFramebuffer(lframe);

		model = glm::rotate(time, glm::vec3(0, 1, 0)) * glm::translate(glm::vec3(0, -1, 0));

		// Geometry Pass
		tdraw(spear, gpass, gframe, model, view, proj,
			spear_diffuse, spear_normal, spear_specular);

		// Lighting pass
		tdraw(quad, lpass, lframe, view, proj,
			gframe.colors[0], gframe.colors[1],
			gframe.colors[2], gframe.colors[3],
			gframe.depth);

		// Debug Rendering Stuff.
		for (int i = 0; i < 4; ++i)
		{
			glm::mat4 mod =
				glm::translate(glm::vec3(-.75f + .5*i, 0.75f, 0)) *
				glm::scale(glm::vec3(0.25f, 0.25f, 1.f));
			tdraw(quad, post, screen, gframe.colors[i], mod);
		}

		glm::mat4 mod =
			glm::translate(glm::vec3(-.75f, 0.25f, 0)) *
			glm::scale(glm::vec3(0.25f, 0.25f, 1.f));
		tdraw(quad, post, screen, gframe.depth, mod);

		mod =
			glm::translate(glm::vec3(-.25f, 0.25f, 0)) *
			glm::scale(glm::vec3(0.25f, 0.25f, 1.f));
		tdraw(quad, post, screen, lframe.colors[0], mod);

		mod =
			glm::translate(glm::vec3(.25f, 0.25f, 0)) *
			glm::scale(glm::vec3(0.25f, 0.25f, 1.f));
		tdraw(quad, post, screen, lframe.colors[1], mod);

		mod =
			glm::translate(glm::vec3(.75f, 0.25f, 0)) *
			glm::scale(glm::vec3(0.25f, 0.25f, 1.f));
		tdraw(quad, post, screen, lframe.colors[2], mod);
	}

	context.term();
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
