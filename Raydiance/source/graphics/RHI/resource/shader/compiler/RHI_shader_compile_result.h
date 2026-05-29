#pragma once
// Core includes
#include "./core/error/result.h"


// Graphics includes
#include "./graphics/RHI/resource/shader/compiler/RHI_shader_reflection.h"


// Generic includes
#include <string>
#include <vector>


namespace Raydiance
{
	namespace Graphics
	{
		class RHI_ShaderCompileResult
		{
		public:
			// Default constructor and descructor
			// ======================================
			 RHI_ShaderCompileResult(void) = default;
			~RHI_ShaderCompileResult(void) = default;


			// Compulation results
			Result		CompilationResult = Result::RESULT_INVALID;
			std::string ErrorStr;


			// The actual compiled shader source
			std::vector<uint8> ByteCode;


			RHI_ShaderReflection Reflection;
		};
	}
}