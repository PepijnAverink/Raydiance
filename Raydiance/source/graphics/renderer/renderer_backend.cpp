#include "./pch.h"
#include "./graphics/renderer/renderer_backend.h"

// Core includes
#include "./core/window/window.h"

namespace Raydiance
{
	namespace Graphics
	{
		// Static instance
		static RendererBackend* s_RenderBackend = nullptr;

		RendererBackend* RendererBackend::Create(Window* _window)
		{
			s_RenderBackend = new RendererBackend(_window);
			return s_RenderBackend;
		}

		void RendererBackend::Destroy()
		{
			delete s_RenderBackend;
		}

		void RendererBackend::SubmitCommandBuffer(CommandBuffer* _commandBuffer, RHI_Fence* _fence)
		{
			s_RenderBackend->m_CommandQueue->SubmitCommandBuffer(_commandBuffer, _fence);
		}

		uint32_t RendererBackend::AquireNewFrame(RHI_Fence* _fence)
		{
			return s_RenderBackend->m_Swapchain->AquireNewImage(s_RenderBackend->m_CommandQueue, _fence);
		}

		void RendererBackend::Present()
		{
			s_RenderBackend->m_Swapchain->Present(s_RenderBackend->m_CommandQueue);
		}

		void RendererBackend::OnResize(const uint32_t _width, const uint32_t _height)
		{
			s_RenderBackend->m_Swapchain->Resize(s_RenderBackend->m_CommandQueue, _width, _height);
			s_RenderBackend->m_ClientWidth = s_RenderBackend->m_Swapchain->GetWidth();
			s_RenderBackend->m_ClientHeight = s_RenderBackend->m_Swapchain->GetHeight();
		}

		uint32_t RendererBackend::GetClientWidth()
		{
			return s_RenderBackend->m_ClientWidth;
		}

		uint32_t RendererBackend::GetClientHeight()
		{
			return s_RenderBackend->m_ClientHeight;
		}

		uint32_t RendererBackend::GetBackbufferCount()
		{
			return s_RenderBackend->m_BackbufferCount;
		}

		uint32_t RendererBackend::GetCurrntBackbufferIndex()
		{
			return s_RenderBackend->m_Swapchain->GetCurrentBufferIndex();
		}

		RendererBackend::RendererBackend(Window* _window)
		{
			// RenderDevice
			// --------------------------------------------------------------------
			Raydiance::Graphics::RHI_RenderDeviceDescriptor renderDeviceDesc;
			renderDeviceDesc.DebugMode			= Raydiance::Graphics::RHI_DebugMode::RHI_DEBUG_MODE_DEBUG_ONLY;
			renderDeviceDesc.NativeWindowHandle = _window->GetWindowHandlePtr();


			RHI_GraphicsAPI api = RHI_GraphicsAPI::RHI_GRAPHICS_API_VULKAN;
			Result res = RHI_RenderDevice::Create(api);
			if (CheckError(res) == true)
			{
				Logger::Log("Failed to create the 'RHI_RenderDevice' object.", LogType::LOG_TYPE_ERROR);
				Logger::Log("No further evidence what went wrong, please see earlier logs.", LogType::LOG_TYPE_ERROR);
				return;
			}
			RHI_RenderDevice::Get().Initialize(renderDeviceDesc);

			uint32 adapterCount = 0;
			RHI_RenderDevice::Get().GetAdapterCount(adapterCount);

			for (int i = 0; i < adapterCount; i++)
			{
				RHI_RenderDevice::Get().GetAdapter(i);
			}

			// CommandQueue
			// --------------------------------------------------------------------
			Graphics::CommandQueueDescriptor commandQueueDesc;
			commandQueueDesc.Name = "GeneralCommandQueue";
			commandQueueDesc.Type = CommandQueueType::COMMAND_QUEUE_TYPE_GRAPHICS;

			m_CommandQueue = RHI_RenderDevice::Get().CreateCommandQueue(&commandQueueDesc);

			// Swapchain
			// --------------------------------------------------------------------
			RHI_SwapchainDescriptor swapchainDesc;
			swapchainDesc.Name   = "Swapchain";
			swapchainDesc.Window = _window;
			swapchainDesc.Width  = _window->GetWidth();
			swapchainDesc.Height = _window->GetHeight();

			// Create swapchain and query dimensions
			m_Swapchain			 = RHI_RenderDevice::Get().CreateSwapchain(m_CommandQueue, &swapchainDesc);
			m_ClientWidth		 = m_Swapchain->GetWidth();
			m_ClientHeight		 = m_Swapchain->GetHeight();
			m_BackbufferCount	 = m_Swapchain->GetBufferCount();
		}

		RendererBackend::~RendererBackend()
		{
			delete m_Swapchain;
			delete m_CommandQueue;

			// Destroying the 'RHI_RenderDevice' object should happen after all other graphics objects are destroyed, 
			//	since they might be using the 'RHI_RenderDevice' object internally.
			RHI_RenderDevice::Destroy();
		}
	}
}