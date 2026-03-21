#pragma once
#include "./graphics/renderer/model/sub_mesh.h"
#include "./graphics/RHI/resource/buffer/RHI_buffer.h"

#include <memory>
#include <vector>

namespace Raydiance
{
	namespace Graphics
	{
		class RHI_CommandBuffer;
		class RHI_FenceCPU;
		class Mesh
		{
		public:
			Mesh() = default;
			~Mesh();


			// Helpers for the submeshes
			inline uint32_t GetSubmeshCount() const { return m_SubMeshCount; }
			inline std::vector<SubMesh> GetSubMeshes() { return m_SubMeshes; }
			inline const std::vector<SubMesh> GetSubMeshes() const { return m_SubMeshes; }

			// Individual buffer getters
			inline RHI_Buffer* GetVertexBuffer() const { return m_VertexBuffer; }
			inline RHI_Buffer* GetIndexBuffer()  const { return m_IndexBuffer; }

		protected:
			void CreateVertexBuffer(RHI_CommandBuffer* _commandBuffer, std::shared_ptr<RHI_FenceCPU> _fence, void* _data, const uint32_t _size, RHI_BufferLayout _layout);
			void CreateIndexBuffer(RHI_CommandBuffer* _commandBuffer, std::shared_ptr<RHI_FenceCPU> _fence, void* _data, const uint32_t _size, RHI_BufferLayout _layout);

			// Helper for friend classes.
			void AddSubmesh(SubMesh _mesh);

			RHI_Buffer* m_VertexBuffer = nullptr;
			RHI_Buffer* m_IndexBuffer = nullptr;
			RHI_BufferLayout m_VertexBufferLayout;

			uint32_t m_SubMeshCount = 0;
			std::vector<SubMesh> m_SubMeshes;
		};
	}
}