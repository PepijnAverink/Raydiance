#pragma once
#include <string>
#include <vector>

namespace Raydiance
{
	namespace Graphics
	{
		class RHI_Texture2D;
		class RHI_RenderPass;
		class RHI_FrameBufferDescriptor
		{
		public:
			RHI_FrameBufferDescriptor() = default;

			std::string		Name;

			uint32_t		Width;
			uint32_t		Height;

			RHI_RenderPass*	RenderPass = nullptr;

			uint32_t				      AttachmentCount;
			std::vector<RHI_Texture2D*>   Attachments;

			RHI_Texture2D* DepthStencilAttachment = nullptr;
		};
	}
}