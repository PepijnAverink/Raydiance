// Graphics includes
#include "./graphics/RHI_api/dx12/object/command/RHI_DX12_command_queue.h"
#include "./graphics/RHI_api/dx12/object/command/RHI_DX12_command_queue_type.h"
#include "./graphics/RHI_api/dx12/RHI_DX12_render_device.h"
#include "./graphics/RHI_api/dx12/object/command/RHI_DX12_command_buffer.h"
#include "./graphics/RHI_api/dx12/object/sync/RHI_DX12_fenceCPU.h"

// Utility includes
#include "./utilities/string_utilities.h"

namespace Raydiance
{
	namespace Graphics
	{
		RHI_DX12_CommandQueue::RHI_DX12_CommandQueue()
			: RHI_CommandQueue()
		{ }

		RHI_DX12_CommandQueue::~RHI_DX12_CommandQueue()
		{
			m_CommandQueueObj->Release();
		}

		const Result RHI_DX12_CommandQueue::Initialize(RHI_DX12_RenderDevice* _renderDevice, const RHI_CommandQueueDescriptor* _commandQueueDescriptor)
		{	
			// Initialize the base class of the RHI_DX12_CommandQueue graphics object class,
			// And error check the result.
			// --------------------------------------------------------------------------
			Result result = RHI_CommandQueue::Initialize(_commandQueueDescriptor);
			if (CheckError(result) == true)
			{
				// When result is RESULT_ERROR || RESULT_FATAL.
				Logger::Log("Error while intitializing the base class of the 'RHI_CommandQueue' object.", LogLevel::LOG_LEVEL_ERROR);
				Logger::Log("No further evidence what went wrong, please see earlier logs.", LogLevel::LOG_LEVEL_ERROR);
				return result;
			}

			D3D12_COMMAND_QUEUE_DESC cqDesc = {};
			cqDesc.Flags = D3D12_COMMAND_QUEUE_FLAG_NONE;
			cqDesc.Type = ResolveDX12CommandQueueType(m_Type);

			// Create Queue and error check
			if (_renderDevice->GetD3DDevice()->CreateCommandQueue(&cqDesc, IID_PPV_ARGS(&m_CommandQueueObj)) != S_OK)
			{
				Logger::Log("Failed to create DX12CommandQueue...", LogLevel::LOG_LEVEL_ERROR);
				return Result::RESULT_ERROR;
			}

			// Set name of the commandQueueObj
			m_CommandQueueObj->SetName(StringToWString(_commandQueueDescriptor->Name).c_str());
			return result;
		}

		void RHI_DX12_CommandQueue::Execute(RHI_CommandBuffer* _commandBuffer, RHI_FenceCPU* _fence)
		{
			// Execute commandBuffer
			ID3D12CommandList* commandlist[] = { ((RHI_DX12_CommandBuffer*)_commandBuffer)->GetD3DCommandBuffer() };
			m_CommandQueueObj->ExecuteCommandLists(1, commandlist);

			// Signal fence
			if (_fence != nullptr)
				m_CommandQueueObj->Signal(((RHI_DX12_FenceCPU*)_fence)->GetD3DFence(), ((RHI_DX12_FenceCPU*)_fence)->GetFenceValue());
		}

		void RHI_DX12_CommandQueue::InsertDebugLabel(const std::string& _name, float* _color)
		{

		}

		void RHI_DX12_CommandQueue::BeginDebugLabel(const std::string& _name, float* _color)
		{

		}

		void RHI_DX12_CommandQueue::EndDebugLabel()
		{

		}
	}
}