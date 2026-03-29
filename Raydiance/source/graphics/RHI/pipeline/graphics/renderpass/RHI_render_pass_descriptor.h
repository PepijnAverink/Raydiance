#pragma once
#include "./graphics/RHI/pipeline/graphics/renderpass/RHI_render_pass_attachment.h"

#include <string>
#include <vector>

namespace Raydiance
{
	namespace Graphics
	{
		class RHI_RenderPassDescriptor
		{
		public:
			RHI_RenderPassDescriptor() = default;

			std::string Name;
			std::vector<RHI_RenderPassAttachment> Attachments;
		};
	}
}