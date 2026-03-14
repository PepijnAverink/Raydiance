#pragma once
// Core includes
#include "./core/error/result.h"

// Graphics includes
#include "./graphics/RHI_api/RHI_graphics_api.h"
#include "./graphics/RHI/render_device_descriptor.h"

//#include "graphics/api/graphics_api.h"
//#include "graphics/RHI/debug_mode.h"

class Window;
namespace Graphics
{
	class CommandPool;
	class CommandPoolDescriptor;
	class CommandBuffer;
	class CommandBufferDescriptor;
	class CommandQueue;
	class CommandQueueDescriptor;
	class Swapchain;
	class SwapchainDescriptor;
	class Fence;
	class FenceDescriptor;

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
	class RenderDevice
	{
	public:
		[[nodiscard]]
		static std::shared_ptr<RenderDevice> Create(RHI_GraphicsAPI _api);
		static std::shared_ptr<RenderDevice> Get();

		virtual ~RenderDevice();

		virtual Raydiance::Result Initialize(const Raydiance::Graphics::RHI_RenderDeviceDescriptor& _renderDeviceDescriptor);

		virtual CommandPool* CreateCommandPool(const CommandPoolDescriptor* _commandPoolDescriptor) = 0;
		virtual CommandBuffer* CreateCommandBuffer(const CommandBufferDescriptor* _commandBufferDescriptor) = 0;
		virtual CommandQueue* CreateCommandQueue(const CommandQueueDescriptor* _commandQueueDescriptor) = 0;
		virtual Swapchain* CreateSwapchain(CommandQueue* _commandQueue, const SwapchainDescriptor* _swapchainDescriptor) = 0;
		virtual Fence* CreateFence(const FenceDescriptor* _fenceDescriptor) = 0;

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
		RenderDevice();

		// API
		RHI_GraphicsAPI m_API = RHI_GraphicsAPI::RHI_GRAPHICS_API_INVALID;

		// DebugMode
		// Set's the DebugEnabled according to the DebugMode
		bool m_DebugEnabled   = false;
		Raydiance::Graphics::RHI_DebugMode m_DebugMode = Raydiance::Graphics::RHI_DebugMode::RHI_DEBUG_MODE_INVALID;
		void CorrectDebugMode();

	};
}