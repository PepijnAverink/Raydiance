#pragma once
#include "./graphics/RHI/pipeline/graphics/renderpass/RHI_render_pass_store_op.h"
#include "./core/error/logger.h"

#include <d3d12.h>

namespace Raydiance
{
	namespace Graphics
	{
		inline D3D12_RENDER_PASS_ENDING_ACCESS_TYPE  ResolveDX12StoreOp(RHI_RenderPassStoreOp _storep)
		{
			switch (_storep)
			{
			case RHI_RenderPassStoreOp::RHI_RENDER_PASS_STORE_OP_STORE:
				return D3D12_RENDER_PASS_ENDING_ACCESS_TYPE_PRESERVE;
			case RHI_RenderPassStoreOp::RHI_RENDER_PASS_STORE_OP_DONT_CARE:
				return D3D12_RENDER_PASS_ENDING_ACCESS_TYPE_DISCARD;
			}

			Logger::Log("Failed to resolve DX12StoreOp.", LogType::LOG_TYPE_ERROR);
			return D3D12_RENDER_PASS_ENDING_ACCESS_TYPE_DISCARD;
		}
	}
}