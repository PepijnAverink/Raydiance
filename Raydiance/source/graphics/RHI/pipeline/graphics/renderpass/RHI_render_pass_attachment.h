#pragma once
#include "./graphics/RHI/pipeline/graphics/renderpass/RHI_render_pass_attachment_type.h"
#include "./graphics/RHI/pipeline/graphics/renderpass/RHI_render_pass_load_op.h"
#include "./graphics/RHI/pipeline/graphics/renderpass/RHI_render_pass_store_op.h"
#include "./graphics/RHI/resource/RHI_resource_format.h"
#include "./graphics/RHI/resource/RHI_resource_state.h"

namespace Raydiance
{
	namespace Graphics
	{
		class RHI_RenderPassAttachment
		{
		public:
			RHI_RenderPassAttachment() = default;

			// Constructor to allow brace-initialization when creating attachments
			RHI_RenderPassAttachment(RHI_RenderPassAttachmentType type,
				RHI_ResourceFormat format,
				RHI_RenderPassLoadOp loadOp,
				RHI_RenderPassStoreOp storeOp,
				RHI_ResourceState initialState,
				RHI_ResourceState finalState)
				: Type(type), Format(format), LoadOp(loadOp), StoreOp(storeOp), InitialState(initialState), FinalStatte(finalState)
			{ }

			RHI_RenderPassAttachmentType Type = RHI_RenderPassAttachmentType::RHI_RENDER_PASS_ATTACHMENT_TYPE_INVALID;
			RHI_ResourceFormat           Format = RHI_ResourceFormat::RHI_RESOURCE_FORMAT_INVALID;
			RHI_RenderPassLoadOp         LoadOp = RHI_RenderPassLoadOp::RHI_RENDER_PASS_LOAD_OP_INVALID;
			RHI_RenderPassStoreOp		 StoreOp = RHI_RenderPassStoreOp::RHI_RENDER_PASS_STORE_OP_INVALID;
			RHI_ResourceState			 InitialState = RHI_ResourceState::RHI_RESOURCE_STATE_INVALID;
			RHI_ResourceState			 FinalStatte = RHI_ResourceState::RHI_RESOURCE_STATE_INVALID;
		};
	}
}