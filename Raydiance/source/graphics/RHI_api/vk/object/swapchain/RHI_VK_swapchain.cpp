 // Graphics includes 
#include "./graphics/RHI_api/vk/RHI_VK_render_device.h"
#include "./graphics/RHI_api/vk/object/swapchain/RHI_VK_swapchain.h"
#include "./graphics/RHI_api/vk/object/command/RHI_VK_command_queue.h"
#include "./graphics/RHI_api/vk/resource/texture/RHI_VK_texture2D.h"

#include "./graphics/RHI_api/vk/RHI_VK_adapter.h"

#include "./graphics/RHI_api/vk/resource/RHI_VK_resource_format.h"

#include "./graphics/RHI_api/vk/object/sync/RHI_VK_fenceCPU.h"

#include <algorithm>
#include <vector>

namespace Raydiance
{
	namespace Graphics
	{
		RHI_VK_Swapchain::RHI_VK_Swapchain()
			: RHI_Swapchain()
		{ }

		RHI_VK_Swapchain::~RHI_VK_Swapchain()
		{
			// Destroy the swapchain
			vkDestroySwapchainKHR(((RHI_VK_RenderDevice*)RHI_RenderDevice::Get())->GetVKDevice(), m_SwapChainObj, nullptr);		
		}

		const Result RHI_VK_Swapchain::Initialize(RHI_VK_RenderDevice* _RHI_RenderDevice, RHI_CommandQueue* _commandQueue, const RHI_SwapchainDescriptor* _swapchainDescriptor)
		{
			Result result = RHI_Swapchain::Initialize(_swapchainDescriptor);
			if (CheckError(result) == true)
			{
				// Log error
				return result;
			}

			VkSurfaceCapabilitiesKHR capabilities;
			std::vector<VkSurfaceFormatKHR> formats;
			std::vector<VkPresentModeKHR> presentModes;

			vkGetPhysicalDeviceSurfaceCapabilitiesKHR(((RHI_VK_Adapter*)RHI_RenderDevice::Get()->RHI_GetAdapter())->GetPhysicalDevice(), _RHI_RenderDevice->GetVKSurface(), &capabilities);

			uint32_t formatCount;
			vkGetPhysicalDeviceSurfaceFormatsKHR(((RHI_VK_Adapter*)RHI_RenderDevice::Get()->RHI_GetAdapter())->GetPhysicalDevice(), _RHI_RenderDevice->GetVKSurface(), &formatCount, nullptr);

			if (formatCount != 0) {
				formats.resize(formatCount);
				vkGetPhysicalDeviceSurfaceFormatsKHR(((RHI_VK_Adapter*)RHI_RenderDevice::Get()->RHI_GetAdapter())->GetPhysicalDevice(), _RHI_RenderDevice->GetVKSurface(), &formatCount, formats.data());
			}

			uint32_t presentModeCount;
			vkGetPhysicalDeviceSurfacePresentModesKHR(((RHI_VK_Adapter*)RHI_RenderDevice::Get()->RHI_GetAdapter())->GetPhysicalDevice(), _RHI_RenderDevice->GetVKSurface(), &presentModeCount, nullptr);

			if (presentModeCount != 0) {
				presentModes.resize(presentModeCount);
				vkGetPhysicalDeviceSurfacePresentModesKHR(((RHI_VK_Adapter*)RHI_RenderDevice::Get()->RHI_GetAdapter())->GetPhysicalDevice(), _RHI_RenderDevice->GetVKSurface(), &presentModeCount, presentModes.data());
			}

			// Create BackBuffer's
			m_RenderTargets = new RHI_Texture2D * [m_BufferCount];

			CreateSwapchain(_RHI_RenderDevice, _commandQueue);

			return Result::RESULT_GOOD;
		}

		void RHI_VK_Swapchain::Resize(RHI_RenderDevice* _RHI_RenderDevice, RHI_CommandQueue* _commandQueue, RHI_FenceCPU* _fence, const uint32_t _width, const uint32_t _height)
		{
		}

