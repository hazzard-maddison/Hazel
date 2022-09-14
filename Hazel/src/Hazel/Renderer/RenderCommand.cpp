#include "hzpch.h"
#include "RenderCommand.h"

#include "Platform/OpenGL/OpenGLRendererAPI.h"

namespace Hazel {

	// we support OpenGL at this time
	RendererAPI* RenderCommand::s_RendererAPI = new OpenGLRendererAPI;
}