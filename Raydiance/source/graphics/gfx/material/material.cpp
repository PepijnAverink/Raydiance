#include "./pch.h"
#include "./graphics/gfx/material/material.h"


// Graphics includs
#include "./graphics/gfx/render_backend.h"


namespace Raydiance
{
	namespace Graphics
	{
		Material::Material(const RHI_InputSet& _inputSet, const uint32 _instanceReserve)
			: m_InputSet(_inputSet)
			, m_ReserveCount(_instanceReserve)
		{
			// Resource counts
			uint32 bufferCount  = 0;
			uint32 textureCount = 0;
			uint32 samplerCount = 0;

			for (auto element : m_InputSet.Elements)
			{
				// Look fot texture elements
				if (element.Type == RHI_InputType::RHI_INPUT_TYPE_BUFFER)
					bufferCount++;
				else if (element.Type == RHI_InputType::RHI_INPUT_TYPE_TEXTURE2D)
					textureCount++;
				else if (element.Type == RHI_InputType::RHI_INPUT_TYPE_SAMPLER)
					samplerCount++;
			}


			// Setup texture slots for the descriptorPool
			RHI_DescriptorPoolSize bufferPoolSize;
			bufferPoolSize.Type  = RHI_InputType::RHI_INPUT_TYPE_BUFFER;
			bufferPoolSize.Flags = RHI_InputFlag::RHI_INPUT_FLAG_INVALID;
			bufferPoolSize.Count = bufferCount * m_ReserveCount;

			RHI_DescriptorPoolSize texturePoolSize;
			texturePoolSize.Type  = RHI_InputType::RHI_INPUT_TYPE_TEXTURE2D;
			texturePoolSize.Flags = RHI_InputFlag::RHI_INPUT_FLAG_INVALID;
			texturePoolSize.Count = textureCount * m_ReserveCount;

			RHI_DescriptorPoolSize samplerPoolSize;
			samplerPoolSize.Type  = RHI_InputType::RHI_INPUT_TYPE_SAMPLER;
			samplerPoolSize.Flags = RHI_InputFlag::RHI_INPUT_FLAG_INVALID;
			samplerPoolSize.Count = samplerCount * m_ReserveCount;


			// Descriptor for the descriptorPool
			RHI_DescriptorPoolDescriptor descriptorPoolDesc = {};
			descriptorPoolDesc.Name				= "DescriptorPool";
			descriptorPoolDesc.MaxDescriptorSet = m_ReserveCount;

			// Add sizes to the descriptorPool descriptor
			if (bufferCount > 0)
				descriptorPoolDesc.Sizes.push_back(bufferPoolSize);
			if (textureCount > 0)
				descriptorPoolDesc.Sizes.push_back(texturePoolSize);
			if (samplerCount > 0)
				descriptorPoolDesc.Sizes.push_back(samplerPoolSize);


			// Create the actual descriptorPool
			m_DescriptorPool = RenderBackend::GetRenderDevice()->RHI_CreateDescriptorPool(&descriptorPoolDesc);
		}


		Material::~Material(void)
		{
			delete m_DescriptorPool;
		}


		MaterialInstance* Material::AllocateMaterialInstance(void)
		{
			if (m_AllocatedCount < m_ReserveCount)
			{
				m_AllocatedCount++;

				RHI_DescriptorSetDescriptor descriptorSetDescriptor = {};
				descriptorSetDescriptor.Name	 = "MaterialDescriptorSet" + std::to_string(m_AllocatedCount);
				descriptorSetDescriptor.InputSet = m_InputSet;

				return new MaterialInstance(this, m_DescriptorPool->AllocateDescriptorSet(&descriptorSetDescriptor));
			}

			return nullptr;
		}


		const uint32 Material::FindDescriptorId(const std::string& _name) const
		{
			for (uint32 i = 0; i < m_InputSet.Elements.size(); i++)
			{
				if (m_InputSet.Elements[i].Name == _name)
					return i;
			}
			return -1;
		}
	}
}