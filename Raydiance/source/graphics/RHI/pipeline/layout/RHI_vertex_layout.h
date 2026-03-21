#pragma once
#include "./graphics/RHI/pipeline/layout/RHI_vertex_element.h"

#include <vector>

namespace Raydiance
{
	namespace Graphics
	{
		class RHI_VertexLayout
		{
		public:
			RHI_VertexLayout() = default;
			RHI_VertexLayout(std::initializer_list<RHI_VertexElement> elements)
				: m_Elements(elements)
			{
				CalculateOffsetsAndStride();
			}

			uint32_t GetStride() const { return m_Stride; }
			const std::vector<RHI_VertexElement>& GetElements() const { return m_Elements; }

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

			std::vector<RHI_VertexElement>  m_Elements;
			uint32_t					m_Stride = 0;
		};
	}
}