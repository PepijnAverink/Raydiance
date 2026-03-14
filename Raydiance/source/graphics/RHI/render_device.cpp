//#include "./graphics/RHI/render_device.h"
//#include "./graphics/RHI_api/vk/vk_render_device.h"
//
//#include "./core/error/logger.h"
#include "core/stdafx.h"
#include "render_device.h"

namespace Graphics
{
	// Static instance
	static std::shared_ptr<RenderDevice> s_RenderDevice = nullptr;

	std::shared_ptr<RenderDevice> RenderDevice::Create(RHI_GraphicsAPI _api)
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

	std::shared_ptr<RenderDevice> RenderDevice::Get()
	{
		return s_RenderDevice;
	}

	RenderDevice::RenderDevice()
	{ }

	RenderDevice::~RenderDevice()
	{ }

	Raydiance::Result RenderDevice::Initialize(const Raydiance::Graphics::RHI_RenderDeviceDescriptor & _renderDeviceDescriptor)
	{
		// Set the debug mode
		m_DebugMode = _renderDeviceDescriptor.DebugMode;
		CorrectDebugMode();

		return Raydiance::Result::RESULT_GOOD;
	}

	void RenderDevice::CorrectDebugMode()
	{
		switch (m_DebugMode)
		{
		case Raydiance::Graphics::RHI_DebugMode::RHI_DEBUG_MODE_ALWAYS :
			m_DebugEnabled = true;
			break;
		case Raydiance::Graphics::RHI_DebugMode::RHI_DEBUG_MODE_NEVER :
			m_DebugEnabled = false;
			break;
		case Raydiance::Graphics::RHI_DebugMode::RHI_DEBUG_MODE_DEBUG_ONLY :
#if defined(_DEBUG)
			m_DebugEnabled = true;
#else
			m_DebugEnabled = false;
#endif
			break;
		}
	}
}