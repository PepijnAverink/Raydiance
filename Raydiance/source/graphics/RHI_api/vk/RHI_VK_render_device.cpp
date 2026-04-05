#include "./pch.h"
#include "./graphics/RHI_api/vk/RHI_VK_render_device.h"

#include "./graphics/RHI_api/vk/RHI_VK_adapter.h"
#include "./core/error/logger.h"

#include <iostream>

#include "./graphics/RHI_api/vk/object/command/RHI_VK_command_queue.h"
#include "./graphics/RHI_api/vk/object/command/RHI_VK_command_buffer.h"
#include "./graphics/RHI_api/vk/object/command/RHI_VK_command_pool.h"

#include "./graphics/RHI_api/vk/object/swapchain/RHI_VK_swapchain.h"
#include "./graphics/RHI_api/vk/object/sync/RHI_VK_fenceCPU.h"

#include "./graphics/RHI_api/vk/resource/texture/RHI_VK_texture2D.h"
#include "./graphics/RHI_api/vk/resource/shader/RHI_VK_shader.h"
#include "./graphics/RHI_api/vk/resource/buffer/RHI_VK_buffer.h"
#include "./graphics/RHI_api/vk/resource/sampler/RHI_VK_sampler.h"

#include "./graphics/RHI_api/vk/pipeline/graphics/renderpass/RHI_VK_render_pass.h"
#include "./graphics/RHI_api/vk/pipeline/graphics/framebuffer/RHI_VK_frame_buffer.h"

#include "./graphics/RHI_api/vk/pipeline/layout/descriptor/RHI_VK_descriptor_pool.h"
#include "./graphics/RHI_api/vk/pipeline/layout/RHI_VK_input_layout.h"
#include "./graphics/RHI_api/vk/pipeline/graphics/RHI_VK_graphics_pipeline.h"
#include "./graphics/RHI_api/vk/pipeline/compute/RHI_VK_compute_pipeline.h"

#include "./graphics/RHI_api/vk/resource/RHI_VK_resource_format.h"

// String defs for the validation layer callback
#define STRING_RESET   "\033[0m"
#define STRING_INFO    "\033[37m"
#define STRING_WARNING "\033[33m"
#define STRING_ERROR   "\033[36m"

namespace Raydiance
{
	namespace Graphics
	{
		PFN_vkSetDebugUtilsObjectNameEXT    Raydiance::Graphics::RHI_VK_RenderDevice::vkSetDebugUtilsObjectNameEXT    = nullptr;
		PFN_vkQueueBeginDebugUtilsLabelEXT  Raydiance::Graphics::RHI_VK_RenderDevice::vkQueueBeginDebugUtilsLabelEXT  = nullptr;
		PFN_vkQueueEndDebugUtilsLabelEXT    Raydiance::Graphics::RHI_VK_RenderDevice::vkQueueEndDebugUtilsLabelEXT    = nullptr;
		PFN_vkQueueInsertDebugUtilsLabelEXT Raydiance::Graphics::RHI_VK_RenderDevice::vkQueueInsertDebugUtilsLabelEXT = nullptr;
		PFN_vkCmdBeginDebugUtilsLabelEXT    Raydiance::Graphics::RHI_VK_RenderDevice::vkCmdBeginDebugUtilsLabelEXT    = nullptr;
		PFN_vkCmdEndDebugUtilsLabelEXT      Raydiance::Graphics::RHI_VK_RenderDevice::vkCmdEndDebugUtilsLabelEXT      = nullptr;
		PFN_vkCmdInsertDebugUtilsLabelEXT   Raydiance::Graphics::RHI_VK_RenderDevice::vkCmdInsertDebugUtilsLabelEXT   = nullptr;

		PFN_vkGetBufferDeviceAddressKHR				Raydiance::Graphics::RHI_VK_RenderDevice::vkGetBufferDeviceAddressKHR = nullptr;
		PFN_vkGetAccelerationStructureBuildSizesKHR Raydiance::Graphics::RHI_VK_RenderDevice::vkGetAccelerationStructureBuildSizesKHR = nullptr;

		PFN_vkCreateAccelerationStructureKHR		Raydiance::Graphics::RHI_VK_RenderDevice::vkCreateAccelerationStructureKHR = nullptr;
		PFN_vkDestroyAccelerationStructureKHR		Raydiance::Graphics::RHI_VK_RenderDevice::vkDestroyAccelerationStructureKHR = nullptr;
		PFN_vkCmdBuildAccelerationStructuresKHR		Raydiance::Graphics::RHI_VK_RenderDevice::vkCmdBuildAccelerationStructuresKHR = nullptr;
		PFN_vkGetAccelerationStructureDeviceAddressKHR   Raydiance::Graphics::RHI_VK_RenderDevice::vkGetAccelerationStructureDeviceAddressKHR = nullptr;
		PFN_vkCreateRayTracingPipelinesKHR			Raydiance::Graphics::RHI_VK_RenderDevice::vkCreateRayTracingPipelinesKHR = nullptr;
		PFN_vkGetRayTracingShaderGroupHandlesKHR	Raydiance::Graphics::RHI_VK_RenderDevice::vkGetRayTracingShaderGroupHandlesKHR = nullptr;
		PFN_vkCmdTraceRaysKHR						Raydiance::Graphics::RHI_VK_RenderDevice::vkCmdTraceRaysKHR = nullptr;

