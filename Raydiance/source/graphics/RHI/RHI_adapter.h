#pragma once
// Core includes
#include "./core/container/types.h"

// Graphics includes
#include "./graphics/RHI/RHI_adapter_type.h"

namespace Raydiance
{
	namespace Graphics
	{
		class RHI_Adapter
		{
		public:
			// Default constructor and descructor
			// ======================================
					 RHI_Adapter(void) = default;
			virtual ~RHI_Adapter(void) = default;

		protected:
			// Raw stored data about the adapter
			std::string		m_Name;
			std::string		m_Vendor;
			uint32			m_VRam = 0;

			RHI_AdapterType m_Type = RHI_AdapterType::RHI_ADAPTER_TYPE_INVALID;
		};

		inline std::string ResolvePCI_ID(uint32_t _id)
		{
			if (_id == 0x10DE)
				return "NVIDIA Corporation";
			else if (_id == 0x1002)
				return "Advanced Micro Devices, Inc.";
			else if (_id == 0x8086)
				return "Intel Corporation";

			return "Unknown_Vendor";
		}

	}
}