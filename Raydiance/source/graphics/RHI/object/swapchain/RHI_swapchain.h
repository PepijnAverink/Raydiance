#pragma once
// Core includes
#include "./core/error/result.h"

// Graphics includes
#include "./graphics/RHI/object/swapchain/RHI_swapchain_descriptor.h"

namespace Raydiance
{
	namespace Graphics
	{
		class RHI_FenceCPU;
		class RHI_Texture2D;
		
		class RHI_CommandQueue;

		class RHI_RenderDevice;
		class RHI_Swapchain
		{
		public:
			virtual ~RHI_Swapchain(void);
			const Result Initialize(const RHI_SwapchainDescriptor* _swapchainDescriptor);

			virtual void Resize(RHI_RenderDevice* _RHI_RenderDevice, RHI_CommandQueue* _commandQueue, RHI_FenceCPU* _fence, const uint32_t _width, const uint32_t _height) = 0;

			virtual uint32_t AquireNewFrame(RHI_CommandQueue* _commandQueue, RHI_FenceCPU* _fence) = 0;
			virtual void Present(RHI_CommandQueue* _commandQueue) = 0;


			// Getters
			virtual RHI_Texture2D* GetCurrentRenderTexture(void) const { return m_RenderTargets[m_BufferIndex]; }
			virtual RHI_Texture2D* GetRenderTextureAtIndex(const uint32_t _id) const { return m_RenderTargets[_id]; }


			inline uint32 GetBufferIndex(void)   const { return m_BufferIndex; }
			inline uint32 GetBufferCount(void)   const { return m_BufferCount; }

			inline uint32_t GetBufferWidth(void)  const { return m_Width; }
			inline uint32_t GetBufferHeight(void) const { return m_Height; }

			inline bool IsVSyncEnabled(void) const { return m_VSync; }
			inline RHI_ResourceFormat GetBufferFormat(void) const { return m_ResourceFormat; }

		protected:
			RHI_Swapchain(void);
			void ReleaseBuffers(void);

			uint32   		m_Width  = 0;
			uint32			m_Height = 0;
			uint32			m_BufferCount = 0;

			uint32_t		m_BufferIndex = 0;
			RHI_Texture2D** m_RenderTargets = nullptr;

			bool			m_VSync = false;
			RHI_ResourceFormat m_ResourceFormat = RHI_ResourceFormat::RHI_RESOURCE_FORMAT_INVALID;
		};
	}
}