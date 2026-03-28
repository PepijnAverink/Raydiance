#pragma once
// Core includes
#include "./core/error/result.h"

// Graphics includes
#include "./graphics/RHI_api/RHI_graphics_api.h"

#include "./graphics/RHI/RHI_adapter.h"
#include "./graphics/RHI/RHI_debug_mode.h"
#include "./graphics/RHI/RHI_render_device_descriptor.h"

#include <memory>

class Window;
namespace Raydiance
{
	namespace Graphics
	{
		class RHI_CommandPool;
		class RHI_CommandPoolDescriptor;
		class RHI_CommandBuffer;
		class RHI_CommandBufferDescriptor;
		class RHI_CommandQueue;
		class RHI_CommandQueueDescriptor;
		class RHI_Swapchain;
		class RHI_SwapchainDescriptor;
		class RHI_FenceCPU;
		class RHI_FenceCPUDescriptor;

		class RHI_GraphicsPipeline;
		class RHI_GraphicsPipelineDescriptor;
		class RHI_InputLayout;
		class RHI_InputLayoutDescriptor;
		class RHI_RenderPass;
		class RHI_RenderPassDescriptor;
		class RHI_FrameBuffer;
		class RHI_FrameBufferDescriptor;

		class RHI_DescriptorPool;
		class RHI_DescriptorPoolDescriptor;
		class RHI_DescriptorSet;
		class RHI_DescriptorSetDescriptor;

		class RHI_Buffer;
		class RHI_BufferDescriptor;
		class RHI_Shader;
		class RHI_ShaderDescriptor;
		class RHI_Texture2D;
		class RHI_Texture2DDescriptor;
		class RHI_Sampler;
		class RHI_SamplerDescriptor;
		class RHI_RenderDevice
		{
		public:
			// Public destructor
			virtual ~RHI_RenderDevice();


			// RHI_RenderDevice creation, retrieval and destruction
			// ====================================================
			[[nodiscard]] static Result Create(RHI_GraphicsAPI _api);
			[[nodiscard]] static Result Destroy();

			[[nodiscard]] virtual Result Initialize(const RHI_RenderDeviceDescriptor& _renderDeviceDescriptor); // Needs to be public, because we are not making an abstract version implicitely.
																												// TODO:: Could move Initialize() call into create(), then its abstracted away from the user, and this can be proetected, like it should.
			// Singleton getter
			[[nodiscard]] static RHI_RenderDevice& Get();


			// TODO:: Check if adapter functions can be marked with noexcept.
			// Adapter functions
			// ----------------------------------------------------------------------
			[[nodiscard]] virtual Result GetAdapterCount(uint32& _count) const = 0;
			[[nodiscard]] virtual Result GetAdapter(const uint32 _adapterID, std::unique_ptr<RHI_Adapter>& _adapter) const = 0;

			[[nodiscard]] virtual Result LinkAdapter(std::unique_ptr<RHI_Adapter> _adapter) = 0;

			
			// Gets the active physical adapter.
			[[nodiscard]] inline const RHI_Adapter& GetActiveAdapter() const noexcept { return *m_Adapter; }


			// Create functions
			// ----------------------------------------------------------------------
			[[nodiscard]] virtual std::shared_ptr<RHI_CommandPool>   CreateCommandPool   (const RHI_CommandPoolDescriptor&   _commandPoolDescriptor)   = 0;
			[[nodiscard]] virtual std::shared_ptr<RHI_CommandBuffer> CreateCommandBuffer (const RHI_CommandBufferDescriptor& _commandBufferDescriptor) = 0;
			[[nodiscard]] virtual std::shared_ptr<RHI_CommandQueue>  CreateCommandQueue  (const RHI_CommandQueueDescriptor&  _commandQueueDescriptor)  = 0;
			
			[[nodiscard]] virtual std::shared_ptr<RHI_Swapchain>     CreateSwapchain     (const RHI_CommandQueue&		     _commandQueue, const RHI_SwapchainDescriptor& _swapchainDescriptor) = 0;
			[[nodiscard]] virtual std::shared_ptr<RHI_FenceCPU>      CreateFenceCPU      (const RHI_FenceCPUDescriptor&      _fenceDescriptor) = 0;

			[[nodiscard]] virtual RHI_GraphicsPipeline* CreateGraphicsPipeline(const RHI_GraphicsPipelineDescriptor* _graphicsPipelineDescriptor) = 0;
			[[nodiscard]] virtual RHI_InputLayout* CreateInputLayout(const RHI_InputLayoutDescriptor* _inputLayoutDescriptor) = 0;
			[[nodiscard]] virtual RHI_RenderPass* CreateRenderPass(const RHI_RenderPassDescriptor* _renderPassDescriptor) = 0;
			[[nodiscard]] virtual RHI_FrameBuffer* CreateFrameBuffer(const RHI_FrameBufferDescriptor* _frameBufferDescriptor) = 0;

			[[nodiscard]] virtual RHI_DescriptorPool* CreateDescriptorPool(const RHI_DescriptorPoolDescriptor* _descriptorPoolDescriptor) = 0;

			[[nodiscard]] virtual RHI_Buffer* CreateBuffer(const RHI_BufferDescriptor* _bufferDescriptor) = 0;
			[[nodiscard]] virtual RHI_Shader* CreateShader(const RHI_ShaderDescriptor* _shaderDescriptor) = 0;
			[[nodiscard]] virtual RHI_Texture2D* CreateTexture2D(const RHI_Texture2DDescriptor* _texture2DDescriptor) = 0;
			[[nodiscard]] virtual RHI_Sampler* CreateSampler(const RHI_SamplerDescriptor& _sampler2DDescripotr) = 0;

			// Utility functions
			// ----------------------------------------------------------------------
			inline RHI_DebugMode  GetDebugMode() const { return m_DebugMode; }
			inline bool     IsDebugModeEnabled() const { return m_DebugModeEnabled; }

		protected:
			// Protected constructor, user should not create base instance.
			RHI_RenderDevice(RHI_GraphicsAPI _api);

			// Graphics API of the 'RHI_RenderDevice' object, set at construction and cannot be changed.
			RHI_GraphicsAPI				 m_API = RHI_GraphicsAPI::RHI_GRAPHICS_API_INVALID;
			std::unique_ptr<RHI_Adapter> m_Adapter; // The active adapter also cannot be changed after it is linked to the device.


			// DebugMode
			// ----------------------------------------------------------------
			// Set's the DebugEnabled according to the DebugMode
			bool		  m_DebugModeEnabled = false;
			RHI_DebugMode m_DebugMode        = RHI_DebugMode::RHI_DEBUG_MODE_INVALID;


			std::vector<RHI_CommandQueueAllocation> m_CommandQueueAllocations;

		private:
			// Should only be called by the local initialization function.
			void CorrectDebugMode();
		};
	}
}