#include "hzpch.h"
#include "Renderer.h"

namespace Hazel {

	void Renderer::BeginScene()
	{
		// camera, environment
	}

	void Renderer::EndScene()
	{
	}

	void Renderer::Submit(const std::shared_ptr<VertexArray>& vertexArray)
	{
		vertexArray->Bind();
		RenderCommand::DrawIndexed(vertexArray);
	}
}