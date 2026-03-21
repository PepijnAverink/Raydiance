#pragma once
#include "./graphics/RHI/resource/texture/RHI_texture2D_descriptor.h"

namespace Raydiance
{
	namespace Graphics
	{
		class RHI_Texture2D
		{
		public:
			RHI_Texture2D(const RHI_Texture2DDescriptor* _texture2DDescriptor);
			virtual ~RHI_Texture2D();

			// Get dimensions
			inline uint32_t GetWidth() const { return m_Width; }
			inline uint32_t GetHeight() const { return m_Height; }

			inline RHI_ResourceFormat GetFormat() const { return m_Format; }

		protected:
			uint32_t m_Width;
			uint32_t m_Height;

			RHI_ResourceFormat m_Format = RHI_ResourceFormat::RHI_RESOURCE_FORMAT_INVALID;
			RHI_ResourceState m_State = RHI_ResourceState::RHI_RESOURCE_STATE_INVALID;
		};
	}
}