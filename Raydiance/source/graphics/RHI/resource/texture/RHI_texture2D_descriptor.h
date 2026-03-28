#pragma once
#include "./graphics/RHI/resource/RHI_resource_format.h"
#include "./graphics/RHI/resource/RHI_resource_state.h"

#include "./graphics/RHI/resource/texture/RHI_texture_usage.h"

#include <string>

namespace Raydiance
{
	namespace Graphics
	{
		class RHI_Texture2DDescriptor
		{
		public:
			RHI_Texture2DDescriptor() = default;

			std::string DebugName;

			uint32		Width  = 0;
			uint32		Height = 0;

			uint32 UsageFlags  = (uint32) RHI_TextureUsageFlags::RHI_TEXTURE_USAGE_FLAGS_INVALID;

			RHI_ResourceFormat Format		 = RHI_ResourceFormat::RHI_RESOURCE_FORMAT_INVALID;
			RHI_ResourceState  InitialState  = RHI_ResourceState::RHI_RESOURCE_STATE_INVALID; // TODO:: Use the initial state....
		};
	}
}