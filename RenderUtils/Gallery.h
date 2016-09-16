#pragma once
#include <string>
#include <map>
#include "cRenderUtils.h"
#include "globjects.h"

// Render object: A thing we render, i.e Geometry, Mesh, Polygons, etc
// Shader Program: Pipeline of shader scripts that divide and fill the screen

class Gallery
{
	std::map<std::string, Geometry> objects;
	std::map<std::string, Shader> shaders;
	std::map<std::string, Texture> textures;

	// Shader makeShader(vsource, fsource)
public:
	bool makeShader(const char* name, const char* vsource, const char* fsource);
	bool loadShader(const char* name, const char* vpath, const char* fpath);

	bool makeObject(const char* name, const Vertex *verts, size_t vsize, const unsigned *tris, size_t tsize);
	bool loadOBJ(const char* name, const char* path);

	bool makeTexture(const char *name, int w, int h, int f, const unsigned char *p);
	bool loadTexture(const char *name, const char *path);

	const Texture  &getTexture(const char *name);
	const Geometry &getObject(const char *name);
	const Shader &getShader(const char *name);

	bool init();
	bool term();

};