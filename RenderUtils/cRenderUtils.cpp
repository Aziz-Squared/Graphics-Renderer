#define GLEW_STATIC
#define TINYOBJLOADER_IMPLEMENTATION
#include "GLEW\glew.h"
#include "GLFW\glfw3.h"
#include "cRenderUtils.h"
#include "Vertex.h"
#include "OBJ\tiny_obj_loader.h"
#include <fstream>
#include <iostream>
#include <cstring>
#include <string>
#include <sstream>


Geometry makeGeometry(const Vertex * verts, size_t vsize, const unsigned int * tris, size_t tsize)
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

void draw(const Geometry &geometry, const Shader &shader)
{
	glUseProgram(shader.handle);

	// Binding the VAO also binds the IBO (tri) and VBO (verts)
	glBindVertexArray(geometry.vao);

	// Draw elements will draw the vertices that are currently bound
	// using an array of indices
	// IF AN IBO IS BOUND, we don't need to provide any indices
	glDrawElements(GL_TRIANGLES, geometry.size, GL_UNSIGNED_INT, 0);
}

void draw(const Geometry &geometry, const Shader &shader, float time)
{
	glUseProgram(shader.handle);
	glBindVertexArray(geometry.vao);

	int loc = glGetUniformLocation(shader.handle, "time");

	glUniform1f(loc, time);

	glDrawElements(GL_TRIANGLES, geometry.size, GL_UNSIGNED_INT, 0);


}

std::string copyFileToArray(const char *path)
{
	std::stringstream line;
	std::ifstream file;
	file.open(path);
	file.seekg(0, file.beg);
	if (file.is_open())
	{
		line << file.rdbuf();
	}
	line << '\0';

	return line.str();

}

Shader loadShader(const char *vpath, const char *fpath)
{
	std::string fsource = copyFileToArray(fpath).c_str();
	std::string vsource = copyFileToArray(vpath).c_str();

	Shader retval = makeShader(vsource.c_str(), fsource.c_str());


	return retval;
}

Geometry loadOBJ(const char *path)
{
	// We can use TinyOBJ to load the file
	// We can extract vertex positions and face data
	// We can create an array to store that vertex and face data

	std::string inputfile = "cornell_box.obj";
	tinyobj::attrib_t attrib;
	std::vector<tinyobj::shape_t> shapes;
	std::vector<tinyobj::material_t> materials;
	std::string err;
	
	bool ret = tinyobj::LoadObj(&attrib, &shapes, &materials, &err, path);

	Vertex *verts = new Vertex[attrib.vertices.size() / 3];
	unsigned *tris = new unsigned[shapes[0].mesh.indices.size()];

	shapes[0].mesh.indices;

	for (int i = 0; i < attrib.vertices.size() / 3 ; ++i)
	{
		verts[i] = { attrib.vertices[i*3],
					attrib.vertices[i*3+1],
					attrib.vertices[i*3+2], 1 };
	}

	for (int i = 0; i < shapes[0].mesh.indices.size(); ++i)
		tris[i] = shapes[0].mesh.indices[i].vertex_index;


	Geometry retval = makeGeometry(verts, attrib.vertices.size() / 3,
									tris, shapes[0].mesh.indices.size());

	delete[] tris;
	delete[] verts;

	// Then we can call makeGeometry as per model
	return retval;
}