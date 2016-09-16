#pragma once
#include "globjects.h"

void clearFramebuffer(const Framebuffer &buffer);

namespace tdraw_internal
{
	void tdraw_begin(const Geometry &geometry, const Shader &shader, const Framebuffer &buffer);
	void tdraw_close(const Geometry &geometry, const Shader &shader, const Framebuffer &buffer);

}

inline void tdraw(const Geometry &geometry,
	const Shader &shader,
	const Framebuffer &buffer)
{
	tdraw_internal::tdraw_begin(geometry, shader, buffer);
	tdraw_internal::tdraw_close(geometry, shader, buffer);
}

