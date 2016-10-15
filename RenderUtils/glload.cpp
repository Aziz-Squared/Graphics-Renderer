#pragma once
#include "gldecs.h"
#include "glload.h"
#include "glmake.h"
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

Shader loadShader(const char *vpath, const char *fpath,
				  bool depth, bool add, bool face)
{
	std::string fsource = copyFileToArray(fpath).c_str();
	std::string vsource = copyFileToArray(vpath).c_str();

	Shader retval = makeShader(vsource.c_str(), fsource.c_str(), depth, add, face);


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

	retval = makeTexture(w, h, f, p);
	stbi_image_free(p);
	return retval;
}

Geometry loadOBJ(const char *path)
{
	// We can use TinyOBJ to load the file
	// We can extract vertex positions and face data
	// We can create an array to store that vertex and face data

	//std::string inputfile = "cornell_box.obj";
	tinyobj::attrib_t attrib;
	std::vector<tinyobj::shape_t> shapes;
	std::vector<tinyobj::material_t> materials;
	std::string err;

	bool ret = tinyobj::LoadObj(&attrib, &shapes, &materials, &err, path);

	int vsize = shapes[0].mesh.indices.size();
	Vertex   *verts = new Vertex[vsize];
	unsigned * tris = new unsigned[vsize];

	for (int i = 0; i < vsize; ++i)
	{
		auto ind = shapes[0].mesh.indices[i];

		const float *n = &attrib.normals[ind.normal_index * 3]; // +1, +2, 0
		const float *p = &attrib.vertices[ind.vertex_index * 3]; // +1, +2, 1

		verts[i].position = glm::vec4(p[0], p[1], p[2], 1.f);
		verts[i].normal = glm::vec4(n[0], n[1], n[2], 0.f);

		if (ind.texcoord_index >= 0)
		{
			const float *t = &attrib.texcoords[ind.texcoord_index * 2]; // +1
			verts[i].texCoord = glm::vec2(t[0], t[1]);
		}

		tris[i] = i;
	}


	Geometry retval = makeGeometry(verts, vsize,
										tris, vsize);

	delete[] tris;
	delete[] verts;

	// Then we can call makeGeometry as per model
	return retval;
}


