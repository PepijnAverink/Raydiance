#pragma once
#include "./core/container/types.h"
#include "./graphics/RHI/resource/RHI_resource_format.h"

namespace Raydiance
{
	namespace Graphics
	{
		class RHI_SwapchainDescriptor final
		{
		public:
			RHI_SwapchainDescriptor() = default;

			std::string			Name;

			uint32  			Width;
			uint32  			Height;
			uint8 				BufferCount;

			void*				NativeWindowHandle = nullptr;

			bool				VSync  = true;
			RHI_ResourceFormat  Format = RHI_ResourceFormat::RHI_RESOURCE_FORMAT_INVALID;
		};
	}
}