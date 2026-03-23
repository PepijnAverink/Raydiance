#include "./graphics/RHI_api/dx12/RHI_DX12_render_device.h"

namespace Raydiance
{
	namespace Graphics
	{
		RHI_DX12_RenderDevice::RHI_DX12_RenderDevice()
			: RHI_RenderDevice(RHI_GraphicsAPI::RHI_GRAPHICS_API_DIRECTX12)
		{ }

		RHI_DX12_RenderDevice::~RHI_DX12_RenderDevice()
		{ }

		Result RHI_DX12_RenderDevice::Initialize(const RHI_RenderDeviceDescriptor& _renderDeviceDescriptor)
		{
			return Result::RESULT_GOOD;
		}
		Result RHI_DX12_RenderDevice::GetAdapterCount(uint32& _count) const
		{
			return Result::RESULT_GOOD;
		}
		Result RHI_DX12_RenderDevice::GetAdapter(const uint32 _adapterID, std::unique_ptr<RHI_Adapter>& _adapter) const
		{
			return Result::RESULT_GOOD;
		}
		Result RHI_DX12_RenderDevice::LinkAdapter(std::unique_ptr<RHI_Adapter> _adapter)
		{
			return Result::RESULT_GOOD;
		}
		std::shared_ptr<RHI_CommandPool> RHI_DX12_RenderDevice::CreateCommandPool(const RHI_CommandPoolDescriptor& _commandPoolDescriptor)
		{
			return std::shared_ptr<RHI_CommandPool>();
		}
		std::shared_ptr<RHI_CommandBuffer> RHI_DX12_RenderDevice::CreateCommandBuffer(const RHI_CommandBufferDescriptor& _commandBufferDescriptor)
		{
			return std::shared_ptr<RHI_CommandBuffer>();
		}
		std::shared_ptr<RHI_CommandQueue> RHI_DX12_RenderDevice::CreateCommandQueue(const RHI_CommandQueueDescriptor& _commandQueueDescriptor)
		{
			return std::shared_ptr<RHI_CommandQueue>();
		}
		std::shared_ptr<RHI_Swapchain> RHI_DX12_RenderDevice::CreateSwapchain(const RHI_CommandQueue& _commandQueue, const RHI_SwapchainDescriptor& _swapchainDescriptor)
		{
			return std::shared_ptr<RHI_Swapchain>();
		}
		std::shared_ptr<RHI_FenceCPU> RHI_DX12_RenderDevice::CreateFenceCPU(const RHI_FenceCPUDescriptor& _fenceDescriptor)
		{
			return std::shared_ptr<RHI_FenceCPU>();
		}
		RHI_GraphicsPipeline* RHI_DX12_RenderDevice::CreateGraphicsPipeline(const RHI_GraphicsPipelineDescriptor* _graphicsPipelineDescriptor)
		{
			return nullptr;
		}
		RHI_InputLayout* RHI_DX12_RenderDevice::CreateInputLayout(const RHI_InputLayoutDescriptor* _inputLayoutDescriptor)
		{
			return nullptr;
		}
		RHI_RenderPass* RHI_DX12_RenderDevice::CreateRenderPass(const RHI_RenderPassDescriptor* _renderPassDescriptor)
		{
			return nullptr;
		}
		RHI_FrameBuffer* RHI_DX12_RenderDevice::CreateFrameBuffer(const RHI_FrameBufferDescriptor* _frameBufferDescriptor)
		{
			return nullptr;
		}
		RHI_DescriptorPool* RHI_DX12_RenderDevice::CreateDescriptorPool(const RHI_DescriptorPoolDescriptor* _descriptorPoolDescriptor)
		{
			return nullptr;
		}
		RHI_Buffer* RHI_DX12_RenderDevice::CreateBuffer(const RHI_BufferDescriptor* _bufferDescriptor)
		{
			return nullptr;
		}
		RHI_Shader* RHI_DX12_RenderDevice::CreateShader(const RHI_ShaderDescriptor* _shaderDescriptor)
		{
			return nullptr;
		}
		RHI_Sampler* RHI_DX12_RenderDevice::CreateSampler(const RHI_SamplerDescriptor& _sampler2DDescripotr)
		{
			return nullptr;
		}
		RHI_Texture2D* RHI_DX12_RenderDevice::CreateTexture2D(const RHI_Texture2DDescriptor* _texture2DDescriptor)
		{
			return nullptr;
		}
	}
}