		VkResult CreateDebugUtilsMessengerEXT(VkInstance instance, const VkDebugUtilsMessengerCreateInfoEXT* pCreateInfo, const VkAllocationCallbacks* pAllocator, VkDebugUtilsMessengerEXT* pDebugMessenger) {
			auto func = (PFN_vkCreateDebugUtilsMessengerEXT)vkGetInstanceProcAddr(instance, "vkCreateDebugUtilsMessengerEXT");
			if (func != nullptr)
				return func(instance, pCreateInfo, pAllocator, pDebugMessenger);
			else
				return VK_ERROR_EXTENSION_NOT_PRESENT;
		}

		void DestroyDebugUtilsMessengerEXT(VkInstance instance, VkDebugUtilsMessengerEXT debugMessenger, const VkAllocationCallbacks* pAllocator) {
			auto func = (PFN_vkDestroyDebugUtilsMessengerEXT)vkGetInstanceProcAddr(instance, "vkDestroyDebugUtilsMessengerEXT");
			if (func != nullptr)
				func(instance, debugMessenger, pAllocator);
		}

		RHI_VK_RenderDevice::RHI_VK_RenderDevice()
		{
			// Set the vulkan graphics API
			m_API = RHI_GraphicsAPI::RHI_GRAPHICS_API_VULKAN;
		}

		RHI_VK_RenderDevice::~RHI_VK_RenderDevice()
		{ 
			// Destroy the surface
			vkDestroySurfaceKHR(((RHI_VK_RenderDevice*)RHI_RenderDevice::Get())->GetVKInstance(), m_Surface, nullptr);

			if (m_Device != VK_NULL_HANDLE)
				vkDestroyDevice(m_Device, nullptr);

			// Only if the DebugMessenger was created destroy the instance
			if (Is_DebugModeEnabled() == true)
				DestroyDebugUtilsMessengerEXT(m_Instance, m_DebugMessenger, nullptr);

			vkDestroyInstance(m_Instance, nullptr);
		}

		// Header or cpp (anonymous namespace if in cpp)
		constexpr const char* validationLayers[] = {
			"VK_LAYER_KHRONOS_validation"
		};

		constexpr const char* deviceExtensions[] = {
			VK_KHR_SWAPCHAIN_EXTENSION_NAME
		};

		// Debug callback function for the Vulkan validation layer
		// --------------------------------------------------------------------------
		static VKAPI_ATTR VkBool32 VKAPI_CALL DebugCallback(VkDebugUtilsMessageSeverityFlagBitsEXT messageSeverity, VkDebugUtilsMessageTypeFlagsEXT messageTypes, const VkDebugUtilsMessengerCallbackDataEXT* pCallbackData, void* pUserData)
		{
			// Retreive the message from the callback
			std::string message = pCallbackData->pMessage;

			// INFO
			// --------------------------------------------------------------------------
			if (messageSeverity & VK_DEBUG_UTILS_MESSAGE_SEVERITY_INFO_BIT_EXT) {
				message = STRING_INFO + message + STRING_RESET;
				std::cout << message.c_str() << std::endl;
			}

			// WARNING
			// --------------------------------------------------------------------------
			if (messageSeverity & VK_DEBUG_UTILS_MESSAGE_SEVERITY_WARNING_BIT_EXT) {
				message = STRING_WARNING + message + STRING_RESET;
				std::cerr << message.c_str() << std::endl;
			}

			// ERROR
			// --------------------------------------------------------------------------
			if (messageSeverity & VK_DEBUG_UTILS_MESSAGE_SEVERITY_ERROR_BIT_EXT) {
				message = STRING_ERROR + message + STRING_RESET;
				std::cerr << message.c_str() << std::endl;
			}

			return VK_FALSE;
		}

