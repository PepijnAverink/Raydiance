#pragma once
#include "./graphics/RHI/pipeline/layout/RHI_input_layout_descriptor.h"

#include <vector>

namespace Raydiance
{
	namespace Graphics
	{
		class RHI_InputLayout
		{
		public:
			RHI_InputLayout(const RHI_InputLayoutDescriptor* _inputLayoutDescriptor);
			virtual ~RHI_InputLayout();

			const std::vector<RHI_InputSet>& GetLayouts() const { return m_Layouts; }

			std::vector<RHI_InputSet>::iterator begin() { return m_Layouts.begin(); }
			std::vector<RHI_InputSet>::iterator end() { return m_Layouts.end(); }
			std::vector<RHI_InputSet>::const_iterator begin() const { return m_Layouts.begin(); }
			std::vector<RHI_InputSet>::const_iterator end()	  const { return m_Layouts.end(); }

		protected:
			std::vector<RHI_InputSet> m_Layouts;
		};
	}
}