#pragma once
#include "./graphics/RHI/resource/buffer/RHI_buffer.h"

#include <vulkan/vulkan.h>

namespace Raydiance
{
	namespace Graphics
	{
		class RHI_VK_RenderDevice;
		class RHI_VK_Buffer final : public RHI_Buffer
		{
		public:
			RHI_VK_Buffer();
			virtual ~RHI_VK_Buffer();

			const Result Initialize(RHI_VK_RenderDevice* _RHI_RenderDevice, const RHI_BufferDescriptor* _bufferDescriptor);

			virtual void SetData(void* _data, uint32_t _offset, uint32_t _size) override;
			virtual void GetData(void* _data, uint32_t _offset, uint32_t _size) override;

			virtual void* Map() override;
			virtual void UnMap() override;

			// Getters
			inline VkBuffer GetVKBuffer() const { return m_BufferObj; }
			inline VkIndexType GetVKIndexFormat() const { return m_IndexFormat; }
			inline VkDeviceAddress GetVKBufferAddress() const { return m_BufferAddress; }

		private:
			uint32_t FindMemoryType(RHI_VK_RenderDevice* _RHI_RenderDevice, uint32_t typeFilter, VkMemoryPropertyFlags properties);

			VkBuffer        m_BufferObj;
			VkDeviceMemory  m_BufferMemory;
			VkDeviceAddress m_BufferAddress;

			VkIndexType m_IndexFormat;

		};
	}
}