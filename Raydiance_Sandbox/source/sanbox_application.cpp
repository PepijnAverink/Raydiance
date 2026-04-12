#include "stdafx.h"
#include "sandbox_application.h"

// #define USE_DEBUG_ALLOCATOR
// #include "./core/memory/allocator/debug_allocator.h"

#include "./graphics/gfx/render_backend.h"


namespace Sandbox
{
	SandboxApplication::SandboxApplication()
		: Raydiance::Application()
	{
		//Raydiance::Graphics::RenderBackend::Create();

		printf("\nSANDBOX TURTLE!\n");
	}

	SandboxApplication::~SandboxApplication(void)
	{
		
	}

	Result SandboxApplication::Initialize(const PlatformType& _platformType, const FilePath& _filepath)
	{
		// Initialize base application
		Result result = Application::Initialize(_platformType, _filepath);
		if (CheckError(result) == true)
		{
			Logger::Log("Something went wrong while initializing the application.", LogLevel::LOG_LEVEL_ERROR);
			Logger::Log("No further evidence what went wrong, please see earlier logs.", LogLevel::LOG_LEVEL_ERROR);
			return result;
		}
		
		return Result::RESULT_GOOD;
	}
}

Raydiance::Application* CreateApplication()
{
	return new Sandbox::SandboxApplication();
}