#pragma once
// Graphics includes
#include "./graphics/RHI/pipeline/layout/RHI_vertex_layout.h"


namespace Raydiance
{
	namespace Graphics
	{
		class RHI_ShaderReflection
		{
		public:
			RHI_ShaderReflection();
			virtual ~RHI_ShaderReflection();
			

			RHI_VertexLayout ShaderInput;
			RHI_VertexLayout ShaderOutput;
		};
	}
}