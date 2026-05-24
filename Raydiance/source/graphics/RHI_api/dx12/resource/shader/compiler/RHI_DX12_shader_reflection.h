#pragma once
#include "./graphics/RHI/resource/shader/compiler/RHI_shader_reflection.h"


namespace Raydiance
{
	namespace Graphics
	{
		class RHI_DX12_ShaderReflection final : public RHI_ShaderReflection
		{
		public:
			RHI_DX12_ShaderReflection(void* _data, size_t _size);
			virtual ~RHI_DX12_ShaderReflection();

		private:

		};
	}
}