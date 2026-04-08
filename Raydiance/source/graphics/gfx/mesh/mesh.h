#pragma once
// Core includes
#include "./core/error/result.h"


// Graphics includes
#include "./graphics/gfx/mesh/sub_mesh.h"

#include "./graphics/RHI/object/sync/RHI_fenceCPU.h"
#include "./graphics/RHI/object/command/RHI_command_buffer.h"
#include "./graphics/RHI/resource/buffer/RHI_buffer.h"


namespace Raydiance
{
	namespace Graphics
	{
		class Mesh
		{
		public:
			virtual ~Mesh(void);

			// Submesh helper functions
			void AddSubMesh(const SubMesh& _subMesh);

			inline uint32 GetSubMeshCount(void) const { return m_SubMeshCount; }
			inline       std::vector<SubMesh>& GetSubMeshes()       { return m_SubMeshes; }
			inline const std::vector<SubMesh>& GetSubMeshes() const { return m_SubMeshes; }


			// Individual buffer getters
			inline RHI_Buffer* GetVertexBuffer(void) const { return m_VertexBuffer; }
			inline RHI_Buffer* GetIndexBuffer(void)  const { return m_IndexBuffer; }


			// VerteLayout
			inline void SetVertexLayout(const RHI_BufferLayout& _layout) { m_VertexLayout = _layout; }
			inline RHI_BufferLayout GetVertexLayout(void) const { return m_VertexLayout; }


			// Get index format
			inline RHI_ResourceFormat GetIndexFormat(void) const { return m_IndexFormat; }

		protected:
			Mesh(void);

			// Protected helper functiosn for creation of the internal buffers
			Result CreateVertexBuffer(RHI_CommandBuffer* _commandBuffer, RHI_FenceCPU* _fence, void* _data, const uint32 _size, RHI_BufferLayout _layout);
			Result CreateIndexBuffer(RHI_CommandBuffer* _commandBuffer, RHI_FenceCPU* _fence, void* _data, const uint32 _size, RHI_BufferLayout _layout);


			// Raw internal resources
			RHI_Buffer* m_VertexBuffer = nullptr;
			RHI_Buffer* m_IndexBuffer  = nullptr;


			// Internal layouts
			RHI_BufferLayout   m_VertexLayout;
			RHI_ResourceFormat m_IndexFormat = RHI_ResourceFormat::RHI_RESOURCE_FORMAT_INVALID;


			// Submesh data
			uint32			     m_SubMeshCount = 0;
			std::vector<SubMesh> m_SubMeshes;
		};
	}
}