#pragma once
#include "./core/memory/allocator/allocation_statistics.h"

#include <sal.h>
#include <memory>

namespace Raydiance
{
	template<typename T>
	class DebugAllocator : public DebugAllocationStatistics
	{
	public:
		using value_type = T;

		// Default constructor
		DebugAllocator() = default;

		template<typename U>
		constexpr DebugAllocator(const DebugAllocator<U>&) noexcept {}

		T* allocate(std::size_t _n)
		{
			std::size_t bytes = _n * sizeof(T);

			if (_n > std::allocator_traits<DebugAllocator>::max_size(*this))
			{
				// Failed statistics
				s_Statistics.FailedAllocationCount += 1;
				s_Statistics.FailedAllocationSize += bytes;

				throw std::bad_alloc();
			}
			//T* ptr = static_cast<T*>(::operator new(bytes, std::nothrow));
			void* ptr = std::malloc(bytes);

			// Track statistics
			s_Statistics.ActiveAllocationCount += 1;
			s_Statistics.ActiveAllocationSize += bytes;
			s_Statistics.TotalAllocationCount += 1;
			s_Statistics.TotalAllocationSize += bytes;

			// Conditional statistics
			s_Statistics.PeakAllocationCount = std::max(s_Statistics.ActiveAllocationCount, s_Statistics.PeakAllocationCount);
			s_Statistics.PeakAllocationSize = std::max(s_Statistics.ActiveAllocationSize, s_Statistics.PeakAllocationSize);

			// Address statistics
			uintptr address = reinterpret_cast<uintptr>(ptr);
			s_Statistics.HeapAddressMax = std::max(s_Statistics.HeapAddressMax, address);
			s_Statistics.HeapAddressMin = std::min(s_Statistics.HeapAddressMin, address);

			return static_cast<T*>(ptr);
		}

		void deallocate(T* _p, std::size_t _n) noexcept
		{
			std::size_t bytes = _n * sizeof(T);
			//::operator delete(_p);

			if (!_p) return;
			std::free(_p);

			// Track statistics
			s_Statistics.ActiveAllocationCount -= 1;
			s_Statistics.ActiveAllocationSize -= bytes;
			s_Statistics.DeallocationCount += 1;
			s_Statistics.DeallocationSize += bytes;
		}

		template<typename U, typename... Args>
		void construct(U* _p, Args&&... _args) {
			new(_p) U(std::forward<Args>(_args)...);
		}

		template<typename U>
		void destroy(U* p) noexcept {
			p->~U();
		}

		// should be implemented for basic STL containers to behave correctly
		friend bool operator==(const DebugAllocator&, const DebugAllocator&) { return true; }
		friend bool operator!=(const DebugAllocator&, const DebugAllocator&) { return false; }
	};
}

#ifdef USE_DEBUG_ALLOCATOR
template<typename T>
using DefaultAllocator = Raydiance::DebugAllocator<T>;

Raydiance::DebugAllocator<std::byte> g_debugAllocator;

// Override global operator new
_Ret_notnull_
void* operator new(std::size_t size) {
	void* ptr = g_debugAllocator.allocate(size);
	if (!ptr)
		throw std::bad_alloc();
	return ptr;
}

// Override global operator new[]
_Ret_notnull_
void* operator new[](std::size_t size) {
	void* ptr = g_debugAllocator.allocate(size);
	if (!ptr)
		throw std::bad_alloc();
	return ptr;
}

// Override global operator delete
void operator delete(void* ptr) noexcept {
	if (ptr)
		g_debugAllocator.deallocate(static_cast<std::byte*>(ptr), 1); // size is not needed for tracking in DebugAllocator
}

// Override global operator delete[]
void operator delete[](void* ptr) noexcept {
	if (ptr)
		g_debugAllocator.deallocate(static_cast<std::byte*>(ptr), 1);
}

// Optional: sized delete (C++14+)
void operator delete(void* ptr, std::size_t size) noexcept {
	if (ptr)
		g_debugAllocator.deallocate(static_cast<std::byte*>(ptr), size);
}
void operator delete[](void* ptr, std::size_t size) noexcept {
	if (ptr)
		g_debugAllocator.deallocate(static_cast<std::byte*>(ptr), size);
}

#else
template<typename T>
using DefaultAllocator = std::allocator<T>;
#endif