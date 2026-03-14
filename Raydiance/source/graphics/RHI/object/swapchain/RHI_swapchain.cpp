//#include "./graphics/RHI/object/swapchain/swapchain.h"
//#include "./core/window/window.h"
#include "core/stdafx.h"
namespace Raydiance
{
	namespace Graphics
	{
		RHI_Swapchain::RHI_Swapchain(const RHI_SwapchainDescriptor* _swapchainDescriptor)
			: m_WindowPtr(_swapchainDescriptor->Window)
			, m_Width(_swapchainDescriptor->Width == 0 ? _swapchainDescriptor->Window->GetWidth() : _swapchainDescriptor->Width)
			, m_Height(_swapchainDescriptor->Height == 0 ? _swapchainDescriptor->Window->GetHeight() : _swapchainDescriptor->Height)
		{
		}

		RHI_Swapchain::~RHI_Swapchain()
		{
		}
	}
}