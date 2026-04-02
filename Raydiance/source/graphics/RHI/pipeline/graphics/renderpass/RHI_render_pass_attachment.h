#pragma once
#include "./graphics/RHI/pipeline/graphics/renderpass/RHI_load_op.h"
#include "./graphics/RHI/pipeline/graphics/renderpass/RHI_store_op.h"
#include "./graphics/RHI/resource/RHI_resource_format.h"
#include "./graphics/RHI/resource/RHI_resource_state.h"

namespace Raydiance
{
	namespace Graphics
	{
		class RHI_RenderPassAttachment
		{
		public:
			RHI_RenderPassAttachment(void) = default;

			RHI_ResourceFormat Format	   = RHI_ResourceFormat::RHI_RESOURCE_FORMAT_INVALID;
			RHI_LoadOp  LoadOperation      = RHI_LoadOp::RHI_LOAD_OP_INVALID;
			RHI_StoreOp StoreOperation     = RHI_StoreOp::RHI_STORE_OP_INVALID;
			RHI_ResourceState InitialState = RHI_ResourceState::RHI_RESOURCE_STATE_INVALID;
			RHI_ResourceState FinalState   = RHI_ResourceState::RHI_RESOURCE_STATE_INVALID;
		};
	}
}