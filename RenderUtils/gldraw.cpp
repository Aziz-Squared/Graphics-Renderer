#include "gldecs.h"
#include "gldraw.h"
#include "GLM\glm.hpp"
#include "GLM\ext.hpp"

void clearFramebuffer(const Framebuffer &buffer)
{
	glBindFramebuffer(GL_FRAMEBUFFER, buffer.handle);
	glClear(GL_DEPTH_BUFFER_BIT | GL_COLOR_BUFFER_BIT);
}

void useShaderFlags(const Shader &shader)
{
	if (shader.depthTest)
		glEnable(GL_DEPTH_TEST);
	else glDisable(GL_DEPTH_TEST);

	if (shader.faceCulling)
		glEnable(GL_CULL_FACE);
	else glDisable(GL_CULL_FACE);

	if (shader.additiveBlend)
		glEnable(GL_BLEND);
	else glDisable(GL_BLEND);

}

void tdraw_internal::tdraw_begin(const Geometry &geometry, const Shader &shader, const Framebuffer &buffer)
{
	glBindFramebuffer(GL_FRAMEBUFFER, buffer.handle);
	glUseProgram(shader.handle);
	glBindVertexArray(geometry.vao);

	useShaderFlags(shader);
	glViewport(0, 0, buffer.width, buffer.height);
}

void tdraw_internal::tdraw_close(const Geometry & geometry, const Shader & shader, const Framebuffer & buffer)
{
	//glDrawArrays(GL_TRIANGLES, 0, geometry.size);
	glDrawElements(GL_TRIANGLES, geometry.size, GL_UNSIGNED_INT, 0);

	glBindVertexArray(0);
	glUseProgram(0);
	glBindFramebuffer(GL_FRAMEBUFFER, 0);
	int w, h;
	glfwGetFramebufferSize(glfwGetCurrentContext(), &w, &h);

	glViewport(0, 0, w, h);
}

void tdraw_internal::tdraw_format(size_t idx, size_t tex, const glm::mat4 & val)
{
	glUniformMatrix4fv(idx, 1, GL_FALSE, glm::value_ptr(val));
	idx++;
}

void tdraw_internal::tdraw_format(size_t idx, size_t tex, const glm::vec3 & val)
{
	glUniform3fv(idx, 1, glm::value_ptr(val));
	idx++;
}

void tdraw_internal::tdraw_format(size_t idx, size_t tex, const glm::vec4 &val)
{
	glUniform4fv(idx, 1, glm::value_ptr(val));
	idx++;
}

void tdraw_internal::tdraw_format(size_t idx, size_t tex, int val)
{
	glUniform1i(idx, val);
	idx++;
}

void tdraw_internal::tdraw_format(size_t idx, size_t tex, float val)
{
	glUniform1f(idx, val);
	idx++;
}

void tdraw_internal::tdraw_format(size_t idx, size_t tex, const Texture & val)
{
	glActiveTexture(GL_TEXTURE0 + tex);
	glBindTexture(GL_TEXTURE_2D, val.handle);
	glUniform1i(idx, tex);
	idx++;
}
