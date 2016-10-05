#pragma once
#include "gldecs.h"
#include "globjects.h"
#include "Vertex.h"
#include "cRenderUtils.h"


Geometry makeGeometry(const Vertex * verts, size_t vsize,
	const unsigned int * tris, size_t tsize);

void freeGeometry(Geometry &geo);

Shader makeShader(const char *vsource, const char *fsource,
				  bool depth = true, bool add = false, bool face = true);

void freeShader(Shader &shader);

Texture makeTexture(unsigned width, unsigned height, unsigned channels, 
					const void *pixels, bool isFloat = false);

Texture makeTextureF(unsigned square, const float * pixels);

void freeTexture(Texture &t);

Framebuffer makeFramebuffer(unsigned width, unsigned height, unsigned nColors, bool *isfloat = nullptr, int *channels = nullptr);

void freeFramebuffer(Framebuffer &fb);