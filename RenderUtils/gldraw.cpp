#include "gldecs.h"
#include "gldraw.h"

void clearFramebuffer(const Framebuffer &buffer)
{
	glBindFramebuffer(GL_FRAMEBUFFER, buffer.handle);
	glClear(GL_DEPTH_BUFFER_BIT | GL_COLOR_BUFFER_BIT);
}

void tdraw_begin(const Geometry &geometry, const Shader &shader, const Framebuffer &buffer)
{
	glBindFramebuffer(GL_FRAMEBUFFER, buffer.handle);
	glUseProgram(shader.handle);
	glBindVertexArray(geometry.vao);

	glEnable(GL_CULL_FACE);
	glEnable(GL_DEPTH_TEST);
	glViewport(0, 0, buffer.width, buffer.height);
}

void tdraw_internal::tdraw_close(const Geometry & geometry, const Shader & shader, const Framebuffer & buffer)
{
	glDrawElements(GL_TRIANGLES, geometry.size, GL_UNSIGNED_INT, 0);

	glBindVertexArray(0);
	glUseProgram(0);
	glBindFramebuffer(GL_FRAMEBUFFER, 0);
	int w, h;
	glfwGetFramebufferSize(glfwGetCurrentContext(), &w, &h);

	glViewport(0, 0, w, h);
}
