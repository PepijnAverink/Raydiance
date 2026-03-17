#pragma once
#include "./graphics/renderer/model/mesh.h"

namespace Raydiance
{
	namespace Graphics
	{
		class Cube : public Mesh
		{
		public:
			Cube(CommandBuffer* _commandBuffer, std::shared_ptr<RHI_FenceCPU> _fence);
		};
	}
}