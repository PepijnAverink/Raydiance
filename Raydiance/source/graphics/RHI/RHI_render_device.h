#pragma once
#include "./core/error/result.h"

#include "./graphics/RHI_api/RHI_graphics_api.h"
#include "./graphics/RHI/RHI_adapter.h"
#include "./graphics/RHI/RHI_render_device_descriptor.h"

#include "./graphics/RHI/resource/RHI_resource_format.h"

namespace Raydiance
{
	namespace Graphics
	{
		class RHI_CommandQueue;
		class RHI_CommandQueueDescriptor;
		class RHI_CommandBuffer;
		class RHI_CommandBufferDescriptor;
		class RHI_CommandPool;
		class RHI_CommandPoolDescriptor;

		class RHI_Swapchain;
		class RHI_SwapchainDescriptor;
		class RHI_FenceCPU;
		class RHI_FenceCPUDescriptor;

		class RHI_Texture2D;
		class RHI_Texture2DDescriptor;
		class RHI_Shader;
		class RHI_ShaderDescriptor;
		class RHI_Buffer;
		class RHI_BufferDescriptor;
		class RHI_Sampler;
		class RHI_SamplerDescriptor;

		class RHI_RenderPass;
		class RHI_RenderPassDescriptor;
		class RHI_FrameBuffer;
		class RHI_FrameBufferDescriptor;

		class RHI_DescriptorPool;
		class RHI_DescriptorPoolDescriptor;

		class RHI_InputLayout;
		class RHI_InputLayoutDescriptor;
		class RHI_GraphicsPipeline;
		class RHI_GraphicsPipelineDescriptor;
		class RHI_ComputePipeline;
		class RHI_ComputePipelineDescriptor;

		class RHI_RenderDevice
		{
		public:
			static RHI_RenderDevice* Create(RHI_GraphicsAPI _api);
			static RHI_RenderDevice* Get();

			static void Destroy();

			virtual Result Initialize(const RHI_RenderDeviceDescriptor* _renderDeviceDescriptor);

			// Adapter functions
			// ----------------------------------------------------------------------
			virtual Result GetAdapterCount(uint32& _count) const = 0;
			virtual Result GetAdapter(uint32 _index, RHI_Adapter** _adapter) const = 0;

			virtual Result LinkAdapter(RHI_Adapter* _adapter) = 0;

			// Swapchain functions
			// ----------------------------------------------------------------------
			virtual Result CheckSwapchainResourceFormatSupport(RHI_ResourceFormat _format, bool& _supported) const = 0;
			virtual Result CheckSwapchainCommonResourceFormatsSupport(std::vector<RHI_ResourceFormat>& _support) const;

			// Native create functions
			// ----------------------------------------------------------------------
			virtual RHI_CommandQueue*     RHI_CreateCommandQueue(const RHI_CommandQueueDescriptor* _commandQueueDescriptor) = 0;
			virtual RHI_CommandBuffer*    RHI_CreateCommandBuffer(const RHI_CommandBufferDescriptor* _commandBufferDescriptor) = 0;
			virtual RHI_CommandPool*      RHI_CreateCommandPool(const RHI_CommandPoolDescriptor* _commandPoolDescriptor) = 0;
									      
			virtual RHI_Swapchain*	      RHI_CreateSwapchain(RHI_CommandQueue* _commandQueue, const RHI_SwapchainDescriptor* _swapchainDescriptor) = 0;
			virtual RHI_FenceCPU*		  RHI_CreateFenceCPU(const RHI_FenceCPUDescriptor* _FenceDescriptor) = 0;
									      
			virtual RHI_Texture2D*	      RHI_CreateTexture2D(const RHI_Texture2DDescriptor* _texture2DDescriptor) = 0;
			virtual RHI_Shader*		      RHI_CreateShader(const RHI_ShaderDescriptor* _shaderDescriptor) = 0;
			virtual RHI_Buffer*		      RHI_CreateBuffer(const RHI_BufferDescriptor* _bufferDescriptor) = 0;
			virtual RHI_Sampler*	      RHI_CreateSampler(const RHI_SamplerDescriptor* _samplerDescriptor) = 0;
									      
			virtual RHI_RenderPass*	      RHI_CreateRenderPass(const RHI_RenderPassDescriptor* _renderPassDescriptor) = 0;
			virtual RHI_FrameBuffer*      RHI_CreateFrameBuffer(const RHI_FrameBufferDescriptor* _frameBufferDescriptor) = 0;
										  
			virtual RHI_DescriptorPool*   RHI_CreateDescriptorPool(const RHI_DescriptorPoolDescriptor* _descriptorPoolDescriptor) = 0;

			virtual RHI_InputLayout*	  RHI_CreateInputLayout(const RHI_InputLayoutDescriptor* _inputLayoutDescriptor) = 0;
			virtual RHI_GraphicsPipeline* RHI_CreateGraphicsPipeline(const RHI_GraphicsPipelineDescriptor* _graphicsPipelineDescriptor) = 0;
			virtual RHI_ComputePipeline*  RHI_CreateComputePipeline(const RHI_ComputePipelineDescriptor* _computePipelineDescriptor) = 0;

			// Utility functions
			// ----------------------------------------------------------------------
			inline RHI_DebugMode  RHI_GetDebugMode() const { return m_DebugMode; }
			inline bool        Is_DebugModeEnabled() const { return m_DebugModeEnabled; }

			inline RHI_Adapter* RHI_GetAdapter() const { return m_Adapter; }

		protected:
			RHI_RenderDevice(void);
			virtual ~RHI_RenderDevice(void);

			// Graphics API
			// ----------------------------------------------------------------------
			RHI_GraphicsAPI m_API = RHI_GraphicsAPI::RHI_GRAPHICS_API_INVALID;

			// Debug mode variables
			// ----------------------------------------------------------------------
			RHI_DebugMode m_DebugMode = RHI_DebugMode::RHI_DEBUG_MODE_INVALID;
			bool		  m_DebugModeEnabled = false;

			// Hardware adapter
			// ----------------------------------------------------------------------
			RHI_Adapter* m_Adapter = nullptr;

			std::vector<RHI_CommandQueueAllocation> m_CommandQueueAllocations;
		private:
			void CorrectDebugMode(void);
		};
	}
}