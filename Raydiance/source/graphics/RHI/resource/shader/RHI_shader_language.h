#pragma once
// Core includes
#include "./core/container/types.h"


// Generic includes
#include <string_view>


namespace Raydiance
{
	namespace Graphics
	{
		// Defines shader languages supported by the RHI (Rnedering Hardware Interface)
		enum class RHI_ShaderLanguage : uint8
		{
			RHI_SHADER_LANGUAGE_INVALID = 0x00,
			RHI_SHADER_LANGUAGE_HLSL	= 0x01,
		};


		// Returns true if the language is a valid, usable value
		[[nodiscard]]
		constexpr bool is_valid(RHI_ShaderLanguage _language)
		{
			switch (_language)
			{
			case RHI_ShaderLanguage::RHI_SHADER_LANGUAGE_HLSL:
				return true;

			case RHI_ShaderLanguage::RHI_SHADER_LANGUAGE_INVALID:
			default:
				return false;
			}
		}


		// Converts an RHI_ShaderLanguage value to its string representation
		[[nodiscard]]
		constexpr std::string_view RHI_ShaderLanguage_to_string(RHI_ShaderLanguage _language)
		{
			switch (_language)
			{
			case RHI_ShaderLanguage::RHI_SHADER_LANGUAGE_HLSL    : return "RHI_SHADER_LANGUAGE_HLSL";
			case RHI_ShaderLanguage::RHI_SHADER_LANGUAGE_INVALID : return "RHI_SHADER_LANGUAGE_INVALID";
			default:											   return "RHI_Unknown";				 // Fallback for unexpected values
			}
		}


		// Parses a string into an RHI_ShaderLanguage value (returns RHI_SHADER_LANGUAGE_INVALID on failure)
		[[nodiscard]]
		constexpr RHI_ShaderLanguage RHI_ShaderLanguage_from_string(std::string_view _str)
		{
			if (_str == "RHI_SHADER_LANGUAGE_HLSL") return RHI_ShaderLanguage::RHI_SHADER_LANGUAGE_HLSL;
			return RHI_ShaderLanguage::RHI_SHADER_LANGUAGE_INVALID;
		}
	}
}