#include "./pch.h"
#include "./graphics/RHI/pipeline/layout/RHI_input_layout.h"

namespace Raydiance
{
	namespace Graphics
	{
		RHI_InputLayout::RHI_InputLayout(const RHI_InputLayoutDescriptor* _inputLayoutDescriptor)
			: m_Layouts(_inputLayoutDescriptor->Layouts)
		{
		}

		RHI_InputLayout::~RHI_InputLayout()
		{

		}
	}
}