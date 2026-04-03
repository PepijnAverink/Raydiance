#include "./pch.h"
#include "./graphics/RHI_api/vk/RHI_VK_adapter.h"
#include "./graphics/RHI_api/vk/RHI_VK_adapter_type.h"

#include "./graphics/RHI_api/vk/RHI_VK_adapter_features.h"

namespace Raydiance
{
	namespace Graphics
	{
		RHI_VK_Adapter::RHI_VK_Adapter(VkPhysicalDevice _physicsalDevice)
			: m_PhysicalDevice(_physicsalDevice)
		{
			// Gather physical device properties
			VkPhysicalDeviceProperties properties;
			vkGetPhysicalDeviceProperties(m_PhysicalDevice, &properties);

			// Set internal properties based on adapter query
			// ----------------------------------------------
			m_Name   = properties.deviceName;
			m_Vendor = ResolvePCI_ID(properties.vendorID);
			m_Type   = ResolveVKAdapterType(properties.deviceType);

			// Determine the available device local memory.
			VkPhysicalDeviceMemoryProperties memProperties;
			vkGetPhysicalDeviceMemoryProperties(m_PhysicalDevice, &memProperties);

			auto heapsPointer = memProperties.memoryHeaps;
			auto heaps = std::vector<VkMemoryHeap>(heapsPointer, heapsPointer + memProperties.memoryHeapCount);

			for (const auto& heap : heaps)
			{
				if (heap.flags & VkMemoryHeapFlagBits::VK_MEMORY_HEAP_DEVICE_LOCAL_BIT)
				{
					// Device local heap, should be size of total GPU VRAM.
					//heap.size will be the size of VRAM in bytes. (bigger is better)
					m_VRam = ((uint32)heap.size > m_VRam) ? (uint32)heap.size : m_VRam;
				}
			}

			// Setup the features of the adapter
			// ----------------------------------------------
			m_Features = RHI_VK_AdapterFeatures(m_PhysicalDevice);


			VkImageFormatProperties2 props;
			props.sType = VK_STRUCTURE_TYPE_IMAGE_FORMAT_PROPERTIES_2;
			props.pNext = NULL;

			VkPhysicalDeviceImageFormatInfo2 formatInfo;
			formatInfo.sType = VK_STRUCTURE_TYPE_PHYSICAL_DEVICE_IMAGE_FORMAT_INFO_2;

			VkResult result = vkGetPhysicalDeviceImageFormatProperties2(
				m_PhysicalDevice,
				&formatInfo,
				&props
			);

			int z = 0;

		}

		RHI_VK_Adapter::~RHI_VK_Adapter()
		{ }
	}
}