		Result RHI_VK_RenderDevice::Initialize(const RHI_RenderDeviceDescriptor* _renderDeviceDescriptor)
		{
			// Object storing the result of all interal functions.
			Result result = Result::RESULT_INVALID;

			// Initialize the base class of the RHI_RenderDevice graphics object class,
			// And error check the result.
			// --------------------------------------------------------------------------
			result = RHI_RenderDevice::Initialize(_renderDeviceDescriptor);
			if (CheckError(result) == true)
			{
				// When result is RESULT_ERROR || RESULT_FATAL.
				Logger::Log("Error while intitializing the base class of the 'RHI_RenderDevice' object.", LogLevel::LOG_LEVEL_ERROR);
				Logger::Log("No further evidence what went wrong, please see earlier logs.", LogLevel::LOG_LEVEL_ERROR);
				return result;
			}

			// ==========================================================================
			// The actual VULKAN initialization follows
			// ==========================================================================

			// Current extensions
			std::vector<const char*> extensions = {
				VK_KHR_SURFACE_EXTENSION_NAME,
				VK_KHR_WIN32_SURFACE_EXTENSION_NAME,
			};

			// Check validation layer support if requested
			if (Is_DebugModeEnabled() == true && CheckValidationLayerSupport() == false)
				Logger::Log("Validation layer was requested, but layer not present in the current configuration.", LogLevel::LOG_LEVEL_ERROR);

			// Add debug util to device extension list if debugmode was enabled
			if (Is_DebugModeEnabled() == true)
				extensions.push_back(VK_EXT_DEBUG_UTILS_EXTENSION_NAME);

			// Vulkan API version
			uint32 vulkan_version = VK_API_VERSION_1_3;

			// Vulkan application info
			VkApplicationInfo appInfo{};
			appInfo.sType					    = VK_STRUCTURE_TYPE_APPLICATION_INFO;
			appInfo.pApplicationName		    = "Raydiance";
			appInfo.applicationVersion		    = VK_MAKE_VERSION(1, 0, 0);
			appInfo.pEngineName				    = "Raydiance Engine";
			appInfo.engineVersion			    = VK_MAKE_VERSION(1, 0, 0);
			appInfo.apiVersion				    = vulkan_version;


			// Vulkan instance create info	    
			VkInstanceCreateInfo createInfo{};  
			createInfo.sType				    = VK_STRUCTURE_TYPE_INSTANCE_CREATE_INFO;
			createInfo.pApplicationInfo		    = &appInfo;
			createInfo.enabledExtensionCount    = static_cast<uint32_t>(extensions.size());
			createInfo.ppEnabledExtensionNames  = extensions.data();
			createInfo.enabledLayerCount	    = 0;
			createInfo.pNext				    = nullptr;

			// Enable debug layer
			VkDebugUtilsMessengerCreateInfoEXT debugCreateInfo = {};
			if (Is_DebugModeEnabled() == true) {
				debugCreateInfo.sType			= VK_STRUCTURE_TYPE_DEBUG_UTILS_MESSENGER_CREATE_INFO_EXT;
				debugCreateInfo.messageSeverity = VK_DEBUG_UTILS_MESSAGE_SEVERITY_VERBOSE_BIT_EXT | VK_DEBUG_UTILS_MESSAGE_SEVERITY_WARNING_BIT_EXT | VK_DEBUG_UTILS_MESSAGE_SEVERITY_ERROR_BIT_EXT;
				debugCreateInfo.messageType		= VK_DEBUG_UTILS_MESSAGE_TYPE_GENERAL_BIT_EXT | VK_DEBUG_UTILS_MESSAGE_TYPE_VALIDATION_BIT_EXT | VK_DEBUG_UTILS_MESSAGE_TYPE_PERFORMANCE_BIT_EXT;
				debugCreateInfo.pfnUserCallback = DebugCallback;

				// Adjust the layer in the createInfo
				createInfo.enabledLayerCount    = std::size(validationLayers);
				createInfo.ppEnabledLayerNames  = validationLayers;
				createInfo.pNext			    = (VkDebugUtilsMessengerCreateInfoEXT*)&debugCreateInfo;
			}

			// Create the actual vulkan instance using the information above
			// --------------------------------------------------------------------------
			if (vkCreateInstance(&createInfo, nullptr, &m_Instance) != VK_SUCCESS) {
				Logger::Log("Failed to create the vulkan instance.", LogLevel::LOG_LEVEL_ERROR);
				return Result::RESULT_ERROR;
			}

			// Setup the validation messenger if debugmode is enabled
			if (Is_DebugModeEnabled() == true)
			{
				if (CreateDebugUtilsMessengerEXT(m_Instance, &debugCreateInfo, nullptr, &m_DebugMessenger) != VK_SUCCESS) {
					Logger::Log("Failed to create the vulkan DebugMessenger.", LogLevel::LOG_LEVEL_ERROR);
					return Result::RESULT_ERROR;
				}
			}

			VkWin32SurfaceCreateInfoKHR surfaceCreateInfo{};
			surfaceCreateInfo.sType		= VK_STRUCTURE_TYPE_WIN32_SURFACE_CREATE_INFO_KHR;
			surfaceCreateInfo.flags		= 0;
			surfaceCreateInfo.hwnd		= (HWND)_renderDeviceDescriptor->NativeWindowHandle;
			surfaceCreateInfo.hinstance = GetModuleHandle(nullptr);
			surfaceCreateInfo.pNext     = NULL;

			if (vkCreateWin32SurfaceKHR(m_Instance, &surfaceCreateInfo, nullptr, &m_Surface) != VK_SUCCESS) {
				Logger::Log("VK_ERROR: failed to create SwapchainSurface.", LogLevel::LOG_LEVEL_ERROR);
				return Result::RESULT_ERROR;
			}

			// Return the result, getting here indicates no error is returned
			// However, warning are possible
			return result;
		}

		Result RHI_VK_RenderDevice::GetAdapterCount(uint32& _count) const
		{
			// Get the number of devices
			vkEnumeratePhysicalDevices(m_Instance, &_count, nullptr);
			return Result::RESULT_GOOD;
		}

		Result RHI_VK_RenderDevice::GetAdapter(uint32 _index, RHI_Adapter** _adapter) const
		{
			// Query the number of adapters present in this device
			uint32 count = 0;
			GetAdapterCount(count);

			// Error checking on the number of presen adapters
			if (count <= _index)
			{
				Logger::Log("The user queried a non-existing adapter, could not retrieve any information for the 'RHI_AdapterInfo' class.", LogLevel::LOG_LEVEL_ERROR);
				return Result::RESULT_ERROR;
			}

			// The number of devices to be queried
			// Always +1 to convert from index to count
			count = _index + 1;

			// allocate vector of logical devices
			std::vector<VkPhysicalDevice> devices(count);
			vkEnumeratePhysicalDevices(m_Instance, &count, devices.data());

			// Gather info about the specific adapter requested
			*_adapter = new RHI_VK_Adapter(devices[_index]);
			return Result::RESULT_GOOD;
		}

