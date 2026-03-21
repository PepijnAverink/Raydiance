#include "./pch.h"
#include "./graphics/RHI_api/vk/RHI_VK_render_device.h"

// Graphics includes
#include "./graphics/RHI_api/vk/object/command/RHI_VK_command_pool.h"
#include "./graphics/RHI_api/vk/object/command/RHI_VK_command_buffer.h"
#include "./graphics/RHI_api/vk/object/command/RHI_VK_command_queue.h"
#include "./graphics/RHI_api/vk/object/swapchain/RHI_VK_swapchain.h"
#include "./graphics/RHI_api/vk/object/sync/RHI_VK_fenceCPU.h"

#include "./graphics/RHI_api/vk/pipeline/graphics/RHI_VK_graphics_pipeline.h"
#include "./graphics/RHI_api/vk/pipeline/layout/RHI_VK_input_layout.h"
#include "./graphics/RHI_api/vk/pipeline/renderpass/RHI_VK_render_pass.h"
#include "./graphics/RHI_api/vk/pipeline/framebuffer/RHI_VK_frame_buffer.h"

#include "./graphics/RHI_api/vk/pipeline/layout/descriptor/RHI_VK_descriptor_pool.h"
#include "./graphics/RHI_api/vk/pipeline/layout/descriptor/RHI_VK_descriptor_set.h"

#include "./graphics/RHI_api/vk/resource/buffer/RHI_VK_buffer.h"
#include "./graphics/RHI_api/vk/resource/shader/RHI_VK_shader.h"
#include "./graphics/RHI_api/vk/resource/sampler/RHI_VK_sampler.h"
#include "./graphics/RHI_api/vk/resource/texture/RHI_VK_texture2D.h"

#include "./graphics/RHI_api/vk/RHI_VK_adapter.h"

// Core includes
#include "./core/window/window.h"

const std::vector<const char*> validationLayers = {
    "VK_LAYER_KHRONOS_validation"
};

const std::vector<const char*> deviceExtensions = {
    VK_KHR_SWAPCHAIN_EXTENSION_NAME
};

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

// Debug callback
// Validation layer message print
static VKAPI_ATTR VkBool32 VKAPI_CALL debugCallback(VkDebugUtilsMessageSeverityFlagBitsEXT messageSeverity, VkDebugUtilsMessageTypeFlagsEXT messageType, const VkDebugUtilsMessengerCallbackDataEXT* pCallbackData, void* pUserData) {
    std::cerr << "validation layer: " << pCallbackData->pMessage << std::endl;
    return VK_FALSE;
}

namespace Raydiance
{
    namespace Graphics
    {
        struct QueueFamilyIndices {
            std::optional<uint32_t> graphicsFamily;
            std::optional<uint32_t> presentFamily;

            bool isComplete() {
                return graphicsFamily.has_value() && presentFamily.has_value();
            }
        };
        QueueFamilyIndices FindQueueFamilies(VkPhysicalDevice device, VkSurfaceKHR _surface);

        RHI_VK_RenderDevice::RHI_VK_RenderDevice()
            : RHI_RenderDevice(RHI_GraphicsAPI::RHI_GRAPHICS_API_VULKAN)
        { }

        RHI_VK_RenderDevice::~RHI_VK_RenderDevice()
        {
            vkDestroyDevice(m_Device, nullptr);

            if (m_DebugEnabled == true)
                DestroyDebugUtilsMessengerEXT(m_Instance, m_DebugMessenger, nullptr);

            vkDestroySurfaceKHR(m_Instance, m_Surface, nullptr);
            vkDestroyInstance(m_Instance, nullptr);
        }

        Result RHI_VK_RenderDevice::Initialize(const RHI_RenderDeviceDescriptor& _renderDeviceDescriptor)
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
                Logger::Log("Error while intitializing the base class of the 'RHI_RenderDevice' object.", LogType::LOG_TYPE_ERROR);
                Logger::Log("No further evidence what went wrong, please see earlier logs.", LogType::LOG_TYPE_ERROR);
                return result;
            }

            // ==========================================================================
            // The actual VULKAN initialization follows
            // ==========================================================================


            // Corrct debug mode
            if (m_DebugEnabled == true)
                m_DebugEnabled = CheckValidationLayerSupport();

