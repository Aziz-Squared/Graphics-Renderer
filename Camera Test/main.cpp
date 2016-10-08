#include "crenderutils.h"
#include "window.h"
#include "Input.h"
#include "Vertex.h"

#include "GLM\glm.hpp"
#include "GLM\ext.hpp"

struct RenderComponent
{
	// WWe want the gameObject's scale to be 1,
	// but the model doesn't fit that scale.
	// so we might add an extra model matrix to bring
	// the matrix into the right orientation/size for our game object

	glm::mat4 model;
	Geometry mesh;

	Texture norm, diff, spec;

	static Shader shader;
	static Framebuffer fb;

	//gpass shader for this object
	//draw(Shader, Target, Transform)
		//tdraw(...);

};

struct DirectionLight
{
	glm::vec3 dir, color;
	float size;
	glm::mat4 getMatrix()
	{return glm::ortho<float>(-size, size, -size, size, -size, size)
		* glm::lookAt(-dir, glm::vec3(0, 0, 0), glm::vec3(0, 1, 0)); }
};

void main()
{
	Window context;
	Input input;
	context.init(1280, 720);
	input.init(context);

	Geometry quad = makeGeometry(quad_verts, 4, quad_tris, 6);
	Geometry spear = loadOBJ("../res/models/soulspear.obj");
	Geometry sphere = loadOBJ("../res/models/sphere.obj");

	Texture spear_normal = loadTexture("../res/textures/soulspear_normal.tga");
	Texture spear_diffuse = loadTexture("../res/textures/soulspear_diffuse.tga");
	Texture spear_specular = loadTexture("../res/textures/soulspear_specular.tga");

	Texture spear_Textures[3] = { spear_normal, spear_diffuse, spear_specular };

	const unsigned char norm_pixels[4] = { 127, 127, 255, 255 };
	Texture vertex_normals = makeTexture(1, 1, 4, norm_pixels);

	const unsigned char white_pixels[4] = { 255, 255, 255, 255 };
	Texture white = makeTexture(1, 1, 4, white_pixels);


	Shader qdraw = loadShader("../res/shaders/quadVert.glsl", 
								"../res/shaders/quadFrag.glsl", false);

	Shader gpass = loadShader("../res/shaders/gpassVert.glsl",
								"../res/shaders/gpassFrag.glsl");

	Shader lpass = loadShader("../res/shaders/lPassVert.glsl",
								"../res/shaders/lPassFrag.glsl", false, true);
	Shader spass = loadShader("..res/shaders/spassVert.glsl",
								"..res/shaders/spassFrag.glsl", false);


	Framebuffer screen = { 0, 1280, 720 };

	// Colors don't need floats, but position/normal should use it
	bool isFtex[] = { false, true, false, true };
	Framebuffer gframe = makeFramebuffer(1280, 720, 4, isFtex);
	Framebuffer lframe = makeFramebuffer(1280, 720, 3);

	// Temporary shadow framebuffer. Will be cleared and reused by each light!
	// Its RESOLUTION WILL GREATLY EFFECT THE QUALITY. Try playing around with high/low res
	Framebuffer sframe = makeFramebuffer(4096, 4096, 0);

	// Camera information
	glm::mat4 camView = glm::lookAt(glm::vec3(0, 0, 4), glm::vec3(0, 0, 0), glm::vec3(0, 1, 0));
	glm::mat4 camProj = glm::perspective(45.f, 1280.f / 720.f, 1.f, 100.f);
	
	// Model Matrices
	glm::mat4 spearModel; // Rotates in main
	glm::mat4 sphereModel = glm::translate(glm::vec3(0.3f, -1, -0.2f));
	glm::mat4 wallModel = glm::rotate(45.f, glm::vec3(0, -1, 0)) * glm::translate(glm::vec3(0, 0, -2)) * glm::scale(glm::vec3(2, 2, 1));
	glm::mat4 gaigeModel = glm::translate(glm::vec3(0, -2.f, 0)) * glm::scale(glm::vec3(.05f, .05f, .05f))*glm::rotate(90.f, -glm::vec3(1, 0, 0));

	// Light Matrices and data
		// THey can all use the same projection matrix...
	glm::mat4 lightProj = glm::ortho<float>(-10, 10, -10, 10, -10, 10);
	glm::mat4 redView = glm::lookAt(glm::normalize(-glm::vec3(1, -1, -1)),
									glm::vec3(0, 0, 0), glm::vec3(0, 1, 0));
	glm::vec4 redColor = glm::vec4(1, 0, 0, 1);

	glm::mat4 greenView = glm::lookAt(glm::normalize(-glm::vec3(1, 1, -1)), glm::vec3(0, 0, 0), glm::vec3(0, 1, 0));
	glm::vec4 greenColor = glm::vec4(0, 1, 0, 1);


	float time = 0;

	while (context.step())
	{
		//	tdraw(quad, onequad, screen);

		time += 0.016f;
		spearModel = glm::rotate(time, glm::vec3(0, 1, 0)) * glm::translate(glm::vec3(0, -1, 0));

		////////////////////////////////////////////////
		// Geometry pass
		//
		clearFramebuffer(gframe);
		//
		tdraw(quad, gpass, gframe, camView, camProj, white, vertex_normals, white);

		//////////////////////////////////////////////
		// Light pass
		clearFramebuffer(lframe);
		////////////////////////////////////
		// Red Light

		// Shadow prepass
		clearFramebuffer(sframe);
		tdraw(quad, spass, sframe, redView, lightProj);

		// Add the green light now
		tdraw(quad, lpass, lframe, camView,
			gframe.colors[0], gframe.colors[1], gframe.colors[2], gframe.colors[3],
			sframe.depth, greenColor, greenView, lightProj);

		////////////////////////////////////////////////
		// Debug rendering stuff. Just single textures, to quads
		// drawing most of the images I've gathered so far

		// note that the sframe (shadow pass) will only be from the most recent light
		Texture debug_list[] = { gframe.colors[0], gframe.colors[1], gframe.colors[2], gframe.colors[3],
								gframe.depth, lframe.colors[1], lframe.colors[2], sframe.depth };

		for (int i = 0; i < sizeof(debug_list) / sizeof(Texture); ++i)
		{
			glm::mat4 mod = glm::translate(glm::vec3(-.75f + .5f*(i % 4), 0.75f - .5f*(i / 4), 0))
				* glm::scale(glm::vec3(0.25f, 0.25f, 1.f));

			tdraw(quad, qdraw, screen, debug_list[i], mod);
		}

		glm::mat4 mod =
			glm::translate(glm::vec3(-.5f, -.5f, 0)) *
			glm::scale(glm::vec3(.5f, .5f, 1.f));
		tdraw(quad, qdraw, screen, lframe.colors[0], mod);

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
