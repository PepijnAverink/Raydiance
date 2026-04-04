#pragma once
// Core includes
#include "./core/error/result.h"
#include "./core/error/logger.h"
#include "./core/window/window.h"
#include "./core/files/file_path.h"


// Platform includes
#include "./platform/platform_type.h"


namespace Raydiance
{
	class Application
	{
	public:
		virtual ~Application(void);

		virtual Result Initialize(const PlatformType& _platformType);
		virtual Result Initialize(const PlatformType& _platformType, const FilePath& _filepath);

		virtual Result Run(void);

		bool OnEvent(Event& _event);

	protected:
		explicit Application(void);

		Window* m_Window = nullptr;

		Logger* m_Logger = nullptr;
	};
}

// To be defined by client
extern Raydiance::Application* CreateApplication(void);