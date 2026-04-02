#include "./graphics/RHI/pipeline/layout/descriptor/RHI_descriptor_pool.h"

namespace Raydiance
{
	namespace Graphics
	{
		RHI_DescriptorPool::RHI_DescriptorPool()
		{

		}

		RHI_DescriptorPool::~RHI_DescriptorPool()
		{

		}

		const Result RHI_DescriptorPool::Initialize(const RHI_DescriptorPoolDescriptor* _descriptorPoolDescriptor)
		{
			return Result::RESULT_GOOD;
		}
	}
}