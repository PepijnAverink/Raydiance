#include "./pch.h"
#include "./graphics/RHI_api/vk/RHI_VK_adapter_features.h"

#include <vector>
#include <string>
#include <set>

namespace Raydiance
{
	namespace Graphics
	{
		static std::vector<const char*> RaytracingExtensions =
		{
			VK_KHR_MAINTENANCE1_EXTENSION_NAME,
			VK_KHR_BUFFER_DEVICE_ADDRESS_EXTENSION_NAME,
			VK_KHR_ACCELERATION_STRUCTURE_EXTENSION_NAME,
			VK_KHR_RAY_TRACING_PIPELINE_EXTENSION_NAME,
			VK_KHR_DEFERRED_HOST_OPERATIONS_EXTENSION_NAME,
			VK_KHR_PIPELINE_LIBRARY_EXTENSION_NAME,
			VK_KHR_SPIRV_1_4_EXTENSION_NAME,
		};

		RHI_VK_AdapterFeatures::RHI_VK_AdapterFeatures(VkPhysicalDevice _physicalDevice)
		{
			// Get the properties of the physical device
			//  Nesseccary to check feature support
			VkPhysicalDeviceProperties properties;
			vkGetPhysicalDeviceProperties(_physicalDevice, &properties);

			// Get total extension count
			uint32_t extensionCount;
			vkEnumerateDeviceExtensionProperties(_physicalDevice, nullptr, &extensionCount, nullptr);

			// Allocate vector of extensions available on this adapter
			std::vector<VkExtensionProperties> availableExtensions(extensionCount);
			vkEnumerateDeviceExtensionProperties(_physicalDevice, nullptr, &extensionCount, availableExtensions.data());

			// Check if raytracing features is supported on this adapter
			// ----------------------------------------------------------
			{
				// Set of all the required vulkan extensions for raytracing
				std::set<std::string> rayTraceExtensionsSet(RaytracingExtensions.begin(), RaytracingExtensions.end());

				// Remove extensions if found
				for (const auto& extension : availableExtensions) {
					rayTraceExtensionsSet.erase(extension.extensionName);
				}

				// Only if all the required extensions are supproted, we can support the full RT-package
				// --------------------------------------------------------------------------------------
				m_SupportRayTracing = rayTraceExtensionsSet.empty();
			}
		}

		RHI_VK_AdapterFeatures::~RHI_VK_AdapterFeatures(void)
		{ }
	}
}