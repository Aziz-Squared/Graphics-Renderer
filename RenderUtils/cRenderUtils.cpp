#define GLEW_STATIC
#include "GLEW\glew.h"
#include "GLFW\glfw3.h"
#include "cRenderUtils.h"
#include "Vertex.h"


void test()
{
	glfwInit();
	glfwTerminate();
}

Geometry makeGeometry(Vertex * verts, size_t vsize, unsigned int * tris, size_t tsize)
{
	Geometry retval;
	// Define the variables
	glCreateBuffers(1, &retval.vbo);	   // Store my vertices
	glCreateBuffers(1, &retval.ibo);	   // Store my indices
	glCreateVertexArrays(1, &retval.vao);  // Store attribute information

	// Scope the variables
	glBindVertexArray(retval.vao);
	glBindBuffer(GL_ARRAY_BUFFER, retval.vbo); // Scope our vertices
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, retval.ibo); // Triangle is scope

	// Initialize the variables
	new float[4];
	glBufferData(GL_ARRAY_BUFFER, vsize * sizeof(Vertex), verts, GL_STATIC_DRAW);
	glBufferData(GL_ARRAY_BUFFER, tsize * sizeof(unsigned), tris, GL_STATIC_DRAW);

	// Attributes
	glEnableVertexAttribArray(0);
	glEnableVertexAttribArray(1);
	glVertexAttribPointer(0, 4, GL_FLOAT, GL_FALSE, sizeof(Vertex), 0);
	glVertexAttribPointer(1, 4, GL_FLOAT, GL_FALSE, sizeof(Vertex), (const void*)16);

	// Unscope the variables
	glBindVertexArray(0);
	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
	retval.size = tsize;

	return retval;
}

void freeGeometry(Geometry &)
{
	glDeleteBuffers(1, &geo.vbo);
	glDeleteBuffers(1, &geo.ibo);
	glDeleteVertexArrays(1, &geo.vao);
	geo = { 0, 0, 0, 0 };
}
