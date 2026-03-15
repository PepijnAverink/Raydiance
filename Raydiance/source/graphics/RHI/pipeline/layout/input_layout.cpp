#include "./pch.h"
#include "./graphics/RHI/pipeline/layout/input_layout.h"

namespace Raydiance
{
	namespace Graphics
	{
		InputLayout::InputLayout(const InputLayoutDescriptor* _inputLayoutDescriptor)
			: m_Layouts(_inputLayoutDescriptor->Layouts)
		{
		}

		InputLayout::~InputLayout()
		{

		}
	}
}