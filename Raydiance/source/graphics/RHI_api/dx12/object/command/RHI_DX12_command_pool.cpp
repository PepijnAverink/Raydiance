#include "./pch.h"
#include "./graphics/RHI_api/dx12/object/command/RHI_DX12_command_pool.h"

#include "./graphics/RHI_api/dx12/RHI_DX12_render_device.h"


#include "./graphics/RHI_api/dx12/object/command/RHI_DX12_command_buffer_type.h"

namespace Raydiance
{
	namespace Graphics
	{
		RHI_DX12_CommandPool::RHI_DX12_CommandPool(RHI_DX12_RenderDevice* _renderDevice, const RHI_CommandPoolDescriptor& _commandPoolDescriptor)
			: RHI_CommandPool(_commandPoolDescriptor)
		{ 
			if (_renderDevice->GetD3DDevice()->CreateCommandAllocator(ResolveDX12CommandBufferType(_commandPoolDescriptor.Type), IID_PPV_ARGS(&m_CommandAllocatorObj)) != S_OK)
			{
				Logger::Log("Failed to create DX12CommandAllocator...", LogType::LOG_TYPE_ERROR);
			}
			m_CommandAllocatorObj->SetName(L"CommandAllocator");
		}

		RHI_DX12_CommandPool::~RHI_DX12_CommandPool()
		{ }

		void RHI_DX12_CommandPool::Reset()
		{
			m_CommandAllocatorObj->Reset();
		}
	}
}