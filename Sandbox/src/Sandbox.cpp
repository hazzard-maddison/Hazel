#include <Hazel.h>

#include <imgui/imgui.h>
class ExampleLayer : public Hazel::Layer
{
public:
	ExampleLayer() :
		Layer("Example Layer")
	{

	}

	void OnUpdate() override
	{
		
		if (Hazel::Input::IsKeyPressed(HZ_KEY_TAB))
			HZ_INFO("Tab key is pressed");
	}

	void OnImGuiRender()
	{
		ImGui::Begin("Sandbox");
		ImGui::Text("Hello Hazel Sandbox");
		ImGui::End();
	}

	/*void OnEvent(Hazel::Event& event) override
	{
		
	}*/
};

class Sandbox : public Hazel::Application
{
public:
	Sandbox()
	{
		PushOverlay(new ExampleLayer());
	}

	~Sandbox()
	{

	}
};

Hazel::Application* Hazel::CreateApplication()
{
	return new Sandbox();
}