#include "hzpch.h"
#include "Buffer.h"
#include "Renderer.h"
#include "Platform/OpenGL/OpenGLBuffer.h"


namespace Hazel {

	Ref<VertexBuffer> VertexBuffer::Create(float* vertices, uint32_t size)
	{
		switch (Renderer::GetAPI())
		{
		case RendererAPI::API::None :
			{
				HZ_CORE_ASSERT(false, "RendererAPI::None is not supported");
				return nullptr;
			}break;

		case RendererAPI::API::OpenGL :
			{
				return CreateRef<OpenGLVertexBuffer>(vertices, size);
			}break;

		};

		HZ_CORE_ASSERT(false, "Unknown RendererAPI");
		return nullptr;
	}

	Ref<IndexBuffer> IndexBuffer::Create(uint32_t* indices, uint32_t size)
	{
		switch (Renderer::GetAPI())
		{
		case RendererAPI::API::None:
		{
			HZ_CORE_ASSERT(false, "RendererAPI::None is not supported");
			return nullptr;
		}break;

		case RendererAPI::API::OpenGL:
		{
			return CreateRef<OpenGLIndexBuffer>(indices, size);
		}break;

		};

		HZ_CORE_ASSERT(false, "Unknown RendererAPI");
		return nullptr;
	}
}