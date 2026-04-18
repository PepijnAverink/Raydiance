#pragma once
#include "./graphics/RHI/RHI_render_device.h"
#include "./graphics/RHI_api/dx12/pipeline/layout/descriptor/RHI_DX12_descriptor_heap.h"

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

			virtual Result Initialize(const RHI_RenderDeviceDescriptor* _renderDeviceDescriptor) override;

			// Adapter functions
			// ----------------------------------------------------------------------
			virtual Result GetAdapterCount(uint32& _count) const override;
			virtual Result GetAdapter(uint32 _index, RHI_Adapter** _adapter) const override;

			virtual Result LinkAdapter(RHI_Adapter* _adapter) override;


			// Swapchain functions
			// ----------------------------------------------------------------------
			virtual Result CheckSwapchainResourceFormatSupport(RHI_ResourceFormat _format, bool& _supported) const override;


			// Native create functions
			// ----------------------------------------------------------------------
			virtual RHI_CommandQueue* RHI_CreateCommandQueue(const RHI_CommandQueueDescriptor* _commandQueueDescriptor) override;
			virtual RHI_CommandBuffer* RHI_CreateCommandBuffer(const RHI_CommandBufferDescriptor* _commandBufferDescriptor) override;
			virtual RHI_CommandPool* RHI_CreateCommandPool(const RHI_CommandPoolDescriptor* _commandPoolDescriptor) override;

			virtual RHI_Swapchain* RHI_CreateSwapchain(RHI_CommandQueue* _commandQueue, const RHI_SwapchainDescriptor* _swapchainDescriptor) override;
			virtual RHI_FenceCPU* RHI_CreateFenceCPU(const RHI_FenceCPUDescriptor* _FenceDescriptor) override;

			virtual RHI_Texture2D* RHI_CreateTexture2D(const RHI_Texture2DDescriptor* _texture2DDescriptor) override;
			virtual RHI_Shader* RHI_CreateShader(const RHI_ShaderDescriptor* _shaderDescriptor) override;
			virtual RHI_Buffer* RHI_CreateBuffer(const RHI_BufferDescriptor* _bufferDescriptor) override;
			virtual RHI_Sampler* RHI_CreateSampler(const RHI_SamplerDescriptor* _samplerDescriptor) override;

			virtual RHI_RenderPass* RHI_CreateRenderPass(const RHI_RenderPassDescriptor* _renderPassDescriptor) override;
			virtual RHI_FrameBuffer* RHI_CreateFrameBuffer(const RHI_FrameBufferDescriptor* _frameBufferDescriptor) override;

			virtual RHI_DescriptorPool* RHI_CreateDescriptorPool(const RHI_DescriptorPoolDescriptor* _descriptorPoolDescriptor) override;

			virtual RHI_InputLayout* RHI_CreateInputLayout(const RHI_InputLayoutDescriptor* _inputLayoutDescriptor) override;
			virtual RHI_GraphicsPipeline* RHI_CreateGraphicsPipeline(const RHI_GraphicsPipelineDescriptor* _graphicsPipelineDescriptor) override;
			virtual RHI_ComputePipeline* RHI_CreateComputePipeline(const RHI_ComputePipelineDescriptor* _computePipelineDescriptor) override;

			virtual RHI_Pipeline* RHI_CreatePipeline(const RHI_ComputePipelineDescriptor* _computePipelineDescriptor) override;
			virtual RHI_Pipeline* RHI_CreatePipeline(const RHI_GraphicsPipelineDescriptor* _graphicsPipelineDescriptor) override;

			// Getters
			inline ID3D12Device* GetD3DDevice()  const { return m_Device; }
			inline IDXGIFactory* GetD3DFactory() const { return m_Factory; }

			// Descriptor allocation
			RHI_DX12_DescriptorHeapAllocation* AllocateCPUDescriptor(D3D12_DESCRIPTOR_HEAP_TYPE _type, const uint32_t _count = 1);
			RHI_DX12_DescriptorHeapAllocation* AllocateGPUDescriptor(D3D12_DESCRIPTOR_HEAP_TYPE _type, const uint32_t _count = 1);

			// Getters
			//DX12DescriptorHeap* GetCPUDescriptorHeapEditor();
			RHI_DX12_DescriptorHeap* GetCPUDescriptorHeap(D3D12_DESCRIPTOR_HEAP_TYPE _type);
			RHI_DX12_DescriptorHeap* GetGPUDescriptorHeap(D3D12_DESCRIPTOR_HEAP_TYPE _type);

		private:
			//// DescriptorHeaps
			RHI_DX12_DescriptorHeap* m_CPUDescriptorHeap_CBV_SRV_UAV = nullptr;
			RHI_DX12_DescriptorHeap* m_CPUDescriptorHeap_SAMPLER	 = nullptr;
			RHI_DX12_DescriptorHeap* m_CPUDescriptorHeap_RTV		 = nullptr;
			RHI_DX12_DescriptorHeap* m_CPUDescriptorHeap_DSV		 = nullptr;

			RHI_DX12_DescriptorHeap* m_GPUDescriptorHeap_CBV_SRV_UAV = nullptr;
			RHI_DX12_DescriptorHeap* m_GPUDescriptorHeap_SAMPLER     = nullptr;

			void CreateDescriptorHeaps();

			ID3D12Device* m_Device = nullptr;
			IDXGIFactory* m_Factory = nullptr;
		};
	}
}