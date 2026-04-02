// Graphics includes
#include "./graphics/RHI/object/swapchain/RHI_swapchain.h"

#include "./graphics/RHI/resource/texture/RHI_texture2D.h"

namespace Raydiance
{
	namespace Graphics
	{
		RHI_Swapchain::RHI_Swapchain()
		{ }

		RHI_Swapchain::~RHI_Swapchain()
		{
			ReleaseBuffers();
		}

		void RHI_Swapchain::ReleaseBuffers()
		{
			for (uint8_t i = 0; i < m_BufferCount; i++)
				delete m_RenderTargets[i];
		}

		const Result RHI_Swapchain::Initialize(const RHI_SwapchainDescriptor* _swapchainDescriptor)
		{
			m_VSync = _swapchainDescriptor->VSync;
			m_ResourceFormat = _swapchainDescriptor->Format;

			m_BufferCount = _swapchainDescriptor->BufferCount;

			m_Width = _swapchainDescriptor->Width;
			m_Height = _swapchainDescriptor->Height;

			return Result::RESULT_GOOD;
		}
	}
}