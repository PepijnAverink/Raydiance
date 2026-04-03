#include "./pch.h"
#include "./graphics/RHI_api/vk/resource/texture/RHI_VK_texture2D.h"
#include "./graphics/RHI_api/vk/RHI_VK_render_device.h"
#include "./graphics/RHI_api/vk/RHI_VK_adapter.h"
#include "./graphics/RHI_api/vk/resource/RHI_VK_resource_format.h"

#include "./core/error/logger.h"

namespace Raydiance
{
	namespace Graphics
	{
		RHI_VK_Texture2D::RHI_VK_Texture2D()
			: RHI_Texture2D()
		{ }

		RHI_VK_Texture2D::~RHI_VK_Texture2D(void)
		{
			if (m_IsSwapchainImage == false)
				vkDestroyImage(((RHI_VK_RenderDevice*)RHI_RenderDevice::Get())->GetVKDevice(), m_ImageObj, nullptr);

			vkFreeMemory(((RHI_VK_RenderDevice*)RHI_RenderDevice::Get())->GetVKDevice(), m_BufferMemory, nullptr);
			vkDestroyImageView(((RHI_VK_RenderDevice*)RHI_RenderDevice::Get())->GetVKDevice(), m_ImageViewObj, nullptr);
		}

		const Result RHI_VK_Texture2D::Initialize(RHI_VK_RenderDevice* _RHI_RenderDevice, const RHI_Texture2DDescriptor* _texture2DDescriptor)
		{
			Result result = RHI_Texture2D::Initialize(_texture2DDescriptor);
			if (CheckError(result) == true)
			{
				// Log error
				return result;
			}

			// TODO:: Make a resolve function for this
			VkImageUsageFlags use = VK_IMAGE_USAGE_COLOR_ATTACHMENT_BIT;
			if (_texture2DDescriptor->UsageFlags == RHI_TextureUsageFlags::RHI_TEXTURE_USAGE_FLAGS_DEPTH_ACCESS)
			{
				use = VK_IMAGE_USAGE_TRANSFER_DST_BIT | VK_IMAGE_USAGE_SAMPLED_BIT | VK_IMAGE_USAGE_STORAGE_BIT | VK_IMAGE_USAGE_DEPTH_STENCIL_ATTACHMENT_BIT;
			}
			else if (_texture2DDescriptor->UsageFlags == RHI_TextureUsageFlags::RHI_TEXTURE_USAGE_FLAGS_RENDER_ACCESS)
			{
				use = VK_IMAGE_USAGE_TRANSFER_DST_BIT | VK_IMAGE_USAGE_SAMPLED_BIT | VK_IMAGE_USAGE_STORAGE_BIT | VK_IMAGE_USAGE_COLOR_ATTACHMENT_BIT;
			}
			else
			{
				use = VK_IMAGE_USAGE_TRANSFER_DST_BIT | VK_IMAGE_USAGE_SAMPLED_BIT | VK_IMAGE_USAGE_STORAGE_BIT;
			}

			VkImageCreateInfo imageInfo{};
			imageInfo.sType = VK_STRUCTURE_TYPE_IMAGE_CREATE_INFO;
			imageInfo.imageType = VK_IMAGE_TYPE_2D;
			imageInfo.extent.width = static_cast<uint32_t>(_texture2DDescriptor->Width);
			imageInfo.extent.height = static_cast<uint32_t>(_texture2DDescriptor->Height);
			imageInfo.extent.depth = 1;
			imageInfo.mipLevels = 1;
			imageInfo.arrayLayers = 1;
			imageInfo.format = ResolveVKResourceFormat(_texture2DDescriptor->Format);
			imageInfo.tiling = VK_IMAGE_TILING_OPTIMAL;
			imageInfo.initialLayout = VK_IMAGE_LAYOUT_UNDEFINED;
			imageInfo.usage = use;
			imageInfo.sharingMode = VK_SHARING_MODE_EXCLUSIVE;
			imageInfo.samples = VK_SAMPLE_COUNT_1_BIT;
			imageInfo.flags = 0; // Optional

			if (vkCreateImage(_RHI_RenderDevice->GetVKDevice(), &imageInfo, nullptr, &m_ImageObj) != VK_SUCCESS)
			{
				Logger::Log("VK_ERROR - Failed to create 'VKTexture2D' object.", LogLevel::LOG_LEVEL_ERROR);
				return Result::RESULT_ERROR;
			}

			VkMemoryRequirements memRequirements;
			vkGetImageMemoryRequirements(_RHI_RenderDevice->GetVKDevice(), m_ImageObj, &memRequirements);

			VkMemoryAllocateInfo allocInfo{};
			allocInfo.sType = VK_STRUCTURE_TYPE_MEMORY_ALLOCATE_INFO;
			allocInfo.allocationSize = memRequirements.size;
			allocInfo.memoryTypeIndex = FindMemoryType(_RHI_RenderDevice, memRequirements.memoryTypeBits, VK_MEMORY_PROPERTY_DEVICE_LOCAL_BIT);

			if (vkAllocateMemory(_RHI_RenderDevice->GetVKDevice(), &allocInfo, nullptr, &m_BufferMemory) != VK_SUCCESS) {
				Logger::Log("VK_ERROR - Failed to create 'VKTexture2D' object.", LogLevel::LOG_LEVEL_ERROR);
				return Result::RESULT_ERROR;
			}

			vkBindImageMemory(_RHI_RenderDevice->GetVKDevice(), m_ImageObj, m_BufferMemory, 0);

			VkImageViewCreateInfo createInfo{};
			createInfo.sType						   = VK_STRUCTURE_TYPE_IMAGE_VIEW_CREATE_INFO;
			createInfo.image						   = m_ImageObj;
			createInfo.viewType						   = VK_IMAGE_VIEW_TYPE_2D;
			createInfo.format						   = ResolveVKResourceFormat(m_Format);
			createInfo.subresourceRange.aspectMask     = ((uint8)_texture2DDescriptor->UsageFlags & (uint8)RHI_TextureUsageFlags::RHI_TEXTURE_USAGE_FLAGS_DEPTH_ACCESS) ? VK_IMAGE_ASPECT_DEPTH_BIT : VK_IMAGE_ASPECT_COLOR_BIT;
			createInfo.subresourceRange.baseMipLevel   = 0;
			createInfo.subresourceRange.levelCount     = 1;
			createInfo.subresourceRange.baseArrayLayer = 0;
			createInfo.subresourceRange.layerCount	   = 1;

			if (vkCreateImageView(_RHI_RenderDevice->GetVKDevice(), &createInfo, nullptr, &m_ImageViewObj) != VK_SUCCESS)
			{
				Logger::Log("VK_ERROR - Failed to create 'ImageView' object.", LogLevel::LOG_LEVEL_ERROR);
				return Result::RESULT_ERROR;
			}

			VkDebugUtilsObjectNameInfoEXT nameInfo{};
			nameInfo.sType = VK_STRUCTURE_TYPE_DEBUG_UTILS_OBJECT_NAME_INFO_EXT;
			nameInfo.objectType = VK_OBJECT_TYPE_IMAGE;
			nameInfo.objectHandle = (uint64)m_ImageObj;
			nameInfo.pObjectName = _texture2DDescriptor->Name.c_str();

			RHI_VK_RenderDevice::vkSetDebugUtilsObjectNameEXT(_RHI_RenderDevice->GetVKDevice(), &nameInfo);

			return Result::RESULT_GOOD;
		}

