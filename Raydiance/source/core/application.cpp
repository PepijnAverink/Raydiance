#include "./pch.h"
#include "./core/application.h"

namespace Raydiance
{
	Application::Application(void)
	{

	}

	Application::~Application(void)
	{
		delete m_Window;
	}

	Result Application::Initialize(const PlatformType& _platformType)
	{


		return Initialize(_platformType, FilePath());
	}

	Result Application::Initialize(const PlatformType& _platformType, const FilePath& _filepath)
	{
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