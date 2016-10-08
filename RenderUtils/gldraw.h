#pragma once
#include "globjects.h"
#include "GLM\fwd.hpp"
#include <cstring>

void clearFramebuffer(const Framebuffer &buffer);

namespace tdraw_internal
{
	void tdraw_begin(const Geometry &geometry, const Shader &shader, const Framebuffer &buffer);
	void tdraw_close(const Geometry &geometry, const Shader &shader, const Framebuffer &buffer);

	void tdraw_format(size_t idx, size_t tex, const glm::mat4 &val);
	void tdraw_format(size_t idx, size_t tex, const glm::vec4 &val);
	void tdraw_format(size_t idx, size_t tex, const glm::vec3 &val);
	void tdraw_format(size_t idx, size_t tex, int   val);
	void tdraw_format(size_t idx, size_t tex, float val);
	void tdraw_format(size_t idx, size_t tex, const Texture &val);

	template<typename T, typename ...U>
	void tdraw_unpack(size_t idx, size_t tex, T val, U &&...uniforms)
	{
		tdraw_format(idx, tex, val);
		tex++;
		tdraw_unpack(idx + 1, tex, uniforms...);

	}

	template<typename T>
	void tdraw_unpack(size_t idx, size_t tex, T val)
	{
		tdraw_format(idx, tex, val);
	}

}

// "f1 t5 i1 f1 f1 f1 f1"
template<typename ...U>
void tdraw(const Geometry &geometry, const Shader &shader, const Framebuffer &buffer, U ... uniforms)
{
	tdraw_internal::tdraw_begin(geometry, shader, buffer);

	tdraw_internal::tdraw_unpack(0, 0, uniforms...);

	tdraw_internal::tdraw_close(geometry, shader, buffer);
}

inline void tdraw(const Geometry &geometry,
	const Shader &shader,
	const Framebuffer &buffer)
{
	tdraw_internal::tdraw_begin(geometry, shader, buffer);
	tdraw_internal::tdraw_close(geometry, shader, buffer);
}

