#pragma once

namespace Raydiance
{
	namespace Graphics
	{
		// Used to identify what the functionality of a certain shader object is.
		// Passed in at creation of a shader object.
		enum RHI_ShaderType
		{
			RHI_SHADER_TYPE_INVALID = 0x00,
			RHI_SHADER_TYPE_VERTEX  = 0x01, // Vertex Shader
			RHI_SHADER_TYPE_PIXEL   = 0x02, // Pixel  Shader
		};
	}
}