		uint32_t RHI_VK_Swapchain::AquireNewFrame(RHI_CommandQueue* _commandQueue, RHI_FenceCPU* _fence)
		{
			VkResult result = vkAcquireNextImageKHR(((RHI_VK_RenderDevice*)RHI_RenderDevice::Get())->GetVKDevice(), m_SwapChainObj, UINT64_MAX, VK_NULL_HANDLE, _fence == nullptr ? VK_NULL_HANDLE : ((RHI_VK_FenceCPU*)_fence)->GetVKFence(), &m_BufferIndex);
			return m_BufferIndex;
		}

		void RHI_VK_Swapchain::Present(RHI_CommandQueue* _commandQueue)
		{
			VkPresentInfoKHR presentInfo{};
			presentInfo.sType = VK_STRUCTURE_TYPE_PRESENT_INFO_KHR;
			presentInfo.waitSemaphoreCount = 0;
			presentInfo.swapchainCount = 1;
			presentInfo.pSwapchains = &m_SwapChainObj;
			presentInfo.pImageIndices = &m_BufferIndex;

			VkResult result = vkQueuePresentKHR(((RHI_VK_CommandQueue*)_commandQueue)->GetVKQueue(), &presentInfo);

			if (result == VK_ERROR_OUT_OF_DATE_KHR) {
				Logger::Log("Swapchain out of date.", LogLevel::LOG_LEVEL_WARNING);
			}
		}

