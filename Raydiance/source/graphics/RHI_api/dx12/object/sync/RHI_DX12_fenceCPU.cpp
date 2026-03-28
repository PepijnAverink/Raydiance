#include "./pch.h"
#include "./graphics/RHI_api/dx12/object/sync/RHI_DX12_FenceCPU.h"
#include "./graphics/RHI_api/dx12/RHI_DX12_render_device.h"

#include "./utility/string_utility.h"

namespace Raydiance
{
	namespace Graphics
	{
		RHI_DX12_FenceCPU::RHI_DX12_FenceCPU(void)
			: RHI_FenceCPU()
		{ }


		RHI_DX12_FenceCPU::~RHI_DX12_FenceCPU(void)
		{ 
			CloseHandle(m_FenceEvent);
		}


		const Result RHI_DX12_FenceCPU::Initialize(const RHI_DX12_RenderDevice& _renderDevice, const RHI_FenceCPUDescriptor& _fenceDescriptor)
		{
			Result result = RHI_FenceCPU::Initialize(_fenceDescriptor);
			if (CheckError(result) == true)
			{
				// Log error
				return result;
			}

			m_FenceValue = 0;

			m_FenceEvent = CreateEvent(nullptr, FALSE, FALSE, nullptr);
			if (_renderDevice.GetD3DDevice()->CreateFence(m_FenceValue, D3D12_FENCE_FLAG_NONE, IID_PPV_ARGS(&m_FenceObj)) != S_OK)
			{
				Logger::Log("Failed to Create DX12Fence...", LogType::LOG_TYPE_ERROR);
				return Result::RESULT_ERROR;
			}
			m_FenceValue++;
			m_FenceObj->SetName(StringToWString(_fenceDescriptor.Name).c_str());

			// Correct the timeout
			if (m_TimeOut == 0)
				m_TimeOut = INFINITE;

			return result;
		}


		const Result RHI_DX12_FenceCPU::Wait(void)
		{
			if (m_FenceObj->GetCompletedValue() < m_FenceValue)
			{
				m_FenceObj->SetEventOnCompletion(m_FenceValue, m_FenceEvent);
				WaitForSingleObject(m_FenceEvent, m_TimeOut);
			}
			m_FenceValue++;

			return Result::RESULT_GOOD;
		}
	}
}