#pragma once
#include "./graphics/RHI/resource/RHI_resource_format.h"
#include "./graphics/RHI/resource/RHI_resource_state.h"

#include <string>

namespace Raydiance
{
	namespace Graphics
	{
		class RHI_Texture2DDescriptor
		{
		public:
			RHI_Texture2DDescriptor() = default;

			std::string Name;
			uint32 Width = 0;
			uint32 Height = 0;

			RHI_ResourceFormat Format = RHI_ResourceFormat::RHI_RESOURCE_FORMAT_INVALID;
			RHI_ResourceState  State  = RHI_ResourceState::RHI_RESOURCE_STATE_INVALID;
		};
	}
}