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
			// Public destructor
			virtual ~RHI_RenderDevice();


			// RHI_RenderDevice creation, retrieval and destruction
			// ====================================================
			[[nodiscard]] static Result Create(RHI_GraphicsAPI _api);
			[[nodiscard]] static Result Destroy();

			[[nodiscard]] virtual Result Initialize(const RHI_RenderDeviceDescriptor& _renderDeviceDescriptor);

			// Singleton getter
			[[nodiscard]] static RHI_RenderDevice& Get();


			// TODO:: Check if adapter functions can be marked with noexcept.
			// Adapter functions
			// ----------------------------------------------------------------------
			[[nodiscard]] virtual Result GetAdapterCount(uint32& _count) const = 0;
			[[nodiscard]] virtual Result GetAdapter(const uint32 _adapterID, std::unique_ptr<RHI_Adapter>& _adapter) const = 0;

			[[nodiscard]] virtual Result LinkAdapter(std::unique_ptr<RHI_Adapter> _adapter) = 0;


			// Gets the active physical adapter.
			[[nodiscard]] inline RHI_Adapter& GetActiveAdapter() const noexcept { return *m_Adapter; }


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
			// Protected constructor, user should not create base instance.
			RHI_RenderDevice(RHI_GraphicsAPI _api);

			// Graphics API of the 'RHI_RenderDevice' object, set at construction and cannot be changed.
			RHI_GraphicsAPI				 m_API = RHI_GraphicsAPI::RHI_GRAPHICS_API_INVALID;
			std::unique_ptr<RHI_Adapter> m_Adapter; // The active adapter also cannot be changed after it is linked to the device.


			// DebugMode
			// ----------------------------------------------------------------
			// Set's the DebugEnabled according to the DebugMode
			bool		  m_DebugEnabled = false;
			RHI_DebugMode m_DebugMode    = RHI_DebugMode::RHI_DEBUG_MODE_INVALID;


		private:
			// Should only be called by the local initialization function.
			void CorrectDebugMode();
		};
	}
}