#pragma once
#include "./graphics/RHI/pipeline/layout/descriptor/RHI_descriptor_set_descriptor.h"

namespace Raydiance
{
	namespace Graphics
	{
		class RHI_Buffer;
		class RHI_Texture2D;
		class RHI_Sampler;

		class RHI_InputSet;
		class RHI_DescriptorSet
		{
		public:
			RHI_DescriptorSet(void);
			virtual ~RHI_DescriptorSet();

			const Result Initialize(const RHI_DescriptorSetDescriptor* _descriptorSetDescriptor);

			virtual void AllocateDescriptor(RHI_Buffer* _buffer, const uint32_t _setIndex, const uint32_t _arrayIndex = 0) = 0;
			virtual void AllocateDescriptor(RHI_Texture2D* _texture, const uint32_t _setIndex, const uint32_t _arrayIndex = 0) = 0;
			virtual void AllocateDescriptor(RHI_Sampler* _sampler, const uint32_t _setIndex, const uint32_t _arrayIndex = 0) = 0;

		protected:
			RHI_InputSet m_InputSet;
		};
	}
}