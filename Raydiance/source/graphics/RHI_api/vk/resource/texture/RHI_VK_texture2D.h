#pragma once
#include "./graphics/RHI/resource/texture/RHI_texture2D.h"
#include "./graphics/RHI_api/vk/RHI_VK_render_device.h"

namespace Raydiance
{
	namespace Graphics
	{
		class RHI_VK_Texture2D final : public RHI_Texture2D
		{
		public:
			RHI_VK_Texture2D(RHI_VK_RenderDevice* _renderDevice, const RHI_Texture2DDescriptor* _texture2DDescriptor);
			RHI_VK_Texture2D(const RHI_VK_RenderDevice& _renderDevice, VkImage _resource, const RHI_Texture2DDescriptor* _texture2DDescriptor);
			virtual ~RHI_VK_Texture2D();

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