#include "hzpch.h"
#include "VertexArray.h"
#include "Renderer.h"
#include "Hazel/Platform/OpenGL/OpenGLVertexArray.h"

namespace Hazel {

	VertexArray* VertexArray::Create()
	{
		switch (Renderer::GetAPI()) {
			case RendererAPI::None:
			{
				HZ_CORE_ASSERT(false, "RendererAPI::None is not supported");
				return nullptr;
			}break;
			
			case RendererAPI::OpenGL: 
			{
				return new OpenGLVertexArray();
			}
		}

		HZ_CORE_ASSERT(false, "Unknown Renderer API");
		return nullptr;
	}
}