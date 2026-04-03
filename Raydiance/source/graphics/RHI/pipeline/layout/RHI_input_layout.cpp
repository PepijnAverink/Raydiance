#include "./pch.h"
#include "./graphics/RHI/pipeline/layout/RHI_input_layout.h"

namespace Raydiance
{
	namespace Graphics
	{
		RHI_InputLayout::RHI_InputLayout()
		{ }

		RHI_InputLayout::~RHI_InputLayout()
		{
		}
		const Result RHI_InputLayout::Initialize(const RHI_InputLayoutDescriptor* _inputLayoutDescriptor)
		{
			m_Layouts = _inputLayoutDescriptor->Layouts;
				//, m_Samplers(_inputLayoutDescriptor->Samplers)
			return Result::RESULT_GOOD;
		}
	}
}