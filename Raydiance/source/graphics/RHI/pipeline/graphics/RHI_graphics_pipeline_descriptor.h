#pragma once
#include "./graphics/RHI/pipeline/layout/RHI_input_layout.h"
#include "./graphics/RHI/pipeline/layout/RHI_vertex_layout.h"
#include "./graphics/RHI/pipeline/graphics/rasterizer/RHI_cull_mode.h"
#include "./graphics/RHI/pipeline/graphics/rasterizer/RHI_fill_mode.h"
#include "./graphics/RHI/pipeline/graphics/rasterizer/RHI_winding_order.h"
#include "./graphics/RHI/pipeline/graphics/topology/RHI_topology.h"
#include "./graphics/RHI/pipeline/graphics/viewport/RHI_view_port.h"
#include "./graphics/RHI/pipeline/graphics/viewport/RHI_scissor_rect.h"
#include "./graphics/RHI/resource/shader/RHI_shader.h"

#include "./graphics/RHI/pipeline/renderpass/RHI_render_pass.h"

#include <string>

namespace Raydiance
{
	namespace Graphics
	{
		class RHI_GraphicsPipelineDescriptor
		{
		public:
			RHI_GraphicsPipelineDescriptor() = default;

			std::string Name;

			// Topology
			RHI_Topology Topology = RHI_Topology::RHI_TOPOLOGY_INVALID;

			RHI_InputLayout* InputLayout = nullptr;
			RHI_VertexLayout VertexLayout;

			// Rasterizer
			RHI_CullMode CullMode = RHI_CullMode::RHI_CULL_MODE_INVALID;
			RHI_FillMode FillMode = RHI_FillMode::RHI_FILL_MODE_INVALID;
			RHI_WindingOrder WindingOrder = RHI_WindingOrder::RHI_WINDING_ORDER_INVALID;

			// Viewport
			uint32_t	Width;
			uint32_t	Height;
			RHI_ViewPort    ViewPort;
			RHI_ScissorRect ScissorRect;

			// Shaders
			RHI_Shader* VertexShader = nullptr;
			RHI_Shader* PixelShader = nullptr;

			// RenderPass
			RHI_RenderPass* RenderPass = nullptr;
		};
	}
}