		Result RHI_VK_RenderDevice::LinkAdapter(RHI_Adapter* _adapter)
		{
			m_Adapter = _adapter;
			RHI_VK_Adapter* vk_adapter = ((RHI_VK_Adapter*)m_Adapter);

			// Get the number of queue families
			uint32_t queueFamilyPropertyCount = 0;
			vkGetPhysicalDeviceQueueFamilyProperties(vk_adapter->GetPhysicalDevice(), &queueFamilyPropertyCount, NULL);

			// Get properties of the physical device queues
			std::vector<VkQueueFamilyProperties> queueFamilyPropertiesList(queueFamilyPropertyCount);
			vkGetPhysicalDeviceQueueFamilyProperties(vk_adapter->GetPhysicalDevice(), &queueFamilyPropertyCount, queueFamilyPropertiesList.data());

			// Pre-allocate the largest list-size for queue priorities
			std::vector<float> queuePriorities;
			for (uint32 i = 0; i < m_CommandQueueAllocations.size(); i++)
			{
				// If the count is larger, then set a new max
				if (m_CommandQueueAllocations[i].Count > queuePriorities.size())
					queuePriorities.resize(m_CommandQueueAllocations[i].Count, 1.0f);
			}

			std::vector<VkDeviceQueueCreateInfo> queueCreateInfos;
			for (uint32 i = 0; i < m_CommandQueueAllocations.size(); i++)
			{
				// Get allocation for the queues
				RHI_CommandQueueAllocation allocation = m_CommandQueueAllocations[i];

				VkDeviceQueueCreateInfo queueCreateInfo{};
				queueCreateInfo.pNext = NULL;
				queueCreateInfo.sType            = VK_STRUCTURE_TYPE_DEVICE_QUEUE_CREATE_INFO;
				queueCreateInfo.queueCount       = allocation.Count;
				queueCreateInfo.pQueuePriorities = queuePriorities.data();

				// Loop over the queues
				for (uint32_t j = 0; j < queueFamilyPropertiesList.size(); j++)
				{
					RHI_VK_CommandQueueFamily family;
					family.Index		  = j;
					family.Count		  = queueFamilyPropertiesList[j].queueCount;
					family.SurfaceSupport = false;

					queueCreateInfo.queueFamilyIndex = j;

					if (queueFamilyPropertiesList[j].queueFlags & VK_QUEUE_GRAPHICS_BIT && allocation.Type == RHI_CommandQueueType::RHI_COMMAND_QUEUE_TYPE_GRAPHICS)
					{
						family.Type = RHI_CommandQueueType::RHI_COMMAND_QUEUE_TYPE_GRAPHICS;
						family.SurfaceSupport = true;
						m_CommandQueueFamilies.push_back(family);

						queueCreateInfos.push_back(queueCreateInfo);
						break;
					}
					else if (queueFamilyPropertiesList[j].queueFlags & VK_QUEUE_COMPUTE_BIT && allocation.Type == RHI_CommandQueueType::RHI_COMMAND_QUEUE_TYPE_COMPUTE)
					{
						family.Type = RHI_CommandQueueType::RHI_COMMAND_QUEUE_TYPE_COMPUTE;
						m_CommandQueueFamilies.push_back(family);

						queueCreateInfos.push_back(queueCreateInfo);
						break;
					}
					else if (queueFamilyPropertiesList[j].queueFlags & VK_QUEUE_TRANSFER_BIT && allocation.Type == RHI_CommandQueueType::RHI_COMMAND_QUEUE_TYPE_COPY)
					{
						family.Type = RHI_CommandQueueType::RHI_COMMAND_QUEUE_TYPE_COPY;
						m_CommandQueueFamilies.push_back(family);

						queueCreateInfos.push_back(queueCreateInfo);
						break;
					}
					else if (queueFamilyPropertiesList[j].queueFlags & VK_QUEUE_VIDEO_DECODE_BIT_KHR && allocation.Type == RHI_CommandQueueType::RHI_COMMAND_QUEUE_TYPE_VIDEO_DECODE)
					{
						family.Type = RHI_CommandQueueType::RHI_COMMAND_QUEUE_TYPE_VIDEO_DECODE;
						m_CommandQueueFamilies.push_back(family);

						queueCreateInfos.push_back(queueCreateInfo);
						break;
					}
					else if (queueFamilyPropertiesList[j].queueFlags & VK_QUEUE_VIDEO_ENCODE_BIT_KHR && allocation.Type == RHI_CommandQueueType::RHI_COMMAND_QUEUE_TYPE_VIDEO_ENCODE)
					{
						family.Type = RHI_CommandQueueType::RHI_COMMAND_QUEUE_TYPE_VIDEO_ENCODE;
						m_CommandQueueFamilies.push_back(family);

						queueCreateInfos.push_back(queueCreateInfo);
						break;
					}
				}
			}

			std::vector<const char*> extensions(
				std::begin(deviceExtensions),
				std::end(deviceExtensions)
			);

			if (_adapter->GetFeatures().Is_RaytracingSupported() == true)
			{
				extensions.push_back(VK_KHR_BUFFER_DEVICE_ADDRESS_EXTENSION_NAME);

				extensions.push_back(VK_KHR_ACCELERATION_STRUCTURE_EXTENSION_NAME);
				extensions.push_back(VK_KHR_RAY_TRACING_PIPELINE_EXTENSION_NAME);
				extensions.push_back(VK_KHR_DEFERRED_HOST_OPERATIONS_EXTENSION_NAME);
				extensions.push_back(VK_KHR_PIPELINE_LIBRARY_EXTENSION_NAME);
				extensions.push_back(VK_KHR_SPIRV_1_4_EXTENSION_NAME);
			}

			VkPhysicalDeviceAccelerationStructureFeaturesKHR accel{};
			VkPhysicalDeviceRayTracingPipelineFeaturesKHR pipeline{};

			VkPhysicalDeviceBufferDeviceAddressFeatures address{};
			address.pNext				= NULL;
			address.sType				= VK_STRUCTURE_TYPE_PHYSICAL_DEVICE_BUFFER_DEVICE_ADDRESS_FEATURES;
			address.bufferDeviceAddress = VK_TRUE;

			if (_adapter->GetFeatures().Is_RaytracingSupported() == true)
			{
				accel.sType = VK_STRUCTURE_TYPE_PHYSICAL_DEVICE_ACCELERATION_STRUCTURE_FEATURES_KHR;
				accel.accelerationStructure = VK_TRUE;
				accel.pNext = NULL;

				
				pipeline.sType = VK_STRUCTURE_TYPE_PHYSICAL_DEVICE_RAY_TRACING_PIPELINE_FEATURES_KHR;
				pipeline.pNext = &accel;
				pipeline.rayTracingPipeline = VK_TRUE;

				address.pNext = &pipeline;
			}

			VkPhysicalDeviceFeatures2 deviceFeatures{};
			deviceFeatures.sType = VK_STRUCTURE_TYPE_PHYSICAL_DEVICE_FEATURES_2;
			deviceFeatures.pNext = &address;
			deviceFeatures.features.samplerAnisotropy = VK_TRUE;

			VkDeviceCreateInfo createInfo{};
			createInfo.sType				   = VK_STRUCTURE_TYPE_DEVICE_CREATE_INFO;
			createInfo.pNext				   = &deviceFeatures;
			createInfo.queueCreateInfoCount    = static_cast<uint32_t>(queueCreateInfos.size());
			createInfo.pQueueCreateInfos	   = queueCreateInfos.data();
			//createInfo.pEnabledFeatures	   = &deviceFeatures;
			createInfo.enabledExtensionCount   = static_cast<uint32_t>(extensions.size());
			createInfo.ppEnabledExtensionNames = extensions.data();
			createInfo.enabledLayerCount	   = 0;

			if (Is_DebugModeEnabled() == true) 
			{
				createInfo.enabledLayerCount   = std::size(validationLayers);
				createInfo.ppEnabledLayerNames = validationLayers;
			}

			if (vkCreateDevice(vk_adapter->GetPhysicalDevice(), &createInfo, nullptr, &m_Device) != VK_SUCCESS) {
				throw std::runtime_error("failed to create logical device!");
			}

			vkSetDebugUtilsObjectNameEXT    = (PFN_vkSetDebugUtilsObjectNameEXT)vkGetInstanceProcAddr(m_Instance, "vkSetDebugUtilsObjectNameEXT");
			vkQueueBeginDebugUtilsLabelEXT  = (PFN_vkQueueBeginDebugUtilsLabelEXT)vkGetDeviceProcAddr(m_Device,   "vkQueueBeginDebugUtilsLabelEXT");
			vkQueueEndDebugUtilsLabelEXT    = (PFN_vkQueueEndDebugUtilsLabelEXT)vkGetDeviceProcAddr(m_Device,     "vkQueueEndDebugUtilsLabelEXT");
			vkQueueInsertDebugUtilsLabelEXT = (PFN_vkQueueInsertDebugUtilsLabelEXT)vkGetDeviceProcAddr(m_Device,  "vkQueueInsertDebugUtilsLabelEXT");
			vkCmdBeginDebugUtilsLabelEXT    = (PFN_vkCmdBeginDebugUtilsLabelEXT)vkGetDeviceProcAddr(m_Device,     "vkCmdBeginDebugUtilsLabelEXT");
			vkCmdEndDebugUtilsLabelEXT      = (PFN_vkCmdEndDebugUtilsLabelEXT)vkGetDeviceProcAddr(m_Device,       "vkCmdEndDebugUtilsLabelEXT");
			vkCmdInsertDebugUtilsLabelEXT   = (PFN_vkCmdInsertDebugUtilsLabelEXT)vkGetDeviceProcAddr(m_Device,    "vkCmdInsertDebugUtilsLabelEXT");

			if (_adapter->GetFeatures().Is_RaytracingSupported() == true)
			{
				vkGetBufferDeviceAddressKHR				   = reinterpret_cast<PFN_vkGetBufferDeviceAddressKHR>(vkGetDeviceProcAddr(m_Device,				"vkGetBufferDeviceAddressKHR"));
				vkCreateAccelerationStructureKHR		   = reinterpret_cast<PFN_vkCreateAccelerationStructureKHR>(vkGetDeviceProcAddr(m_Device,			"vkCreateAccelerationStructureKHR"));
				vkDestroyAccelerationStructureKHR		   = reinterpret_cast<PFN_vkDestroyAccelerationStructureKHR>(vkGetDeviceProcAddr(m_Device,			"vkDestroyAccelerationStructureKHR"));
				vkGetAccelerationStructureBuildSizesKHR    = reinterpret_cast<PFN_vkGetAccelerationStructureBuildSizesKHR>(vkGetDeviceProcAddr(m_Device,	"vkGetAccelerationStructureBuildSizesKHR"));
				vkCmdBuildAccelerationStructuresKHR		   = reinterpret_cast<PFN_vkCmdBuildAccelerationStructuresKHR>(vkGetDeviceProcAddr(m_Device,		"vkCmdBuildAccelerationStructuresKHR"));
				vkGetAccelerationStructureDeviceAddressKHR = reinterpret_cast<PFN_vkGetAccelerationStructureDeviceAddressKHR>(vkGetDeviceProcAddr(m_Device, "vkGetAccelerationStructureDeviceAddressKHR"));
				vkCreateRayTracingPipelinesKHR			   = reinterpret_cast<PFN_vkCreateRayTracingPipelinesKHR>(vkGetDeviceProcAddr(m_Device,				"vkCreateRayTracingPipelinesKHR"));
				vkGetRayTracingShaderGroupHandlesKHR	   = reinterpret_cast<PFN_vkGetRayTracingShaderGroupHandlesKHR>(vkGetDeviceProcAddr(m_Device,		"vkGetRayTracingShaderGroupHandlesKHR"));
				vkCmdTraceRaysKHR						   = reinterpret_cast<PFN_vkCmdTraceRaysKHR>(vkGetDeviceProcAddr(m_Device,							"vkCmdTraceRaysKHR"));
			}

			return Result::RESULT_GOOD;
		}

