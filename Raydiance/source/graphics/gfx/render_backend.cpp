#include "./pch.h"
#include "./graphics/gfx/render_backend.h"


// Core includes
#include "./core/error/assert.h"
#include "./core/error/logger.h"


namespace Raydiance
{
	namespace Graphics
	{
		// Static instance
		static RenderBackend* s_RenderBackend = nullptr;


		[[nodiscard]]
		Result RenderBackend::Create(Window* _window)
		{
			return Create(_window, DEFAULT_GRAPHICS_API);
		}


		[[nodiscard]]
		Result RenderBackend::Create(Window* _window, const RHI_GraphicsAPI _graphicsAPI)
		{
			s_RenderBackend = new RenderBackend();
			s_RenderBackend->Initialize(_window, _graphicsAPI);

			return Result::RESULT_GOOD;
		}


		[[nodiscard]]
		Result RenderBackend::Destroy(void)
		{
			delete s_RenderBackend;
			s_RenderBackend = nullptr;

			return Result::RESULT_GOOD;
		}


		RenderBackend::RenderBackend(void)
		{ }


		RenderBackend::~RenderBackend(void)
		{
			delete m_Swapchain;
			delete m_CommandQueue;
			RHI_RenderDevice::Destroy();
		}


		Result RenderBackend::Initialize(Window* _window, const RHI_GraphicsAPI _graphicsAPI)
		{
			// Setup RHI_RenderDevice
			// ---------------------------------------------------------
			{
				// Creating the RHI_RenderDevice object
				m_RenderDevice = RHI_RenderDevice::Create(_graphicsAPI);


				// RHI_RenderDevice descriptor
				RHI_RenderDeviceDescriptor renderDeviceDesc = { };
				renderDeviceDesc.NativeWindowHandle = _window->GetWindowHandlePtr();
				renderDeviceDesc.DebugMode			= RHI_DebugMode::RHI_DEBUG_MODE_DEBUG_ONLY;
				renderDeviceDesc.CommandQueues		= { RHI_CommandQueueAllocation(RHI_CommandQueueType::RHI_COMMAND_QUEUE_TYPE_GRAPHICS, 1), };

				// Initializing using the descriptor
				m_RenderDevice->Initialize(&renderDeviceDesc);


				// Get the number of adapters present in the current system
				uint32 adapterCount = 0;
				m_RenderDevice->GetAdapterCount(adapterCount);


				// Error check, for 0 adapters present.
				if (adapterCount == 0)
				{
					Logger::Log("No hardware or software adapters are present in the current system, while trying to setup the 'RHI_RenderDevice' object.", LogLevel::LOG_LEVEL_ERROR);
					return Result::RESULT_ERROR;
				}


				// Loop over the adapters to select the prefered one
				RHI_Adapter* preferedAdapter = nullptr;
				for (uint32 i = 0; i < adapterCount; i++)
				{
					// Get a temporary adapter for adapter properties
					RHI_Adapter* tempAdapter = nullptr;
					m_RenderDevice->GetAdapter(i, &tempAdapter);


					// Assign if no adapter has been assigned yet
					if (preferedAdapter == nullptr)
					{
						preferedAdapter = tempAdapter;
						continue;
					}


					// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
					// 1. We prefer discrete GPU's over integrated GPU's.
					// 2. We also prefer GPU's with a higher VRam.       
					// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
					if ((preferedAdapter->GetType() == RHI_AdapterType::RHI_ADAPTER_TYPE_INTEGRATED && tempAdapter->GetType() == RHI_AdapterType::RHI_ADAPTER_TYPE_DISCRETE) ||
						(tempAdapter->GetVRam() > preferedAdapter->GetVRam() && (preferedAdapter->GetType() == RHI_AdapterType::RHI_ADAPTER_TYPE_INTEGRATED || tempAdapter->GetType() == RHI_AdapterType::RHI_ADAPTER_TYPE_DISCRETE)))
					{ 
						delete preferedAdapter;
						preferedAdapter = tempAdapter;
					} else {
						delete tempAdapter;
					}
				}

				// Check if a valid adapter exist
				if (preferedAdapter == nullptr)
				{
					Logger::Log("No valid RHI_Adapter object was found, something went wrong.", LogLevel::LOG_LEVEL_ERROR);
					return Result::RESULT_ERROR;
				}

				// Link the choosen adapter
				Logger::Log(std::format("Adapter linked to deive: {}", preferedAdapter->GetName()), LogLevel::LOG_LEVEL_INFO);
				m_RenderDevice->LinkAdapter(preferedAdapter);
			}


			// Setup RHI_CommandQueue
			// ---------------------------------------------------------
			{
				// RHI_CommandQueue descriptor
				RHI_CommandQueueDescriptor commandQueueDesc = { };
				commandQueueDesc.Name = "RB_CommandQueue";
				commandQueueDesc.Type = RHI_CommandQueueType::RHI_COMMAND_QUEUE_TYPE_GRAPHICS;

				// Creating the RHI_CommandQueue object
				m_CommandQueue = m_RenderDevice->RHI_CreateCommandQueue(&commandQueueDesc);
			}


			// Setup RHI_Swapchain
			// ---------------------------------------------------------
			{
				// Query for supported swapchain formats
				std::vector<RHI_ResourceFormat> supportedFormats;
				m_RenderDevice->CheckSwapchainCommonResourceFormatsSupport(supportedFormats);


				// Error check support formats
				if (supportedFormats.size() < 1)
				{
					Logger::Log("No commonly supported swapchain formats were detected.", LogLevel::LOG_LEVEL_ERROR);
					Logger::Log("Cannot create swapchain correctly.", LogLevel::LOG_LEVEL_ERROR);
					return Result::RESULT_ERROR;
				}


				// RHI_Swapchain descriptor
				RHI_SwapchainDescriptor swapchainDesc = { };
				swapchainDesc.Name				 = "RB_Swapchain";
				swapchainDesc.NativeWindowHandle = _window->GetWindowHandlePtr();
				swapchainDesc.Width				 = _window->GetClientWidth();
				swapchainDesc.Height			 = _window->GetClientHeight();
				// TODO:: Maybe somehow expose this to a higher level
				swapchainDesc.Format			 = supportedFormats[0];
				// TODO:: For sure somehow expose this to a higher level
				swapchainDesc.BufferCount		 = 2;
				swapchainDesc.VSync				 = true;
			

				// Creating the RHI_Swapchain object
				m_Swapchain = m_RenderDevice->RHI_CreateSwapchain(m_CommandQueue, &swapchainDesc);
			}

			return Result::RESULT_GOOD;
		}


