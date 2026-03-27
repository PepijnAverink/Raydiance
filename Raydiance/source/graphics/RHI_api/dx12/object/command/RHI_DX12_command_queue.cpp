#include "./pch.h"
#include "./graphics/RHI_api/dx12/object/command/RHI_DX12_command_queue.h"


namespace Raydiance
{
	namespace Graphics
	{
		RHI_DX12_CommandQueue::RHI_DX12_CommandQueue()
			: RHI_CommandQueue()
		{ }


		RHI_DX12_CommandQueue::~RHI_DX12_CommandQueue()
		{ }


		const Result RHI_DX12_CommandQueue::Initialize(const RHI_DX12_RenderDevice& _renderDevice, const RHI_CommandQueueDescriptor& _commandQueueDescriptor)
		{
			return Result::RESULT_GOOD;
		}


		void RHI_DX12_CommandQueue::SubmitCommandBuffer(RHI_CommandBuffer* _commandBuffer, std::shared_ptr<RHI_FenceCPU> _fence)
		{

		}
	}
}