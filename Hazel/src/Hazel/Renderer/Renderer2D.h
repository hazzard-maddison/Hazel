#pragma once

#include "OrthographicCamera.h"
#include "Texture.h"

namespace Hazel {

	class Renderer2D
	{
	public:
		static void Init();
		static void Shutdown();

		static void BeginScene(const OrthographicCamera& camera);
		static void EndScene();
		static void Flush();


		// Premitives
		static void DrawQuad(const glm::vec3& position, const glm::vec2& size, const Ref<Texture2D>& texture, const glm::vec4 color, float tilingFactor = 1.0f);
		static void DrawQuad(const glm::vec2& position, const glm::vec2& size, const glm::vec4& color);
		static void DrawQuad(const glm::vec3& position, const glm::vec2& size, const glm::vec4& color);
		static void DrawQuad(const glm::vec2& position, const glm::vec2& size, const Ref<Texture2D>& texture, float tilingFactor = 1.0f);
		static void DrawQuad(const glm::vec3& position, const glm::vec2& size, const Ref<Texture2D>& texture, float tilingFactor = 1.0f);

		static void DrawRotatedQuad(const glm::vec3& position, float radians, const glm::vec2& size, const Ref<Texture2D>& texture, const glm::vec4 color, float tilingFactor = 1.0f);
		static void DrawRotatedQuad(const glm::vec2& position, float radians, const glm::vec2& size, const glm::vec4 color);
		static void DrawRotatedQuad(const glm::vec3& position, float radians, const glm::vec2& size, const glm::vec4 color);
		static void DrawRotatedQuad(const glm::vec2& position, float radians, const glm::vec2& size, const Ref<Texture2D>& texture, float tilingFactor = 1.0f);
		static void DrawRotatedQuad(const glm::vec3& position, float radians, const glm::vec2& size, const Ref<Texture2D>& texture, float tilingFactor = 1.0f);
		
		
	};
}