		const Result RHI_VK_Texture2D::Initialize(RHI_VK_RenderDevice* _RHI_RenderDevice, VkImage _resource, const RHI_Texture2DDescriptor* _texture2DDescriptor)
		{
			m_ImageObj = _resource;

			Result result = RHI_Texture2D::Initialize(_texture2DDescriptor);
			if (CheckError(result) == true)
			{
				// Log error
				return result;
			}

			m_IsSwapchainImage = true;

			VkImageViewCreateInfo createInfo{};
			createInfo.sType = VK_STRUCTURE_TYPE_IMAGE_VIEW_CREATE_INFO;
			createInfo.image = m_ImageObj;
			createInfo.viewType = VK_IMAGE_VIEW_TYPE_2D;
			createInfo.format = ResolveVKResourceFormat(m_Format);
			createInfo.components.r = VK_COMPONENT_SWIZZLE_IDENTITY;
			createInfo.components.g = VK_COMPONENT_SWIZZLE_IDENTITY;
			createInfo.components.b = VK_COMPONENT_SWIZZLE_IDENTITY;
			createInfo.components.a = VK_COMPONENT_SWIZZLE_IDENTITY;
			createInfo.subresourceRange.aspectMask = VK_IMAGE_ASPECT_COLOR_BIT;
			createInfo.subresourceRange.baseMipLevel = 0;
			createInfo.subresourceRange.levelCount = 1;
			createInfo.subresourceRange.baseArrayLayer = 0;
			createInfo.subresourceRange.layerCount = 1;

			if (vkCreateImageView(_RHI_RenderDevice->GetVKDevice(), &createInfo, nullptr, &m_ImageViewObj) != VK_SUCCESS)
			{
				Logger::Log("VK_ERROR - Failed to create 'ImageView' object.", LogLevel::LOG_LEVEL_ERROR);
				return Result::RESULT_ERROR;
			}


			VkDebugUtilsObjectNameInfoEXT nameInfo{};
			nameInfo.sType = VK_STRUCTURE_TYPE_DEBUG_UTILS_OBJECT_NAME_INFO_EXT;
			nameInfo.objectType = VK_OBJECT_TYPE_IMAGE;
			nameInfo.objectHandle = (uint64)m_ImageObj;
			nameInfo.pObjectName = _texture2DDescriptor->Name.c_str();

			RHI_VK_RenderDevice::vkSetDebugUtilsObjectNameEXT(_RHI_RenderDevice->GetVKDevice(), &nameInfo);

			return Result::RESULT_GOOD;
		}

		uint32_t RHI_VK_Texture2D::FindMemoryType(RHI_VK_RenderDevice* _RHI_RenderDevice, uint32_t typeFilter, VkMemoryPropertyFlags properties)
		{
			VkPhysicalDeviceMemoryProperties memProperties;
			vkGetPhysicalDeviceMemoryProperties(((RHI_VK_Adapter*)_RHI_RenderDevice->RHI_GetAdapter())->GetPhysicalDevice(), &memProperties);

			for (uint32_t i = 0; i < memProperties.memoryTypeCount; i++) {
				if ((typeFilter & (1 << i)) && (memProperties.memoryTypes[i].propertyFlags & properties) == properties) {
					return i;
				}
			}

			Logger::Log("VK_ERROR - Failed to find suitable memory type.", LogLevel::LOG_LEVEL_ERROR);
			return 0;
		}
	}
}