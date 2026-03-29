#pragma once
#include "./graphics/RHI/resource/RHI_resource_format.h"
#include <vulkan/vulkan.h>

namespace Raydiance
{
	namespace Graphics
	{
		inline VkFormat ResolveVKResourceFormat(RHI_ResourceFormat _resourceFormat)
		{
			switch (_resourceFormat)
			{
			case RHI_ResourceFormat::RHI_RESOURCE_FORMAT_B8G8R8A8_SRGB:
				return VK_FORMAT_B8G8R8A8_SRGB;
			case RHI_ResourceFormat::RHI_RESOURCE_FORMAT_R32G32_SFLOAT:
				return VK_FORMAT_R32G32_SFLOAT;
			case RHI_ResourceFormat::RHI_RESOURCE_FORMAT_R32G32B32_SFLOAT:
				return VK_FORMAT_R32G32B32_SFLOAT;
			case RHI_ResourceFormat::RHI_RESOURCE_FORMAT_R16_UINT:
				return VK_FORMAT_R16_UINT;
			case RHI_ResourceFormat::RHI_RESOURCE_FORMAT_B8G8R8A8_UNORM:
				return VK_FORMAT_B8G8R8A8_UNORM;
			}

			return VK_FORMAT_UNDEFINED;
		}

		inline VkIndexType ResolveVKIndexFormat(RHI_ResourceFormat _resourceFormat)
		{
			switch (_resourceFormat)
			{
			case RHI_ResourceFormat::RHI_RESOURCE_FORMAT_R16_UINT:
				return VK_INDEX_TYPE_UINT16;
			}

			return VK_INDEX_TYPE_UINT16;
		}

		inline RHI_ResourceFormat ResolveResourceFormat(VkFormat _format)
		{
			switch (_format)
			{
			case VK_FORMAT_B8G8R8A8_SRGB:
				return RHI_ResourceFormat::RHI_RESOURCE_FORMAT_B8G8R8A8_SRGB;
			case VK_FORMAT_R32G32_SFLOAT:
				return RHI_ResourceFormat::RHI_RESOURCE_FORMAT_R32G32_SFLOAT;
			case VK_FORMAT_R32G32B32_SFLOAT:
				return RHI_ResourceFormat::RHI_RESOURCE_FORMAT_R32G32B32_SFLOAT;
			}

			return RHI_ResourceFormat::RHI_RESOURCE_FORMAT_INVALID;
		}
	}
}