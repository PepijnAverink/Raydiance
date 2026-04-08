#include "./pch.h"
#include "./core/application.h"


// Graphics includes
#include "./graphics/gfx/render_backend.h"


namespace Raydiance
{
	Application::Application(void)
	{

	}

	Application::~Application(void)
	{
		m_Renderer->Terminate();
		delete m_Renderer;

		Graphics::RenderBackend::Destroy();

		delete m_Window;

		delete m_Logger;
	}

	Result Application::Initialize(const PlatformType& _platformType)
	{


		return Initialize(_platformType, FilePath());
	}

	Result Application::Initialize(const PlatformType& _platformType, const FilePath& _filepath)
	{
		// Setup logger
		// ---------------------------------------------------------
		m_Logger = Logger::Create("");


		// Setup window
		// ---------------------------------------------------------
		{
			// Window descriptor
			WindowDescriptor windowDesc = { };
			windowDesc.Title  = "Raydiance - Sandbox application";
			windowDesc.Width  = 1280;
			windowDesc.Height = 720;


			// Window creation
			m_Window = Window::Create(windowDesc);
			m_Window->SetEventCallback(BIND_EVENT_FN(Application::OnEvent));
		}

		// Setup the RenderBackend
		Graphics::RenderBackend::Create(m_Window);


		// Create the 3D renderer
		{
			// Renderer3D descriptor
			Graphics::Renderer3DDescriptor rendererDesc = { };
			rendererDesc.FramesInFlight = 2; // Example value, adjust as needed


			// Renderer creation
			m_Renderer = new Graphics::Renderer3D();
			m_Renderer->Initialize(rendererDesc);	
		}

		m_Window->Show();
		return Result::RESULT_GOOD;
	}

	Result Application::Run(void)
	{

		while (m_Window->ShouldClose() == false)
		{
			m_Window->PollEvents();

			m_Renderer->BeginFrame();

			m_Renderer->EndFrame();
		}

		return Result::RESULT_GOOD;
	}

	bool Application::OnEvent(Event& _event)
	{

		return true;
	}
}