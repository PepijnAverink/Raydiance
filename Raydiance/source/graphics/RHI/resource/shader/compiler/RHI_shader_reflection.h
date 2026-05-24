#pragma once
// Graphics api's includes
#include "./graphics/RHI_api/RHI_graphics_api.h"


namespace Raydiance
{
	namespace Graphics
	{
		class RHI_ShaderReflection
		{
		public:
			virtual ~RHI_ShaderReflection();
			
			static RHI_ShaderReflection* Reflection(RHI_GraphicsAPI _api, void* _data, size_t _size);


		protected:
			RHI_ShaderReflection();
		};
	}
}