#pragma once

namespace Raydiance
{
	namespace Graphics
	{
		enum class RHI_ShaderType
		{
			RHI_SHADER_TYPE_INVALID = 0x00,
			RHI_SHADER_TYPE_VERTEX  = 0x01,
			RHI_SHADER_TYPE_PIXEL   = 0x02,
			RHI_SHADER_TYPE_COMPUTE = 0x04,
		};
	}
}