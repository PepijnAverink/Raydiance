#include "./pch.h"
#include "./graphics/gfx/mesh/mesh.h"


// Graphics includes
#include "./graphics/gfx/render_backend.h"


namespace Raydiance
{
	namespace Graphics
	{
		Mesh::Mesh(void)
		{ }


		Mesh::~Mesh(void)
		{
			delete m_VertexBuffer;
			delete m_IndexBuffer;
		}


		void Mesh::AddSubMesh(const SubMesh& _subMesh)
		{
			m_SubMeshes.push_back(_subMesh);
			m_SubMeshCount++;
		}


		Result Mesh::CreateVertexBuffer(RHI_CommandBuffer* _commandBuffer, RHI_FenceCPU* _fence, void* _data, const uint32 _size, RHI_BufferLayout _layout)
		{
			RHI_Buffer* vStagingBuffer = nullptr;

			// Vertex StagingBuffer
			// --------------------------------------------------
			{
				RHI_BufferDescriptor bufferDesc;
				bufferDesc.Name		  = "Generated-StagingBuffer";
				bufferDesc.Data		  = _data;
				bufferDesc.Layout	  = _layout;
				bufferDesc.MemoryType = RHI_ResourceMemoryType::RHI_RESOURCE_MEMORY_TYPE_CPU;
				bufferDesc.State	  = RHI_ResourceState::RHI_RESOURCE_STATE_COPY_SRC;
				bufferDesc.Size		  = _size;
				bufferDesc.Flags	  = RHI_BufferUsageFlags::RHI_BUFFER_USAGE_FLAGS_STAGING_BUFFER;

				vStagingBuffer = RenderBackend::GetRenderDevice()->RHI_CreateBuffer(&bufferDesc);
			}

			// VertexBuffer
			// --------------------------------------------------
			{
				RHI_BufferDescriptor bufferDesc;
				bufferDesc.Name       = "VertexBuffer";
				bufferDesc.Data       = nullptr;
				bufferDesc.Layout     = _layout;
				bufferDesc.MemoryType = RHI_ResourceMemoryType::RHI_RESOURCE_MEMORY_TYPE_GPU;
				bufferDesc.State      = RHI_ResourceState::RHI_RESOURCE_STATE_VERTEX_BUFFER;
				bufferDesc.Size       = _size;
				bufferDesc.Flags      = RHI_BufferUsageFlags::RHI_BUFFER_USAGE_FLAGS_VERTEX_BUFFER;

				m_VertexBuffer = RenderBackend::GetRenderDevice()->RHI_CreateBuffer(&bufferDesc);
			}

			_commandBuffer->BeginRecording();
			_commandBuffer->CopyBuffer(vStagingBuffer, m_VertexBuffer);
			_commandBuffer->TransitionResource(m_VertexBuffer, RHI_ResourceState::RHI_RESOURCE_STATE_COPY_DST, RHI_ResourceState::RHI_RESOURCE_STATE_VERTEX_BUFFER);
			_commandBuffer->EndRecording();

			RenderBackend::SubmitCommandBuffer(_commandBuffer, _fence);
			_fence->Wait();

			delete vStagingBuffer;
			return Result::RESULT_GOOD;
		}


		Result Mesh::CreateIndexBuffer(RHI_CommandBuffer* _commandBuffer, RHI_FenceCPU* _fence, void* _data, const uint32 _size, RHI_BufferLayout _layout)
		{
			RHI_Buffer* iStagingBuffer = nullptr;

			// Vertex StagingBuffer
			// --------------------------------------------------
			{
				RHI_BufferDescriptor bufferDesc;
				bufferDesc.Name       = "Generated-StagingBuffer";
				bufferDesc.Data       = _data;
				bufferDesc.Layout     = _layout;
				bufferDesc.MemoryType = RHI_ResourceMemoryType::RHI_RESOURCE_MEMORY_TYPE_CPU;
				bufferDesc.State      = RHI_ResourceState::RHI_RESOURCE_STATE_COPY_SRC;
				bufferDesc.Size       = _size;
				bufferDesc.Flags      = RHI_BufferUsageFlags::RHI_BUFFER_USAGE_FLAGS_STAGING_BUFFER;

				iStagingBuffer = RenderBackend::GetRenderDevice()->RHI_CreateBuffer(&bufferDesc);
			}

			// IndexBuffer
			// --------------------------------------------------
			{
				RHI_BufferDescriptor bufferDesc;
				bufferDesc.Name       = "IndexBuffer";
				bufferDesc.Data       = nullptr;
				bufferDesc.Layout     = _layout;
				bufferDesc.MemoryType = RHI_ResourceMemoryType::RHI_RESOURCE_MEMORY_TYPE_GPU;
				bufferDesc.State      = RHI_ResourceState::RHI_RESOURCE_STATE_INDEX_BUFFER;
				bufferDesc.Size       = _size;
				bufferDesc.Flags      = RHI_BufferUsageFlags::RHI_BUFFER_USAGE_FLAGS_INDEX_BUFFER;

				m_IndexBuffer = RenderBackend::GetRenderDevice()->RHI_CreateBuffer(&bufferDesc);
			}

			_commandBuffer->BeginRecording();
			_commandBuffer->CopyBuffer(iStagingBuffer, m_IndexBuffer);
			_commandBuffer->TransitionResource(m_IndexBuffer, RHI_ResourceState::RHI_RESOURCE_STATE_COPY_DST, RHI_ResourceState::RHI_RESOURCE_STATE_INDEX_BUFFER);
			_commandBuffer->EndRecording();

			Graphics::RenderBackend::SubmitCommandBuffer(_commandBuffer, _fence);
			_fence->Wait();

			delete iStagingBuffer;
		}
	}
}