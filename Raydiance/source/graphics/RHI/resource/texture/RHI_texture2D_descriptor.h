#pragma once
#include "./graphics/RHI/resource/RHI_resource_state.h"
#include "./graphics/RHI/resource/RHI_resource_format.h"
#include "./graphics/RHI/resource/texture/RHI_texture_usage.h"

namespace Raydiance
{
	namespace Graphics
	{
		class RHI_Texture2DDescriptor final
		{
		public:
			RHI_Texture2DDescriptor(void)  = default;
			~RHI_Texture2DDescriptor(void) = default;

			std::string		   Name;
			uint32			   Width  = 0;
			uint32			   Height = 0;

			RHI_TextureUsageFlags UsageFlags = RHI_TextureUsageFlags::RHI_TEXTURE_USAGE_FLAGS_INVALID;
			RHI_ResourceFormat	  Format	 = RHI_ResourceFormat::RHI_RESOURCE_FORMAT_INVALID;
		};
	}
}