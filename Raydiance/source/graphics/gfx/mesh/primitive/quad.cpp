#include "./pch.h"
#include "./graphics/gfx/mesh/primitive/quad.h"


namespace Raydiance
{
	namespace Graphics
	{

		Quad::Quad(RHI_VertexLayout _vertexLayout, RHI_CommandBuffer* _commandBuffer, RHI_FenceCPU* _fence)
			: Mesh()
		{
			uint32 vertexCount = 4;

			std::vector<float> vertexData;

			std::vector<std::vector<float>> vertexPositions = { { -1.0f, -1.0f, 0.0f }, { 1.0f, -1.0f, 0.0f }, { 1.0f,  1.0f, 0.0f }, { -1.0f, 1.0f, 0.0f } };
			std::vector<std::vector<float>> textureCoords = { { 0.0f, 1.0f }, { 1.0f, 1.0f }, { 1.0f,  0.0f }, { 0.0f, 0.0f } };
			std::vector<float> vertexNormals = { 0.0f, 0.0f, 1.0f };
			for (uint32 i = 0; i < vertexCount; i++)
			{
				std::vector<Graphics::RHI_VertexElement> vertexElements = _vertexLayout.GetElements();
				for (uint32_t j = 0; j < vertexElements.size(); j++)
				{
					// Vertex Position
					if (vertexElements[j].Name == VL_POSITION)
					{
						vertexData.insert(vertexData.end(), vertexPositions[i].begin(), vertexPositions[i].end());
					}
					// Texture coordinates
					else if (vertexElements[j].Name == VL_TEXCOORDS0)
					{
						vertexData.insert(vertexData.end(), textureCoords[i].begin(), textureCoords[i].end());
					}
					// Normals
					else if (vertexElements[j].Name == VL_NORMALS)
					{
						vertexData.insert(vertexData.end(), vertexNormals.begin(), vertexNormals.end());
					}
					// Tangents
					else if (vertexElements[j].Name == VL_TANGENT)
					{
						Logger::Log("Tangents currently unsupported for Quad primitive mesh.", LogLevel::LOG_LEVEL_WARNING);
					}
				}
			}

			CreateVertexBuffer(_commandBuffer, _fence, vertexData.data(), vertexCount * _vertexLayout.GetStride(), _vertexLayout);

			std::vector<uint32> indexData = { 0, 1, 2, 0, 2, 3 };
			Graphics::RHI_BufferLayout indexBufferLayout = Graphics::RHI_BufferLayout({ { "INDEX", Graphics::RHI_ResourceFormat::RHI_RESOURCE_FORMAT_R32_UINT }, });

			CreateIndexBuffer(_commandBuffer, _fence, indexData.data(), indexData.size() * sizeof(uint32), indexBufferLayout);

			SubMesh submeh;
			submeh.Name         = "Quad";
			submeh.VertexCount  = 4;
			submeh.VertexOffset = 0;
			submeh.IndexCount   = 6;
			submeh.IndexOffset  = 0;

			AddSubMesh(submeh);
		}


		Quad::~Quad(void)
		{ }
	}
}