#include "./pch.h"
#include "./graphics/gfx/mesh/mesh.h"


namespace Raydiance
{
	namespace Graphics
	{
		Mesh::Mesh(void)
		{

		}


		Result Mesh::CreateVertexBuffer(RHI_CommandBuffer* _commandBuffer, RHI_FenceCPU* _fence, void* _data, const uint32 _size, RHI_BufferLayout _layout)
		{
			return Result::RESULT_GOOD;
		}


		Result Mesh::CreateIndexBuffer(RHI_CommandBuffer* _commandBuffer, RHI_FenceCPU* _fence, void* _data, const uint32 _size, RHI_BufferLayout _layout)
		{
			return Result::RESULT_GOOD;
		}


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
	}
}