		Result RHI_VK_RenderDevice::CheckSwapchainResourceFormatSupport(RHI_ResourceFormat _format, bool& _supported) const
		{
			_supported = false;
			uint32_t formatCount = 0;

			vkGetPhysicalDeviceSurfaceFormatsKHR(((RHI_VK_Adapter*)RHI_RenderDevice::Get()->RHI_GetAdapter())->GetPhysicalDevice(), m_Surface, &formatCount, nullptr);

			std::vector<VkSurfaceFormatKHR> formats;
			if (formatCount != 0) {
				formats.resize(formatCount);
				vkGetPhysicalDeviceSurfaceFormatsKHR(((RHI_VK_Adapter*)RHI_RenderDevice::Get()->RHI_GetAdapter())->GetPhysicalDevice(), m_Surface, &formatCount, formats.data());
			}
			else
			{
				return Result::RESULT_ERROR;
			}

			VkFormat format = ResolveVKResourceFormat(_format);
			for (const auto& availableFormat : formats) {
				if (availableFormat.format == format && availableFormat.colorSpace == VK_COLOR_SPACE_SRGB_NONLINEAR_KHR) {
					_supported = true;
					return Result::RESULT_GOOD;
				}
			}

			return Result::RESULT_GOOD;
		}

		RHI_CommandQueue* RHI_VK_RenderDevice::RHI_CreateCommandQueue(const RHI_CommandQueueDescriptor* _commandQueueDescriptor)
		{
			// Create and initialize
			RHI_VK_CommandQueue* commandQueue = new RHI_VK_CommandQueue();
			Result result = commandQueue->Initialize(this, _commandQueueDescriptor);

			// Error check
			if (CheckError(result) == true)
			{
				// Destroy pointer
				delete commandQueue;

				// Log error
				Logger::Log("Initialization of RHI_VK_CommandQueue failed.", LogLevel::LOG_LEVEL_ERROR);
				Logger::Log("No further evidence what went wrong, please see earlier logs.", LogLevel::LOG_LEVEL_ERROR);
				return nullptr;
			}

			// Return pointer
			return commandQueue;
		}

