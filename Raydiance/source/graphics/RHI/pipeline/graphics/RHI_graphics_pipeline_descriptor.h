#pragma once
#include "./graphics/RHI/pipeline/layout/RHI_vertex_layout.h"
#include "./graphics/RHI/pipeline/layout/RHI_input_layout.h"

#include "./graphics/RHI/resource/shader/RHI_shader.h"

#include "./graphics/RHI/pipeline/graphics/topology/RHI_topology.h"
#include "./graphics/RHI/pipeline/graphics/rasterizer/RHI_cull_mode.h"
#include "./graphics/RHI/pipeline/graphics/rasterizer/RHI_fill_mode.h"
#include "./graphics/RHI/pipeline/graphics/rasterizer/RHI_winding_order.h"

#include "./graphics/RHI/pipeline/graphics/renderpass/RHI_render_pass.h"
#include "./graphics/RHI/pipeline/graphics/framebuffer/RHI_frame_buffer.h"

#include <string>

namespace Raydiance
{
	namespace Graphics
	{
		class RHI_GraphicsPipelineDescriptor
		{
		public:
			RHI_GraphicsPipelineDescriptor() = default;

			std::string  Name;

			RHI_InputLayout* InputLayout = nullptr;
			RHI_VertexLayout VertexLayout;
			RHI_RenderPass*  RenderPass = nullptr;

			RHI_FrameBuffer* FrameBuffer = nullptr;
			RHI_Topology	 Topology = RHI_Topology::RHI_TOPOLOGY_INVALID;

			// Rasterizer
			RHI_CullMode	 CullMode = RHI_CullMode::RHI_CULL_MODE_INVALID;
			RHI_FillMode	 FillMode = RHI_FillMode::RHI_FILL_MODE_INVALID;
			RHI_WindingOrder WindingOrder = RHI_WindingOrder::RHI_WINDING_ORDER_INVALID;

			bool DepthEnable = false;

			RHI_Shader* VertexShader = nullptr;
			RHI_Shader* GeometryShader = nullptr;
			RHI_Shader* PixelShader = nullptr;
		};
	}
}