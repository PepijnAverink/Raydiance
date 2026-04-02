#include "stdafx.h"

// Memory includes
//#define USE_DEBUG_ALLOCATOR
#include "./core/memory/allocator/debug_allocator.h"

int main(char** argc, char** argv)
{
    Raydiance::DebugAllocator<void>::printStats();


    Raydiance::DebugAllocator<void>::printStats();

    return 0;
}