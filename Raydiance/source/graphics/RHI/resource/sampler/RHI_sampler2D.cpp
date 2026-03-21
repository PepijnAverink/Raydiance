#include "./pch.h"
#include "RHI_sampler2D.h"

namespace Raydiance
{
	namespace Graphics
	{
		RHI_Sampler2D::RHI_Sampler2D(const RHI_Sampler2DDescriptor* _sampler2DDescriptor)
			: m_FilterMode(_sampler2DDescriptor->Filter)
		{
		}

		RHI_Sampler2D::~RHI_Sampler2D()
		{
		}
	}
}