#pragma once
// Core includes
#include "./core/container/types.h"


// Generic includes
#include <array>


namespace Raydiance
{
	class UUID
	{
	public:
		UUID();
		UUID(uint64 _uuid);
		UUID(const UUID& _other);

		operator uint64 () { return m_UUID; }
		operator const uint64() const { return m_UUID; }
	private:
		uint64 m_UUID;
	};
}


namespace std 
{
	template <>
	struct hash<Raydiance::UUID>
	{
		std::size_t operator()(const Raydiance::UUID& uuid) const
		{
			return hash<uint64>()((uint64)uuid);
		}
	};
}