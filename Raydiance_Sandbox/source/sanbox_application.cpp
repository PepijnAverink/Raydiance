#include "stdafx.h"
#include "sandbox_application.h"

// #define USE_DEBUG_ALLOCATOR
// #include "./core/memory/allocator/debug_allocator.h"

#include "./graphics/renderer/render_backend.h"


namespace Sandbox
{
	SandboxApplication::SandboxApplication()
		: Raydiance::Application()
	{
		//Raydiance::Graphics::RenderBackend::Create();

		printf("\nSANDBOX TURTLE!\n");
	}
}

Raydiance::Application* CreateApplication()
{
	return new Sandbox::SandboxApplication();
}