		RHI_CommandBuffer* RHI_VK_RenderDevice::RHI_CreateCommandBuffer(const RHI_CommandBufferDescriptor* _commandBufferDescriptor)
		{
			// Create and initialize
			RHI_VK_CommandBuffer* commandBuffer = new RHI_VK_CommandBuffer();
			Result result = commandBuffer->Initialize(this, _commandBufferDescriptor);

			// Error check
			if (CheckError(result) == true)
			{
				// Destroy pointer
				delete commandBuffer;

				// Log error
				Logger::Log("Initialization of RHI_VK_CommandBuffer failed.", LogLevel::LOG_LEVEL_ERROR);
				Logger::Log("No further evidence what went wrong, please see earlier logs.", LogLevel::LOG_LEVEL_ERROR);
				return nullptr;
			}

			// Return pointer
			return commandBuffer;
		}

		RHI_CommandPool* RHI_VK_RenderDevice::RHI_CreateCommandPool(const RHI_CommandPoolDescriptor* _commandPoolDescriptor)
		{
			// Create and initialize
			RHI_VK_CommandPool* commandPool = new RHI_VK_CommandPool();
			Result result = commandPool->Initialize(this, _commandPoolDescriptor);

			// Error check
			if (CheckError(result) == true)
			{
				// Destroy pointer
				delete commandPool;

				// Log error
				Logger::Log("Initialization of RHI_VK_CommandPool failed.", LogLevel::LOG_LEVEL_ERROR);
				Logger::Log("No further evidence what went wrong, please see earlier logs.", LogLevel::LOG_LEVEL_ERROR);
				return nullptr;
			}

			// Return pointer
			return commandPool;
		}

		RHI_Swapchain* RHI_VK_RenderDevice::RHI_CreateSwapchain(RHI_CommandQueue* _commandQueue, const RHI_SwapchainDescriptor* _swapchainDescriptor)
		{
			// Create and initialize
			RHI_VK_Swapchain* swapchain = new RHI_VK_Swapchain();
			Result result = swapchain->Initialize(this, _commandQueue, _swapchainDescriptor);

			// Error check
			if (CheckError(result) == true)
			{
				// Destroy pointer
				delete swapchain;

				// Log error
				Logger::Log("Initialization of RHI_VK_Swapchain failed.", LogLevel::LOG_LEVEL_ERROR);
				Logger::Log("No further evidence what went wrong, please see earlier logs.", LogLevel::LOG_LEVEL_ERROR);
				return nullptr;
			}

			// Return pointer
			return swapchain;
		}

