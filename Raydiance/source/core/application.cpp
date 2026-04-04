#include "./pch.h"
#include "./core/application.h"


// Graphics includes
#include "./graphics/renderer/render_backend.h"


namespace Raydiance
{
	Application::Application(void)
	{

	}

	Application::~Application(void)
	{
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
			windowDesc.Title  = "Raydiance - Sanxbox application";
			windowDesc.Width  = 1280;
			windowDesc.Height = 720;


			// Window creation
			m_Window = Window::Create(windowDesc);
			m_Window->SetEventCallback(BIND_EVENT_FN(Application::OnEvent));
		}

		// Setup the RenderBackend
		Graphics::RenderBackend::Create(m_Window);


		m_Window->Show();
		return Result::RESULT_GOOD;
	}

	Result Application::Run(void)
	{

		while (m_Window->ShouldClose() == false)
		{
			m_Window->PollEvents();
		}

		return Result::RESULT_GOOD;
	}

	bool Application::OnEvent(Event& _event)
	{

		return true;
	}
}