#include "hzpch.h"
#include "Buffer.h"
#include "Renderer.h"
#include "Hazel/Platform/OpenGL/OpenGLBuffer.h"


namespace Hazel {

	VertexBuffer* VertexBuffer::Create(float* vertices, uint32_t size)
	{
		switch (Renderer::GetAPI())
		{
			case RendererAPI::None :
			{
				HZ_CORE_ASSERT(false, "RendererAPI::None is not supported");
				return nullptr;
			}break;

			case RendererAPI::OpenGL :
			{
				return new OpenGLVertexBuffer(vertices, size);
			}break;

		};

		HZ_CORE_ASSERT(false, "Unknown RendererAPI");
		return nullptr;
	}

	IndexBuffer* IndexBuffer::Create(uint32_t* indices, uint32_t size)
	{
		switch (Renderer::GetAPI())
		{
		case RendererAPI::None:
		{
			HZ_CORE_ASSERT(false, "RendererAPI::None is not supported");
			return nullptr;
		}break;

		case RendererAPI::OpenGL:
		{
			return new OpenGLIndexBuffer(indices, size);
		}break;

		};

		HZ_CORE_ASSERT(false, "Unknown RendererAPI");
		return nullptr;
	}
}