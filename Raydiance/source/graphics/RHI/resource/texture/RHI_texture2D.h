#pragma once
#include "./core/error/result.h"

#include "./graphics/RHI/resource/texture/RHI_texture2D_descriptor.h"

namespace Raydiance
{
	namespace Graphics
	{
		class RHI_Texture2D
		{
		public:
			virtual ~RHI_Texture2D(void);

			// Getters
			inline uint32 GetWidth(void)  const { return m_Width; }
			inline uint32 GetHeight(void) const { return m_Height; }

			inline RHI_ResourceFormat GetFormat(void) const { return m_Format; }

		protected:
			RHI_Texture2D(void);

			const Result Initialize(const RHI_Texture2DDescriptor* _texture2DDescriptor);
			
			uint32			   m_Width = 0;
			uint32			   m_Height = 0;
			RHI_ResourceFormat m_Format;
		};
	}
}