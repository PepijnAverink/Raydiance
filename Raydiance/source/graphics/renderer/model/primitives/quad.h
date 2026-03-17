#pragma once
#include "./graphics/renderer/model/mesh.h"

namespace Raydiance
{
	namespace Graphics
	{
		class Quad : public Mesh
		{
		public:
			Quad(CommandBuffer* _commandBuffer, std::shared_ptr<RHI_FenceCPU> _fence);
		};
	}
}