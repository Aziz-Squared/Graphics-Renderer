#include "gldecs.h"
#include "crenderutils.h"
#include "Gallery.h"

bool Gallery::makeShader(const char * name, const char * vsource, const char * fsource)
{
	// Check to make sure that the name already doesn't exist
	if (shaders.count(name) < 1)
	{
		return false;
	}
	else shaders[name] = ::makeShader(vsource, fsource);

	return true;
}
bool Gallery::loadShader(const char* name, const char* vpath, const char* fpath)
{
	if (!shaders.count(name))
	{
		shaders[name] = ::loadShader(vpath, fpath);
		if (shaders[name].handle == 0)
		{
			shaders.erase(name);
		}
		return true;
	}

	return false;
}

const Shader & Gallery::getShader(const char * name)
{
	return shaders[name];
}

bool Gallery::makeObject(const char* name, const Vertex *verts, size_t vsize, const unsigned *tris, size_t tsize)
{
	if (objects.count(name) < 1)
	{
		return false;
	}
	else
		objects[name] = ::makeGeometry(verts, vsize, tris, tsize);
	return true;
}


bool Gallery::loadOBJ(const char* name, const char* path)
{
	if (!objects.count(name))
	{
		objects[name] = ::loadOBJ(path);

		return true;
	}

	return false;
}

const Texture & Gallery::getTexture(const char * name)
{
	return textures[name];
}

const Geometry & Gallery::getObject(const char *name)
{
		return objects[name];
}

bool Gallery::makeTexture(const char * name, int w, int h, int f, const unsigned char * p)
{
	textures[name] = ::makeTexture(w, h, f, p);
	return true;
}

bool Gallery::loadTexture(const char * name, const char * path)
{
	textures[name] = ::loadTexture(path);
	return true;
}

bool Gallery::term()
{
	// Loop through my maps and call my free functions
	for each(auto shader in shaders)
		freeShader(shader.second);
	for each(auto object in objects)
		freeGeometry(object.second);
	return false;
}
