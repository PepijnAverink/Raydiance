#pragma once
#include "./core/container/types.h"

#include "./graphics/RHI/RHI_adapter_type.h"
#include "./graphics/RHI/RHI_adapter_features.h"

#include <string>

namespace Raydiance
{
	namespace Graphics
	{
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

		class RHI_Adapter
		{
		public:
			// Default constructor and descructor
			// ======================================
			         RHI_Adapter(void) = default;
			virtual ~RHI_Adapter(void) = default;

			// Inline internal getter functions
			// --------------------------------------
			inline std::string GetName()   const { return m_Name; }
			inline std::string GetVendor() const { return m_Vendor; }

			inline uint32 GetVRam() const { return m_VRam; }

			inline RHI_AdapterType GetType() const { return m_Type; }

			inline RHI_AdapterFeatures GetFeatures() const { return m_Features; }

		protected:
			std::string		m_Name;
			std::string		m_Vendor;
			uint32			m_VRam = 0;

			RHI_AdapterType m_Type = RHI_AdapterType::RHI_ADAPTER_TYPE_INVALID;

			RHI_AdapterFeatures m_Features;
		};
	}
}