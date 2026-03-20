#include "./pch.h"
#include "./graphics/RHI_api/vk/object/swapchain/RHI_VK_swapchain.h"

// Graphics includes
#include "./graphics/RHI_api/vk/RHI_VK_adapter.h"

#include "./graphics/RHI_api/vk/object/sync/RHI_VK_fenceCPU.h"
#include "./graphics/RHI_api/vk/object/command/vk_command_queue.h"

#include "./graphics/RHI_api/vk/resource/vk_resource_format.h"
#include "./graphics/RHI_api/vk/resource/texture/vk_texture2D.h"

// Core includes
#include "./core/window/window.h"

namespace Raydiance
{
	namespace Graphics
	{
		RHI_VK_Swapchain::RHI_VK_Swapchain()
			: RHI_Swapchain()
		{ }

		RHI_VK_Swapchain::~RHI_VK_Swapchain()
		{
			for (uint32_t i = 0; i < m_BufferCount; i++)
				((VKTexture2D*)m_Textures[i])->FreeImageView();

			vkDestroySwapchainKHR(static_cast<RHI_VK_RenderDevice&>(RHI_RenderDevice::Get()).GetDevice(), m_SwapChainObj, nullptr);
		}

		const Result RHI_VK_Swapchain::Initialize(const RHI_VK_RenderDevice& _renderDevice, const RHI_CommandQueue& _commandQueue, const RHI_SwapchainDescriptor& _swapchainDescriptor)
		{
			// Object storing the result of all interal functions.
			Result result = Result::RESULT_INVALID;

			// Initialize the base class of the RHI_Swapchain graphics object class,
			// And error check the result.
			// --------------------------------------------------------------------------
			result = RHI_Swapchain::Initialize(_swapchainDescriptor);
			if (CheckError(result) == true)
			{
				// When result is RESULT_ERROR || RESULT_FATAL.
				Logger::Log("Error while intitializing the base class of the 'RHI_Swapchain' object.", LogType::LOG_TYPE_ERROR);
				Logger::Log("No further evidence what went wrong, please see earlier logs.", LogType::LOG_TYPE_ERROR);
				return result;
			}


			// ==========================================================================
			// The actual VULKAN initialization follows
			// ==========================================================================

			CreateSwapchain(_renderDevice, _commandQueue);
			return Result::RESULT_GOOD;
		}

		void RHI_VK_Swapchain::Resize(const RHI_CommandQueue& _commandQueue, const uint32 _width, const uint32 _height)
		{
			// Cleanup
			for (uint32_t i = 0; i < m_BufferCount; i++)
				((VKTexture2D*)m_Textures[i])->FreeImageView();
			vkDestroySwapchainKHR(static_cast<RHI_VK_RenderDevice&>(RHI_RenderDevice::Get()).GetDevice(), m_SwapChainObj, nullptr);
			m_Textures.clear();

			m_Width = _width;
			m_Height = _height;

			// Create new
			RHI_VK_RenderDevice& device = static_cast<RHI_VK_RenderDevice&>(RHI_RenderDevice::Get());
			CreateSwapchain(device, _commandQueue);
		}

		uint32_t RHI_VK_Swapchain::AquireNewImage(RHI_CommandQueue* _commandQueue, std::shared_ptr<RHI_FenceCPU> _fence)
		{
			VkResult result = vkAcquireNextImageKHR(static_cast<RHI_VK_RenderDevice&>(RHI_RenderDevice::Get()).GetDevice(), m_SwapChainObj, UINT64_MAX, VK_NULL_HANDLE, ((RHI_VK_FenceCPU*)_fence.get())->GetVKFence(), &m_CurrentBufferIndex);
			return m_CurrentBufferIndex;
		}

		void RHI_VK_Swapchain::Present(RHI_CommandQueue* _commandQueue)
		{
			VkPresentInfoKHR presentInfo{};
			presentInfo.sType			   = VK_STRUCTURE_TYPE_PRESENT_INFO_KHR;
			presentInfo.waitSemaphoreCount = 0; // TODO:: Look into semaphores here.
			presentInfo.swapchainCount     = 1;
			presentInfo.pSwapchains        = &m_SwapChainObj;
			presentInfo.pImageIndices      = &m_CurrentBufferIndex;

			vkQueuePresentKHR(((VKCommandQueue*)_commandQueue)->GetVKQueue(), &presentInfo);
		}

