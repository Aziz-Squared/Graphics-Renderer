#pragma once

struct Geometry
{
	unsigned vbo, ibo, vao, size;
	// Vertex Buffer Object: an array of vertices
	// Index Buffer Object : an array of indices(triangles)
	// Vertex Array Object : Groups the two with some formatting
	//Size				   : number of triangles
};

Geometry makeGeometry(const struct Vertex *verts, size_t vsize, 
						const unsigned int *tris, size_t tsize);
void freeGeometry(Geometry &);


struct Shader
{
	unsigned handle;
};

Shader makeShader(const char *vsource, const char *fsource);

void freeShader(Shader &shader);

void draw(const Geometry &geometry, const Shader &shader);

Shader loadShader(const char *vpath, const char *fpath);

Geometry loadOBJ(const char *path);	
