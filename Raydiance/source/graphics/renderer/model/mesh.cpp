#include "./pch.h"
#include "./graphics/renderer/model/mesh.h"

#include "./graphics/renderer/renderer_backend.h"

#include "./graphics/RHI/RHI_render_device.h"
#include "./graphics/RHI/object/command/RHI_command_buffer.h"

#include "./graphics/RHI/object/sync/RHI_fenceCPU.h"

namespace Raydiance
{
    namespace Graphics
    {
        Mesh::~Mesh()
        {
            delete m_VertexBuffer;
            delete m_IndexBuffer;
        }

        void Mesh::CreateVertexBuffer(RHI_CommandBuffer* _commandBuffer, std::shared_ptr<RHI_FenceCPU> _fence, void* _data, const uint32_t _size, RHI_BufferLayout _layout)
        {
            RHI_BufferDescriptor bufferDesc;
            bufferDesc.Name = "Generated-VertexStagingBuffer";
            bufferDesc.Size = _size;
            bufferDesc.MemoryType = RHI_ResourceMemoryType::RHI_RESOURCE_MEMORY_TYPE_CPU_MEMORY;
            bufferDesc.Usage = RHI_BufferUsage::RHI_BUFFER_USAGE_STAGING_BUFFER;
            bufferDesc.Data = _data;
            bufferDesc.BufferLayout = _layout;

            RHI_Buffer* stagingBuffer = RHI_RenderDevice::Get().CreateBuffer(&bufferDesc);

            bufferDesc = {};
            bufferDesc.Name = "Generated-VertexBuffer";
            bufferDesc.Size = _size;
            bufferDesc.MemoryType = RHI_ResourceMemoryType::RHI_RESOURCE_MEMORY_TYPE_GPU_MEMORY;
            bufferDesc.Usage = RHI_BufferUsage::RHI_BUFFER_USAGE_VERTEX_BUFFER;
            bufferDesc.Data = nullptr;
            bufferDesc.BufferLayout = _layout;

            m_VertexBuffer = RHI_RenderDevice::Get().CreateBuffer(&bufferDesc);

            _commandBuffer->BeginRecording();
            _commandBuffer->CopyBuffer(stagingBuffer, m_VertexBuffer, _size);
            _commandBuffer->EndRecording();

            //_fence->Reset();
            RendererBackend::SubmitCommandBuffer(_commandBuffer, _fence);
            _fence->Wait();

            delete stagingBuffer;
        }

        void Mesh::CreateIndexBuffer(RHI_CommandBuffer* _commandBuffer, std::shared_ptr<RHI_FenceCPU> _fence, void* _data, const uint32_t _size, RHI_BufferLayout _layout)
        {
            RHI_BufferDescriptor bufferDesc;
            bufferDesc.Name = "Generated-IndexStagingBuffer";
            bufferDesc.Size = _size;
            bufferDesc.MemoryType = RHI_ResourceMemoryType::RHI_RESOURCE_MEMORY_TYPE_CPU_MEMORY;
            bufferDesc.Usage = RHI_BufferUsage::RHI_BUFFER_USAGE_STAGING_BUFFER;
            bufferDesc.Data = _data;
            bufferDesc.BufferLayout = _layout;

            RHI_Buffer* stagingBuffer = RHI_RenderDevice::Get().CreateBuffer(&bufferDesc);

            bufferDesc = {};
            bufferDesc.Name = "Generated-IndexBuffer";
            bufferDesc.Size = _size;
            bufferDesc.MemoryType = RHI_ResourceMemoryType::RHI_RESOURCE_MEMORY_TYPE_GPU_MEMORY;
            bufferDesc.Usage = RHI_BufferUsage::RHI_BUFFER_USAGE_INDEX_BUFFER;
            bufferDesc.Data = nullptr;
            bufferDesc.BufferLayout = _layout;

            m_IndexBuffer = RHI_RenderDevice::Get().CreateBuffer(&bufferDesc);

            _commandBuffer->BeginRecording();
            _commandBuffer->CopyBuffer(stagingBuffer, m_IndexBuffer, _size);
            _commandBuffer->EndRecording();

            RendererBackend::SubmitCommandBuffer(_commandBuffer, _fence);
            _fence->Wait();

            delete stagingBuffer;
        }

        void Mesh::AddSubmesh(SubMesh _mesh)
        {
            m_SubMeshes.push_back(_mesh);
            m_SubMeshCount++;
        }
    }
}