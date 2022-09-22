#include "Sandbox2D.h"
#include "Platform/OpenGL/OpenGLShader.h"
#include <imgui/imgui.h>
#include <glm/gtc/type_ptr.hpp>


Sandbox2D::Sandbox2D() :
	Layer("Sandbox 2D"), m_CameraController(1280.0f/720.0f)
{

}

void Sandbox2D::OnAttach()
{
	HZ_PROFILE_FUNCTION();

	m_CheckerboardTexture = Hazel::Texture2D::Create("assets/textures/Checkerboard.png");
}

void Sandbox2D::OnDetach()
{
	HZ_PROFILE_FUNCTION();

}

void Sandbox2D::OnUpdate(Hazel::Timestep timestep)
{
	HZ_PROFILE_FUNCTION();
	// Update
	m_CameraController.OnUpdate(timestep);
	
	// Render
	{
		HZ_PROFILE_SCOPE("Renderer Prep");

		Hazel::RenderCommand::SetClearColor({ 0.1f, 0.1f, 0.1f, 1 });
		Hazel::RenderCommand::Clear();
	}

	// BEGIN SCENE
	{
		HZ_PROFILE_SCOPE("Renderer Draw");
		Hazel::Renderer2D::BeginScene(m_CameraController.GetCamera());

		auto red = glm::vec4(1.0f, 0.0f, 0.0f, 1.0f);
		auto blue = glm::vec4(0.0f, 0.0f, 1.0f, 1.0f);
		auto green = glm::vec4(0.0f, 1.0f, 0.0f, 1.0f);
		auto purple = glm::vec4(1.0f, 0.0f, 1.0f, 1.0f);
		auto yellow = glm::vec4(1.0f, 1.0f, 0.0f, 1.0f);
		auto orange = glm::vec4(1.0f, 0.5f, 0.0f, 1.0f);
		auto cyan = glm::vec4(0.0f, 1.0f, 1.0f, 1.0f);

		auto rotation = glm::radians(45.0f);

		Hazel::Renderer2D::DrawQuad({-5.0f, 0.0f}, {1.0f, 1.0f}, red);
		Hazel::Renderer2D::DrawQuad({-4.5f, 0.0f, -0.1f}, {1.0f, 1.0f}, blue);
		Hazel::Renderer2D::DrawQuad({-3.0f, 0.0f}, {1.0f, 1.0f}, m_CheckerboardTexture);
		Hazel::Renderer2D::DrawQuad({ -2.5f, 0.0f, -0.1f }, { 1.0f, 1.0f }, m_CheckerboardTexture, 10.0f);
		Hazel::Renderer2D::DrawQuad({-1.0f, 0.0f, 0.0f}, {1.0f, 1.0f}, m_CheckerboardTexture, green);

		Hazel::Renderer2D::DrawRotatedQuad({1.0f, 0.0f}, rotation, {2.0f, 2.0f}, yellow);
		Hazel::Renderer2D::DrawRotatedQuad({2.0f, 0.0f, 0.1}, rotation, {2.0f, 2.0f}, orange);
		
		Hazel::Renderer2D::DrawRotatedQuad({5.0f, 0.0f}, rotation, {2.0f, 2.0f}, m_CheckerboardTexture);
		Hazel::Renderer2D::DrawRotatedQuad({6.0f, 0.0f, 0.1}, rotation, {2.0f, 2.0f}, m_CheckerboardTexture, 10.0f);

		Hazel::Renderer2D::DrawRotatedQuad({9.0f, 0.0f, 0.1}, rotation, {2.0f, 2.0f}, m_CheckerboardTexture, blue);


		Hazel::Renderer2D::EndScene();
	}
}

void Sandbox2D::OnImGuiRender()
{
	HZ_PROFILE_FUNCTION();

	ImGui::Begin("Settings");
	ImGui::ColorEdit4("Square Color", glm::value_ptr(m_SquareColor));
	ImGui::End();
}

void Sandbox2D::OnEvent(Hazel::Event& event)
{
	m_CameraController.OnEvent(event);
}
