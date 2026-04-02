#pragma once
#include "./core/container/types.h"

namespace Raydiance
{
	namespace Graphics
	{
		class RHI_Buffer;
		class RHI_BLASInstance
		{
		public:
			RHI_BLASInstance() = default;

			RHI_Buffer* VertexBuffer = nullptr;
			RHI_Buffer* IndexBuffer  = nullptr;
		};
	}
}