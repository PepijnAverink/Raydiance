#pragma once
#include "./graphics/RHI/pipeline/renderpass/render_pass_attachment.h"

#include <string>
#include <vector>

namespace Raydiance
{
	namespace Graphics
	{
		class RenderPassDescriptor
		{
		public:
			RenderPassDescriptor() = default;

			std::string Name;
			std::vector<RenderPassAttachment> Attachments;
		};
	}
}