		RHI_FenceCPU* RHI_VK_RenderDevice::RHI_CreateFenceCPU(const RHI_FenceCPUDescriptor* _FenceDescriptor)
		{
			// Create and initialize
			RHI_VK_FenceCPU* fence = new RHI_VK_FenceCPU();
			Result result = fence->Initialize(this, _FenceDescriptor);

			// Error check
			if (CheckError(result) == true)
			{
				// Destroy pointer
				delete fence;

				// Log error
				Logger::Log("Initialization of RHI_VK_FenceCPU failed.", LogLevel::LOG_LEVEL_ERROR);
				Logger::Log("No further evidence what went wrong, please see earlier logs.", LogLevel::LOG_LEVEL_ERROR);
				return nullptr;
			}

			// Return pointer
			return fence;
		}

		RHI_Texture2D* RHI_VK_RenderDevice::RHI_CreateTexture2D(const RHI_Texture2DDescriptor* _texture2DDescriptor)
		{
			// Create and initialize
			RHI_VK_Texture2D* texture = new RHI_VK_Texture2D();
			Result result = texture->Initialize(this, _texture2DDescriptor);

			// Error check
			if (CheckError(result) == true)
			{
				// Destroy pointer
				delete texture;

				// Log error
				Logger::Log("Initialization of RHI_VK_Texture2D failed.", LogLevel::LOG_LEVEL_ERROR);
				Logger::Log("No further evidence what went wrong, please see earlier logs.", LogLevel::LOG_LEVEL_ERROR);
				return nullptr;
			}

			// Return pointer
			return texture;
		}

		RHI_Shader* RHI_VK_RenderDevice::RHI_CreateShader(const RHI_ShaderDescriptor* _shaderDescriptor)
		{
			// Create and initialize
			RHI_VK_Shader* shader = new RHI_VK_Shader();
			Result result = shader->Initialize(this, _shaderDescriptor);

			// Error check
			if (CheckError(result) == true)
			{
				// Destroy pointer
				delete shader;

				// Log error
				Logger::Log("Initialization of RHI_VK_Shader failed.", LogLevel::LOG_LEVEL_ERROR);
				Logger::Log("No further evidence what went wrong, please see earlier logs.", LogLevel::LOG_LEVEL_ERROR);
				return nullptr;
			}

			// Return pointer
			return shader;
		}

		RHI_Buffer* RHI_VK_RenderDevice::RHI_CreateBuffer(const RHI_BufferDescriptor* _bufferDescriptor)
		{
			// Create and initialize
			RHI_VK_Buffer* buffer = new RHI_VK_Buffer();
			Result result = buffer->Initialize(this, _bufferDescriptor);

			// Error check
			if (CheckError(result) == true)
			{
				// Destroy pointer
				delete buffer;

				// Log error
				Logger::Log("Initialization of RHI_VK_Buffer failed.", LogLevel::LOG_LEVEL_ERROR);
				Logger::Log("No further evidence what went wrong, please see earlier logs.", LogLevel::LOG_LEVEL_ERROR);
				return nullptr;
			}

			// Return pointer
			return buffer;
		}

		RHI_Sampler* RHI_VK_RenderDevice::RHI_CreateSampler(const RHI_SamplerDescriptor* _samplerDescriptor)
		{
			// Create and initialize
			RHI_VK_Sampler* sampler = new RHI_VK_Sampler();
			Result result = sampler->Initialize(this, _samplerDescriptor);

			// Error check
			if (CheckError(result) == true)
			{
				// Destroy pointer
				delete sampler;

				// Log error
				Logger::Log("Initialization of RHI_VK_Sampler failed.", LogLevel::LOG_LEVEL_ERROR);
				Logger::Log("No further evidence what went wrong, please see earlier logs.", LogLevel::LOG_LEVEL_ERROR);
				return nullptr;
			}

			// Return pointer
			return sampler;
		}

		RHI_RenderPass* RHI_VK_RenderDevice::RHI_CreateRenderPass(const RHI_RenderPassDescriptor* _renderPassDescriptor)
		{
			// Create and initialize
			RHI_VK_RenderPass* renderPass = new RHI_VK_RenderPass();
			Result result = renderPass->Initialize(this, _renderPassDescriptor);

			// Error check
			if (CheckError(result) == true)
			{
				// Destroy pointer
				delete renderPass;

				// Log error
				Logger::Log("Initialization of RHI_VK_RenderPass failed.", LogLevel::LOG_LEVEL_ERROR);
				Logger::Log("No further evidence what went wrong, please see earlier logs.", LogLevel::LOG_LEVEL_ERROR);
				return nullptr;
			}

			// Return pointer
			return renderPass;
		}

		RHI_FrameBuffer* RHI_VK_RenderDevice::RHI_CreateFrameBuffer(const RHI_FrameBufferDescriptor* _frameBufferDescriptor)
		{
			// Create and initialize
			RHI_VK_FrameBuffer* framebuffer = new RHI_VK_FrameBuffer();
			Result result = framebuffer->Initialize(this, _frameBufferDescriptor);

			// Error check
			if (CheckError(result) == true)
			{
				// Destroy pointer
				delete framebuffer;

				// Log error
				Logger::Log("Initialization of RHI_VK_FrameBuffer failed.", LogLevel::LOG_LEVEL_ERROR);
				Logger::Log("No further evidence what went wrong, please see earlier logs.", LogLevel::LOG_LEVEL_ERROR);
				return nullptr;
			}

			// Return pointer
			return framebuffer;
		}

