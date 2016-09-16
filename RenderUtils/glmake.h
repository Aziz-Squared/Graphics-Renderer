#pragma once
#include "gldecs.h"
#include "globjects.h"
#include "Vertex.h"
#include "cRenderUtils.h"


Geometry makeGeometry(const Vertex * verts, size_t vsize, 
						const unsigned int * tris, size_t tsize)
{
	Geometry retval;
	// Define the variables
	glGenBuffers(1, &retval.vbo);	   // Store my vertices
	glGenBuffers(1, &retval.ibo);	   // Store my indices
	glGenVertexArrays(1, &retval.vao);  // Store attribute information

										// Scope the variables
	glBindVertexArray(retval.vao);
	glBindBuffer(GL_ARRAY_BUFFER, retval.vbo); // Scope our vertices
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, retval.ibo); // Triangle is scope

													   // Initialize the variables
	glBufferData(GL_ARRAY_BUFFER, vsize * sizeof(Vertex), verts, GL_STATIC_DRAW);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, tsize * sizeof(unsigned), tris, GL_STATIC_DRAW);

	// Attributes
	glEnableVertexAttribArray(0); // Position
	glEnableVertexAttribArray(1); // Color
	glEnableVertexAttribArray(2); // Normal
	glEnableVertexAttribArray(3); // TexCoord'



	glVertexAttribPointer(0, 4, GL_FLOAT, GL_FALSE, sizeof(Vertex), 0);
	glVertexAttribPointer(1, 4, GL_FLOAT, GL_FALSE, sizeof(Vertex), (const void*)16);

	// Unscope the variables
	glBindVertexArray(0);
	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
	retval.size = tsize;

	return retval;
}

void freeGeometry(Geometry &geo)
{
	glDeleteBuffers(1, &geo.vbo);
	glDeleteBuffers(1, &geo.ibo);
	glDeleteVertexArrays(1, &geo.vao);
	geo = { 0, 0, 0, 0 };
}

Shader makeShader(const char *vsource, const char *fsource)
{
	Shader retval;
	// Create our variables
	retval.handle = glCreateProgram();
	unsigned vs = glCreateShader(GL_VERTEX_SHADER);
	unsigned fs = glCreateShader(GL_FRAGMENT_SHADER);
	// Initialize our variables
	glShaderSource(vs, 1, &vsource, 0);
	glShaderSource(fs, 1, &fsource, 0);
	// Compile the shaders
	glCompileShader(vs);
	glCompileShader(fs);
	// Linke the shaders into a single program
	glAttachShader(retval.handle, vs);
	glAttachShader(retval.handle, fs);
	glLinkProgram(retval.handle);
	// No longer need these! Their functionality has been eaten by the program
	glDeleteShader(vs);
	glDeleteShader(fs);


	return retval;
}

void freeShader(Shader &shader)
{
	glDeleteProgram(shader.handle);
	shader.handle = 0;
}

Texture makeTexture(unsigned width, unsigned height, unsigned format, const unsigned char *pixels)
{
	Texture retval = { 0, width, height, format };

	glGenTextures(1, &retval.handle);				// Declaration
	glBindTexture(GL_TEXTURE_2D, retval.handle);    // Scoping

	glTexImage2D(GL_TEXTURE_2D, 0, format, width, height, 0, format, GL_UNSIGNED_BYTE, pixels);

	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);

	glBindTexture(GL_TEXTURE_2D, 0);

	return retval;

}

Texture makeTextureF(unsigned square, const float * pixels)
{
	Texture retval = { 0, square, square, GL_RED }; // GL_RED, GL_RG, GL_RGB, GL_RGBA

	glGenTextures(1, &retval.handle);				// Declaration
	glBindTexture(GL_TEXTURE_2D, retval.handle);    // Scoping

	glTexImage2D(GL_TEXTURE_2D, 0, GL_R32F, square, square, 0, GL_RED, GL_FLOAT, pixels);

	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);

	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_R, GL_CLAMP_TO_EDGE);

	glBindTexture(GL_TEXTURE_2D, 0);
	return retval;
}

void freeTexture(Texture &t)
{
	glDeleteTextures(1, &t.handle);
	t = { 0,0,0,0 };
}


Framebuffer makeFrameBuffer(unsigned width, unsigned height, unsigned nColors)
{
	Framebuffer retval = { 0,width,height,nColors };

	glGenFramebuffers(1, &retval.handle);
	glBindFramebuffer(GL_FRAMEBUFFER, retval.handle);

	////////////////////////////////////////////////////////////////////////////////////
	retval.depth = makeTexture(width, height, GL_DEPTH_COMPONENT, 0);
	glFramebufferTexture(GL_FRAMEBUFFER, GL_DEPTH_ATTACHMENT, retval.depth.handle, 0);
	////////////////////////////////////////////////////////////////////////////////////
	const GLenum attachments[8] =
	{ GL_COLOR_ATTACHMENT0, GL_COLOR_ATTACHMENT1, GL_COLOR_ATTACHMENT2,
		GL_COLOR_ATTACHMENT3, GL_COLOR_ATTACHMENT4, GL_COLOR_ATTACHMENT5,
		GL_COLOR_ATTACHMENT6, GL_COLOR_ATTACHMENT7 };

	for (int i = 0; i < nColors && i < 8; ++i)
	{
		retval.colors[i] = makeTexture(width, height, GL_RGBA, 0);
		glFramebufferTexture(GL_FRAMEBUFFER, attachments[i],
			retval.colors[i].handle, 0);
	}
	glDrawBuffers(nColors, attachments);
	glBindFramebuffer(GL_FRAMEBUFFER, 0);
	return retval;
}

void freeFramebuffer(Framebuffer &fb)
{
	for (unsigned i = 0; i < fb.nColors; ++i)
		freeTexture(fb.colors[i]);

	glDeleteFramebuffers(1, &fb.handle);
	fb = { 0,0,0,0 };
}
