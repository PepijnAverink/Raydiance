#include "./pch.h"
#include "./graphics/gfx/material/material_instance.h"


// Graphcis includes
#include "./graphics/gfx/material/material.h"


namespace Raydiance
{
	namespace Graphics
	{
		MaterialInstance::MaterialInstance(Material* _material, RHI_DescriptorSet* _descriptorSet)
			: m_ParentMaterial(_material)
			, m_DescriptorSet(_descriptorSet)
		{ }


		MaterialInstance::~MaterialInstance(void)
		{
			delete m_DescriptorSet;
		}


		void MaterialInstance::BindBuffer(const std::string& _bindingName, RHI_Buffer* _buffer)
		{
			uint32 id = m_ParentMaterial->FindDescriptorId(_bindingName);
			m_DescriptorSet->AllocateDescriptor(_buffer, id, 0);
		}


		void MaterialInstance::BindTexture(const std::string& _bindingName, RHI_Texture2D* _texture)
		{
			uint32 id = m_ParentMaterial->FindDescriptorId(_bindingName);
			m_DescriptorSet->AllocateDescriptor(_texture, id, 0);
		}


		void MaterialInstance::BindSampler(const std::string& _bindingName, RHI_Sampler* _sampler)
		{
			uint32 id = m_ParentMaterial->FindDescriptorId(_bindingName);
			m_DescriptorSet->AllocateDescriptor(_sampler, id, 0);
		}
	}
}