		void RHI_VK_Swapchain::CreateSwapchain(RHI_VK_RenderDevice* _RHI_RenderDevice, RHI_CommandQueue* _commandQueue)
		{
			// Capabilites
			VkSurfaceCapabilitiesKHR capabilities;
			vkGetPhysicalDeviceSurfaceCapabilitiesKHR(((RHI_VK_Adapter*)_RHI_RenderDevice->RHI_GetAdapter())->GetPhysicalDevice(), _RHI_RenderDevice->GetVKSurface(), &capabilities);

			std::vector<VkSurfaceFormatKHR> formats;
			std::vector<VkPresentModeKHR> presentModes;

			uint32_t formatCount;
			vkGetPhysicalDeviceSurfaceFormatsKHR(((RHI_VK_Adapter*)_RHI_RenderDevice->RHI_GetAdapter())->GetPhysicalDevice(), _RHI_RenderDevice->GetVKSurface(), &formatCount, nullptr);

			if (formatCount != 0) {
				formats.resize(formatCount);
				vkGetPhysicalDeviceSurfaceFormatsKHR(((RHI_VK_Adapter*)_RHI_RenderDevice->RHI_GetAdapter())->GetPhysicalDevice(), _RHI_RenderDevice->GetVKSurface(), &formatCount, formats.data());
			}

			uint32_t presentModeCount;
			vkGetPhysicalDeviceSurfacePresentModesKHR(((RHI_VK_Adapter*)_RHI_RenderDevice->RHI_GetAdapter())->GetPhysicalDevice(), _RHI_RenderDevice->GetVKSurface(), &presentModeCount, nullptr);

			if (presentModeCount != 0) {
				presentModes.resize(presentModeCount);
				vkGetPhysicalDeviceSurfacePresentModesKHR(((RHI_VK_Adapter*)_RHI_RenderDevice->RHI_GetAdapter())->GetPhysicalDevice(), _RHI_RenderDevice->GetVKSurface(), &presentModeCount, presentModes.data());
			}

			VkSurfaceFormatKHR format = formats[0];
			for (const auto& availableFormat : formats) {
				if (availableFormat.format == ResolveVKResourceFormat(m_ResourceFormat)) { //&& availableFormat.colorSpace == VK_COLOR_SPACE_SRGB_NONLINEAR_KHR) {
					format = availableFormat;
				}
			}

			VkPresentModeKHR mode = VK_PRESENT_MODE_FIFO_KHR;
			for (const auto& availablePresentMode : presentModes) {
				if (m_VSync == true) // VSync enabled
				{
					if (availablePresentMode == VK_PRESENT_MODE_FIFO_KHR) {
						mode = availablePresentMode;
					}
				}
				else // VSync disabled
				{
					if (availablePresentMode == VK_PRESENT_MODE_IMMEDIATE_KHR) {
						mode = availablePresentMode;
					}
				}
			}

			VkExtent2D extend;
			if (capabilities.currentExtent.width != UINT32_MAX) {
				extend = capabilities.currentExtent;
			}
			else {

				VkExtent2D actualExtent = {
					static_cast<uint32_t>(m_Width),
					static_cast<uint32_t>(m_Height)
				};

				actualExtent.width = std::clamp(actualExtent.width, capabilities.minImageExtent.width, capabilities.maxImageExtent.width);
				actualExtent.height = std::clamp(actualExtent.height, capabilities.minImageExtent.height, capabilities.maxImageExtent.height);
				extend = actualExtent;

				m_Width = extend.width;
				m_Height = extend.height;
			}

			uint32_t imageCount = capabilities.minImageCount;
			if (capabilities.maxImageCount > 0 && imageCount > capabilities.maxImageCount)
				imageCount = capabilities.maxImageCount;
			if (imageCount < m_BufferCount && m_BufferCount < capabilities.maxImageCount)
				imageCount = m_BufferCount;

			m_Format = format.format;

			VkSwapchainCreateInfoKHR createInfo{};
			createInfo.sType = VK_STRUCTURE_TYPE_SWAPCHAIN_CREATE_INFO_KHR;
			createInfo.surface = _RHI_RenderDevice->GetVKSurface();

			createInfo.minImageCount = imageCount;
			createInfo.imageFormat = m_Format;
			createInfo.imageColorSpace = format.colorSpace;
			createInfo.imageExtent = extend;
			createInfo.imageArrayLayers = 1;
			createInfo.imageUsage = VK_IMAGE_USAGE_COLOR_ATTACHMENT_BIT | VK_IMAGE_USAGE_TRANSFER_DST_BIT;
			createInfo.imageSharingMode = VK_SHARING_MODE_EXCLUSIVE;

			uint32_t queueFamilyIndices[] = { ((RHI_VK_CommandQueue*)_commandQueue)->GetVKFamilyID() };


			//createInfo.imageSharingMode = VK_SHARING_MODE_CONCURRENT;
			createInfo.queueFamilyIndexCount = 1;
			createInfo.pQueueFamilyIndices = queueFamilyIndices;
			createInfo.preTransform = capabilities.currentTransform;
			createInfo.compositeAlpha = VK_COMPOSITE_ALPHA_OPAQUE_BIT_KHR;
			createInfo.presentMode = mode;
			createInfo.clipped = VK_TRUE;

			if (vkCreateSwapchainKHR(_RHI_RenderDevice->GetVKDevice(), &createInfo, nullptr, &m_SwapChainObj) != VK_SUCCESS)
				Logger::Log("VK_ERROR - Failed to create 'Swapchain' object.", LogLevel::LOG_LEVEL_ERROR);

			std::vector<VkImage> images;
			vkGetSwapchainImagesKHR(_RHI_RenderDevice->GetVKDevice(), m_SwapChainObj, &imageCount, nullptr);
			images.resize(imageCount);
			vkGetSwapchainImagesKHR(_RHI_RenderDevice->GetVKDevice(), m_SwapChainObj, &imageCount, images.data());
			m_BufferCount = imageCount;

			RHI_Texture2DDescriptor textureDesc = {};
			textureDesc.Width = m_Width;
			textureDesc.Height = m_Height;
			textureDesc.Format = ResolveResourceFormat(format.format);

			for (uint32_t i = 0; i < m_BufferCount; i++)
			{
				textureDesc.Name = "SwapchainImage" + std::to_string(i);
				m_RenderTargets[i] = ((RHI_VK_RenderDevice*)_RHI_RenderDevice)->CreateTexture2DFromVkImage(images[i], &textureDesc);
			}
		}
	}
}