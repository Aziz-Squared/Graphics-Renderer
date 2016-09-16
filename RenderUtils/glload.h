#pragma once
#include "gldecs.h"
#define TINYOBJLOADER_IMPLEMENTATION
#define STB_IMAGE_IMPLEMENTATION
#include "OBJ\tiny_obj_loader.h"
#include "GLM\gtc\noise.hpp"
#include "STB\stb_image.h"
#include "globjects.h"
#include <fstream>
#include <iostream>
#include <cstring>
#include <string>
#include <sstream>

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

Texture loadTexture(const char *path)
{
	glog("loading Texture", path);

	int w, h, f;
	unsigned char *p;

	Texture retval = { 0,0,0,0 };

	stbi_set_flip_vertically_on_load(true); // DirectX or OpenGL
	p = stbi_load(path, &w, &h, &f, STBI_default);

	if (!p) return retval;

	switch (f)
	{
	case STBI_grey: f = GL_RED;  break;
	case STBI_grey_alpha: f = GL_RG;   break;
	case STBI_rgb: f = GL_RGB;  break;
	case STBI_rgb_alpha: f = GL_RGBA; break;
	}

	retval = makeTexture(w, h, f, p);
	stbi_image_free(p);
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

	for (int i = 0; i < attrib.vertices.size() / 3; ++i)
	{
		verts[i].position = { attrib.vertices[i * 3],
			attrib.vertices[i * 3 + 1],
			attrib.vertices[i * 3 + 2], 1 };
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


