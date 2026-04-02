#include "./graphics/RHI/resource/texture/RHI_texture2D.h"

namespace Raydiance
{
	namespace Graphics
	{
		RHI_Texture2D::RHI_Texture2D(void)
		{ }

		RHI_Texture2D::~RHI_Texture2D(void)
		{ }

		const Result RHI_Texture2D::Initialize(const RHI_Texture2DDescriptor* _texture2DDescriptor)
		{
			m_Format = _texture2DDescriptor->Format;

			m_Width  = _texture2DDescriptor->Width;
			m_Height = _texture2DDescriptor->Height;

			return Result::RESULT_GOOD;
		}
	}
}