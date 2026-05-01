#include <./pch.h>
#include "./core/UUID.h"


// Generic includes
#include <random>


namespace Raydiance
{
	static std::random_device s_RandomDevice;
	static std::mt19937_64 eng(s_RandomDevice());
	static std::uniform_int_distribution<uint64_t> s_UniformDistribution;

	UUID::UUID()
		: m_UUID(s_UniformDistribution(eng))
	{ }


	UUID::UUID(uint64 _uuid)
		: m_UUID(_uuid)
	{ }


	UUID::UUID(const UUID& _other)
		: m_UUID(_other.m_UUID)
	{ }
}