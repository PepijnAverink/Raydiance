#pragma once
#include "./core/error/logger.h"
#include "./graphics/RHI/resource/sampler/RHI_compare_op.h"

#include <vulkan/vulkan.h>

namespace Raydiance
{
	namespace Graphics
	{
		inline VkCompareOp ResolveVKCompareOp(RHI_CompareOp _filter)
		{
			switch (_filter)
			{
			case RHI_CompareOp::RHI_COMPARE_OP_NEVER:
				return VK_COMPARE_OP_NEVER;
			case RHI_CompareOp::RHI_COMPARE_OP_ALWAYS:
				return VK_COMPARE_OP_ALWAYS;
			case RHI_CompareOp::RHI_COMPARE_OP_EQUAL:
				return VK_COMPARE_OP_EQUAL;
			case RHI_CompareOp::RHI_COMPARE_OP_NOT_EQUAL:
				return VK_COMPARE_OP_NOT_EQUAL;
			case RHI_CompareOp::RHI_COMPARE_OP_LESS:
				return VK_COMPARE_OP_LESS;
			case RHI_CompareOp::RHI_COMPARE_OP_LESS_EQUAL:
				return VK_COMPARE_OP_LESS_OR_EQUAL;
			case RHI_CompareOp::RHI_COMPARE_OP_GREATER:
				return VK_COMPARE_OP_GREATER_OR_EQUAL;
			case RHI_CompareOp::RHI_COMPARE_OP_GREATER_EQUAL:
				return VK_COMPARE_OP_GREATER_OR_EQUAL;
			}
			return VK_COMPARE_OP_NEVER;
		}
	}
}