#include "./graphics/RHI/pipeline/layout/descriptor/RHI_descriptor_set.h"

namespace Raydiance
{
	namespace Graphics
	{
		RHI_DescriptorSet::RHI_DescriptorSet()
		{ }

		RHI_DescriptorSet::~RHI_DescriptorSet()
		{ }

		const Result RHI_DescriptorSet::Initialize(const RHI_DescriptorSetDescriptor* _descriptorSetDescriptor)
		{
			m_InputSet = _descriptorSetDescriptor->InputSet;
			return Result::RESULT_GOOD;
		}
	}
}