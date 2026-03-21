#pragma once
#include "./graphics/RHI/object/swapchain/RHI_swapchain_descriptor.h"

// Graphics includes
#include "./graphics/RHI/object/command/RHI_command_queue.h"

#include "graphics/RHI/resource/RHI_resource_format.h"

#include "./core/error/result.h"

#include <vector> // TODO:: Use array...

namespace Raydiance
{
	namespace Graphics
	{
		class RHI_FenceCPU;

		class RHI_Texture2D;
		class TextureView;
		class RHI_Swapchain
		{
		public:
			// Public destructor
			virtual ~RHI_Swapchain(void);

			virtual void Resize(const RHI_CommandQueue& _commandQueue, const uint32 _width, const uint32 _height) = 0;

			virtual uint32 AquireNewImage(RHI_CommandQueue* _commandQueue, std::shared_ptr<RHI_FenceCPU> _fence) = 0;
			virtual void   Present(RHI_CommandQueue* _commandQueue) = 0;

			inline uint32 GetBufferCount() const { return m_BufferCount; }
			inline uint32 GetCurrentBufferIndex() const { return m_CurrentBufferIndex; }

			inline uint32 GetWidth() const { return m_Width; }
			inline uint32 GetHeight() const { return m_Height; }

			inline RHI_ResourceFormat GetFormat() const { return m_Format; }

			inline RHI_Texture2D* GetTextureAtIndex(const uint32 _i) const { return m_Textures[_i]; }

		protected:
			// Protected constructor and initialize(), user should not create base instance.
			RHI_Swapchain(void);
			[[nodiscard]] const Result Initialize(const RHI_SwapchainDescriptor& _swapchainDescriptor);

			Window* m_WindowPtr = nullptr; //TODO:: Do we have to store this??
			uint32  m_Width     = 0;
			uint32  m_Height    = 0;

			RHI_ResourceFormat m_Format = RHI_ResourceFormat::RHI_RESOURCE_FORMAT_INVALID;

			uint32_t m_BufferCount		  = 0;
			uint32_t m_CurrentBufferIndex = 0;

			std::vector<RHI_Texture2D*> m_Textures;
		};
	}
}