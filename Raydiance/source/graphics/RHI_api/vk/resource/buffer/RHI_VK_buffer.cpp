#include "./pch.h"
#include "./graphics/RHI_api/vk/resource/buffer/RHI_VK_buffer.h"
#include "./graphics/RHI_api/vk/resource/RHI_VK_resource_format.h"
#include "./graphics/RHI_api/vk/resource/RHI_VK_resource_memory_type.h"
#include "./graphics/RHI_api/vk/resource/RHI_VK_resource_state.h"
#include "./graphics/RHI_api/vk/RHI_vk_render_device.h"
#include "./graphics/RHI_api/vk/RHI_vk_adapter.h"


namespace Raydiance
{
	namespace Graphics
	{
		// ✅ Define the static member (THIS FIXES THE LNK2001)
		//PFN_vkSetDebugUtilsObjectNameEXT RHI_VK_RenderDevice::vkSetDebugUtilsObjectNameEXT = nullptr;

		RHI_VK_Buffer::RHI_VK_Buffer()
			: RHI_Buffer()
		{ }

		RHI_VK_Buffer::~RHI_VK_Buffer()
		{
			vkDestroyBuffer(((RHI_VK_RenderDevice*)RHI_RenderDevice::Get())->GetVKDevice(), m_BufferObj, nullptr);
			vkFreeMemory(((RHI_VK_RenderDevice*)RHI_RenderDevice::Get())->GetVKDevice(), m_BufferMemory, nullptr);
		}

		const Result RHI_VK_Buffer::Initialize(RHI_VK_RenderDevice* _RHI_RenderDevice, const RHI_BufferDescriptor* _bufferDescriptor)
		{
			Result result = RHI_Buffer::Initialize(_bufferDescriptor);
			if (CheckError(result) == true)
			{
				// Log error
				return result;
			}

			VkDeviceSize bufferSize = _bufferDescriptor->Size;

			VkBufferCreateInfo bufferInfo{};
			bufferInfo.sType       = VK_STRUCTURE_TYPE_BUFFER_CREATE_INFO;
			bufferInfo.size        = _bufferDescriptor->Size;
			bufferInfo.usage       = ResolveVKBufferStateFlags(_bufferDescriptor->State);
			bufferInfo.sharingMode = VK_SHARING_MODE_EXCLUSIVE;

			if (vkCreateBuffer(_RHI_RenderDevice->GetVKDevice(), &bufferInfo, nullptr, &m_BufferObj) != VK_SUCCESS)
				Logger::Log("VK_ERROR - Failed to create 'VKBuffer' object.", LogLevel::LOG_LEVEL_ERROR);

			VkMemoryRequirements memRequirements;
			vkGetBufferMemoryRequirements(_RHI_RenderDevice->GetVKDevice(), m_BufferObj, &memRequirements);

			VkMemoryAllocateFlagsInfo flags{};
			flags.sType = VK_STRUCTURE_TYPE_MEMORY_ALLOCATE_FLAGS_INFO;
			//flags.flags = VK_MEMORY_ALLOCATE_DEVICE_ADDRESS_BIT_KHR;

			VkMemoryAllocateInfo allocInfo{};
			allocInfo.pNext = &flags;
			allocInfo.sType = VK_STRUCTURE_TYPE_MEMORY_ALLOCATE_INFO;
			allocInfo.allocationSize = memRequirements.size;
			allocInfo.memoryTypeIndex = FindMemoryType(_RHI_RenderDevice, memRequirements.memoryTypeBits, ResoleVKBufferUsage(_bufferDescriptor->MemoryType));

			if (vkAllocateMemory(_RHI_RenderDevice->GetVKDevice(), &allocInfo, nullptr, &m_BufferMemory) != VK_SUCCESS)
				Logger::Log("VK_ERROR - Failed to create 'VKBuffer' object.", LogLevel::LOG_LEVEL_ERROR);

			vkBindBufferMemory(_RHI_RenderDevice->GetVKDevice(), m_BufferObj, m_BufferMemory, 0);

			VkBufferDeviceAddressInfo addressInfo{};
			addressInfo.sType = VK_STRUCTURE_TYPE_BUFFER_DEVICE_ADDRESS_INFO;
			addressInfo.buffer = m_BufferObj;

			//m_BufferAddress = _RHI_RenderDevice->pfnGetBufferDeviceAddressKHR(_RHI_RenderDevice->GetVKDevice(), &addressInfo);

			// Set the indexBufferFormat
			if (m_Layout.GetElements().size() > 0)
				m_IndexFormat = ResolveVKIndexFormat(m_Layout.GetElements()[0].Type);

			// Set the data
			if (_bufferDescriptor->Data != nullptr)
				SetData(_bufferDescriptor->Data, 0, m_Size);


			VkDebugUtilsObjectNameInfoEXT nameInfo{};
			nameInfo.sType	      = VK_STRUCTURE_TYPE_DEBUG_UTILS_OBJECT_NAME_INFO_EXT;
			nameInfo.objectType   = VK_OBJECT_TYPE_BUFFER;
			nameInfo.objectHandle = (uint64)m_BufferObj;
			nameInfo.pObjectName  = _bufferDescriptor->Name.c_str();
		
			RHI_VK_RenderDevice::vkSetDebugUtilsObjectNameEXT(_RHI_RenderDevice->GetVKDevice(), &nameInfo);

			return Result::RESULT_GOOD;
		}

