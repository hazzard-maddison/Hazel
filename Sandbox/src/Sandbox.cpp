#include <Hazel.h>
#include <Hazel/Renderer/OrthographicCamera.h>
#include <imgui/imgui.h>
#include <glm/gtc/matrix_transform.hpp>

class ExampleLayer : public Hazel::Layer{

public:
	ExampleLayer() :
			Layer("Example Layer"), m_Camera(-1.6f, 1.6f, -0.9f, 0.9f), m_SquarePosition(0.0f)
		{

			m_CameraPosition = m_Camera.GetPosition();
			// Triangle
			m_VertexArray.reset(Hazel::VertexArray::Create());

			float vertices[7 * 3] = {
				-0.5f, -0.5f, 0.0f,    1.0f, 1.0f, 0.0f, 1.0f,
				 0.5f, -0.5f, 0.0f,    0.0f, 1.0f, 1.0f, 1.0f,
				 0.0f,  0.25f, 0.0f,    1.0f, 0.0f, 1.0f, 1.0f,
			};

			std::shared_ptr<Hazel::VertexBuffer> vertexBuffer;
			vertexBuffer.reset(Hazel::VertexBuffer::Create(vertices, sizeof(vertices)));
			Hazel::BufferLayout layout = {
				{ Hazel::ShaderDataType::Float3, "a_Position"},
				{ Hazel::ShaderDataType::Float4, "a_Color"}
			};
			vertexBuffer->SetLayout(layout);
			m_VertexArray->AddVertexBuffer(vertexBuffer);


			uint32_t indices[3] = { 0, 1, 2 };
			std::shared_ptr<Hazel::IndexBuffer> indexBuffer;
			indexBuffer.reset(Hazel::IndexBuffer::Create(indices, sizeof(indices) / sizeof(uint32_t)));
			m_VertexArray->SetIndexBuffer(indexBuffer);

			std::string vertexSrc = R"(
				#version 330 core
			
				layout(location = 0) in vec3 a_Position;
				layout(location = 1) in vec4 a_Color;

				uniform mat4 u_ViewProjection;
				uniform mat4 u_Transform;

				out vec3 v_Position;
				out vec4 v_Color;

				void main()
				{
					v_Position = a_Position;
					v_Color = a_Color;
					gl_Position = u_ViewProjection * u_Transform * vec4(a_Position, 1.0);
				}
			)";

			std::string fragmentSrc = R"(
				#version 330 core
			
				layout(location = 0) out vec4 color;

				in vec3 v_Position;
				in vec4 v_Color;

