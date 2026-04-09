#pragma once
// Graphics includes
#include "./graphics/RHI/resource/buffer/RHI_buffer.h"
#include "./graphics/RHI/resource/sampler/RHI_sampler.h"
#include "./graphics/RHI/resource/texture/RHI_texture2D.h"
#include "./graphics/RHI/pipeline/layout/descriptor/RHI_descriptor_set.h"

namespace Raydiance
{
	namespace Graphics
	{
		class Material;
		class MaterialInstance
		{
		public:
			virtual ~MaterialInstance(void);

			virtual void BindBuffer(const std::string& _bindingName, RHI_Buffer* _buffer);
			virtual void BindTexture(const std::string& _bindingName, RHI_Texture2D* _texture);
			virtual void BindSampler(const std::string& _bindingName, RHI_Sampler* _sampler);

		protected:
			friend class Material;
			MaterialInstance(Material* _material, RHI_DescriptorSet* _descriptorSet);


			// Parent material (non owning!)
			Material*		   m_ParentMaterial = nullptr;
			RHI_DescriptorSet* m_DescriptorSet = nullptr;
		};
	}
}