		void RHI_VK_Buffer::SetData(void* _data, uint32_t _offset, uint32_t _size)
		{
			// Error check
			if (m_MemoryType == RHI_ResourceMemoryType::RHI_RESOURCE_MEMORY_TYPE_GPU)
			{
				Logger::Log("Cannot use SetData() on VKBuffer, BufferUsage is BUFFER_USAGE_STATIC.", LogLevel::LOG_LEVEL_ERROR);
				return;
			}

			void* data;
			vkMapMemory(((RHI_VK_RenderDevice*)RHI_RenderDevice::Get())->GetVKDevice(), m_BufferMemory, 0, m_Size, 0, &data);
			memcpy((char*)data + _offset, _data, (size_t)_size);
			vkUnmapMemory(((RHI_VK_RenderDevice*)RHI_RenderDevice::Get())->GetVKDevice(), m_BufferMemory);
		}

		void RHI_VK_Buffer::GetData(void* _data, uint32_t _offset, uint32_t _size)
		{
			// Error check
			if (m_MemoryType == RHI_ResourceMemoryType::RHI_RESOURCE_MEMORY_TYPE_GPU)
			{
				Logger::Log("Cannot use SetData() on VKBuffer, BufferUsage is BUFFER_USAGE_STATIC.", LogLevel::LOG_LEVEL_ERROR);
				return;
			}

			void* data;
			vkMapMemory(((RHI_VK_RenderDevice*)RHI_RenderDevice::Get())->GetVKDevice(), m_BufferMemory, 0, m_Size, 0, &data);
			memcpy(_data, (char*)data + _offset, (size_t)_size);
			vkUnmapMemory(((RHI_VK_RenderDevice*)RHI_RenderDevice::Get())->GetVKDevice(), m_BufferMemory);
		}

		void* RHI_VK_Buffer::Map()
		{
			void* data;
			vkMapMemory(((RHI_VK_RenderDevice*)RHI_RenderDevice::Get())->GetVKDevice(), m_BufferMemory, 0, m_Size, 0, &data);
			return data;
		}

		void RHI_VK_Buffer::UnMap()
		{
			vkUnmapMemory(((RHI_VK_RenderDevice*)RHI_RenderDevice::Get())->GetVKDevice(), m_BufferMemory);
		}

		uint32_t RHI_VK_Buffer::FindMemoryType(RHI_VK_RenderDevice* _RHI_RenderDevice, uint32_t typeFilter, VkMemoryPropertyFlags properties)
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