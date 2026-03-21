#pragma once
#include "./graphics/RHI/resource/buffer/RHI_buffer.h"
#include "./graphics/RHI_api/vk/RHI_VK_render_device.h"

namespace Raydiance
{
	namespace Graphics
	{
		class RHI_VK_Buffer final : public RHI_Buffer
		{
		public:
			RHI_VK_Buffer(RHI_VK_RenderDevice* _renderDevice, const RHI_BufferDescriptor* _bufferDescriptor);
			virtual ~RHI_VK_Buffer();

			virtual void SetData(void* _data, const uint32_t _size) override;

			inline VkBuffer GetRHI_VK_Buffer() const { return m_BufferObj; }
			inline VkIndexType GetIndexFormat() const { return m_IndexFormat; }

		private:
			uint32_t FindMemoryType(RHI_VK_RenderDevice* _renderDevice, uint32_t typeFilter, VkMemoryPropertyFlags properties);

			VkBuffer       m_BufferObj;
			VkDeviceMemory m_BufferMemory;

			VkIndexType m_IndexFormat;
		};
	}
}