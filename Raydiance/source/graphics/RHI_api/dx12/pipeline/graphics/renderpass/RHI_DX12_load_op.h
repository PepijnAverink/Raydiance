#pragma once
#include "./graphics/RHI/pipeline/graphics/renderpass/RHI_load_op.h"
#include "./core/error/logger.h"

#include <d3d12.h>


namespace Raydiance
{
	namespace Graphics
	{
		inline D3D12_RENDER_PASS_BEGINNING_ACCESS_TYPE ResolveDX12LoadOp(RHI_LoadOp _loadOp)
		{
			switch (_loadOp)
			{
				case RHI_LoadOp::RHI_LOAD_OP_LOAD:
					return D3D12_RENDER_PASS_BEGINNING_ACCESS_TYPE_PRESERVE;
				case RHI_LoadOp::RHI_LOAD_OP_CLEAR:
					return D3D12_RENDER_PASS_BEGINNING_ACCESS_TYPE_CLEAR;
				case RHI_LoadOp::RHI_LOAD_OP_DONT_CARE:
					return D3D12_RENDER_PASS_BEGINNING_ACCESS_TYPE_DISCARD;
			}

			Logger::Log("Failed to resolve DX12LoadOp.", LogLevel::LOG_LEVEL_ERROR);
			return D3D12_RENDER_PASS_BEGINNING_ACCESS_TYPE_DISCARD;
		}
	}
}