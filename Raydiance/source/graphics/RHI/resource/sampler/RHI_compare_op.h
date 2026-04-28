#pragma once
// Core includes
#include "./core/container/types.h"


// Generic includes
#include <string_view>


namespace Raydiance
{
	namespace Graphics
	{
		// Defines texture sampling compare operations used by the RHI (Rendering Hardware Interface)
		enum class RHI_CompareOp : uint8
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


		// Returns true if the compare operation is a valid, usable value
		[[nodiscard]]
		constexpr bool is_valid(RHI_CompareOp _compareOp)
		{
			switch (_compareOp)
			{
			case RHI_CompareOp::RHI_COMPARE_OP_NEVER:
			case RHI_CompareOp::RHI_COMPARE_OP_ALWAYS:
			case RHI_CompareOp::RHI_COMPARE_OP_EQUAL:
			case RHI_CompareOp::RHI_COMPARE_OP_NOT_EQUAL:
			case RHI_CompareOp::RHI_COMPARE_OP_LESS:
			case RHI_CompareOp::RHI_COMPARE_OP_LESS_EQUAL:
			case RHI_CompareOp::RHI_COMPARE_OP_GREATER:
			case RHI_CompareOp::RHI_COMPARE_OP_GREATER_EQUAL:
				return true;

			case RHI_CompareOp::RHI_COMPARE_OP_INVALID:
			default:
				return false;
			}
		}


		// Converts an RHI_CompareOp value to its string representation
		[[nodiscard]]
		constexpr std::string_view RHI_CompareOp_to_string(RHI_CompareOp _compareOp)
		{
			switch (_compareOp)
			{
			case RHI_CompareOp::RHI_COMPARE_OP_NEVER:		  return "RHI_COMPARE_OP_NEVER";
			case RHI_CompareOp::RHI_COMPARE_OP_ALWAYS:		  return "RHI_COMPARE_OP_ALWAYS";
			case RHI_CompareOp::RHI_COMPARE_OP_EQUAL:		  return "RHI_COMPARE_OP_EQUAL";
			case RHI_CompareOp::RHI_COMPARE_OP_NOT_EQUAL:	  return "RHI_COMPARE_OP_NOT_EQUAL";
			case RHI_CompareOp::RHI_COMPARE_OP_LESS:		  return "RHI_COMPARE_OP_LESS";
			case RHI_CompareOp::RHI_COMPARE_OP_LESS_EQUAL:	  return "RHI_COMPARE_OP_LESS_EQUAL";
			case RHI_CompareOp::RHI_COMPARE_OP_GREATER:		  return "RHI_COMPARE_OP_GREATER";
			case RHI_CompareOp::RHI_COMPARE_OP_GREATER_EQUAL: return "RHI_COMPARE_OP_GREATER_EQUAL";
			case RHI_CompareOp::RHI_COMPARE_OP_INVALID:		  return "RHI_COMPARE_OP_INVALID";
			default:										  return "RHI_Unknown";			// Fallback for unexpected values
			}
		}


		// Parses a string into an RHI_CompareOp value (returns RHI_COMPARE_OP_INVALID on failure)
		[[nodiscard]]
		constexpr RHI_CompareOp RHI_CompareOp_from_string(std::string_view _str)
		{
			if (_str == "RHI_COMPARE_OP_NEVER")			return RHI_CompareOp::RHI_COMPARE_OP_NEVER;
			if (_str == "RHI_COMPARE_OP_ALWAYS")		return RHI_CompareOp::RHI_COMPARE_OP_ALWAYS;
			if (_str == "RHI_COMPARE_OP_EQUAL")			return RHI_CompareOp::RHI_COMPARE_OP_EQUAL;
			if (_str == "RHI_COMPARE_OP_NOT_EQUAL")		return RHI_CompareOp::RHI_COMPARE_OP_NOT_EQUAL;
			if (_str == "RHI_COMPARE_OP_LESS")			return RHI_CompareOp::RHI_COMPARE_OP_LESS;
			if (_str == "RHI_COMPARE_OP_LESS_EQUAL")	return RHI_CompareOp::RHI_COMPARE_OP_LESS_EQUAL;
			if (_str == "RHI_COMPARE_OP_GREATER")		return RHI_CompareOp::RHI_COMPARE_OP_GREATER;
			if (_str == "RHI_COMPARE_OP_GREATER_EQUAL") return RHI_CompareOp::RHI_COMPARE_OP_GREATER_EQUAL;
			return RHI_CompareOp::RHI_COMPARE_OP_INVALID;
		}
	}
}