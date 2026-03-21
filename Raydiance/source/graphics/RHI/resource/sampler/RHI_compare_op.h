#pragma once
// Core includes
#include "./core/error/logger.h"
#include "./core/container/types.h"


// Generic includes
#include <string_view>


namespace Raydiance
{
	namespace Graphics
	{
		// Describes the compare op of an RHI_Texture2D object.
		enum class RHI_CompareOp : uint32
		{
			RHI_COMPARE_OP_INVALID		 = 0x00,
			RHI_COMPARE_OP_NEVER		 = 0x01,
			RHI_COMPARE_OP_ALWAYS		 = 0x02,
			RHI_COMPARE_OP_EQUAL		 = 0x03,
			RHI_COMPARE_OP_NOT_EQUAL	 = 0x04,
			RHI_COMPARE_OP_LESS			 = 0x05,
			RHI_COMPARE_OP_LESS_EQUAL	 = 0x06,
			RHI_COMPARE_OP_GREATER		 = 0x07,
			RHI_COMPARE_OP_GREATER_EQUAL = 0x08,
		};


		// Converts an RHI_CompareOp enum value to a readble string.
		[[nodiscard]]
		constexpr std::string_view RHI_CompareOpToString(RHI_CompareOp _mode) noexcept
		{
			switch (_mode)
			{
				case RHI_CompareOp::RHI_COMPARE_OP_INVALID:
					return "RHI_COMPARE_OP_INVALID";
				case RHI_CompareOp::RHI_COMPARE_OP_NEVER:
					return "RHI_COMPARE_OP_NEVER";
				case RHI_CompareOp::RHI_COMPARE_OP_ALWAYS:
					return "RHI_COMPARE_OP_ALWAYS";
				case RHI_CompareOp::RHI_COMPARE_OP_EQUAL:
					return "RHI_COMPARE_OP_EQUAL";
				case RHI_CompareOp::RHI_COMPARE_OP_NOT_EQUAL:
					return "RHI_COMPARE_OP_NOT_EQUAL";
				case RHI_CompareOp::RHI_COMPARE_OP_LESS:
					return "RHI_COMPARE_OP_LESS";
				case RHI_CompareOp::RHI_COMPARE_OP_LESS_EQUAL:
					return "RHI_COMPARE_OP_LESS_EQUAL";
				case RHI_CompareOp::RHI_COMPARE_OP_GREATER:
					return "RHI_COMPARE_OP_GREATER";
				case RHI_CompareOp::RHI_COMPARE_OP_GREATER_EQUAL:
					return "RHI_COMPARE_OP_GREATER_EQUAL";
				default:
					// Fallback for unknown/unsupported values.
					// Note:: No logging here to preserve contexpr usability.
					return "RHI_COMPARE_OP_INVALID";
			}
		}
	}
}