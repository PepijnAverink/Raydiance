#include "./pch.h"
#include "./graphics/RHI/object/swapchain/RHI_swapchain.h"

#include "./core/window/window.h"

namespace Raydiance
{
	namespace Graphics
	{
		RHI_Swapchain::~RHI_Swapchain(void)
		{ }

		RHI_Swapchain::RHI_Swapchain(void)
		{ }

		const Result RHI_Swapchain::Initialize(const RHI_SwapchainDescriptor& _swapchainDescriptor)
		{
			m_WindowPtr = _swapchainDescriptor.Window;

			m_Width  = (_swapchainDescriptor.Width == 0)  ? m_WindowPtr->GetWidth()  : _swapchainDescriptor.Width;
			m_Height = (_swapchainDescriptor.Height == 0) ? m_WindowPtr->GetHeight() : _swapchainDescriptor.Height;

			return Result::RESULT_GOOD;
		}
	}
}