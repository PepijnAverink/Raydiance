#include <./pch.h>


// Core includes
#define USE_DEBUG_ALLOCATOR
#include "./core/application.h"
#include "./core/memory/allocator/debug_allocator.h"


int main(char* argc, char** argv)
{
	Raydiance::DebugAllocator<void>::printStats();

	{
		// Create application - user implemented application
		Raydiance::Application* app = CreateApplication();
		app->Initialize(Raydiance::PlatformType::PLATFORM_TYPE_WINDOWS);
		app->Run();

		// Garbage
		delete app;
	}

	Raydiance::DebugAllocator<void>::printStats();
	return 0;
}