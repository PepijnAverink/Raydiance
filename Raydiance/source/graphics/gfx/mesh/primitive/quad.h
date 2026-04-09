#pragma once
// Graphics includes
#include "./graphics/gfx/mesh/mesh.h"


namespace Raydiance
{
	namespace Graphics
	{
		class Quad : public Mesh
		{
		public:
			         Quad(RHI_VertexLayout _vertexLayout, RHI_CommandBuffer* _commandBuffer, RHI_FenceCPU* _fence);
			virtual ~Quad(void);
		};
	}
}