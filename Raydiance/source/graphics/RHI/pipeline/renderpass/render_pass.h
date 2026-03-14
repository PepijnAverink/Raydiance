#pragma once
//#include "./graphics/RHI/pipeline/renderpass/render_pass_descriptor.h"

namespace Graphics
{
	class RenderPass
	{
	public:
		RenderPass(const RenderPassDescriptor* _renderPassDescriptor);
		virtual ~RenderPass();


	};
}