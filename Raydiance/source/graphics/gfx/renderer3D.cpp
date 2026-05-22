#include "./pch.h"
#include "./graphics/gfx/renderer3D.h"

// Graphics includes
#include "./graphics/gfx/mesh/primitive/cube.h"
#include "./graphics/RHI/resource/shader/shader_asset.h"


// Math includes
#include "./math/matrix/row_mat4x4.h"


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
			//	RHI_ShaderDescriptor shaderDesc = { };
			//	shaderDesc.Name		  = "VertexShader";
			//	shaderDesc.FilePath   = "./assets/vertex_shader.hlsl";
			//	shaderDesc.EntryPoint = "main";
			//	shaderDesc.Type       = RHI_ShaderType::RHI_SHADER_TYPE_VERTEX;
			//
			//	m_VertexShader = RenderBackend::GetRenderDevice()->RHI_CreateShader(&shaderDesc);
				Raydiance::Result res = Raydiance::Graphics::ShaderAsset::Load_RHI_Shader(Raydiance::FilePath("./assets/bin/a9d2a84105fd963ca9c1558a1b7fc776.rash"), &m_VertexShader);
				if (CheckError(res) == true)
				{
					Logger::Log("Failed to load shader asset.", LogLevel::LOG_LEVEL_ERROR);
					//return res;
				}
			}


			// Load pixel shader
			{
			//	RHI_ShaderDescriptor shaderDesc = { };
			//	shaderDesc.Name		  = "PixelShader";
			//	shaderDesc.FilePath	  = "./assets/pixel_shader.hlsl";
			//	shaderDesc.EntryPoint = "main";
			//	shaderDesc.Type		  = RHI_ShaderType::RHI_SHADER_TYPE_PIXEL;
			//
			//	m_PixelShader = RenderBackend::GetRenderDevice()->RHI_CreateShader(&shaderDesc);

				Raydiance::Result res = Raydiance::Graphics::ShaderAsset::Load_RHI_Shader(Raydiance::FilePath("./assets/bin/8bf78815c623f73667e509a67982787c.rash"), &m_PixelShader);
				if (CheckError(res) == true)
				{
					Logger::Log("Failed to load shader asset.", LogLevel::LOG_LEVEL_ERROR);
					//return res;
				}
			}

			{
				// Gather the backbuffer format
				RHI_ResourceFormat format = RenderBackend::GetSwapchain()->GetBufferFormat();

				RHI_RenderPassAttachment colorAttachment;
				colorAttachment.Format = format;
				colorAttachment.LoadOperation = RHI_LoadOp::RHI_LOAD_OP_CLEAR;
				colorAttachment.StoreOperation = RHI_StoreOp::RHI_STORE_OP_STORE;
				colorAttachment.InitialState = RHI_ResourceState::RHI_RESOURCE_STATE_RENDER_TEXTURE;
				colorAttachment.FinalState = RHI_ResourceState::RHI_RESOURCE_STATE_PRESENT;

				// RHI_RenderPassAttachment depthAttachment;
				// depthAttachment.Format = RHI_ResourceFormat::RHI_RESOURCE_FORMAT_D32_FLOAT;
				// depthAttachment.LoadOperation = RHI_LoadOp::RHI_LOAD_OP_CLEAR;
				// depthAttachment.StoreOperation = RHI_StoreOp::RHI_STORE_OP_STORE;
				// depthAttachment.InitialState = RHI_ResourceState::RHI_RESOURCE_STATE_DEPTH_WRITE;
				// depthAttachment.FinalState = RHI_ResourceState::RHI_RESOURCE_STATE_DEPTH_WRITE;

				RHI_RenderPassDescriptor renderPassDesc = {};
				renderPassDesc.Name = "RenderPass";
				renderPassDesc.Width = RenderBackend::GetSwapchain()->GetBufferWidth();
				renderPassDesc.Height = RenderBackend::GetSwapchain()->GetBufferHeight();
				renderPassDesc.ColorAttachmentCount = 1;
				renderPassDesc.ColorAttachments = { colorAttachment, };
				//renderPassDesc.DepthStencilAttachment = depthAttachment;

				m_RenderPass = RenderBackend::GetRenderDevice()->RHI_CreateRenderPass(&renderPassDesc);
			}

			{
				for (uint32 i = 0; i < RenderBackend::GetSwapchain()->GetBufferCount(); i++)
				{
					RHI_FrameBufferDescriptor framebufferDesc = {};
					framebufferDesc.Name			= "framebuffer";
					framebufferDesc.Width			= RenderBackend::GetSwapchain()->GetBufferWidth();
					framebufferDesc.Height			= RenderBackend::GetSwapchain()->GetBufferHeight();
					framebufferDesc.AttachmentCount = 1;
					framebufferDesc.Attachments		= { RenderBackend::GetSwapchain()->GetRenderTextureAtIndex(i), };
					//framebufferDesc.DepthStencilAttachment = m_DepthTexture;
					framebufferDesc.RenderPass		= m_RenderPass;

					m_FrameBuffers.push_back(RenderBackend::GetRenderDevice()->RHI_CreateFrameBuffer(&framebufferDesc));
				}
			}


			{
				RHI_InputLayoutDescriptor inputLayoutDesc = {};
				inputLayoutDesc.Name = "InputLayout";
				inputLayoutDesc.Layouts = {
				//	RHI_InputSet({
				//		 { "Lightdata",  RHI_InputType::RHI_INPUT_TYPE_BUFFER,    (uint32)RHI_ShaderType::RHI_SHADER_TYPE_PIXEL,  0, 1,  RHI_InputFlag::RHI_INPUT_FLAG_UNIFORM_ACCESS},
				//	}),
				//	RHI_InputSet({
				//		 { "g_texture",  RHI_InputType::RHI_INPUT_TYPE_TEXTURE2D, (uint32)RHI_ShaderType::RHI_SHADER_TYPE_PIXEL, 0, 1 },
				//		 { "g_texture",  RHI_InputType::RHI_INPUT_TYPE_TEXTURE2D, (uint32)RHI_ShaderType::RHI_SHADER_TYPE_PIXEL, 1, 1 },
				//		 { "g_texture",  RHI_InputType::RHI_INPUT_TYPE_TEXTURE2D, (uint32)RHI_ShaderType::RHI_SHADER_TYPE_PIXEL, 2, 1 },
				//	}),
					RHI_InputSet({
						 { "CameraData", RHI_InputType::RHI_INPUT_TYPE_CONSTANT,  (uint32)RHI_ShaderType::RHI_SHADER_TYPE_VERTEX, 0, 32 },
					}),
				//	RHI_InputSet({
				//		 { "g_sampler",  RHI_InputType::RHI_INPUT_TYPE_SAMPLER,   (uint32)RHI_ShaderType::RHI_SHADER_TYPE_PIXEL, 0, 1 },
				//	}),
				};
			
				m_InputLayout = RenderBackend::GetRenderDevice()->RHI_CreateInputLayout(&inputLayoutDesc);
			}
			
			RHI_VertexLayout vertexlayout = RHI_VertexLayout({
				RHI_VertexElement(VL_POSITION,   RHI_ResourceFormat::RHI_RESOURCE_FORMAT_R32G32B32_FLOAT),
				//RHI_VertexElement(VL_NORMALS,    RHI_ResourceFormat::RHI_RESOURCE_FORMAT_R32G32B32_FLOAT),
				//RHI_VertexElement(VL_TANGENT,    RHI_ResourceFormat::RHI_RESOURCE_FORMAT_R32G32B32_FLOAT),
				RHI_VertexElement(VL_TEXCOORDS0, RHI_ResourceFormat::RHI_RESOURCE_FORMAT_R32G32_FLOAT)
			});
			{
			
				RHI_GraphicsPipelineDescriptor pipelineDescriptor = {};
				pipelineDescriptor.Name         = "GraphicsPipeline";
				pipelineDescriptor.DepthEnable  = false;
				pipelineDescriptor.CullMode     = RHI_CullMode::RHI_CULL_MODE_NONE;
				pipelineDescriptor.WindingOrder = RHI_WindingOrder::RHI_WINDING_ORDER_CW;
				pipelineDescriptor.FillMode     = RHI_FillMode::RHI_FILL_MODE_SOLID;
				pipelineDescriptor.InputLayout  = m_InputLayout;
				pipelineDescriptor.FrameBuffer  = m_FrameBuffers[0];
				pipelineDescriptor.VertexShader = m_VertexShader;
				pipelineDescriptor.PixelShader  = m_PixelShader;
				pipelineDescriptor.VertexLayout = vertexlayout;
				pipelineDescriptor.RenderPass   = m_RenderPass;
				pipelineDescriptor.Topology     = RHI_Topology::RHI_TOPOLOGY_TRIANGLE_LIST;
			
				m_Pipeline = RenderBackend::GetRenderDevice()->RHI_CreatePipeline(&pipelineDescriptor);
			}

			m_Mesh = new Cube(vertexlayout, m_FrameData[0].CommandBuffer, m_FrameData[0].Fence);

			m_CurrentCamera = Camera();
			m_CurrentCamera.SetPosition(Math::vec3(0.0f, 0.0f, 5.0f));
			m_CurrentCamera.SetEulerRotation(Math::vec3(0.0f, 180.0f, 0.0f));

			return Result::RESULT_GOOD;
		}


		Result Renderer3D::Terminate()
		{
			delete m_Mesh;


			delete m_Pipeline;
			delete m_InputLayout;


			if (m_PixelShader != nullptr)
				delete m_PixelShader;
			if (m_VertexShader != nullptr)
				delete m_VertexShader;

			delete m_RenderPass;

			for (uint32 i = 0; i < m_FrameBuffers.size(); i++)
				delete m_FrameBuffers[i];
			m_FrameBuffers.clear();

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
			m_FrameData[m_CurrentFrameIndex].CommandBuffer->TransitionResource(RenderBackend::GetSwapchain()->GetCurrentRenderTexture(), RHI_ResourceState::RHI_RESOURCE_STATE_PRESENT, RHI_ResourceState::RHI_RESOURCE_STATE_GENERIC_WRITE);
			m_FrameData[m_CurrentFrameIndex].CommandBuffer->EndRecording();


			// Submit commandbuffer
			RenderBackend::SubmitCommandBuffer(m_FrameData[m_CurrentFrameIndex].CommandBuffer, m_FrameData[m_CurrentFrameIndex].Fence);
			m_FrameData[m_CurrentFrameIndex].Fence->Wait();
		}


		void Renderer3D::EndFrame()
		{
			// Transition backbuffer
			m_FrameData[m_CurrentFrameIndex].CommandBuffer->BeginRecording();
			
			{
				Math::vec3 pos = m_CurrentCamera.GetPosition() + Math::vec3(0.0f, 0.0f, 0.01f);
				m_CurrentCamera.SetPosition(pos);
				
				Math::row_mat4x4 viewProj = m_CurrentCamera.GetViewProjMatrix();
				Math::row_mat4x4 model = Math::row_mat4x4(1.0f);
			
			
				// PLS REMOVE
				// -----------------------------------------------------
				float clearcolor[4] = { 0.3f, 0.0f, 0.0f, 1.0f };
				float clearDS[2] = { 1.0f, 0.0f };
				m_FrameData[m_CurrentFrameIndex].CommandBuffer->BeginRenderPass(m_RenderPass, m_FrameBuffers[m_CurrentFrameIndex], 1280, 720, clearcolor, nullptr);
			
				m_FrameData[m_CurrentFrameIndex].CommandBuffer->SetViewport(0, 0, 1280, 720);
				m_FrameData[m_CurrentFrameIndex].CommandBuffer->SetScissorRectangle(0, 0, 1280, 720);
				m_FrameData[m_CurrentFrameIndex].CommandBuffer->SetGraphicsPipeline(m_Pipeline);
			
				m_FrameData[m_CurrentFrameIndex].CommandBuffer->SetVertexBuffer(0, m_Mesh->GetVertexBuffer());
				m_FrameData[m_CurrentFrameIndex].CommandBuffer->SetIndexBuffer(m_Mesh->GetIndexBuffer());
			
				//Math::row_mat4 vp = m_Camera->GetViewProjectionMatrix();
			
				m_FrameData[m_CurrentFrameIndex].CommandBuffer->SetGraphicsConstants(&model, 16, 16);
				m_FrameData[m_CurrentFrameIndex].CommandBuffer->SetGraphicsConstants(&viewProj, 0, 16);
			
				//		float color1[4] = { 1.0f, 0.0f, 1.0f, 1.0f };
				//		m_CommandBuffer->InsertDebugLabel("EndFrame", color1);
			
				//		float color[4] = { 0.0f, 1.0f, 1.0f, 1.0f };
				//		m_CommandBuffer->BeginDebugLabel("BeginRendering", color);
			
				std::vector<Graphics::SubMesh> subMeshes = m_Mesh->GetSubMeshes();
				for (uint32_t j = 0; j < subMeshes.size(); j++)
				{
					Graphics::SubMesh smesh = subMeshes[j];
					m_FrameData[m_CurrentFrameIndex].CommandBuffer->DrawIndexed(smesh.IndexCount, smesh.IndexOffset, smesh.VertexOffset);
				}
			
				m_FrameData[m_CurrentFrameIndex].CommandBuffer->EndRenderPass();
			}
			m_FrameData[m_CurrentFrameIndex].CommandBuffer->EndRecording();
			// Submit commandbuffer
			RenderBackend::SubmitCommandBuffer(m_FrameData[m_CurrentFrameIndex].CommandBuffer, m_FrameData[m_CurrentFrameIndex].Fence);
			m_FrameData[m_CurrentFrameIndex].Fence->Wait();

			// Transition backbuffer
			m_FrameData[m_CurrentFrameIndex].CommandBuffer->BeginRecording();
			m_FrameData[m_CurrentFrameIndex].CommandBuffer->TransitionResource(RenderBackend::GetSwapchain()->GetCurrentRenderTexture(), RHI_ResourceState::RHI_RESOURCE_STATE_GENERIC_WRITE, RHI_ResourceState::RHI_RESOURCE_STATE_PRESENT);
			m_FrameData[m_CurrentFrameIndex].CommandBuffer->EndRecording();


			// Submit commandbuffer
			RenderBackend::SubmitCommandBuffer(m_FrameData[m_CurrentFrameIndex].CommandBuffer, m_FrameData[m_CurrentFrameIndex].Fence);
			m_FrameData[m_CurrentFrameIndex].Fence->Wait();


			// Reset command pool for the current frame
			m_FrameData[m_CurrentFrameIndex].CommandPool->Reset();


			// Present the current frame
			RenderBackend::Present();
		}


		void Renderer3D::SubmitMesh()
		{

		}
	}
}