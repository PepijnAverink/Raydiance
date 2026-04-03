#include "stdafx.h"
#include "sandbox_application.h"

// #define USE_DEBUG_ALLOCATOR
// #include "./core/memory/allocator/debug_allocator.h"


namespace Sandbox
{
	SandboxApplication::SandboxApplication()
		: Raydiance::Application()
	{
		printf("\nSANDBOX TURTLE!\n");
	}
}

Raydiance::Application* CreateApplication()
{
	return new Sandbox::SandboxApplication();
}