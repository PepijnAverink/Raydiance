#include "./pch.h"
#include "./graphics/RHI_api/dx12/object/command/RHI_DX12_command_queue.h"


#include "./graphics/RHI_api/dx12/RHI_DX12_render_device.h"
#include "./graphics/RHI_api/dx12/object/command/RHI_DX12_command_queue_type.h"


#include "./utility/string_utility.h"

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
			// Initialize the base class of the RHI_DX12_CommandQueue graphics object class,
			// And error check the result.
			// --------------------------------------------------------------------------
			Result result = RHI_CommandQueue::Initialize(_commandQueueDescriptor);
			if (CheckError(result) == true)
			{
				// When result is RESULT_ERROR || RESULT_FATAL.
				Logger::Log("Error while intitializing the base class of the 'RHI_CommandQueue' object.", LogType::LOG_TYPE_ERROR);
				Logger::Log("No further evidence what went wrong, please see earlier logs.", LogType::LOG_TYPE_ERROR);
				return result;
			}

			D3D12_COMMAND_QUEUE_DESC cqDesc = {};
			cqDesc.Flags = D3D12_COMMAND_QUEUE_FLAG_NONE;
			cqDesc.Type = ResolveDX12CommandQueueType(m_Type);

			// Create Queue and error check
			if (_renderDevice.GetD3DDevice()->CreateCommandQueue(&cqDesc, IID_PPV_ARGS(&m_CommandQueueObj)) != S_OK)
			{
				Logger::Log("Failed to create DX12CommandQueue...", LogType::LOG_TYPE_ERROR);
				return Result::RESULT_ERROR;
			}

			// Set name of the commandQueueObj
			if (_commandQueueDescriptor.DebugName.empty() == false) // TODO:: Maybe only in debug mode
				m_CommandQueueObj->SetName(StringToWString(_commandQueueDescriptor.DebugName).c_str());
			return result;
		}


		void RHI_DX12_CommandQueue::SubmitCommandBuffer(RHI_CommandBuffer* _commandBuffer, std::shared_ptr<RHI_FenceCPU> _fence)
		{

		}
	}
}