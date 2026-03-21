#pragma once
// Core includes
#include "./core/container/types.h"

// Graphics includes
#include "./graphics/RHI/RHI_adapter_type.h"
#include "./graphics/RHI/RHI_adapter_features.h"


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

			inline const std::string_view GetName() const { return m_Name; }
			inline const std::string_view GetVendor() const { return m_Vendor; }

			inline uint64 GetVRam() const { return m_VRam; }
			inline RHI_AdapterType GetType() const { return m_Type; }

			inline RHI_AdapterFeatures GetFeatures() const { return m_Features; }

		protected:
			// Raw stored data about the adapter
			std::string		m_Name;
			std::string		m_Vendor;
			uint64			m_VRam = 0;

			RHI_AdapterType m_Type = RHI_AdapterType::RHI_ADAPTER_TYPE_INTEGRATED;

			RHI_AdapterFeatures m_Features;
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