            // Current extensions
            std::vector<const char*> extensions = { "VK_KHR_surface" };
            {
#if defined(_WIN32)
                extensions.push_back("VK_KHR_win32_surface");
#endif
                if (m_DebugEnabled)
                    extensions.push_back(VK_EXT_DEBUG_UTILS_EXTENSION_NAME);
            }

            // Application information
            VkApplicationInfo appInfo{};
            appInfo.sType = VK_STRUCTURE_TYPE_APPLICATION_INFO;
            appInfo.pApplicationName = "Raydiance_Application";
            appInfo.applicationVersion = VK_MAKE_VERSION(1, 0, 0);
            appInfo.pEngineName = "No Engine";
            appInfo.engineVersion = VK_MAKE_VERSION(1, 0, 0);
            appInfo.apiVersion = VK_API_VERSION_1_0;

            VkInstanceCreateInfo createInfo{};
            createInfo.sType = VK_STRUCTURE_TYPE_INSTANCE_CREATE_INFO;
            createInfo.pApplicationInfo = &appInfo;
            createInfo.enabledExtensionCount = static_cast<uint32_t>(extensions.size());
            createInfo.ppEnabledExtensionNames = extensions.data();
            createInfo.enabledLayerCount = 0;
            createInfo.pNext = nullptr;

            // Enable debug layer
            VkDebugUtilsMessengerCreateInfoEXT debugCreateInfo = {};
            if (m_DebugEnabled == true) {
                debugCreateInfo.sType = VK_STRUCTURE_TYPE_DEBUG_UTILS_MESSENGER_CREATE_INFO_EXT;
                debugCreateInfo.messageSeverity = VK_DEBUG_UTILS_MESSAGE_SEVERITY_VERBOSE_BIT_EXT | VK_DEBUG_UTILS_MESSAGE_SEVERITY_WARNING_BIT_EXT | VK_DEBUG_UTILS_MESSAGE_SEVERITY_ERROR_BIT_EXT;
                debugCreateInfo.messageType = VK_DEBUG_UTILS_MESSAGE_TYPE_GENERAL_BIT_EXT | VK_DEBUG_UTILS_MESSAGE_TYPE_VALIDATION_BIT_EXT | VK_DEBUG_UTILS_MESSAGE_TYPE_PERFORMANCE_BIT_EXT;
                debugCreateInfo.pfnUserCallback = debugCallback;

                createInfo.enabledLayerCount = static_cast<uint32_t>(validationLayers.size());
                createInfo.ppEnabledLayerNames = validationLayers.data();
                createInfo.pNext = (VkDebugUtilsMessengerCreateInfoEXT*)&debugCreateInfo;
            }

            // Create and error check vulkan instance
            if (vkCreateInstance(&createInfo, nullptr, &m_Instance) != VK_SUCCESS)
                Logger::Log("VK_ERROR - Failed to create the vulkan instance.", LogType::LOG_TYPE_ERROR);

            // Enable debug messenger if debugmode is enabled
            if (m_DebugEnabled == true)
                if (CreateDebugUtilsMessengerEXT(m_Instance, &debugCreateInfo, nullptr, &m_DebugMessenger) != VK_SUCCESS)
                    Logger::Log("VK_ERROR - Failed to serup the vulkan debug messenger.", LogType::LOG_TYPE_ERROR);

            // Surface which is associated with the window
            VkWin32SurfaceCreateInfoKHR surfaceCreateInfo;
            surfaceCreateInfo.sType = VK_STRUCTURE_TYPE_WIN32_SURFACE_CREATE_INFO_KHR;
            surfaceCreateInfo.pNext = NULL;
            surfaceCreateInfo.flags = 0;
            surfaceCreateInfo.hinstance = GetModuleHandle(NULL);
            surfaceCreateInfo.hwnd = (HWND)_renderDeviceDescriptor.NativeWindowHandle;

            // Craete and error check the surface
            if (vkCreateWin32SurfaceKHR(m_Instance, &surfaceCreateInfo, NULL, &m_Surface) != VK_SUCCESS)
                Logger::Log("VK_ERROR - Failed to create surface.", LogType::LOG_TYPE_ERROR);

