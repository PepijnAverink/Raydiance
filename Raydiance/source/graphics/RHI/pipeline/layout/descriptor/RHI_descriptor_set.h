#pragma once
#include "./graphics/RHI/pipeline/layout/descriptor/RHI_descriptor_set_descriptor.h"

namespace Raydiance
{
	namespace Graphics
	{
		class RHI_Texture2D;
		class RHI_Sampler;
		class RHI_Buffer;
		class RHI_DescriptorSet
		{
		public:
			RHI_DescriptorSet(const RHI_DescriptorSetDescriptor* _descriptorSetDescriptor);
			virtual ~RHI_DescriptorSet();

			virtual void AllocateDescriptor(RHI_Buffer* _buffer, const uint32_t _bindingIndex, const uint32_t _arrayIndex) = 0;
			virtual void AllocateDescriptor(RHI_Texture2D* _texture, RHI_Sampler* _sampler, const uint32_t _bindingIndex, const uint32_t _arrayIndex) = 0;

		protected:
			RHI_InputSet m_InputSet;
		};
	}
}