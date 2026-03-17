#pragma once
#include <memory>

namespace Raydiance
{
	template<typename T>
	class BasicAllocator
	{
	public:
		using value_type = T;

		// Default constructor
		BasicAllocator() = default;

		template<typename U>
		constexpr BasicAllocator(const BasicAllocator<U>&) noexcept {}

		T* allocate(std::size_t n)
		{
			if (n > std::allocator_traits<BasicAllocator>::max_size(*this))
			{
				throw std::bad_alloc();
			}
			return static_cast<T*>(::operator new(n * sizeof(T)));
		}

		void deallocate(T* p, std::size_t) noexcept
		{
			::operator delete(p);
		}

		template<typename U, typename... Args>
		void construct(U* p, Args&&... args) {
			new(p) U(std::forward<Args>(args)...);
		}

		template<typename U>
		void destroy(U* p) noexcept {
			p->~U();
		}

		// should be implemented for basic STL containers to behave correctly
		friend bool operator==(const BasicAllocator&, const BasicAllocator&) { return true; }
		friend bool operator!=(const BasicAllocator&, const BasicAllocator&) { return false; }
	};
}