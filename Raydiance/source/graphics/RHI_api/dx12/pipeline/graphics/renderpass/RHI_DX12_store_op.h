#pragma once
#include "./graphics/RHI/pipeline/graphics/renderpass/RHI_store_op.h"
#include "./core/error/logger.h"

#include <d3d12.h>

namespace Raydiance
{
	namespace Graphics
	{
		inline D3D12_RENDER_PASS_ENDING_ACCESS_TYPE  ResolveDX12StoreOp(RHI_StoreOp _storep)
		{
			switch (_storep)
			{
				case RHI_StoreOp::RHI_STORE_OP_STORE:
					return D3D12_RENDER_PASS_ENDING_ACCESS_TYPE_PRESERVE;
				case RHI_StoreOp::RHI_STORE_OP_DONT_CARE:
					return D3D12_RENDER_PASS_ENDING_ACCESS_TYPE_DISCARD;
			}

			Logger::Log("Failed to resolve DX12StoreOp.", LogLevel::LOG_LEVEL_ERROR);
			return D3D12_RENDER_PASS_ENDING_ACCESS_TYPE_DISCARD;
		}
	}
}