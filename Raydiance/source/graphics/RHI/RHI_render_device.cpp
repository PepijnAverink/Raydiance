//#include "./graphics/RHI/render_device.h"
//#include "./graphics/RHI_api/vk/vk_render_device.h"
//
//#include "./core/error/logger.h"
#include "core/stdafx.h"

// Graphics includes
#include "./graphics/RHI/RHI_render_device.h"
#include "./graphics/RHI_api/vk/vk_render_device.h"

namespace Raydiance
{

	namespace Graphics
	{
		// Static instance
		static std::shared_ptr<RHI_RenderDevice> s_RenderDevice = nullptr;

		std::shared_ptr<RHI_RenderDevice> RHI_RenderDevice::Create(RHI_GraphicsAPI _api)
		{
			// VULKAN-API
			if (_api == RHI_GraphicsAPI::RHI_GRAPHICS_API_VULKAN)
				s_RenderDevice = std::make_shared<VKRenderDevice>();


			// Return
			if (s_RenderDevice != nullptr)
				return s_RenderDevice;

			// Error checking and logging
			Logger::Log(std::format("No abstraction of 'RenderDevice' object found for: {}", RHI_GraphicsApiToString(_api)), LogType::LOG_TYPE_ERROR);
			return nullptr;
		}

		std::shared_ptr<RHI_RenderDevice> RHI_RenderDevice::Get()
		{
			return s_RenderDevice;
		}

		RHI_RenderDevice::RHI_RenderDevice()
		{ }

		RHI_RenderDevice::~RHI_RenderDevice()
		{ }

		Raydiance::Result RHI_RenderDevice::Initialize(const Raydiance::Graphics::RHI_RenderDeviceDescriptor& _renderDeviceDescriptor)
		{
			// Set the debug mode
			m_DebugMode = _renderDeviceDescriptor.DebugMode;
			CorrectDebugMode();

			return Raydiance::Result::RESULT_GOOD;
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