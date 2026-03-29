#include "./pch.h"
#include "./graphics/RHI/pipeline/layout/descriptor/RHI_descriptor_set.h"

namespace Raydiance
{
	namespace Graphics
	{
		RHI_DescriptorSet::RHI_DescriptorSet(const RHI_DescriptorSetDescriptor* _descriptorSetDescriptor)
		{ 
			m_InputSet = _descriptorSetDescriptor->InputLayout->GetLayouts()[_descriptorSetDescriptor->SetIndex];
		}

		RHI_DescriptorSet::~RHI_DescriptorSet()
		{ }
	}
}