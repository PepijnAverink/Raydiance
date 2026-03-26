#include "./pch.h"

#include "./core/error/assert.h"

// Graphics includes
#include "./graphics/RHI/RHI_render_device.h"
#include "./graphics/RHI_api/vk/RHI_VK_render_device.h"
#include "./graphics/RHI_api/dx12/RHI_DX12_render_device.h"


namespace Raydiance
{
	namespace Graphics
	{
		// Static instance
		static std::shared_ptr<RHI_RenderDevice> s_RenderDevice = nullptr;

		Result RHI_RenderDevice::Create(RHI_GraphicsAPI _api)
		{
			// Check for an already existing device
			if (s_RenderDevice != nullptr)
			{
				Logger::Log("Cannot create a new RHI_RenderDevice object while the old device is still active.", LogType::LOG_TYPE_ERROR);
				return Result::RESULT_ERROR;
			}

			// VULKAN-API
			if (_api == RHI_GraphicsAPI::RHI_GRAPHICS_API_VULKAN)
				s_RenderDevice = std::make_shared<RHI_VK_RenderDevice>();
			// DIRECTX12-API
			if (_api == RHI_GraphicsAPI::RHI_GRAPHICS_API_DIRECTX12)
				s_RenderDevice = std::make_shared<RHI_DX12_RenderDevice>();


			// Return
			if (s_RenderDevice != nullptr)
				return Result::RESULT_GOOD;

			// Error checking and logging
			Logger::Log(std::format("No abstraction of 'RenderDevice' object found for: {}", RHI_GraphicsApiToString(_api)), LogType::LOG_TYPE_ERROR);
			return Result::RESULT_ERROR;
		}

		Result RHI_RenderDevice::Destroy()
		{
			// Error check for valid instance
			if (s_RenderDevice == nullptr)
			{
				Logger::Log("Failed to destroy static instance of 'RHI_RenderDevice' object, no valid instance was active.", LogType::LOG_TYPE_ERROR);
				return Result::RESULT_ERROR;
			}

			// Destroy
			s_RenderDevice.reset();
			return Result::RESULT_GOOD;
		}

		RHI_RenderDevice::RHI_RenderDevice(RHI_GraphicsAPI _api)
			// Assign the graphics API of the 'RHI_RenderDevice' object.
			: m_API(_api)
		{ }

		RHI_RenderDevice::~RHI_RenderDevice()
		{ }

		Result RHI_RenderDevice::Initialize(const RHI_RenderDeviceDescriptor& _renderDeviceDescriptor)
		{
			// Set the debug mode
			m_DebugMode = _renderDeviceDescriptor.DebugMode;
			CorrectDebugMode();

			return Result::RESULT_GOOD;
		}

		RHI_RenderDevice& RHI_RenderDevice::Get()
		{
			RA_ASSERT_MSG(s_RenderDevice != nullptr, "User tried to get instance of RHI_RenderDevice, while no valid isntance was currenly active.");
			return *s_RenderDevice;
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
#if defined(_DEBUG)
				m_DebugModeEnabled = true;
#else
				m_DebugModeEnabled = false;
#endif
				break;
			}
		}
	}
}