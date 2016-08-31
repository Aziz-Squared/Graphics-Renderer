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
Geometry loadOBJ(const char *path);


struct Shader
{
	unsigned handle;
};

Shader makeShader(const char *vsource, const char *fsource);

void freeShader(Shader &shader);

Shader loadShader(const char *vpath, const char *fpath);

void draw(const Geometry &geometry, const Shader &shader);

void draw(const Geometry &geometry, const Shader &shader, float time);

void draw(const Geometry &geometry, const Shader &shader, const float M[16], const float V[16], const float P[16]);
