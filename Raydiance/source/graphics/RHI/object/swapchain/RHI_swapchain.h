#pragma once
#include "./graphics/RHI/object/swapchain/RHI_swapchain_descriptor.h"

#include "graphics/RHI/resource/resource_format.h"

#include "./core/error/result.h"

#include <vector> // TODO:: Use array...

namespace Raydiance
{
	namespace Graphics
	{
		class CommandQueue;
		class RHI_FenceCPU;

		class Texture2D;
		class TextureView;
		class RHI_Swapchain
		{
		public:
			// Public destructor
			virtual ~RHI_Swapchain(void);

			virtual void Resize(const CommandQueue& _commandQueue, const uint32 _width, const uint32 _height) = 0;

			virtual uint32 AquireNewImage(CommandQueue* _commandQueue, std::shared_ptr<RHI_FenceCPU> _fence) = 0;
			virtual void     Present(CommandQueue* _commandQueue) = 0;

			inline uint32 GetBufferCount() const { return m_BufferCount; }
			inline uint32 GetCurrentBufferIndex() const { return m_CurrentBufferIndex; }

			inline uint32 GetWidth() const { return m_Width; }
			inline uint32 GetHeight() const { return m_Height; }

			inline ResourceFormat GetFormat() const { return m_Format; }

			inline Texture2D* GetTextureAtIndex(const uint32 _i) const { return m_Textures[_i]; }

		protected:
			// Protected constructor and initialize(), user should not create base instance.
			RHI_Swapchain(void);
			[[nodiscard]] const Result Initialize(const RHI_SwapchainDescriptor& _swapchainDescriptor);

			Window* m_WindowPtr = nullptr;
			uint32  m_Width;
			uint32  m_Height;

			ResourceFormat m_Format = ResourceFormat::RESOURCE_FORMAT_NONE;

			uint32_t m_BufferCount = 0;
			uint32_t m_CurrentBufferIndex = 0;

			std::vector<Texture2D*> m_Textures;
		};
	}
}