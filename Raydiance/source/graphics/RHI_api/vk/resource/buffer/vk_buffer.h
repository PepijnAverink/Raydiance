#pragma once
#include "./graphics/RHI/resource/buffer/buffer.h"
#include "./graphics/RHI_api/vk/RHI_VK_render_device.h"

namespace Raydiance
{
	namespace Graphics
	{
		class VKBuffer final : public Buffer
		{
		public:
			VKBuffer(RHI_VK_RenderDevice* _renderDevice, const BufferDescriptor* _bufferDescriptor);
			virtual ~VKBuffer();

			virtual void SetData(void* _data, const uint32_t _size) override;

			inline VkBuffer GetVKBuffer() const { return m_BufferObj; }
			inline VkIndexType GetIndexFormat() const { return m_IndexFormat; }

		private:
			uint32_t FindMemoryType(RHI_VK_RenderDevice* _renderDevice, uint32_t typeFilter, VkMemoryPropertyFlags properties);

			VkBuffer       m_BufferObj;
			VkDeviceMemory m_BufferMemory;

			VkIndexType m_IndexFormat;
		};
	}
}