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

			{
				RHI_FenceCPUDescriptor fenceDesc = { };
				fenceDesc.Name    = "AquireFence";
				fenceDesc.TimeOut = 0;

				m_AquireFence = RenderBackend::GetRenderDevice()->RHI_CreateFenceCPU(&fenceDesc);
			}


			{
				m_FrameData[0].CommandBuffer->BeginRecording();

				for (uint32 i = 0; i < RenderBackend::GetSwapchain()->GetBufferCount(); i++)
					m_FrameData[0].CommandBuffer->TransitionResource(RenderBackend::GetSwapchain()->GetRenderTextureAtIndex(i), RHI_ResourceState::RHI_RESOURCE_STATE_INVALID, RHI_ResourceState::RHI_RESOURCE_STATE_PRESENT);
				
				m_FrameData[0].CommandBuffer->EndRecording();


				// Submit commandbuffer
				RenderBackend::SubmitCommandBuffer(m_FrameData[0].CommandBuffer, m_FrameData[0].Fence);
				m_FrameData[0].Fence->Wait();
			}


			// Load vertex shader
			{
				RHI_ShaderDescriptor shaderDesc = { };
				shaderDesc.Name		  = "VertexShader";
				shaderDesc.FilePath   = "./assets/vertex_shader.hlsl";
				shaderDesc.EntryPoint = "main";
				shaderDesc.Type       = Raydiance::Graphics::RHI_ShaderType::RHI_SHADER_TYPE_VERTEX;

				m_VertexShader = Raydiance::Graphics::RenderBackend::GetRenderDevice()->RHI_CreateShader(&shaderDesc);
			}


			// Load pixel shader
			{
				RHI_ShaderDescriptor shaderDesc = { };
				shaderDesc.Name		  = "PixelShader";
				shaderDesc.FilePath	  = "./assets/pixel_shader.hlsl";
				shaderDesc.EntryPoint = "main";
				shaderDesc.Type		  = Raydiance::Graphics::RHI_ShaderType::RHI_SHADER_TYPE_PIXEL;

				m_PixelShader = Raydiance::Graphics::RenderBackend::GetRenderDevice()->RHI_CreateShader(&shaderDesc);
			}

			{
				RHI_RenderPassDescriptor renderPassDesc = { };

			}

			return Result::RESULT_GOOD;
		}

		Result Renderer3D::Terminate()
		{
			delete m_PixelShader;
			delete m_VertexShader;

			// =========================

			delete m_AquireFence;

			for (uint32 i = 0; i < m_FramesInFlight; i++)
			{
				delete m_FrameData[i].CommandBuffer;
				delete m_FrameData[i].CommandPool;
				delete m_FrameData[i].Fence;
			}

			m_FrameData.clear();
			return Result::RESULT_GOOD;
		}

		void Renderer3D::BeginFrame()
		{
			m_CurrentFrameIndex = RenderBackend::AquireNewFrame(m_AquireFence);
			m_AquireFence->Wait();


			// Transition backbuffer
			m_FrameData[m_CurrentFrameIndex].CommandBuffer->BeginRecording();
			m_FrameData[m_CurrentFrameIndex].CommandBuffer->TransitionResource(RenderBackend::GetSwapchain()->GetCurrentRenderTexture(), RHI_ResourceState::RHI_RESOURCE_STATE_PRESENT, RHI_ResourceState::RHI_RESOURCE_STATE_COMMON);
			m_FrameData[m_CurrentFrameIndex].CommandBuffer->EndRecording();


			// Submit commandbuffer
			RenderBackend::SubmitCommandBuffer(m_FrameData[m_CurrentFrameIndex].CommandBuffer, m_FrameData[m_CurrentFrameIndex].Fence);
			m_FrameData[m_CurrentFrameIndex].Fence->Wait();
		}

		void Renderer3D::EndFrame()
		{
			// Transition backbuffer
			m_FrameData[m_CurrentFrameIndex].CommandBuffer->BeginRecording();
			m_FrameData[m_CurrentFrameIndex].CommandBuffer->TransitionResource(RenderBackend::GetSwapchain()->GetCurrentRenderTexture(), RHI_ResourceState::RHI_RESOURCE_STATE_COMMON, RHI_ResourceState::RHI_RESOURCE_STATE_PRESENT);
			m_FrameData[m_CurrentFrameIndex].CommandBuffer->EndRecording();


			// Submit commandbuffer
			RenderBackend::SubmitCommandBuffer(m_FrameData[m_CurrentFrameIndex].CommandBuffer, m_FrameData[m_CurrentFrameIndex].Fence);
			m_FrameData[m_CurrentFrameIndex].Fence->Wait();


			// Reset command pool for the current frame
			m_FrameData[m_CurrentFrameIndex].CommandPool->Reset();


			// Present the current frame
			RenderBackend::Present();
		}
	}
}