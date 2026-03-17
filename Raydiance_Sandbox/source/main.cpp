#include "stdafx.h"

// Memory includes
//#define USE_DEBUG_ALLOCATOR
#include "./core/memory/allocator/debug_allocator.h"

int main(char** argc, char** argv)
{
    Raydiance::DebugAllocator<void>::printStats();

    Application* app = new Application();
    app->OnInitialize();
    app->Run();
    app->OnTerminate();

    delete app;

    Raydiance::DebugAllocator<void>::printStats();

    return 0;
}