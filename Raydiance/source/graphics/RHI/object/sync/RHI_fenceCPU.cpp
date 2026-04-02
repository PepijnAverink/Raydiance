// Graphics includes
#include "./graphics/RHI/object/sync/RHI_fenceCPU.h"

namespace Raydiance
{
	namespace Graphics
	{
		RHI_FenceCPU::RHI_FenceCPU()
		{ }

		RHI_FenceCPU::~RHI_FenceCPU()
		{ }

		const Result RHI_FenceCPU::Initialize(const RHI_FenceCPUDescriptor* _fenceDescriptor)
		{
			m_TimeOut = _fenceDescriptor->TimeOut;

			return Result::RESULT_GOOD;
		}
	}
}