#pragma once
// Core includes
#include "./core/container/types.h"


// Generic includes
#include <string_view>


namespace Raydiance
{
	namespace Graphics
	{
		// Defines shader type that is used by the RHI (Rendering Hardware Interface)
		enum class RHI_ShaderType : uint8
		{
			RHI_SHADER_TYPE_INVALID = 0x00,
			RHI_SHADER_TYPE_VERTEX  = 0x01,
			RHI_SHADER_TYPE_PIXEL   = 0x02,
			RHI_SHADER_TYPE_COMPUTE = 0x04, // TODO:: Is this used as a flag instead?? Should not be used this way...
		};									// Please investigate further, if flag, make seperate access flags, if not adjust this value.


		// Returns true if the type is a valid, usable value
		[[nodiscard]]
		constexpr bool is_valid(RHI_ShaderType _type)
		{
			switch (_type)
			{
			case RHI_ShaderType::RHI_SHADER_TYPE_VERTEX:
			case RHI_ShaderType::RHI_SHADER_TYPE_PIXEL:
			case RHI_ShaderType::RHI_SHADER_TYPE_COMPUTE:
				return true;

			case RHI_ShaderType::RHI_SHADER_TYPE_INVALID:
			default:
				return false;
			}
		}


		// Converts an RHI_ShaderType value to its string representation
		[[nodiscard]]
		constexpr std::string_view RHI_ShaderType_to_string(RHI_ShaderType _type)
		{
			switch (_type)
			{
				case RHI_ShaderType::RHI_SHADER_TYPE_VERTEX  : return "RHI_SHADER_TYPE_VERTEX";
				case RHI_ShaderType::RHI_SHADER_TYPE_PIXEL   : return "RHI_SHADER_TYPE_PIXEL";
				case RHI_ShaderType::RHI_SHADER_TYPE_COMPUTE : return "RHI_SHADER_TYPE_COMPUTE";
				case RHI_ShaderType::RHI_SHADER_TYPE_INVALID : return "RHI_SHADER_TYPE_INVALID";
			default:										   return "RHI_Unknown";			 // Fallback for unexpected values
			}
		}


		// Parses a string into an RHI_ShaderType value (returns RHI_SHADER_TYPE_INVALID on failure)
		[[nodiscard]]
		constexpr RHI_ShaderType RHI_ShaderType_from_string(std::string_view _str)
		{
			if (_str == "RHI_SHADER_TYPE_VERTEX")  return RHI_ShaderType::RHI_SHADER_TYPE_VERTEX;
			if (_str == "RHI_SHADER_TYPE_PIXEL")   return RHI_ShaderType::RHI_SHADER_TYPE_PIXEL;
			if (_str == "RHI_SHADER_TYPE_COMPUTE") return RHI_ShaderType::RHI_SHADER_TYPE_COMPUTE;
			return RHI_ShaderType::RHI_SHADER_TYPE_INVALID;
		}
	}
}