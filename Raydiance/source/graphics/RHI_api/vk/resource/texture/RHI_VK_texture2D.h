#pragma once
#include "./graphics/RHI/resource/texture/RHI_texture2D.h"

#include <vulkan/vulkan.h>

namespace Raydiance
{
	namespace Graphics
	{
		class RHI_VK_RenderDevice;
		class RHI_VK_Texture2D final : public RHI_Texture2D
		{
		public:
			RHI_VK_Texture2D(void);
			virtual ~RHI_VK_Texture2D(void);

			const Result Initialize(RHI_VK_RenderDevice* _RHI_RenderDevice, const RHI_Texture2DDescriptor* _texture2DDescriptor);
			const Result Initialize(RHI_VK_RenderDevice* _RHI_RenderDevice, VkImage _resource, const RHI_Texture2DDescriptor* _texture2DDescriptor);

			// Getters
			inline virtual VkImage GetVKTexture() const { return m_ImageObj; }
			inline virtual VkImageView GetVKTextureView() const { return m_ImageViewObj; }

		private:
			uint32_t FindMemoryType(RHI_VK_RenderDevice* _RHI_RenderDevice, uint32_t typeFilter, VkMemoryPropertyFlags properties);

			VkImage		   m_ImageObj;
			VkImageView	   m_ImageViewObj;
			VkDeviceMemory m_BufferMemory;

			bool		   m_IsSwapchainImage = false;
		};
	}
}