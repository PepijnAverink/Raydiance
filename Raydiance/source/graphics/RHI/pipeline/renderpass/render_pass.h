#pragma once
#include "./graphics/RHI/pipeline/renderpass/render_pass_descriptor.h"

namespace Raydiance
{
	namespace Graphics
	{
		class RenderPass
		{
		public:
			RenderPass(const RenderPassDescriptor* _renderPassDescriptor);
			virtual ~RenderPass();


		};
	}
}