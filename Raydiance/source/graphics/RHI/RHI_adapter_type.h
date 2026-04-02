#pragma once
#include "./core/container/types.h"
#include "./core/error/logger.h"

namespace Raydiance
{
	namespace Graphics
	{
		enum class RHI_AdapterType : uint8
		{
			RHI_ADAPTER_TYPE_INVALID    = 0x00,
			RHI_ADAPTER_TYPE_DISCRETE   = 0x01,
			RHI_ADAPTER_TYPE_INTEGRATED = 0x02,
		};

		inline std::string RHI_AdapterType_ToString(RHI_AdapterType _type)
		{
			switch (_type)
			{
				case RHI_AdapterType::RHI_ADAPTER_TYPE_INVALID:
					return "RHI_ADAPTER_TYPE_INVALID";
				case RHI_AdapterType::RHI_ADAPTER_TYPE_DISCRETE:
					return "RHI_ADAPTER_TYPE_DISCRETE";
				case RHI_AdapterType::RHI_ADAPTER_TYPE_INTEGRATED:
					return "RHI_ADAPTER_TYPE_INTEGRATED";
				default:
					return "RHI_ADAPTER_TYPE_INVALID: " + std::to_string((uint8)_type);
			}
		}

		inline bool RHI_AdapterType_IsValid(RHI_AdapterType _type)
		{
			switch (_type)
			{
				case RHI_AdapterType::RHI_ADAPTER_TYPE_DISCRETE:
				case RHI_AdapterType::RHI_ADAPTER_TYPE_INTEGRATED:
					return true;
			}

			return false;
		}
	}
}