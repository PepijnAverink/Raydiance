#pragma once
#include "./graphics/RHI/pipeline/renderpass/RHI_render_pass_descriptor.h"

namespace Raydiance
{
	namespace Graphics
	{
		class RHI_RenderPass
		{
		public:
			RHI_RenderPass(const RHI_RenderPassDescriptor* _renderPassDescriptor);
			virtual ~RHI_RenderPass();


		};
	}
}