#include "gldecs.h"
#include <conio.h>
#include <stdlib.h>
#include "cRenderUtils.h"
#include "Vertex.h"



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

void draw(const Geometry &geometry, const Shader &shader, const float M[16], const float V[16], const float P[16], float time)
{
	glUseProgram(shader.handle);
	glBindVertexArray(geometry.vao);

	glEnable(GL_CULL_FACE);

	glUniformMatrix4fv(0, 1, GL_FALSE, P);
	glUniformMatrix4fv(1, 1, GL_FALSE, V);
	glUniformMatrix4fv(2, 1, GL_FALSE, M);

	glDrawElements(GL_TRIANGLES, geometry.size, GL_UNSIGNED_INT, 0);
}

void draw(const Geometry &geometry, const Shader &shader, const Texture &texture, const float M[16], const float V[16], const float P[16], float time)
{
	glUseProgram(shader.handle);
	glBindVertexArray(geometry.vao);

	glEnable(GL_CULL_FACE);

	glUniformMatrix4fv(0, 1, GL_FALSE, P);
	glUniformMatrix4fv(1, 1, GL_FALSE, V);
	glUniformMatrix4fv(2, 1, GL_FALSE, M);

	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D, texture.handle);
	glUniform1i(3, 0);

	glDrawElements(GL_TRIANGLES, geometry.size, GL_UNSIGNED_INT, 0);

}







void drawPhong(const Geometry &g, const Shader &s,
	const float M[16], const float V[16], const float P[16])
{
	glEnable(GL_CULL_FACE);
	glEnable(GL_DEPTH_TEST);

	glUseProgram(s.handle);
	glBindVertexArray(g.vao);

	glUniformMatrix4fv(0, 1, GL_FALSE, P);
	glUniformMatrix4fv(1, 1, GL_FALSE, V);
	glUniformMatrix4fv(2, 1, GL_FALSE, M);


	glDrawElements(GL_TRIANGLES, g.size, GL_UNSIGNED_INT, 0);
}

void drawPhong(const Shader &s, const Geometry &g,
	const float M[16], const float V[16], const float P[16],
	const Texture *T, unsigned t_count)
{
	glEnable(GL_CULL_FACE);
	glEnable(GL_DEPTH_TEST);

	glUseProgram(s.handle);
	glBindVertexArray(g.vao);

	glUniformMatrix4fv(0, 1, GL_FALSE, P);
	glUniformMatrix4fv(1, 1, GL_FALSE, V);
	glUniformMatrix4fv(2, 1, GL_FALSE, M);

	int i = 0;
	for (; i < t_count; ++i)
	{
		glActiveTexture(GL_TEXTURE0 + i);
		glBindTexture(GL_TEXTURE_2D, T[i].handle);
		glUniform1i(3 + i, 0 + i);
	}

	glDrawElements(GL_TRIANGLES, g.size, GL_UNSIGNED_INT, 0);
}


void drawFB(const Geometry &geometry, const Shader &shader, const Framebuffer &buffer,
	const float M[16], const float V[16], const float P[16],
	const Texture *texture, unsigned t_count)
{
	glEnable(GL_CULL_FACE);
	glEnable(GL_DEPTH_TEST);

	glBindFramebuffer(GL_FRAMEBUFFER, buffer.handle);
	glUseProgram(shader.handle);
	glBindVertexArray(geometry.vao);

	glViewport(0, 0, buffer.width, buffer.height);

	glUniformMatrix4fv(0, 1, GL_FALSE, P);
	glUniformMatrix4fv(1, 1, GL_FALSE, V);
	glUniformMatrix4fv(2, 1, GL_FALSE, M);

	for (int i = 0; i < t_count; ++i)
	{
		glActiveTexture(GL_TEXTURE0 + i);
		glBindTexture(GL_TEXTURE_2D, texture[i].handle);
		glUniform1i(3 + i, 0 + i);
	}

	glDrawElements(GL_TRIANGLES, geometry.size, GL_UNSIGNED_INT, 0);
}

