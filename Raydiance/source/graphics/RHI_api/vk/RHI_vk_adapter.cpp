#include "./pch.h"
#include "./graphics/RHI_api/vk/RHI_vk_adapter.h"

// Graphics includes
#include "./graphics/RHI_api/vk/RHI_VK_adapter_type.h"
#include "./graphics/RHI_api/vk/RHI_VK_adapter_features.h"


namespace Raydiance
{
	namespace Graphics
	{
		RHI_VK_Adapter::RHI_VK_Adapter(const VkPhysicalDevice& _physicalDevice)
			: m_PhysicalDevice(_physicalDevice)
		{
			// Gather physical device properties
			vkGetPhysicalDeviceProperties(m_PhysicalDevice, &m_Properties);

			// Set internal properties based on adapter query
			// ----------------------------------------------
			m_Name   = m_Properties.deviceName;
			m_Vendor = ResolvePCI_ID(m_Properties.vendorID);
			m_Type   = ResolveVKAdapterType(m_Properties.deviceType);

			// Determine the available device local memory.
			vkGetPhysicalDeviceMemoryProperties(m_PhysicalDevice, &m_MemoryProperties);

			// Loop over the memory heaps and find the one with the largest size that is device local memory.
			for (uint32 i = 0; i < m_MemoryProperties.memoryHeapCount; ++i)
			{
				const auto& heap = m_MemoryProperties.memoryHeaps[i];

				// Store the size of the largest device local memory heap.
				if (heap.flags & VK_MEMORY_HEAP_DEVICE_LOCAL_BIT)
					m_VRam = std::max<uint64>(m_VRam, heap.size);
			}


			// Define new features
			m_Features = RHI_VK_AdapterFeatures(m_PhysicalDevice);
		}

		RHI_VK_Adapter::~RHI_VK_Adapter(void)
		{ }
	}
}