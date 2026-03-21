#pragma once
#include "./graphics/RHI/resource/sampler/RHI_sampler2D_descriptor.h"

namespace Raydiance
{
	namespace Graphics
	{
		class RHI_Sampler2D
		{
		public:
			RHI_Sampler2D(const RHI_Sampler2DDescriptor* _sampler2DDescriptor);
			virtual ~RHI_Sampler2D();

		protected:
			RHI_FilterMode m_FilterMode;
		};
	}
}