#pragma once
#include "./graphics/RHI/pipeline/graphics/RHI_graphics_pipeline.h"

namespace Raydiance
{
	namespace Graphics
	{
		class Material
		{
		public:

		protected:
			RHI_GraphicsPipeline* m_GraphicsPipeline = nullptr;
		};
	}
}