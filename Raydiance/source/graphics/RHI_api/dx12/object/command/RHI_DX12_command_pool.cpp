#include "./pch.h"
#include "./graphics/RHI_api/dx12/object/command/RHI_DX12_command_pool.h"
#include "./graphics/RHI_api/dx12/RHI_DX12_render_device.h"

#include "./graphics/RHI_api/dx12/object/command/RHI_DX12_command_buffer_type.h"

namespace Raydiance
{
	namespace Graphics
	{
		RHI_DX12_CommandPool::RHI_DX12_CommandPool(void)
			: RHI_CommandPool()
		{ }

		RHI_DX12_CommandPool::~RHI_DX12_CommandPool(void)
		{
			m_CommandAllocatorObj->Release();
		}

		const Result RHI_DX12_CommandPool::Initialize(const RHI_DX12_RenderDevice* _RHI_RenderDevice, const RHI_CommandPoolDescriptor* _commandPoolDescriptor)
		{
			Result result = RHI_CommandPool::Initialize(_commandPoolDescriptor);
			if (CheckError(result) == true)
			{
				// When result is RESULT_ERROR || RESULT_FATAL.
				Logger::Log("Error while intitializing the base class of the 'RHI_CommandQueue' object.", LogLevel::LOG_LEVEL_ERROR);
				Logger::Log("No further evidence what went wrong, please see earlier logs.", LogLevel::LOG_LEVEL_ERROR);
				return result;
			}

			if (_RHI_RenderDevice->GetD3DDevice()->CreateCommandAllocator(ResolveDX12CommandBufferType(_commandPoolDescriptor->Type), IID_PPV_ARGS(&m_CommandAllocatorObj)) != S_OK)
			{
				Logger::Log("Failed to create DX12CommandAllocator...", LogLevel::LOG_LEVEL_ERROR);
				return Result::RESULT_ERROR;
			}
			m_CommandAllocatorObj->SetName(L"CommandAllocator");

			return result;
		}

		void RHI_DX12_CommandPool::Reset()
		{
			m_CommandAllocatorObj->Reset();
		}
	}
}