            return Result::RESULT_GOOD;
        }

        Result RHI_VK_RenderDevice::GetAdapterCount(uint32& _count) const
        {
            _count = 0;

            // Get the number of devices
            if (m_Instance == VK_NULL_HANDLE)
            {
                Logger::Log("vkInstance == VK_NULL_HANDLE, RHI_VK_RenderDevice probably isn't initialized correctly.", LogType::LOG_TYPE_ERROR);
				return Result::RESULT_ERROR;
            }

			// Gather the number of devices (or adapters)
            vkEnumeratePhysicalDevices(m_Instance, &_count, nullptr);
            return Result::RESULT_GOOD;
        }

        Result RHI_VK_RenderDevice::GetAdapter(const uint32 _adapterID, std::unique_ptr<RHI_Adapter>& _adapter) const
        {
            // Get the number of devices
            if (m_Instance == VK_NULL_HANDLE)
            {
                Logger::Log("vkInstance == VK_NULL_HANDLE, RHI_VK_RenderDevice probably isn't initialized correctly.", LogType::LOG_TYPE_ERROR);
                return Result::RESULT_ERROR;
            }

            // Query the number of adapters present in this device
            uint32 count = 0;
            GetAdapterCount(count);

            // Error checking on the number of presen adapters
            if (count <= _adapterID)
            {
                Logger::Log("The user queried a non-existing adapter, could not retrieve any information for the 'RHI_AdapterInfo' class.", LogType::LOG_TYPE_ERROR);
                return Result::RESULT_ERROR;
            }

            // The number of devices to be queried
            // Always +1 to convert from index to count
            count = _adapterID + 1;

            // allocate vector of logical devices
            std::vector<VkPhysicalDevice> devices(count);
            vkEnumeratePhysicalDevices(m_Instance, &count, devices.data());

            // Gather info about the specific adapter requested
            _adapter = std::make_unique<RHI_VK_Adapter>(devices[_adapterID]);
            return Result::RESULT_GOOD;
        }

        Result RHI_VK_RenderDevice::LinkAdapter(std::unique_ptr<RHI_Adapter> _adapter)
        {
            // Sets the active adapter
            m_Adapter = std::move(_adapter);

            // Cast the adapter to a vulkan specific adapter.
            const RHI_VK_Adapter* physicalDevice = static_cast<const RHI_VK_Adapter*>(m_Adapter.get());

            QueueFamilyIndices indices = FindQueueFamilies(physicalDevice->GetPhysicalDevice(), m_Surface);

            std::vector<VkDeviceQueueCreateInfo> queueCreateInfos;
            std::set<uint32_t> uniqueQueueFamilies = { indices.graphicsFamily.value(), indices.presentFamily.value() };

            float queuePriority = 1.0f;
            for (uint32_t queueFamily : uniqueQueueFamilies) {
                VkDeviceQueueCreateInfo queueCreateInfo{};
                queueCreateInfo.sType = VK_STRUCTURE_TYPE_DEVICE_QUEUE_CREATE_INFO;
                queueCreateInfo.queueFamilyIndex = queueFamily;
                queueCreateInfo.queueCount = 1;
                queueCreateInfo.pQueuePriorities = &queuePriority;
                queueCreateInfos.push_back(queueCreateInfo);
            }

            VkPhysicalDeviceFeatures deviceFeatures{};
            deviceFeatures.samplerAnisotropy = VK_TRUE;

            VkDeviceCreateInfo createInfo{};
            createInfo.sType = VK_STRUCTURE_TYPE_DEVICE_CREATE_INFO;
            createInfo.queueCreateInfoCount = static_cast<uint32_t>(queueCreateInfos.size());
            createInfo.pQueueCreateInfos = queueCreateInfos.data();
            createInfo.pEnabledFeatures = &deviceFeatures;
            createInfo.enabledExtensionCount = static_cast<uint32_t>(deviceExtensions.size());
            createInfo.ppEnabledExtensionNames = deviceExtensions.data();
            createInfo.enabledLayerCount = 0;

            if (m_DebugEnabled == true) {
                createInfo.enabledLayerCount = static_cast<uint32_t>(validationLayers.size());
                createInfo.ppEnabledLayerNames = validationLayers.data();
            }

            if (vkCreateDevice(physicalDevice->GetPhysicalDevice(), &createInfo, nullptr, &m_Device) != VK_SUCCESS) {
                throw std::runtime_error("failed to create logical device!");
            }

            m_GraphicsQueueID = indices.graphicsFamily.value();
            m_PresentQueueID = indices.presentFamily.value();

            return Result::RESULT_GOOD;
        }

        uint32_t RHI_VK_RenderDevice::GetQueueFamilyID(const RHI_CommandQueueType _type) const
        {
            // TODO:: add support for other types of queues
            if (_type == RHI_CommandQueueType::RHI_COMMAND_QUEUE_TYPE_GRAPHICS)
                return m_GraphicsQueueID;

            return 0;
        }

        std::shared_ptr<RHI_CommandPool> RHI_VK_RenderDevice::CreateCommandPool(const RHI_CommandPoolDescriptor& _commandPoolDescriptor)
        {
            std::shared_ptr<RHI_VK_CommandPool> commandPool = std::make_shared<RHI_VK_CommandPool>(this, _commandPoolDescriptor);
            return commandPool;
        }

        std::shared_ptr<RHI_CommandBuffer> RHI_VK_RenderDevice::CreateCommandBuffer(const RHI_CommandBufferDescriptor& _commandBufferDescriptor)
        {
            std::shared_ptr<RHI_VK_CommandBuffer> commandBuffer = std::make_shared<RHI_VK_CommandBuffer>(this, _commandBufferDescriptor);
            return commandBuffer;
        }

        std::shared_ptr<RHI_CommandQueue> RHI_VK_RenderDevice::CreateCommandQueue(const RHI_CommandQueueDescriptor& _commandQueueDescriptor)
        {
            std::shared_ptr<RHI_VK_CommandQueue> commandQueue = std::make_shared<RHI_VK_CommandQueue>();
            Result result = commandQueue->Initialize(*this, _commandQueueDescriptor);

            // Error check
            if (CheckError(result) == true)
            {
                // Log error
                Logger::Log("Initialization of RHI_VK_CommandQueue failed.", LogType::LOG_TYPE_ERROR);
                Logger::Log("No further evidence what went wrong, please see earlier logs.", LogType::LOG_TYPE_ERROR);
                return nullptr;
            }

            return commandQueue;
        }

        std::shared_ptr<RHI_Swapchain> RHI_VK_RenderDevice::CreateSwapchain(const RHI_CommandQueue& _commandQueue, const RHI_SwapchainDescriptor& _swapchainDescriptor)
        {
            std::shared_ptr<RHI_VK_Swapchain> swapchain = std::make_shared<RHI_VK_Swapchain>();
            Result result = swapchain->Initialize(*this, _commandQueue, _swapchainDescriptor);

            // Error check
            if (CheckError(result) == true)
            {
                // Log error
                Logger::Log("Initialization of RHI_VK_Swapchain failed.", LogType::LOG_TYPE_ERROR);
                Logger::Log("No further evidence what went wrong, please see earlier logs.", LogType::LOG_TYPE_ERROR);
                return nullptr;
            }

            return swapchain;
        }

        RHI_GraphicsPipeline* RHI_VK_RenderDevice::CreateGraphicsPipeline(const RHI_GraphicsPipelineDescriptor* _graphicsPipelineDescriptor)
        {
            RHI_VK_GraphicsPipeline* graphicsPipeline = new RHI_VK_GraphicsPipeline(this, _graphicsPipelineDescriptor);
            return graphicsPipeline;
        }

        RHI_InputLayout* RHI_VK_RenderDevice::CreateInputLayout(const RHI_InputLayoutDescriptor* _inputLayoutDescriptor)
        {
            RHI_VK_InputLayout* inputLayout = new RHI_VK_InputLayout(this, _inputLayoutDescriptor);
            return inputLayout;
        }

        RHI_RenderPass* RHI_VK_RenderDevice::CreateRenderPass(const RHI_RenderPassDescriptor* _renderPassDescriptor)
        {
            RHI_RenderPass* renderPass = new RHI_VK_RenderPass(this, _renderPassDescriptor);
            return renderPass;
        }

        RHI_FrameBuffer* RHI_VK_RenderDevice::CreateFrameBuffer(const RHI_FrameBufferDescriptor* _frameBufferDescriptor)
        {
            RHI_VK_FrameBuffer* frameBuffer = new RHI_VK_FrameBuffer(this, _frameBufferDescriptor);
            return frameBuffer;
        }

        RHI_DescriptorPool* RHI_VK_RenderDevice::CreateDescriptorPool(const RHI_DescriptorPoolDescriptor* _descriptorPoolDescriptor)
        {
            RHI_VK_DescriptorPool* descroptorPool = new RHI_VK_DescriptorPool(this, _descriptorPoolDescriptor);
            return descroptorPool;
        }

        RHI_Buffer* RHI_VK_RenderDevice::CreateBuffer(const RHI_BufferDescriptor* _bufferDescriptor)
        {
            RHI_VK_Buffer* buffer = new RHI_VK_Buffer(this, _bufferDescriptor);
            return buffer;
        }

        RHI_Shader* RHI_VK_RenderDevice::CreateShader(const RHI_ShaderDescriptor* _shaderDescriptor)
        {
            RHI_VK_Shader* shader = new RHI_VK_Shader(this, _shaderDescriptor);
            return shader;
        }

        RHI_Texture2D* RHI_VK_RenderDevice::CreateTexture2D(const RHI_Texture2DDescriptor* _texture2DDescriptor)
        {
            RHI_VK_Texture2D* texture = new RHI_VK_Texture2D(this, _texture2DDescriptor);
            return texture;
        }

        RHI_Sampler* RHI_VK_RenderDevice::CreateSampler(const RHI_SamplerDescriptor& _sampler2DDescripotr)
        {
            RHI_VK_Sampler* sampler = new RHI_VK_Sampler(*this, _sampler2DDescripotr);
            return sampler;
        }

        std::shared_ptr<RHI_FenceCPU> RHI_VK_RenderDevice::CreateFenceCPU(const RHI_FenceCPUDescriptor& _fenceDescriptor)
        {
            std::shared_ptr<RHI_VK_FenceCPU> fence = std::make_shared<RHI_VK_FenceCPU>();
            Result result  = fence->Initialize(*this, _fenceDescriptor);

            // Error check
            if (CheckError(result) == true)
            {
                // Log error
                Logger::Log("Initialization of RHI_VK_FenceCPU failed.", LogType::LOG_TYPE_ERROR);
                Logger::Log("No further evidence what went wrong, please see earlier logs.", LogType::LOG_TYPE_ERROR);
                return nullptr;
            }

            return fence;
        }

        bool RHI_VK_RenderDevice::CheckValidationLayerSupport()
        {
            // Enumerate over all the layers
            uint32_t layerCount;
            vkEnumerateInstanceLayerProperties(&layerCount, nullptr);

            // Allocate vector for all layers
            std::vector<VkLayerProperties> availableLayers(layerCount);
            vkEnumerateInstanceLayerProperties(&layerCount, availableLayers.data());

            // Loop over all requiered validation layers
            for (const char* layerName : validationLayers) {
                bool layerFound = false;

                // Check if the layer is present
                for (const auto& layerProperties : availableLayers) {
                    if (strcmp(layerName, layerProperties.layerName) == 0) {
                        layerFound = true;
                        break;
                    }
                }

                // Layer wasn't found
                if (!layerFound) {
                    Logger::Log("VK_ERROR - User tried to turn on validation layer, but this wasn't supported on host device.", LogType::LOG_TYPE_ERROR);
                    return false;
                }
            }

            return true;
        }

        void RHI_VK_RenderDevice::GetVKPhysicalDevice()
        {
            // Get the number of devices
            uint32_t deviceCount = 0;
            vkEnumeratePhysicalDevices(m_Instance, &deviceCount, nullptr);

            // Error check for deviice not existing
            if (deviceCount == 0) {
                Logger::Log("VK_ERROR - (device_count == 0)", LogType::LOG_TYPE_ERROR);
                return;
            }

            // allocate vector of devices
            std::vector<VkPhysicalDevice> devices(deviceCount);
            vkEnumeratePhysicalDevices(m_Instance, &deviceCount, devices.data());

            // Loop over all avaiable devices
            for (const auto& device : devices) {

                {
                    // Get total extension count
                    uint32_t extensionCount;
                    vkEnumerateDeviceExtensionProperties(device, nullptr, &extensionCount, nullptr);

                    // Allocate vector of extensions
                    std::vector<VkExtensionProperties> availableExtensions(extensionCount);
                    vkEnumerateDeviceExtensionProperties(device, nullptr, &extensionCount, availableExtensions.data());

                    std::set<std::string> requiredExtensions(deviceExtensions.begin(), deviceExtensions.end());
                    for (const auto& extension : availableExtensions) {
                        requiredExtensions.erase(extension.extensionName);
                    }

                    // Not all requirements are meet
                    if (requiredExtensions.empty() == false)
                        continue;
                }

                {
                    // Get capabilities
                    VkSurfaceCapabilitiesKHR capabilities;
                    vkGetPhysicalDeviceSurfaceCapabilitiesKHR(device, m_Surface, &capabilities);

                    // Get formatCount
                    uint32_t formatCount;
                    vkGetPhysicalDeviceSurfaceFormatsKHR(device, m_Surface, &formatCount, nullptr);

                    std::vector<VkSurfaceFormatKHR> formats;
                    if (formatCount != 0) {
                        formats.resize(formatCount);
                        vkGetPhysicalDeviceSurfaceFormatsKHR(device, m_Surface, &formatCount, formats.data());
                    }

                    uint32_t presentModeCount;
                    vkGetPhysicalDeviceSurfacePresentModesKHR(device, m_Surface, &presentModeCount, nullptr);

                    std::vector<VkPresentModeKHR> presentModes;
                    if (presentModeCount != 0) {
                        presentModes.resize(presentModeCount);
                        vkGetPhysicalDeviceSurfacePresentModesKHR(device, m_Surface, &presentModeCount, presentModes.data());
                    }

                    // Not all requirements are meet
                    if (formats.empty() || presentModes.empty())
                        continue;
                }

                {
                    QueueFamilyIndices indices = FindQueueFamilies(device, m_Surface);
                    if (indices.isComplete() == false)
                        continue;
                }

                // Set device
                //m_PhysicalDevice = device;
                return;
            }

           // if (m_PhysicalDevice == VK_NULL_HANDLE)
           //     Logger::Log("VK_ERROR - No physical device found.", LogType::LOG_TYPE_ERROR);
        }


        // TODO:: Probably remove this function
        QueueFamilyIndices FindQueueFamilies(VkPhysicalDevice device, VkSurfaceKHR _surface) 
        {
            QueueFamilyIndices indices;

            uint32_t queueFamilyCount = 0;
            vkGetPhysicalDeviceQueueFamilyProperties(device, &queueFamilyCount, nullptr);

            std::vector<VkQueueFamilyProperties> queueFamilies(queueFamilyCount);
            vkGetPhysicalDeviceQueueFamilyProperties(device, &queueFamilyCount, queueFamilies.data());

            int i = 0;
            for (const auto& queueFamily : queueFamilies) {
                if (queueFamily.queueFlags & VK_QUEUE_GRAPHICS_BIT) {
                    indices.graphicsFamily = i;
                }

                VkBool32 presentSupport = false;
                vkGetPhysicalDeviceSurfaceSupportKHR(device, i, _surface, &presentSupport);

                if (presentSupport) {
                    indices.presentFamily = i;
                }

                if (indices.isComplete()) {
                    break;
                }

                i++;
            }
            //i = 0;
            //for (const auto& queueFamily : queueFamilies) {
            //    if (queueFamily.queueFlags & VK_QUEUE_GRAPHICS_BIT && queueFamily.queueFlags & VK_QUEUE_COMPUTE_BIT && queueFamily.queueFlags & VK_QUEUE_TRANSFER_BIT)
            //        printf("General purpose QUEUE: %i, %i\n", queueFamily.queueCount, i);
            //    if (queueFamily.queueFlags & VK_QUEUE_GRAPHICS_BIT)
            //        printf("Graphics purpose QUEUE: %i, %i\n", queueFamily.queueCount, i);
            //    if (queueFamily.queueFlags & VK_QUEUE_COMPUTE_BIT)
            //        printf("Compute purpose QUEUE: %i, %i\n", queueFamily.queueCount, i);
            //    if (queueFamily.queueFlags & VK_QUEUE_TRANSFER_BIT)
            //        printf("Transfer purpose QUEUE: %i, %i\n", queueFamily.queueCount, i);
            //
            //    i++;
            //}
            return indices;
        }
    }
}