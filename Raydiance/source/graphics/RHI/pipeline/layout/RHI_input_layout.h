#pragma once
#include "./core/error/result.h"
#include "./graphics/RHI/pipeline/layout/RHI_input_layout_descriptor.h"
#include <vector>

namespace Raydiance
{
	namespace Graphics
	{
		class RHI_InputSet;
		class RHI_InputLayout
		{
		public:
			virtual ~RHI_InputLayout();

			RHI_InputSet GetLayout(const uint32 _idx) const { return m_Layouts[_idx]; }
			const std::vector<RHI_InputSet>& GetLayouts() const { return m_Layouts; }
			//const std::vector<Sampler*>& GetSamplers() const { return m_Samplers; }

			// Operator [] overloading
			RHI_InputSet& operator[](size_t index)
			{
				return m_Layouts[index];
			}
			const RHI_InputSet& operator[](size_t index) const
			{
				return m_Layouts[index];
			}

			std::vector<RHI_InputSet>::iterator begin() { return m_Layouts.begin(); }
			std::vector<RHI_InputSet>::iterator end() { return m_Layouts.end(); }
			std::vector<RHI_InputSet>::const_iterator begin() const { return m_Layouts.begin(); }
			std::vector<RHI_InputSet>::const_iterator end()	  const { return m_Layouts.end(); }

		protected:
			RHI_InputLayout();
			const Result Initialize(const RHI_InputLayoutDescriptor* _inputLayoutDescriptor);
			std::vector<RHI_InputSet> m_Layouts;
			//std::vector<Sampler*> m_Samplers;
		};
	}
}