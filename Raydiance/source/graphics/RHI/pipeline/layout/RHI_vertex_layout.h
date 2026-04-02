#pragma once
#include "./graphics/RHI/pipeline/layout/RHI_vertex_element.h"

#include <vector>

#define VL_POSITION		"POSITION"
#define VL_NORMALS		"NORMAL"
#define VL_TANGENT		"TANGENT"
#define VL_BONE_ID		"BLENDINDICES"
#define VL_BONE_WEIGHT  "BLENDWEIGHT"	

#define VL_TEXCOORDS0	"TEXCOORD0"
#define VL_TEXCOORDS1	"TEXCOORD1"
#define VL_TEXCOORDS2	"TEXCOORD2"
#define VL_TEXCOORDS3	"TEXCOORD3"
#define VL_TEXCOORDS4	"TEXCOORD4"
#define VL_TEXCOORDS5	"TEXCOORD5"
#define VL_TEXCOORDS6	"TEXCOORD6"
#define VL_TEXCOORDS7	"TEXCOORD7"
#define VL_TEXCOORDS8	"TEXCOORD8"
#define VL_TEXCOORDS9	"TEXCOORD9"

namespace Raydiance
{
	namespace Graphics
	{
		class RHI_VertexLayout
		{
		public:
			RHI_VertexLayout() = default;
			RHI_VertexLayout(uint32 _elementCount)
			{
				m_Elements.resize(_elementCount);
			}
			RHI_VertexLayout(std::initializer_list<RHI_VertexElement> elements)
				: m_Elements(elements)
			{
				CalculateOffsetsAndStride();
			}

			void SetStride(const uint32 _stride) { m_Stride = _stride; }
			uint32_t GetStride() const { return m_Stride; }
			const std::vector<RHI_VertexElement>& GetElements() const { return m_Elements; }

			// Operator [] overloading
			RHI_VertexElement& operator[](size_t index)
			{
				return m_Elements[index];
			}
			const RHI_VertexElement& operator[](size_t index) const
			{
				return m_Elements[index];
			}

			std::vector<RHI_VertexElement>::iterator begin() { return m_Elements.begin(); }
			std::vector<RHI_VertexElement>::iterator end() { return m_Elements.end(); }
			std::vector<RHI_VertexElement>::const_iterator begin() const { return m_Elements.begin(); }
			std::vector<RHI_VertexElement>::const_iterator end()	 const { return m_Elements.end(); }
		private:
			void CalculateOffsetsAndStride()
			{
				size_t offset = 0;
				m_Stride = 0;
				for (auto& element : m_Elements)
				{
					element.Offset = offset;
					offset += element.Size;
					m_Stride += element.Size;
				}
			}

			std::vector<RHI_VertexElement> m_Elements;
			uint32_t					   m_Stride = 0;
		};
	}
}