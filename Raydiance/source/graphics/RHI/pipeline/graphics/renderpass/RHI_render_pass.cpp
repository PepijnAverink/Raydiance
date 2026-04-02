#include "./graphics/RHI/pipeline/graphics/renderpass/RHI_render_pass.h"

namespace Raydiance
{
	namespace Graphics
	{
		RHI_RenderPass::RHI_RenderPass(void)
		{ }

		RHI_RenderPass::~RHI_RenderPass()
		{ }

		const Result RHI_RenderPass::Initialize(const RHI_RenderPassDescriptor* _renderPassDescriptor)
		{
			m_Width  = _renderPassDescriptor->Width;
			m_Height = _renderPassDescriptor->Height;

			return Result::RESULT_GOOD;
		}
	}
}