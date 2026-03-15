//#include "./graphics/RHI/render_device.h"
//#include "./graphics/RHI_api/vk/vk_render_device.h"
//
//#include "./core/error/logger.h"
#include "core/stdafx.h"

#include "./core/error/assert.h"

// Graphics includes
#include "./graphics/RHI/RHI_render_device.h"
#include "./graphics/RHI_api/vk/vk_render_device.h"

namespace Raydiance
{

	namespace Graphics
	{
		// Static instance
		static std::shared_ptr<RHI_RenderDevice> s_RenderDevice = nullptr;

		Result RHI_RenderDevice::Create(RHI_GraphicsAPI _api)
		{
			if (s_RenderDevice == nullptr)
			// VULKAN-API
			if (_api == RHI_GraphicsAPI::RHI_GRAPHICS_API_VULKAN)
				s_RenderDevice = std::make_shared<VKRenderDevice>();

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

		Result RHI_RenderDevice::Initialize(const Raydiance::Graphics::RHI_RenderDeviceDescriptor& _renderDeviceDescriptor)
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
			case Raydiance::Graphics::RHI_DebugMode::RHI_DEBUG_MODE_ALWAYS:
				m_DebugEnabled = true;
				break;
			case Raydiance::Graphics::RHI_DebugMode::RHI_DEBUG_MODE_NEVER:
				m_DebugEnabled = false;
				break;
			case Raydiance::Graphics::RHI_DebugMode::RHI_DEBUG_MODE_DEBUG_ONLY:
#if defined(_DEBUG)
				m_DebugEnabled = true;
#else
				m_DebugEnabled = false;
#endif
				break;
			}
		}
	}
}