		void RenderBackend::SubmitCommandBuffer(RHI_CommandBuffer* _commandBuffer, RHI_FenceCPU* _fence)
		{
			RA_ASSERT_MSG(s_RenderBackend != nullptr, "User tried to use RenderBackend functionality before initialization.");
			s_RenderBackend->m_CommandQueue->Execute(_commandBuffer, _fence);
		}



		uint32 RenderBackend::AquireNewFrame(RHI_FenceCPU* _fence)
		{
			RA_ASSERT_MSG(s_RenderBackend != nullptr, "User tried to use RenderBackend functionality before initialization.");
			return s_RenderBackend->m_Swapchain->AquireNewFrame(s_RenderBackend->m_CommandQueue, _fence);
		}


		// TODO:: Look into using a fence here 
		void RenderBackend::Present(void)
		{
			RA_ASSERT_MSG(s_RenderBackend != nullptr, "User tried to use RenderBackend functionality before initialization.");
			s_RenderBackend->m_Swapchain->Present(s_RenderBackend->m_CommandQueue);
		}


		RHI_GraphicsAPI RenderBackend::GetAPI(void)
		{
			RA_ASSERT_MSG(s_RenderBackend != nullptr, "User tried to use RenderBackend functionality before initialization.");
			return s_RenderBackend->m_RenderDevice->RHI_GetGraphicsAPI();
		}

		[[nodiscard]]
		RHI_RenderDevice* RenderBackend::GetRenderDevice(void)
		{
			RA_ASSERT_MSG(s_RenderBackend != nullptr, "User tried to use RenderBackend functionality before initialization.");
			return s_RenderBackend->m_RenderDevice;
		}


		[[nodiscard]]
		RHI_Swapchain* RenderBackend::GetSwapchain(void)
		{
			RA_ASSERT_MSG(s_RenderBackend != nullptr, "User tried to use RenderBackend functionality before initialization.");
			return s_RenderBackend->m_Swapchain;
		}
	}
}