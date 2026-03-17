#pragma once
#include "./graphics/RHI/resource/texture/texture2D.h"
#include "./graphics/RHI_api/vk/RHI_VK_render_device.h"

namespace Raydiance
{
	namespace Graphics
	{
		class VKTexture2D final : public Texture2D
		{
		public:
			VKTexture2D(RHI_VK_RenderDevice* _renderDevice, const Texture2DDescriptor* _texture2DDescriptor);
			VKTexture2D(RHI_VK_RenderDevice& _renderDevice, VkImage _resource, const Texture2DDescriptor* _texture2DDescriptor);
			virtual ~VKTexture2D();

			inline VkImage GetVKTexture() const { return m_ImageObj; }
			inline VkImageView GetVKTextureView() const { return m_ImageViewObj; }

		private:
			friend class RHI_VK_Swapchain;
			void FreeImageView();

			uint32_t FindMemoryType(RHI_VK_RenderDevice* _renderDevice, uint32_t typeFilter, VkMemoryPropertyFlags properties);

			VkImage m_ImageObj;
			VkImageView m_ImageViewObj;
			VkDeviceMemory m_BufferMemory;
		};
	}
}