		void RHI_VK_Swapchain::CreateSwapchain(const RHI_VK_RenderDevice& _renderDevice, const RHI_CommandQueue& _commandQueue)
		{
			const auto& physicalDevice = static_cast<const RHI_VK_Adapter&>(_renderDevice.GetActiveAdapter()).GetPhysicalDevice();

			// Capabilites
			VkSurfaceCapabilitiesKHR capabilities;
			vkGetPhysicalDeviceSurfaceCapabilitiesKHR(physicalDevice, _renderDevice.GetVKSurface(), &capabilities);

			std::vector<VkSurfaceFormatKHR> formats;
			std::vector<VkPresentModeKHR> presentModes;

			uint32_t formatCount;
			vkGetPhysicalDeviceSurfaceFormatsKHR(physicalDevice, _renderDevice.GetVKSurface(), &formatCount, nullptr);

			if (formatCount != 0) {
				formats.resize(formatCount);
				vkGetPhysicalDeviceSurfaceFormatsKHR(physicalDevice, _renderDevice.GetVKSurface(), &formatCount, formats.data());
			}

			uint32_t presentModeCount;
			vkGetPhysicalDeviceSurfacePresentModesKHR(physicalDevice, _renderDevice.GetVKSurface(), &presentModeCount, nullptr);

			if (presentModeCount != 0) {
				presentModes.resize(presentModeCount);
				vkGetPhysicalDeviceSurfacePresentModesKHR(physicalDevice, _renderDevice.GetVKSurface(), &presentModeCount, presentModes.data());
			}

			VkSurfaceFormatKHR format = formats[0];
			for (const auto& availableFormat : formats) {
				if (availableFormat.format == VK_FORMAT_B8G8R8A8_SRGB && availableFormat.colorSpace == VK_COLOR_SPACE_SRGB_NONLINEAR_KHR) {
					format = availableFormat;
				}
			}

			VkPresentModeKHR mode = VK_PRESENT_MODE_FIFO_KHR;
			for (const auto& availablePresentMode : presentModes) {
				if (availablePresentMode == VK_PRESENT_MODE_MAILBOX_KHR) {
					mode = availablePresentMode;
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

			uint32_t imageCount = capabilities.minImageCount + 1;
			if (capabilities.maxImageCount > 0 && imageCount > capabilities.maxImageCount) {
				imageCount = capabilities.maxImageCount;
			}

			VkSwapchainCreateInfoKHR createInfo{};
			createInfo.sType = VK_STRUCTURE_TYPE_SWAPCHAIN_CREATE_INFO_KHR;
			createInfo.surface = _renderDevice.GetVKSurface();

			createInfo.minImageCount = imageCount;
			createInfo.imageFormat = format.format;
			createInfo.imageColorSpace = format.colorSpace;
			createInfo.imageExtent = extend;
			createInfo.imageArrayLayers = 1;
			createInfo.imageUsage = VK_IMAGE_USAGE_COLOR_ATTACHMENT_BIT;
			createInfo.imageSharingMode = VK_SHARING_MODE_EXCLUSIVE;

			uint32_t queueFamilyIndices[] = { _renderDevice.GetGraphicsQueueID(), _renderDevice.GetPresentQueueID() };

			if (_commandQueue.CheckSupportFlag(COMMAND_QUEUE_SUPPORT_BIT_PRESENT)) {
				createInfo.imageSharingMode = VK_SHARING_MODE_CONCURRENT;
				createInfo.queueFamilyIndexCount = 2;
				createInfo.pQueueFamilyIndices = queueFamilyIndices;
			}
			else {
			}

			createInfo.preTransform = capabilities.currentTransform;
			createInfo.compositeAlpha = VK_COMPOSITE_ALPHA_OPAQUE_BIT_KHR;
			createInfo.presentMode = mode;
			createInfo.clipped = VK_TRUE;

			if (vkCreateSwapchainKHR(_renderDevice.GetDevice(), &createInfo, nullptr, &m_SwapChainObj) != VK_SUCCESS)
				Logger::Log("VK_ERROR - Failed to create 'Swapchain' object.", LogType::LOG_TYPE_ERROR);

			std::vector<VkImage> images;
			vkGetSwapchainImagesKHR(_renderDevice.GetDevice(), m_SwapChainObj, &imageCount, nullptr);
			images.resize(imageCount);
			vkGetSwapchainImagesKHR(_renderDevice.GetDevice(), m_SwapChainObj, &imageCount, images.data());
			m_BufferCount = imageCount;
			m_Format = ResolveResourceFormat(format.format);

			Texture2DDescriptor textureDesc = {};
			textureDesc.Width = m_Width;
			textureDesc.Height = m_Height;
			textureDesc.Format = ResolveResourceFormat(format.format);

			for (uint32_t i = 0; i < m_BufferCount; i++)
			{
				textureDesc.Name = "SwapchainImage" + i;
				m_Textures.push_back(new VKTexture2D(_renderDevice, images[i], &textureDesc));
			}
		}
	}
}