				void main()
				{
					color = vec4(v_Position * 0.5 + 0.5 , 1.0);
					color = v_Color;
				}
			)";

			m_Shader.reset(new Hazel::Shader(vertexSrc, fragmentSrc));

			// Square
			m_SquareVA.reset(Hazel::VertexArray::Create());

			float squareVertices[4 * 3] = {
				-0.75f, -0.75f, 0.0f,
				 0.75f, -0.75f, 0.0f,
				 0.75f,  0.75f, 0.0f,
				-0.75f,  0.75f, 0.0f
			};

			std::shared_ptr<Hazel::VertexBuffer> squareVB;
			squareVB.reset(Hazel::VertexBuffer::Create(squareVertices, sizeof(squareVertices)));
			Hazel::BufferLayout squareVBLayout = {
				{ Hazel::ShaderDataType::Float3, "a_Position"}
			};
			squareVB->SetLayout(squareVBLayout);
			m_SquareVA->AddVertexBuffer(squareVB);

			uint32_t squareIndices[6] = { 0, 1, 2, 2, 3, 0 };
			std::shared_ptr<Hazel::IndexBuffer> squareIB;
			squareIB.reset(Hazel::IndexBuffer::Create(squareIndices, sizeof(squareIndices) / sizeof(uint32_t)));
			m_SquareVA->SetIndexBuffer(squareIB);

			// Square
			std::string blueShaderVertexSrc = R"(
				#version 330 core
			
				layout(location = 0) in vec3 a_Position;

				out vec3 v_Position;

				uniform mat4 u_ViewProjection;
				uniform mat4 u_Transform;

				void main()
				{
					v_Position =  a_Position;
					gl_Position = u_ViewProjection * u_Transform * vec4(a_Position, 1.0);
				}
			)";

			std::string blueShaderFragmentSrc = R"(
				#version 330 core
			
				layout(location = 0) out vec4 color;

				in vec3 v_Position; 

				void main()
				{
					color = vec4(0.5f * v_Position.y, 0.05f, v_Position.y * 0.5f + 0.5, 1.0f);
				}
			)";

			m_BlueShader.reset(new Hazel::Shader(blueShaderVertexSrc, blueShaderFragmentSrc));

		}

	void OnUpdate(Hazel::Timestep timestep) override
	{
		// Camera Move
		if (Hazel::Input::IsKeyPressed( HZ_KEY_LEFT ))
		{
			m_CameraPosition.x -= m_CameraMoveSpeed * timestep;
		}
		else if (Hazel::Input::IsKeyPressed( HZ_KEY_RIGHT ))
		{
			m_CameraPosition.x += m_CameraMoveSpeed * timestep;
		}

		if (Hazel::Input::IsKeyPressed( HZ_KEY_UP ))
		{
			m_CameraPosition.y += m_CameraMoveSpeed * timestep;
		}
		else if (Hazel::Input::IsKeyPressed( HZ_KEY_DOWN ))
		{
			m_CameraPosition.y -= m_CameraMoveSpeed * timestep;
		}

		// Camera Rotate
		if (Hazel::Input::IsKeyPressed(HZ_KEY_A))
		{
			m_CameraRotation += m_CameraRotationSpeed * timestep;
		}
		else if (Hazel::Input::IsKeyPressed(HZ_KEY_D))
		{
			m_CameraRotation -= m_CameraRotationSpeed * timestep;
		}

		// Square Move
		if (Hazel::Input::IsKeyPressed(HZ_KEY_J))
		{
			m_SquarePosition.x -= m_SquareMoveSpeed * timestep;
		}
		else if (Hazel::Input::IsKeyPressed(HZ_KEY_L))
		{
			m_SquarePosition.x += m_SquareMoveSpeed * timestep;
		}

		if (Hazel::Input::IsKeyPressed(HZ_KEY_I))
		{
			m_SquarePosition.y += m_SquareMoveSpeed * timestep;
		}
		else if (Hazel::Input::IsKeyPressed(HZ_KEY_K))
		{
			m_SquarePosition.y -= m_SquareMoveSpeed * timestep;
		}


		Hazel::RenderCommand::SetClearColor({ 0.1f, 0.1f, 0.1f, 1 });
		Hazel::RenderCommand::Clear();

		m_Camera.SetPosition(m_CameraPosition);
		m_Camera.SetRotation(m_CameraRotation);


		Hazel::Renderer::BeginScene(m_Camera);
		
		glm::mat4 transform = glm::translate(glm::mat4(1.0f), m_SquarePosition);

		Hazel::Renderer::Submit(m_BlueShader, m_SquareVA, transform);

		Hazel::Renderer::Submit(m_Shader, m_VertexArray);

		Hazel::Renderer::EndScene();
	}

	void OnImGuiRender()
		{
			
		}

	void OnEvent(Hazel::Event& event) override
	{
	}

private:
	std::shared_ptr<Hazel::Shader> m_Shader;
	std::shared_ptr<Hazel::VertexArray> m_VertexArray;


	std::shared_ptr<Hazel::Shader> m_BlueShader;
	std::shared_ptr<Hazel::VertexArray> m_SquareVA;

	Hazel::OrthographicCamera m_Camera;
	glm::vec3 m_CameraPosition;
	float m_CameraMoveSpeed = 5.0f;

	float m_CameraRotation = 0.0f;
	float m_CameraRotationSpeed = 45.0f;

	glm::vec3 m_SquarePosition;
	float m_SquareMoveSpeed = 1.0f;

};

class Sandbox : public Hazel::Application
{
public:
	Sandbox() : Application()
	{
		PushOverlay(new ExampleLayer());

		

	}

	~Sandbox()
	{

	}

	virtual void Update() override
	{
		
	}



};

Hazel::Application* Hazel::CreateApplication()
{
	return new Sandbox();
}