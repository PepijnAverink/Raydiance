#pragma once
// Core includes
#include "./core/error/result.h"

// Graphics includes
#include "./graphics/RHI_api/RHI_graphics_api.h"

#include "./graphics/RHI/RHI_render_device_descriptor.h"

//#include "graphics/api/graphics_api.h"
//#include "graphics/RHI/debug_mode.h"

#include <memory>

class Window;
namespace Raydiance
{
	namespace Graphics
	{
		class CommandPool;
		class CommandPoolDescriptor;
		class CommandBuffer;
		class CommandBufferDescriptor;
		class CommandQueue;
		class CommandQueueDescriptor;
		class RHI_Swapchain;
		class RHI_SwapchainDescriptor;
		class RHI_Fence;
		class RHI_FenceDescriptor;

		class GraphicsPipeline;
		class GraphicsPipelineDescriptor;
		class InputLayout;
		class InputLayoutDescriptor;
		class RenderPass;
		class RenderPassDescriptor;
		class FrameBuffer;
		class FrameBufferDescriptor;

		class DescriptorPool;
		class DescriptorPoolDescriptor;
		class DescriptorSet;
		class DescriptorSetDescriptor;

		class Buffer;
		class BufferDescriptor;
		class Shader;
		class ShaderDescriptor;
		class Texture2D;
		class Texture2DDescriptor;
		class Sampler2D;
		class Sampler2DDescriptor;
		class RHI_RenderDevice
		{
		public:
			// RHI_RenderDevice creation, retrieval and destruction
			// ====================================================
			[[nodiscard]]
			static std::shared_ptr<RHI_RenderDevice> Create(RHI_GraphicsAPI _api);
			[[nodiscard]]
			static std::shared_ptr<RHI_RenderDevice> Get();

			virtual ~RHI_RenderDevice();

			[[nodiscard]]
			virtual Raydiance::Result Initialize(const Raydiance::Graphics::RHI_RenderDeviceDescriptor& _renderDeviceDescriptor);

			// Adapter functions
			// ----------------------------------------------------------------------
			[[nodiscard]]
			virtual Result GetAdapterCount(uint32& _count) const = 0;
			//virtual Result GetAdapter(uint32 _index, RHI_Adapter** _adapter) const = 0;

			//virtual Result LinkAdapter(RHI_Adapter* _adapter) = 0;


			virtual CommandPool*   CreateCommandPool(const CommandPoolDescriptor* _commandPoolDescriptor) = 0;
			virtual CommandBuffer* CreateCommandBuffer(const CommandBufferDescriptor* _commandBufferDescriptor) = 0;
			virtual CommandQueue*  CreateCommandQueue(const CommandQueueDescriptor* _commandQueueDescriptor) = 0;
			virtual RHI_Swapchain* CreateSwapchain(CommandQueue* _commandQueue, const RHI_SwapchainDescriptor* _swapchainDescriptor) = 0;
			virtual RHI_Fence*     CreateFence(const RHI_FenceDescriptor* _fenceDescriptor) = 0;

			virtual GraphicsPipeline* CreateGraphicsPipeline(const GraphicsPipelineDescriptor* _graphicsPipelineDescriptor) = 0;
			virtual InputLayout* CreateInputLayout(const InputLayoutDescriptor* _inputLayoutDescriptor) = 0;
			virtual RenderPass* CreateRenderPass(const RenderPassDescriptor* _renderPassDescriptor) = 0;
			virtual FrameBuffer* CreateFrameBuffer(const FrameBufferDescriptor* _frameBufferDescriptor) = 0;

			virtual DescriptorPool* CreateDescriptorPool(const DescriptorPoolDescriptor* _descriptorPoolDescriptor) = 0;

			virtual Buffer* CreateBuffer(const BufferDescriptor* _bufferDescriptor) = 0;
			virtual Shader* CreateShader(const ShaderDescriptor* _shaderDescriptor) = 0;

			virtual Texture2D* CreateTexture2D(const Texture2DDescriptor* _texture2DDescriptor) = 0;
			virtual Sampler2D* CreateSampler2D(const Sampler2DDescriptor* _sampler2DDescripotr) = 0;

		protected:
			RHI_RenderDevice();

			// API
			RHI_GraphicsAPI m_API = RHI_GraphicsAPI::RHI_GRAPHICS_API_INVALID;

			// DebugMode
			// Set's the DebugEnabled according to the DebugMode
			bool m_DebugEnabled = false;
			Raydiance::Graphics::RHI_DebugMode m_DebugMode = Raydiance::Graphics::RHI_DebugMode::RHI_DEBUG_MODE_INVALID;
			void CorrectDebugMode();

		};
	}
}