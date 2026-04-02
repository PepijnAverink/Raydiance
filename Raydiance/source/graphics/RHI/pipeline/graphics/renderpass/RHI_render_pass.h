#pragma once
#include "./core/error/result.h"
#include "./graphics/RHI/pipeline/graphics/renderpass/RHI_render_pass_descriptor.h"

namespace Raydiance
{
	namespace Graphics
	{
		class RHI_RenderPass
		{
		public:
			virtual ~RHI_RenderPass();

		protected:
			RHI_RenderPass();

			const Result Initialize(const RHI_RenderPassDescriptor* _renderPassDescriptor);

			uint32_t m_Width = 0;
			uint32_t m_Height = 0;
		};
	}
}