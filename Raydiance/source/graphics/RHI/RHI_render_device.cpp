#include "./pch.h"
#include "./graphics/RHI/RHI_render_device.h"

// VULKAN - includes
#include "./graphics/RHI_api/vk/RHI_VK_render_device.h"

// D3D12 - includes
#include "./graphics/RHI_api/dx12/RHI_DX12_render_device.h"


#include "./core/error/logger.h"

namespace Raydiance
{
	namespace Graphics
	{
		// static instance of the 'RHI_RenderDevice' object, as only one should only exist at a time
		static RHI_RenderDevice* s_RenderDevice = nullptr;

		RHI_RenderDevice* RHI_RenderDevice::Create(RHI_GraphicsAPI _api)
		{
			// Check if the user passed a valid API value
			// -----------------------------------------------------
			if (RHI_GraphicsAPI_IsValid(_api) == false)
			{
				Logger::Log("Failed to create 'RHI_RenderDevice' object, invalid instance of 'RHI_GraphicsAPI' was passed by the user.", LogLevel::LOG_LEVEL_ERROR);
				return nullptr;
			}

			// =====================================================
			// VULKAN API
			// =====================================================
			if (_api == RHI_GraphicsAPI::RHI_GRAPHICS_API_VULKAN)
			{
				s_RenderDevice = new RHI_VK_RenderDevice();
				return s_RenderDevice;
			}

			// =====================================================
			// D3D12 API
			// =====================================================
			if (_api == RHI_GraphicsAPI::RHI_GRAPHICS_API_DIRECTX12)
			{
				s_RenderDevice = new RHI_DX12_RenderDevice();
				return s_RenderDevice;
			}

			Logger::Log("Failed to create 'RHI_RenderDevice' object, unknown reason.", LogLevel::LOG_LEVEL_ERROR);
			return nullptr;
		}

		RHI_RenderDevice* RHI_RenderDevice::Get()
		{
			return s_RenderDevice;
		}

		void RHI_RenderDevice::Destroy()
		{
			if (s_RenderDevice == nullptr)
			{
				Logger::Log("Failed to destroy static instance of 'RHI_RenderDevice' object, no valid instance was active.", LogLevel::LOG_LEVEL_ERROR);
				return;
			}

			// Delete static instance and reset
			delete s_RenderDevice;
			s_RenderDevice = nullptr;
		}

		Result RHI_RenderDevice::Initialize(const RHI_RenderDeviceDescriptor* _renderDeviceDescriptor)
		{
			// Set debug mode and perform utility to correct
			m_DebugMode = _renderDeviceDescriptor->DebugMode;
			CorrectDebugMode();

			// Set the allocation space of the command queues
			m_CommandQueueAllocations = _renderDeviceDescriptor->CommandQueues;

			return Result::RESULT_GOOD;
		}

		RHI_RenderDevice::RHI_RenderDevice()
		{ }

		RHI_RenderDevice::~RHI_RenderDevice()
		{
			delete m_Adapter; m_Adapter = nullptr;
		}

		void RHI_RenderDevice::CorrectDebugMode()
		{
			switch (m_DebugMode)
			{
				case RHI_DebugMode::RHI_DEBUG_MODE_ALWAYS:
					m_DebugModeEnabled = true;
					break;
				case RHI_DebugMode::RHI_DEBUG_MODE_NEVER:
					m_DebugModeEnabled = false;
					break;
				case RHI_DebugMode::RHI_DEBUG_MODE_DEBUG_ONLY:
#if defined(RA_DEBUG)
					m_DebugModeEnabled = true;
#else
					m_DebugModeEnabled = false;
#endif
				break;
			}
		}

		Result RHI_RenderDevice::CheckSwapchainCommonResourceFormatsSupport(std::vector<RHI_ResourceFormat>& _support) const
		{
			bool support = false;
			_support.clear();

			CheckSwapchainResourceFormatSupport(RHI_ResourceFormat::RHI_RESOURCE_FORMAT_B8G8R8A8_UNORM, support);
			if (support == true)
				_support.push_back(RHI_ResourceFormat::RHI_RESOURCE_FORMAT_B8G8R8A8_UNORM);
			CheckSwapchainResourceFormatSupport(RHI_ResourceFormat::RHI_RESOURCE_FORMAT_R8G8B8A8_UNORM, support);
			if (support == true)
				_support.push_back(RHI_ResourceFormat::RHI_RESOURCE_FORMAT_R8G8B8A8_UNORM);

			return Result::RESULT_GOOD;
		}
	}
}