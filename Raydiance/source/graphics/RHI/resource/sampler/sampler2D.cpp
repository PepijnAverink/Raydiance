#include "./pch.h"
#include "sampler2D.h"

namespace Raydiance
{
	namespace Graphics
	{
		Sampler2D::Sampler2D(const Sampler2DDescriptor* _sampler2DDescriptor)
			: m_FilterMode(_sampler2DDescriptor->Filter)
		{
		}

		Sampler2D::~Sampler2D()
		{
		}
	}
}