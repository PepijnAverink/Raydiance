#pragma once
// Parant class include
#include "./graphics/RHI/RHI_render_device.h"

#include <d3d12.h>
#include <dxgi.h>
#include <dxgi1_3.h>

namespace Raydiance
{
	namespace Graphics
	{
		class RHI_DX12_RenderDevice final : public RHI_RenderDevice
		{
		public:
			         RHI_DX12_RenderDevice();
			virtual ~RHI_DX12_RenderDevice();

			virtual Result Initialize(const RHI_RenderDeviceDescriptor& _renderDeviceDescriptor) override;

			// Adapter functions
			// ----------------------------------------------------------------------
			[[nodiscard]] virtual Result GetAdapterCount(uint32& _count) const override;
			[[nodiscard]] virtual Result GetAdapter(const uint32 _adapterID, std::unique_ptr<RHI_Adapter>& _adapter) const override;

			[[nodiscard]] virtual Result LinkAdapter(std::unique_ptr<RHI_Adapter> _adapter) override;


			// Create functions
			// ----------------------------------------------------------------------
			[[nodiscard]] virtual std::shared_ptr<RHI_CommandPool>   CreateCommandPool(const RHI_CommandPoolDescriptor& _commandPoolDescriptor) override;
			[[nodiscard]] virtual std::shared_ptr<RHI_CommandBuffer> CreateCommandBuffer(const RHI_CommandBufferDescriptor& _commandBufferDescriptor) override;
			[[nodiscard]] virtual std::shared_ptr<RHI_CommandQueue>  CreateCommandQueue(const RHI_CommandQueueDescriptor& _commandQueueDescriptor) override;
			[[nodiscard]] virtual std::shared_ptr<RHI_Swapchain>     CreateSwapchain(const RHI_CommandQueue& _commandQueue, const RHI_SwapchainDescriptor& _swapchainDescriptor) override;
			[[nodiscard]] virtual std::shared_ptr<RHI_FenceCPU>      CreateFenceCPU(const RHI_FenceCPUDescriptor& _fenceDescriptor) override;

			[[nodiscard]] virtual RHI_GraphicsPipeline* CreateGraphicsPipeline(const RHI_GraphicsPipelineDescriptor* _graphicsPipelineDescriptor) override;
			[[nodiscard]] virtual RHI_InputLayout*		CreateInputLayout(const RHI_InputLayoutDescriptor* _inputLayoutDescriptor) override;
			[[nodiscard]] virtual RHI_RenderPass*		CreateRenderPass(const RHI_RenderPassDescriptor* _renderPassDescriptor) override;
			[[nodiscard]] virtual RHI_FrameBuffer*		CreateFrameBuffer(const RHI_FrameBufferDescriptor* _frameBufferDescriptor) override;

			[[nodiscard]] virtual RHI_DescriptorPool*	CreateDescriptorPool(const RHI_DescriptorPoolDescriptor* _descriptorPoolDescriptor) override;

			[[nodiscard]] virtual RHI_Buffer*			CreateBuffer(const RHI_BufferDescriptor* _bufferDescriptor) override;
			[[nodiscard]] virtual RHI_Shader*			CreateShader(const RHI_ShaderDescriptor* _shaderDescriptor) override;

			[[nodiscard]] virtual RHI_Sampler*			CreateSampler(const RHI_SamplerDescriptor& _sampler2DDescripotr) override;
			[[nodiscard]] virtual RHI_Texture2D*		CreateTexture2D(const RHI_Texture2DDescriptor* _texture2DDescriptor) override;


		private:
			IDXGIFactory* m_Factory = nullptr;
		};
	}
}