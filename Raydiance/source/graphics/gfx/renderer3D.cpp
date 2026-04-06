#include "./pch.h"
#include "./graphics/gfx/renderer3D.h"


namespace Raydiance
{
	namespace Graphics
	{
		Result Renderer3D::Initialize(const Renderer3DDescriptor& _renderer3DDescriptor)
		{
			// Set number of frames in flight
			m_FramesInFlight = _renderer3DDescriptor.FramesInFlight;
			m_FrameData.resize(m_FramesInFlight);

			// Allocate frame data
			{
				RHI_FenceCPUDescriptor fenceDesc = { };
				fenceDesc.Name    = "";
				fenceDesc.TimeOut = 0;

				RHI_CommandPoolDescriptor commandPoolDesc = { };
				commandPoolDesc.Name = "";
				commandPoolDesc.Type = RHI_CommandBufferType::RHI_COMMAND_BUFFER_TYPE_GRAPHICS;

				RHI_CommandBufferDescriptor commandBufferDesc = { };
				commandBufferDesc.Name = "";
				commandBufferDesc.Type = RHI_CommandBufferType::RHI_COMMAND_BUFFER_TYPE_GRAPHICS;

				for (uint32 i = 0; i < m_FramesInFlight; i++)
				{
					m_FrameData[i].SwapchainIndex = i;

					fenceDesc.Name				  = "FrameData_Fence_" + std::to_string(i);
					m_FrameData[i].Fence		  = RenderBackend::GetRenderDevice()->RHI_CreateFenceCPU(&fenceDesc);

					commandPoolDesc.Name		  = "FrameData_CommandPool_" + std::to_string(i);
					m_FrameData[i].CommandPool	  = RenderBackend::GetRenderDevice()->RHI_CreateCommandPool(&commandPoolDesc);

					commandBufferDesc.Name		  = "FrameData_CommandBuffer_" + std::to_string(i);
					commandBufferDesc.CommandPool = m_FrameData[i].CommandPool;
					m_FrameData[i].CommandBuffer  = RenderBackend::GetRenderDevice()->RHI_CreateCommandBuffer(&commandBufferDesc);
				}
			}

			return Result::RESULT_GOOD;
		}

		Result Renderer3D::Terminate()
		{
			for (uint32 i = 0; i < m_FramesInFlight; i++)
			{
				delete m_FrameData[i].Fence;
				delete m_FrameData[i].CommandPool;
				delete m_FrameData[i].CommandBuffer;
			}

			m_FrameData.clear();
			return Result::RESULT_GOOD;
		}
	}
}