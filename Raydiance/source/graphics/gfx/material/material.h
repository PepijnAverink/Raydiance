#pragma once
// Graphics includes
#include "./graphics/gfx/material/material_instance.h"

#include "./graphics/RHI/pipeline/layout/descriptor/RHI_descriptor_pool.h"


namespace Raydiance
{
	namespace Graphics
	{
		class Material
		{
		public:
			// TODO:: prolly RHI_GraphicsPipeline should be added here as well;
			// But what about compute then..?
					 Material(const RHI_InputSet& _inputSet, const uint32 _instanceReserve = 1);
			virtual ~Material(void);

			MaterialInstance* AllocateMaterialInstance(void);

		protected:
			uint32 m_ReserveCount   = 0;
			uint32 m_AllocatedCount = 0;

			RHI_InputSet		m_InputSet;
			RHI_DescriptorPool* m_DescriptorPool = nullptr;

			friend class MaterialInstance;
			const uint32 FindDescriptorId(const std::string& _name) const;

		};
	}
}