		RHI_DescriptorPool* RHI_VK_RenderDevice::RHI_CreateDescriptorPool(const RHI_DescriptorPoolDescriptor* _descriptorPoolDescriptor)
		{
			// Create and initialize
			RHI_VK_DescriptorPool* descriptorPool = new RHI_VK_DescriptorPool();
			Result result = descriptorPool->Initialize(this, _descriptorPoolDescriptor);

			RHI_DescriptorPool* poep = 0;

			// Error check
			if (CheckError(result) == true)
			{
				// Destroy pointer
				delete descriptorPool;

				// Log error
				Logger::Log("Initialization of RHI_VK_DescriptorPool failed.", LogLevel::LOG_LEVEL_ERROR);
				Logger::Log("No further evidence what went wrong, please see earlier logs.", LogLevel::LOG_LEVEL_ERROR);
				return nullptr;
			}

			// Return pointer
			return descriptorPool;
		}

		RHI_InputLayout* RHI_VK_RenderDevice::RHI_CreateInputLayout(const RHI_InputLayoutDescriptor* _inputLayoutDescriptor)
		{
			// Create and initialize
			RHI_VK_InputLayout* inputLayout = new RHI_VK_InputLayout();
			Result result = inputLayout->Initialize(this, _inputLayoutDescriptor);

			// Error check
			if (CheckError(result) == true)
			{
				// Destroy pointer
				delete inputLayout;

				// Log error
				Logger::Log("Initialization of RHI_VK_InputLayout failed.", LogLevel::LOG_LEVEL_ERROR);
				Logger::Log("No further evidence what went wrong, please see earlier logs.", LogLevel::LOG_LEVEL_ERROR);
				return nullptr;
			}

			// Return pointer
			return inputLayout;
		}

		RHI_GraphicsPipeline* RHI_VK_RenderDevice::RHI_CreateGraphicsPipeline(const RHI_GraphicsPipelineDescriptor* _graphicsPipelineDescriptor)
		{
			// Create and initialize
			RHI_VK_GraphicsPipeline* graphicsPipeline = new RHI_VK_GraphicsPipeline();
			Result result = graphicsPipeline->Initialize(this, _graphicsPipelineDescriptor);

			// Error check
			if (CheckError(result) == true)
			{
				// Destroy pointer
				delete graphicsPipeline;

				// Log error
				Logger::Log("Initialization of RHI_VK_GraphicsPipeline failed.", LogLevel::LOG_LEVEL_ERROR);
				Logger::Log("No further evidence what went wrong, please see earlier logs.", LogLevel::LOG_LEVEL_ERROR);
				return nullptr;
			}

			// Return pointer
			return graphicsPipeline;
		}

		RHI_ComputePipeline* RHI_VK_RenderDevice::RHI_CreateComputePipeline(const RHI_ComputePipelineDescriptor* _computePipelineDescriptor)
		{
			// Create and initialize
			RHI_VK_ComputePipeline* computePipeline = new RHI_VK_ComputePipeline();
			Result result = computePipeline->Initialize(this, _computePipelineDescriptor);

			// Error check
			if (CheckError(result) == true)
			{
				// Destroy pointer
				delete computePipeline;

				// Log error
				Logger::Log("Initialization of RHI_VK_ComputePipeline failed.", LogLevel::LOG_LEVEL_ERROR);
				Logger::Log("No further evidence what went wrong, please see earlier logs.", LogLevel::LOG_LEVEL_ERROR);
				return nullptr;
			}

			// Return pointer
			return computePipeline;
		}

		RHI_Texture2D* RHI_VK_RenderDevice::CreateTexture2DFromVkImage(VkImage _image, const RHI_Texture2DDescriptor* _texture2DDescriptor)
		{
			RHI_VK_Texture2D* texture = new RHI_VK_Texture2D();
			Result result = texture->Initialize(this, _image, _texture2DDescriptor);
			if (CheckError(result) == true)
			{
				Logger::Log("", LogLevel::LOG_LEVEL_ERROR);
				return nullptr;
			}

			return texture;
		}

		const Result RHI_VK_RenderDevice::QueryCommandQueueIndex(RHI_CommandQueueType _type, uint32& _index) const
		{
			for (uint32 i = 0; i < m_CommandQueueFamilies.size(); i++)
			{
				if (m_CommandQueueFamilies[i].Type == _type)
				{
					_index = m_CommandQueueFamilies[i].Index;
					return Result::RESULT_GOOD;
				}
			}

			_index = 0;
			return Result::RESULT_ERROR;
		}

		bool RHI_VK_RenderDevice::CheckValidationLayerSupport()
		{
			// Gather the number of layers
			uint32_t layerCount;
			vkEnumerateInstanceLayerProperties(&layerCount, nullptr);

			// Get the layer properties
			std::vector<VkLayerProperties> availableLayers(layerCount);
			vkEnumerateInstanceLayerProperties(&layerCount, availableLayers.data());

			// See if all the validation layers are present
			for (const char* layerName : validationLayers) {
				bool layerFound = false;
				for (const auto& layerProperties : availableLayers) {
					if (strcmp(layerName, layerProperties.layerName) == 0) {
						layerFound = true;
						break;
					}
				}

				if (!layerFound) {
					return false;
				}
			}

			return true;
		}
	}
}