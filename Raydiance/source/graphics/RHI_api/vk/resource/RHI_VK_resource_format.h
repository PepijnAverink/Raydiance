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
				case RHI_ResourceFormat::RHI_RESOURCE_FORMAT_INVALID:
					return VK_FORMAT_UNDEFINED;
				case RHI_ResourceFormat::RHI_RESOURCE_FORMAT_R8_UINT:
					return VK_FORMAT_R8_UINT;
				case RHI_ResourceFormat::RHI_RESOURCE_FORMAT_R8_SINT:
					return VK_FORMAT_R8_SINT;
				case RHI_ResourceFormat::RHI_RESOURCE_FORMAT_R8_UNORM:
					return VK_FORMAT_R8_UNORM;
				case RHI_ResourceFormat::RHI_RESOURCE_FORMAT_R8_SNORM:
					return VK_FORMAT_R8_SNORM;
				case RHI_ResourceFormat::RHI_RESOURCE_FORMAT_R8G8_UINT:
					return VK_FORMAT_R8G8_UINT;
				case RHI_ResourceFormat::RHI_RESOURCE_FORMAT_R8G8_SINT:
					return VK_FORMAT_R8G8_SINT;
				case RHI_ResourceFormat::RHI_RESOURCE_FORMAT_R8G8_UNORM:
					return VK_FORMAT_R8G8_UNORM;
				case RHI_ResourceFormat::RHI_RESOURCE_FORMAT_R8G8_SNORM:
					return VK_FORMAT_R8G8_SNORM;
				case RHI_ResourceFormat::RHI_RESOURCE_FORMAT_R8G8B8A8_UINT:
					return VK_FORMAT_R8G8B8A8_UINT;
				case RHI_ResourceFormat::RHI_RESOURCE_FORMAT_R8G8B8A8_SINT:
					return VK_FORMAT_R8G8B8A8_SINT;
				case RHI_ResourceFormat::RHI_RESOURCE_FORMAT_R8G8B8A8_UNORM:
					return VK_FORMAT_R8G8B8A8_UNORM;
				case RHI_ResourceFormat::RHI_RESOURCE_FORMAT_R8G8B8A8_SNORM:
					return VK_FORMAT_R8G8B8A8_SNORM;
				case RHI_ResourceFormat::RHI_RESOURCE_FORMAT_R8G8B8A8_UNORM_SRGB:
					return VK_FORMAT_R8G8B8A8_SRGB;
				case RHI_ResourceFormat::RHI_RESOURCE_FORMAT_B8G8R8A8_UNORM:
					return VK_FORMAT_B8G8R8A8_UNORM;
				case RHI_ResourceFormat::RHI_RESOURCE_FORMAT_B8G8R8A8_UNORM_SRGB:
					return VK_FORMAT_B8G8R8A8_SRGB;
				case RHI_ResourceFormat::RHI_RESOURCE_FORMAT_R16_UINT:
					return VK_FORMAT_R16_UINT;
				case RHI_ResourceFormat::RHI_RESOURCE_FORMAT_R16_SINT:
					return VK_FORMAT_R16_SINT;
				case RHI_ResourceFormat::RHI_RESOURCE_FORMAT_R16_UNORM:
					return VK_FORMAT_R16_UNORM;
				case RHI_ResourceFormat::RHI_RESOURCE_FORMAT_R16_SNORM:
					return VK_FORMAT_R16_SNORM;
				case RHI_ResourceFormat::RHI_RESOURCE_FORMAT_R16_FLOAT:
					return VK_FORMAT_R16_SFLOAT;
				case RHI_ResourceFormat::RHI_RESOURCE_FORMAT_R16G16_UINT:
					return VK_FORMAT_R16G16_UINT;
				case RHI_ResourceFormat::RHI_RESOURCE_FORMAT_R16G16_SINT:
					return VK_FORMAT_R16G16_SINT;
				case RHI_ResourceFormat::RHI_RESOURCE_FORMAT_R16G16_UNORM:
					return VK_FORMAT_R16G16_UNORM;
				case RHI_ResourceFormat::RHI_RESOURCE_FORMAT_R16G16_SNORM:
					return VK_FORMAT_R16G16_SNORM;
				case RHI_ResourceFormat::RHI_RESOURCE_FORMAT_R16G16_FLOAT:
					return VK_FORMAT_R16G16_SFLOAT;
				case RHI_ResourceFormat::RHI_RESOURCE_FORMAT_R16G16B16A16_UINT:
					return VK_FORMAT_R16G16B16A16_UINT;
				case RHI_ResourceFormat::RHI_RESOURCE_FORMAT_R16G16B16A16_SINT:
					return VK_FORMAT_R16G16B16A16_SINT;
				case RHI_ResourceFormat::RHI_RESOURCE_FORMAT_R16G16B16A16_UNORM:
					return VK_FORMAT_R16G16B16A16_UNORM;
				case RHI_ResourceFormat::RHI_RESOURCE_FORMAT_R16G16B16A16_SNORM:
					return VK_FORMAT_R16G16B16A16_SNORM;
				case RHI_ResourceFormat::RHI_RESOURCE_FORMAT_R16G16B16A16_FLOAT:
					return VK_FORMAT_R16G16B16A16_SFLOAT;
				case RHI_ResourceFormat::RHI_RESOURCE_FORMAT_R32_UINT:
					return VK_FORMAT_R32_UINT;
				case RHI_ResourceFormat::RHI_RESOURCE_FORMAT_R32_SINT:
					return VK_FORMAT_R32_SINT;
				case RHI_ResourceFormat::RHI_RESOURCE_FORMAT_R32_FLOAT:
					return VK_FORMAT_R32_SFLOAT;
				case RHI_ResourceFormat::RHI_RESOURCE_FORMAT_R32G32_UINT:
					return VK_FORMAT_R32G32_UINT;
				case RHI_ResourceFormat::RHI_RESOURCE_FORMAT_R32G32_SINT:
					return VK_FORMAT_R32G32_SINT;
				case RHI_ResourceFormat::RHI_RESOURCE_FORMAT_R32G32_FLOAT:
					return VK_FORMAT_R32G32_SFLOAT;
				case RHI_ResourceFormat::RHI_RESOURCE_FORMAT_R32G32B32_UINT:
					return VK_FORMAT_R32G32B32_UINT;
				case RHI_ResourceFormat::RHI_RESOURCE_FORMAT_R32G32B32_SINT:
					return VK_FORMAT_R32G32B32_SINT;
				case RHI_ResourceFormat::RHI_RESOURCE_FORMAT_R32G32B32_FLOAT:
					return VK_FORMAT_R32G32B32_SFLOAT;
				case RHI_ResourceFormat::RHI_RESOURCE_FORMAT_R32G32B32A32_UINT:
					return VK_FORMAT_R32G32B32A32_UINT;
				case RHI_ResourceFormat::RHI_RESOURCE_FORMAT_R32G32B32A32_SINT:
					return VK_FORMAT_R32G32B32A32_SINT;
				case RHI_ResourceFormat::RHI_RESOURCE_FORMAT_R32G32B32A32_FLOAT:
					return VK_FORMAT_R32G32B32A32_SFLOAT;
				case RHI_ResourceFormat::RHI_RESOURCE_FORMAT_D16_UNORM:
					return VK_FORMAT_D16_UNORM;
				case RHI_ResourceFormat::RHI_RESOURCE_FORMAT_D24_UNORM_S8_UINT:
					return VK_FORMAT_D24_UNORM_S8_UINT;
				case RHI_ResourceFormat::RHI_RESOURCE_FORMAT_D32_FLOAT:
					return VK_FORMAT_D32_SFLOAT;
				case RHI_ResourceFormat::RHI_RESOURCE_FORMAT_D32_FLOAT_S8_UINT:
					return VK_FORMAT_D32_SFLOAT_S8_UINT;
				case RHI_ResourceFormat::RHI_RESOURCE_FORMAT_B4G4R4A4_UNORM:
					return VK_FORMAT_B4G4R4A4_UNORM_PACK16;
				case RHI_ResourceFormat::RHI_RESOURCE_FORMAT_BC1_UNORM:
					return VK_FORMAT_BC1_RGBA_UNORM_BLOCK;
				case RHI_ResourceFormat::RHI_RESOURCE_FORMAT_BC1_UNORM_SRGB:
					return VK_FORMAT_BC1_RGBA_SRGB_BLOCK;
				case RHI_ResourceFormat::RHI_RESOURCE_FORMAT_BC2_UNORM:
					return VK_FORMAT_BC2_UNORM_BLOCK;
				case RHI_ResourceFormat::RHI_RESOURCE_FORMAT_BC2_UNORM_SRGB:
					return VK_FORMAT_BC2_SRGB_BLOCK;
				case RHI_ResourceFormat::RHI_RESOURCE_FORMAT_BC3_UNORM:
					return VK_FORMAT_BC3_UNORM_BLOCK;
				case RHI_ResourceFormat::RHI_RESOURCE_FORMAT_BC3_UNORM_SRGB:
					return VK_FORMAT_BC3_SRGB_BLOCK;
				case RHI_ResourceFormat::RHI_RESOURCE_FORMAT_BC4_UNORM:
					return VK_FORMAT_BC4_UNORM_BLOCK;
				case RHI_ResourceFormat::RHI_RESOURCE_FORMAT_BC4_SNORM:
					return VK_FORMAT_BC4_SNORM_BLOCK;
				case RHI_ResourceFormat::RHI_RESOURCE_FORMAT_BC5_UNORM:
					return VK_FORMAT_BC5_UNORM_BLOCK;
				case RHI_ResourceFormat::RHI_RESOURCE_FORMAT_BC5_SNORM:
					return VK_FORMAT_BC5_SNORM_BLOCK;
				case RHI_ResourceFormat::RHI_RESOURCE_FORMAT_BC6H_UFLOAT:
					return VK_FORMAT_BC6H_UFLOAT_BLOCK;
				case RHI_ResourceFormat::RHI_RESOURCE_FORMAT_BC6H_SFLOAT:
					return VK_FORMAT_BC6H_SFLOAT_BLOCK;
				case RHI_ResourceFormat::RHI_RESOURCE_FORMAT_BC7_UNORM:
					return VK_FORMAT_BC7_UNORM_BLOCK;
				case RHI_ResourceFormat::RHI_RESOURCE_FORMAT_BC7_UNORM_SRGB:
					return VK_FORMAT_BC7_SRGB_BLOCK;
				case RHI_ResourceFormat::RHI_RESOURCE_FORMAT_B5G6R5_UNORM:
					return VK_FORMAT_B5G6R5_UNORM_PACK16;
				case RHI_ResourceFormat::RHI_RESOURCE_FORMAT_B5G5R5A1_UNORM:
					return VK_FORMAT_B5G5R5A1_UNORM_PACK16;

				default :
					return VK_FORMAT_UNDEFINED;
			}
		}

		inline RHI_ResourceFormat ResolveResourceFormat(VkFormat _format)
		{
			switch (_format)
			{
				case VK_FORMAT_B8G8R8A8_UNORM:
					return RHI_ResourceFormat::RHI_RESOURCE_FORMAT_B8G8R8A8_UNORM;
				case VK_FORMAT_R32G32_SFLOAT:
					return RHI_ResourceFormat::RHI_RESOURCE_FORMAT_R32G32_FLOAT;
				case VK_FORMAT_R32G32B32_SFLOAT:
					return RHI_ResourceFormat::RHI_RESOURCE_FORMAT_R32G32B32_FLOAT;
				case VK_FORMAT_R8G8B8A8_UNORM:
					return RHI_ResourceFormat::RHI_RESOURCE_FORMAT_R8G8B8A8_UNORM;
			}

			return RHI_ResourceFormat::RHI_RESOURCE_FORMAT_INVALID;
		}

		inline VkIndexType ResolveVKIndexFormat(RHI_ResourceFormat _resourceFormat)
		{
			switch (_resourceFormat)
			{
				case RHI_ResourceFormat::RHI_RESOURCE_FORMAT_R16_UINT:
					return VK_INDEX_TYPE_UINT16;
				case RHI_ResourceFormat::RHI_RESOURCE_FORMAT_R32_UINT:
					return VK_INDEX_TYPE_UINT32;
			}

			return VK_INDEX_TYPE_UINT16;
		}
	}
}