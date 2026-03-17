#pragma once
#include "./core/container/types.h"

#include <iostream>

namespace Raydiance
{
	struct AllocationStatistics
	{
	public:
		uint64 ActiveAllocationCount = 0;
		uint64 ActiveAllocationSize  = 0;
		uint64 TotalAllocationCount  = 0;
		uint64 TotalAllocationSize   = 0;
		uint64 FailedAllocationCount = 0;
		uint64 FailedAllocationSize  = 0;

		uint64 PeakAllocationCount   = 0;
		uint64 PeakAllocationSize    = 0;
		uint64 DeallocationCount     = 0;
		uint64 DeallocationSize      = 0;

		uintptr HeapAddressMin		 = UINTPTR_MAX;
		uintptr HeapAddressMax		 = 0;
	};

	struct DebugAllocationStatistics
	{
	public:
		inline static AllocationStatistics s_Statistics{};

		static AllocationStatistics getStats() { return s_Statistics; }

		static void printStats()
		{
#if defined(USE_DEBUG_ALLOCATOR)
			std::cout << "(ActiveAllocationCount: \t" << s_Statistics.ActiveAllocationCount		<< ", "
				<< "ActiveAllocationSize: \t"		  << s_Statistics.ActiveAllocationSize		<< ")\n"
				<< "(PeakAllocationCount: \t"		  << s_Statistics.PeakAllocationCount		<< ", "
				<< "PeakAllocationSize: \t"			  << s_Statistics.PeakAllocationSize		<< ")\n"
				<< "(TotalAllocationCount: \t"		  << s_Statistics.TotalAllocationCount		<< ", "
				<< "TotalAllocatedSize: \t"			  << s_Statistics.TotalAllocationSize		<< ")\n"
				<< "(FailedAllocationCount: \t"		  << s_Statistics.FailedAllocationCount		<< ", "
				<< "FailedAllocationSize: \t"		  << s_Statistics.FailedAllocationSize		<< ")\n"
				<< "(DeallocationCount: \t"			  << s_Statistics.DeallocationCount			<< ", "
				<< "DeallocationSize: \t"			  << s_Statistics.DeallocationSize			<< ")\n"
				<< "(HeapAddressMin: \t"			  << s_Statistics.HeapAddressMin			<< ", "
				<< "HeapAddressMax: \t"				  << s_Statistics.HeapAddressMax			<< ")\n"
				<< "\n";
#endif
		}
	};
}