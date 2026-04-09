#include "./pch.h"
#include "./graphics/gfx/mesh/primitive/cube.h"


namespace Raydiance
{
	namespace Graphics
	{

		Cube::Cube(RHI_VertexLayout _vertexLayout, RHI_CommandBuffer* _commandBuffer, RHI_FenceCPU* _fence)
			: Mesh()
		{
			uint32 vertexCount = 4;

			std::vector<float> vertexData;

			std::vector<std::vector<float>> vertexPositions = 
			{ 
				// Front
				{ -0.5f, -0.5f, 0.5f },
				{  0.5f, -0.5f, 0.5f },
				{  0.5f,  0.5f, 0.5f },
				{ -0.5f,  0.5f, 0.5f },

				// Right
				{ 0.5f, -0.5f,  0.5f },
				{ 0.5f, -0.5f, -0.5f },
				{ 0.5f,  0.5f, -0.5f },
				{ 0.5f,  0.5f,  0.5f },
				// Back
				{  0.5f, -0.5f, -0.5f },
				{ -0.5f, -0.5f, -0.5f },
				{ -0.5f,  0.5f, -0.5f },
				{  0.5f,  0.5f, -0.5f },
				// Left
				{ -0.5f, -0.5f, -0.5f },
				{ -0.5f, -0.5f,  0.5f },
				{ -0.5f,  0.5f,  0.5f },
				{ -0.5f,  0.5f, -0.5f },
				// Top
				{ -0.5f, 0.5f,  0.5f },
				{  0.5f, 0.5f,  0.5f },
				{  0.5f, 0.5f, -0.5f },
				{ -0.5f, 0.5f, -0.5f },
				// Bottom
				{ -0.5f, -0.5f, -0.5f },
				{  0.5f, -0.5f, -0.5f },
				{  0.5f, -0.5f,  0.5f },
				{ -0.5f, -0.5f,  0.5f },
			};

			std::vector<std::vector<float>> textureCoords = { 
				// Front
				{0.0f, 0.0f},
				{1.0f, 0.0f},
				{1.0f, 1.0f},
				{0.0f, 1.0f},
				
				// Right
				{0.0f, 0.0f},
				{1.0f, 0.0f},
				{1.0f, 1.0f},
				{0.0f, 1.0f},
				// Back
				{0.0f, 0.0f},
				{1.0f, 0.0f},
				{1.0f, 1.0f},
				{0.0f, 1.0f},
				// Left
				{0.0f, 0.0f},
				{1.0f, 0.0f},
				{1.0f, 1.0f},
				{0.0f, 1.0f},
				// Top
				{0.0f, 0.0f},
				{1.0f, 0.0f},
				{1.0f, 1.0f},
				{0.0f, 1.0f},
				// Bottom
				{0.0f, 0.0f},
				{1.0f, 0.0f},
				{1.0f, 1.0f},
				{0.0f, 1.0f},
			};

			std::vector<std::vector<float>> vertexNormals = 
			{
				// Front
				{ 0.0f, 0.0f, 1.0f },
				{ 0.0f, 0.0f, 1.0f },
				{ 0.0f, 0.0f, 1.0f },
				{ 0.0f, 0.0f, 1.0f },

				// Right
				{ 1.0f, 0.0f, 0.0f },
				{ 1.0f, 0.0f, 0.0f },
				{ 1.0f, 0.0f, 0.0f },
				{ 1.0f, 0.0f, 0.0f },
				// Back
				{ 0.0f, 0.0f, -1.0f },
				{ 0.0f, 0.0f, -1.0f },
				{ 0.0f, 0.0f, -1.0f },
				{ 0.0f, 0.0f, -1.0f },
				// Left
				{ -1.0f, 0.0f, 0.0f },
				{ -1.0f, 0.0f, 0.0f },
				{ -1.0f, 0.0f, 0.0f },
				{ -1.0f, 0.0f, 0.0f },
				// Top
				{ 0.0f, 1.0f, 0.0f },
				{ 0.0f, 1.0f, 0.0f },
				{ 0.0f, 1.0f, 0.0f },
				{ 0.0f, 1.0f, 0.0f },
				// Bottom
				{ 0.0f, -1.0f, 0.0f },
				{ 0.0f, -1.0f, 0.0f },
				{ 0.0f, -1.0f, 0.0f },
				{ 0.0f, -1.0f, 0.0f },
			};
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
						vertexData.insert(vertexData.end(), vertexNormals[i].begin(), vertexNormals[i].end());
					}
					// Tangents
					else if (vertexElements[j].Name == VL_TANGENT)
					{
						Logger::Log("Tangents currently unsupported for Quad primitive mesh.", LogLevel::LOG_LEVEL_WARNING);
					}
				}
			}

			CreateVertexBuffer(_commandBuffer, _fence, vertexData.data(), vertexCount * _vertexLayout.GetStride(), _vertexLayout);

			std::vector<uint32> indexData = {
				// Front
				2, 1, 0,
				0, 3, 2,
				// Right
				6, 5, 4,
				4, 7, 6,
				// Back
				10, 9, 8,
				8, 11, 10,
				// Left
				14, 13, 12,
				12, 15, 14,
				// Top
				18, 17, 16,
				16, 19, 18,
				// Bottom
				22, 21, 20,
				20, 23, 22,
			};

			Graphics::RHI_BufferLayout indexBufferLayout = Graphics::RHI_BufferLayout({ { "INDEX", Graphics::RHI_ResourceFormat::RHI_RESOURCE_FORMAT_R32_UINT }, });

			CreateIndexBuffer(_commandBuffer, _fence, indexData.data(), indexData.size() * sizeof(uint32), indexBufferLayout);

			SubMesh submeh;
			submeh.Name         = "Cube";
			submeh.VertexCount  = 24;
			submeh.VertexOffset = 0;
			submeh.IndexCount   = 36;
			submeh.IndexOffset  = 0;

			AddSubMesh(submeh);
		}


		Cube::~Cube(void)
		{ }
	}
}