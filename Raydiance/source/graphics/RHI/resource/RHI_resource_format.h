#pragma once
#include "./core/error/logger.h"

namespace Raydiance
{
	namespace Graphics
	{
		enum RHI_ResourceFormat
		{
			RHI_RESOURCE_FORMAT_INVALID				= 0x00,
			RHI_RESOURCE_FORMAT_B8G8R8A8_SRGB		= 0x01,
			RHI_RESOURCE_FORMAT_R32G32_SFLOAT		= 0x02,
			RHI_RESOURCE_FORMAT_R32G32B32_SFLOAT	= 0x03,
			RHI_RESOURCE_FORMAT_R16_UINT			= 0x04,
			RHI_RESOURCE_FORMAT_CUSTOM				= 0x05,
		};

		inline uint32_t GetFormatSize(RHI_ResourceFormat _resourceFormat)
		{
			switch (_resourceFormat)
			{
				case RHI_RESOURCE_FORMAT_B8G8R8A8_SRGB:
					return sizeof(uint8_t) * 4;
				case RHI_RESOURCE_FORMAT_R32G32_SFLOAT:
					return sizeof(float) * 2;
				case RHI_RESOURCE_FORMAT_R32G32B32_SFLOAT:
					return sizeof(float) * 3;
				case RHI_RESOURCE_FORMAT_R16_UINT:
					return sizeof(uint16_t) * 1;
			}

			Logger::Log("No correct size was found for ResourceFormat:" + _resourceFormat, LogType::LOG_TYPE_ERROR);
			return 0;
		}
	}
}