#include "./graphics/RHI_api/dx12/RHI_DX12_render_device.h"
#include "./graphics/RHI_api/dx12/RHI_DX12_adapter.h"


#include "./graphics/RHI_api/dx12/object/command/RHI_DX12_command_queue.h"
#include "./graphics/RHI_api/dx12/object/swapchain/RHI_DX12_swapchain.h"
#include "./graphics/RHI_api/dx12/object/sync/RHI_DX12_fenceCPU.h"
#include "./graphics/RHI_api/dx12/object/command/RHI_DX12_command_buffer.h"
#include "./graphics/RHI_api/dx12/object/command/RHI_DX12_command_pool.h"
#include "./graphics/RHI_api/dx12/resource/texture/RHI_DX12_texture2D.h"

#include "./graphics/RHI_api/dx12/pipeline/graphics/framebuffer/RHI_DX12_frame_buffer.h"
#include "./graphics/RHI_api/dx12/pipeline/graphics/renderpass/RHI_DX12_render_pass.h"

#include "./graphics/RHI_api/dx12/resource/shader/RHI_DX12_shader.h"
#include "./graphics/RHI_api/dx12/resource/buffer/RHI_DX12_buffer.h"
#include "./graphics/RHI_api/dx12/resource/RHI_DX12_resource_format.h"

#include "./graphics/RHI_api/dx12/pipeline/layout/RHI_DX12_input_layout.h"
#include "./graphics/RHI_api/dx12/pipeline/graphics/RHI_DX12_graphics_pipeline.h"

#include "./graphics/RHI_api/dx12/resource/sampler/RHI_DX12_sampler.h"
#include "./graphics/RHI_api/dx12/pipeline/layout/descriptor/RHI_DX12_descriptor_pool.h"


namespace Raydiance
{
	namespace Graphics
	{
		RHI_DX12_RenderDevice::RHI_DX12_RenderDevice()
		{

		}

		RHI_DX12_RenderDevice::~RHI_DX12_RenderDevice()
		{
			delete m_CPUDescriptorHeap_CBV_SRV_UAV;
			delete m_CPUDescriptorHeap_SAMPLER;
			delete m_CPUDescriptorHeap_RTV;
			delete m_CPUDescriptorHeap_DSV;

			delete m_GPUDescriptorHeap_CBV_SRV_UAV;
			delete m_GPUDescriptorHeap_SAMPLER;

			m_Factory->Release();
			m_Device->Release();
		}

		Result RHI_DX12_RenderDevice::Initialize(const RHI_RenderDeviceDescriptor* _renderDeviceDescriptor)
		{
			// Object storing the result of all interal functions.
			Result result = Result::RESULT_INVALID;

			// Initialize the base class of the RHI_RenderDevice graphics object class,
			// And error check the result.
			// --------------------------------------------------------------------------
			result = RHI_RenderDevice::Initialize(_renderDeviceDescriptor);
			if (CheckError(result) == true)
			{
				// When result is RESULT_ERROR || RESULT_FATAL.
				Logger::Log("Error while intitializing the base class of the 'RHI_RenderDevice' object.", LogLevel::LOG_LEVEL_ERROR);
				Logger::Log("No further evidence what went wrong, please see earlier logs.", LogLevel::LOG_LEVEL_ERROR);
				return result;
			}

			// ==========================================================================
			// The actual D3D12 initialization follows
			// ==========================================================================

			// Create DXGI-factory object
			UINT createFactoryFlags = (Is_DebugModeEnabled() == true) ? DXGI_CREATE_FACTORY_DEBUG : 0;
			CreateDXGIFactory2(createFactoryFlags, IID_PPV_ARGS(&m_Factory));

			// Enabling debug mode if set
			if (Is_DebugModeEnabled() == true)
			{
				ID3D12Debug* pDx12Debug;
				if (SUCCEEDED(D3D12GetDebugInterface(IID_PPV_ARGS(&pDx12Debug))))
					pDx12Debug->EnableDebugLayer();
			}

			return result;
		}
		Result RHI_DX12_RenderDevice::GetAdapterCount(uint32& _count) const
		{
			_count = 0;
			IDXGIAdapter* adapter = nullptr;
			for (uint32_t i = 0; DXGI_ERROR_NOT_FOUND != m_Factory->EnumAdapters(i, &adapter); i++)
			{
				adapter->Release();
				_count++;
			}

			return Result::RESULT_GOOD;
		}

		Result RHI_DX12_RenderDevice::GetAdapter(uint32 _index, RHI_Adapter** _adapter) const
		{
			IDXGIAdapter* adapter = nullptr;
			if (m_Factory->EnumAdapters(_index, &adapter) == DXGI_ERROR_NOT_FOUND)
			{
				printf("[Error] Adapter with index %i could not be found.", _index);
				return Result::RESULT_ERROR;
			}

			// Gather info about the specific adapter requested
			*_adapter = new RHI_DX12_Adapter(adapter);
			return Result::RESULT_GOOD;
		}

		Result RHI_DX12_RenderDevice::LinkAdapter(RHI_Adapter* _adapter)
		{
			m_Adapter = _adapter;
			RHI_DX12_Adapter* d3d12_adapter = ((RHI_DX12_Adapter*)m_Adapter);

			// Create the RenderDevice using the adapter specified by the user
			if (D3D12CreateDevice((IDXGIAdapter1*)d3d12_adapter->GetPhysicalDevice(), D3D_FEATURE_LEVEL_11_0, IID_PPV_ARGS(&m_Device)) != S_OK)
			{
				printf("[Error] Failed to create D3D12Device.");
				return Result::RESULT_ERROR;
			}

			CreateDescriptorHeaps();
			return Result::RESULT_GOOD;
		}

		Result RHI_DX12_RenderDevice::CheckSwapchainResourceFormatSupport(RHI_ResourceFormat _format, bool& _supported) const
		{
			D3D12_FEATURE_DATA_FORMAT_SUPPORT formatSupport = {};
			formatSupport.Format = ResolveDX12ResourceFormat(_format);

			if (SUCCEEDED(m_Device->CheckFeatureSupport(D3D12_FEATURE_FORMAT_SUPPORT, &formatSupport, sizeof(formatSupport))))
			{
				if ((formatSupport.Support1 & D3D12_FORMAT_SUPPORT1_RENDER_TARGET) && (formatSupport.Support1 & D3D12_FORMAT_SUPPORT1_DISPLAY))
				{
					_supported = true;
					return Result::RESULT_GOOD;
				}
			}

			_supported = false;
			return Result::RESULT_GOOD;
		}

		RHI_CommandQueue* RHI_DX12_RenderDevice::RHI_CreateCommandQueue(const RHI_CommandQueueDescriptor* _commandQueueDescriptor)
		{
			// Create and initialize
			RHI_DX12_CommandQueue* commandQueue = new RHI_DX12_CommandQueue();
			Result result = commandQueue->Initialize(this, _commandQueueDescriptor);

			// Error check
			if (CheckError(result) == true)
			{
				// Destroy pointer
				delete commandQueue;

				// Log error
				Logger::Log("Initialization of RHI_DX12_CommandQueue failed.", LogLevel::LOG_LEVEL_ERROR);
				Logger::Log("No further evidence what went wrong, please see earlier logs.", LogLevel::LOG_LEVEL_ERROR);
				return nullptr;
			}

			// Return pointer
			return commandQueue;
		}

		RHI_CommandBuffer* RHI_DX12_RenderDevice::RHI_CreateCommandBuffer(const RHI_CommandBufferDescriptor* _commandBufferDescriptor)
		{
			// Create and initialize
			RHI_DX12_CommandBuffer* commandBuffer = new RHI_DX12_CommandBuffer();
			Result result = commandBuffer->Initialize(this, _commandBufferDescriptor);

			// Error check
			if (CheckError(result) == true)
			{
				// Destroy pointer
				delete commandBuffer;

				// Log error
				Logger::Log("Initialization of RHI_DX12_CommandBuffer failed.", LogLevel::LOG_LEVEL_ERROR);
				Logger::Log("No further evidence what went wrong, please see earlier logs.", LogLevel::LOG_LEVEL_ERROR);
				return nullptr;
			}

			// Return pointer
			return commandBuffer;
		}

		RHI_CommandPool* RHI_DX12_RenderDevice::RHI_CreateCommandPool(const RHI_CommandPoolDescriptor* _commandPoolDescriptor)
		{
			// Create and initialize
			RHI_DX12_CommandPool* commandPool = new RHI_DX12_CommandPool();
			Result result = commandPool->Initialize(this, _commandPoolDescriptor);

			// Error check
			if (CheckError(result) == true)
			{
				// Destroy pointer
				delete commandPool;

				// Log error
				Logger::Log("Initialization of RHI_DX12_CommandPool failed.", LogLevel::LOG_LEVEL_ERROR);
				Logger::Log("No further evidence what went wrong, please see earlier logs.", LogLevel::LOG_LEVEL_ERROR);
				return nullptr;
			}

			// Return pointer
			return commandPool;
		}

		RHI_Swapchain* RHI_DX12_RenderDevice::RHI_CreateSwapchain(RHI_CommandQueue* _commandQueue, const RHI_SwapchainDescriptor* _swapchainDescriptor)
		{
			// Create and initialize
			RHI_DX12_Swapchain* swapchain = new RHI_DX12_Swapchain();
			Result result = swapchain->Initialize(this, _commandQueue, _swapchainDescriptor);

			// Error check
			if (CheckError(result) == true)
			{
				// Destroy pointer
				delete swapchain;

				// Log error
				Logger::Log("Initialization of RHI_DX12_Swapchain failed.", LogLevel::LOG_LEVEL_ERROR);
				Logger::Log("No further evidence what went wrong, please see earlier logs.", LogLevel::LOG_LEVEL_ERROR);
				return nullptr;
			}

			// Return pointer
			return swapchain;
		}

		RHI_FenceCPU* RHI_DX12_RenderDevice::RHI_CreateFenceCPU(const RHI_FenceCPUDescriptor* _FenceDescriptor)
		{
			// Create and initialize
			RHI_DX12_FenceCPU* fence = new RHI_DX12_FenceCPU();
			Result result = fence->Initialize(this, _FenceDescriptor);

			// Error check
			if (CheckError(result) == true)
			{
				// Destroy pointer
				delete fence;

				// Log error
				Logger::Log("Initialization of RHI_DX12_FenceCPU failed.", LogLevel::LOG_LEVEL_ERROR);
				Logger::Log("No further evidence what went wrong, please see earlier logs.", LogLevel::LOG_LEVEL_ERROR);
				return nullptr;
			}

			// Return pointer
			return fence;
		}

		RHI_Texture2D* RHI_DX12_RenderDevice::RHI_CreateTexture2D(const RHI_Texture2DDescriptor* _texture2DDescriptor)
		{
			// Create and initialize
			RHI_DX12_Texture2D* texture = new RHI_DX12_Texture2D();
			Result result = texture->Initialize(this, _texture2DDescriptor);

			// Error check
			if (CheckError(result) == true)
			{
				// Destroy pointer
				delete texture;

				// Log error
				Logger::Log("Initialization of RHI_DX12_Texture2D failed.", LogLevel::LOG_LEVEL_ERROR);
				Logger::Log("No further evidence what went wrong, please see earlier logs.", LogLevel::LOG_LEVEL_ERROR);
				return nullptr;
			}

			// Return pointer
			return texture;
		}

		RHI_Shader* RHI_DX12_RenderDevice::RHI_CreateShader(const RHI_ShaderDescriptor* _shaderDescriptor)
		{
			// Create and initialize
			RHI_DX12_Shader* shader = new RHI_DX12_Shader();
			Result result = shader->Initialize(this, _shaderDescriptor);

			// Error check
			if (CheckError(result) == true)
			{
				// Destroy pointer
				delete shader;

				// Log error
				Logger::Log("Initialization of RHI_DX12_Shader failed.", LogLevel::LOG_LEVEL_ERROR);
				Logger::Log("No further evidence what went wrong, please see earlier logs.", LogLevel::LOG_LEVEL_ERROR);
				return nullptr;
			}

			// Return pointer
			return shader;
		}

		RHI_Buffer* RHI_DX12_RenderDevice::RHI_CreateBuffer(const RHI_BufferDescriptor* _bufferDescriptor)
		{
			// Create and initialize
			RHI_DX12_Buffer* buffer = new RHI_DX12_Buffer();
			Result result = buffer->Initialize(this, _bufferDescriptor);

			// Error check
			if (CheckError(result) == true)
			{
				// Destroy pointer
				delete buffer;

				// Log error
				Logger::Log("Initialization of RHI_DX12_Buffer failed.", LogLevel::LOG_LEVEL_ERROR);
				Logger::Log("No further evidence what went wrong, please see earlier logs.", LogLevel::LOG_LEVEL_ERROR);
				return nullptr;
			}

			// Return pointer
			return buffer;
		}

		RHI_Sampler* RHI_DX12_RenderDevice::RHI_CreateSampler(const RHI_SamplerDescriptor* _samplerDescriptor)
		{
			// Create and initialize
			RHI_DX12_Sampler* sampler = new RHI_DX12_Sampler();
			Result result = sampler->Initialize(this, _samplerDescriptor);

			// Error check
			if (CheckError(result) == true)
			{
				// Destroy pointer
				delete sampler;

				// Log error
				Logger::Log("Initialization of RHI_DX12_Sampler failed.", LogLevel::LOG_LEVEL_ERROR);
				Logger::Log("No further evidence what went wrong, please see earlier logs.", LogLevel::LOG_LEVEL_ERROR);
				return nullptr;
			}

			// Return pointer
			return sampler;
		}

		RHI_RenderPass* RHI_DX12_RenderDevice::RHI_CreateRenderPass(const RHI_RenderPassDescriptor* _renderPassDescriptor)
		{
			// Create and initialize
			RHI_DX12_RenderPass* renderPass = new RHI_DX12_RenderPass();
			Result result = renderPass->Initialize(this, _renderPassDescriptor);

			// Error check
			if (CheckError(result) == true)
			{
				// Destroy pointer
				delete renderPass;

				// Log error
				Logger::Log("Initialization of RHI_DX12_RenderPass failed.", LogLevel::LOG_LEVEL_ERROR);
				Logger::Log("No further evidence what went wrong, please see earlier logs.", LogLevel::LOG_LEVEL_ERROR);
				return nullptr;
			}

			// Return pointer
			return renderPass;
		}

		RHI_FrameBuffer* RHI_DX12_RenderDevice::RHI_CreateFrameBuffer(const RHI_FrameBufferDescriptor* _frameBufferDescriptor)
		{
			// Create and initialize
			RHI_DX12_FrameBuffer* framebuffer = new RHI_DX12_FrameBuffer();
			Result result = framebuffer->Initialize(this, _frameBufferDescriptor);

			// Error check
			if (CheckError(result) == true)
			{
				// Destroy pointer
				delete framebuffer;

				// Log error
				Logger::Log("Initialization of RHI_DX12_FrameBuffer failed.", LogLevel::LOG_LEVEL_ERROR);
				Logger::Log("No further evidence what went wrong, please see earlier logs.", LogLevel::LOG_LEVEL_ERROR);
				return nullptr;
			}

			// Return pointer
			return framebuffer;
		}

		RHI_DescriptorPool* RHI_DX12_RenderDevice::RHI_CreateDescriptorPool(const RHI_DescriptorPoolDescriptor* _descriptorPoolDescriptor)
		{
			// Create and initialize
			RHI_DX12_DescriptorPool* descriptorPool = new RHI_DX12_DescriptorPool();
			Result result = descriptorPool->Initialize(this, _descriptorPoolDescriptor);

			// Error check
			if (CheckError(result) == true)
			{
				// Destroy pointer
				delete descriptorPool;

				// Log error
				Logger::Log("Initialization of RHI_DX12_DescriptorPool failed.", LogLevel::LOG_LEVEL_ERROR);
				Logger::Log("No further evidence what went wrong, please see earlier logs.", LogLevel::LOG_LEVEL_ERROR);
				return nullptr;
			}

			// Return pointer
			return descriptorPool;
		}

		RHI_InputLayout* RHI_DX12_RenderDevice::RHI_CreateInputLayout(const RHI_InputLayoutDescriptor* _inputLayoutDescriptor)
		{
			// Create and initialize
			RHI_DX12_InputLayout* inputLayout = new RHI_DX12_InputLayout();
			Result result = inputLayout->Initialize(this, _inputLayoutDescriptor);

			// Error check
			if (CheckError(result) == true)
			{
				// Destroy pointer
				delete inputLayout;

				// Log error
				Logger::Log("Initialization of RHI_DX12_InputLayout failed.", LogLevel::LOG_LEVEL_ERROR);
				Logger::Log("No further evidence what went wrong, please see earlier logs.", LogLevel::LOG_LEVEL_ERROR);
				return nullptr;
			}

			// Return pointer
			return inputLayout;
		}

		RHI_GraphicsPipeline* RHI_DX12_RenderDevice::RHI_CreateGraphicsPipeline(const RHI_GraphicsPipelineDescriptor* _graphicsPipelineDescriptor)
		{
			// Create and initialize
			RHI_DX12_GraphicsPipeline* pipeline = new RHI_DX12_GraphicsPipeline();
			Result result = pipeline->Initialize(this, _graphicsPipelineDescriptor);

			// Error check
			if (CheckError(result) == true)
			{
				// Destroy pointer
				delete pipeline;

				// Log error
				Logger::Log("Initialization of RHI_DX12_GraphicsPipeline failed.", LogLevel::LOG_LEVEL_ERROR);
				Logger::Log("No further evidence what went wrong, please see earlier logs.", LogLevel::LOG_LEVEL_ERROR);
				return nullptr;
			}

			// Return pointer
			return pipeline;
		}

		RHI_ComputePipeline* RHI_DX12_RenderDevice::RHI_CreateComputePipeline(const RHI_ComputePipelineDescriptor* _computePipelineDescriptor)
		{
			return nullptr;
		}

		RHI_DX12_DescriptorHeapAllocation* RHI_DX12_RenderDevice::AllocateCPUDescriptor(D3D12_DESCRIPTOR_HEAP_TYPE _type, const uint32_t _count)
		{
			switch (_type)
			{
				case D3D12_DESCRIPTOR_HEAP_TYPE_CBV_SRV_UAV:
					return m_CPUDescriptorHeap_CBV_SRV_UAV->AllocateDescriptors(_count);
				case D3D12_DESCRIPTOR_HEAP_TYPE_SAMPLER:
					return m_CPUDescriptorHeap_SAMPLER->AllocateDescriptors(_count);
				case D3D12_DESCRIPTOR_HEAP_TYPE_RTV:
					return m_CPUDescriptorHeap_RTV->AllocateDescriptors(_count);
				case D3D12_DESCRIPTOR_HEAP_TYPE_DSV:
					return m_CPUDescriptorHeap_DSV->AllocateDescriptors(_count);
			}

			return nullptr;
		}

		RHI_DX12_DescriptorHeapAllocation* RHI_DX12_RenderDevice::AllocateGPUDescriptor(D3D12_DESCRIPTOR_HEAP_TYPE _type, const uint32_t _count)
		{
			switch (_type)
			{
				case D3D12_DESCRIPTOR_HEAP_TYPE_CBV_SRV_UAV:
					return m_GPUDescriptorHeap_CBV_SRV_UAV->AllocateDescriptors(_count);
				case D3D12_DESCRIPTOR_HEAP_TYPE_SAMPLER:
					return m_GPUDescriptorHeap_SAMPLER->AllocateDescriptors(_count);
			}

			return nullptr;
		}

		RHI_DX12_DescriptorHeap* RHI_DX12_RenderDevice::GetCPUDescriptorHeap(D3D12_DESCRIPTOR_HEAP_TYPE _type)
		{
			switch (_type)
			{
				case D3D12_DESCRIPTOR_HEAP_TYPE_CBV_SRV_UAV:
					return m_CPUDescriptorHeap_CBV_SRV_UAV;
				case D3D12_DESCRIPTOR_HEAP_TYPE_SAMPLER:
					return m_CPUDescriptorHeap_SAMPLER;
				case D3D12_DESCRIPTOR_HEAP_TYPE_RTV:
					return m_CPUDescriptorHeap_RTV;
				case D3D12_DESCRIPTOR_HEAP_TYPE_DSV:
					return m_CPUDescriptorHeap_DSV;
			}

			return nullptr;
		}

		RHI_DX12_DescriptorHeap* RHI_DX12_RenderDevice::GetGPUDescriptorHeap(D3D12_DESCRIPTOR_HEAP_TYPE _type)
		{
			switch (_type)
			{
				case D3D12_DESCRIPTOR_HEAP_TYPE_CBV_SRV_UAV:
					return m_GPUDescriptorHeap_CBV_SRV_UAV;
				case D3D12_DESCRIPTOR_HEAP_TYPE_SAMPLER:
					return m_GPUDescriptorHeap_SAMPLER;
			}

			return nullptr;
		}

		void RHI_DX12_RenderDevice::CreateDescriptorHeaps()
		{
			{
				RHI_DX12_DescritorHeapDescriptor descriptorHeapDesc = {};
				descriptorHeapDesc.Name   = "CPUDescriptorHeap_CBV_SRV_UAV";
				descriptorHeapDesc.Type   = D3D12_DESCRIPTOR_HEAP_TYPE_CBV_SRV_UAV;
				descriptorHeapDesc.Access = RHI_DX12_DescriptorHeapAccess::RHI_DX12_DESCRIPTOR_HEAP_ACCESS_CPU;
				descriptorHeapDesc.Count  = 8192;

				m_CPUDescriptorHeap_CBV_SRV_UAV = new RHI_DX12_DescriptorHeap(this, &descriptorHeapDesc);
			}
			{
				RHI_DX12_DescritorHeapDescriptor descriptorHeapDesc = {};
				descriptorHeapDesc.Name   = "CPUDescriptorHeap_SAMPLER";
				descriptorHeapDesc.Type   = D3D12_DESCRIPTOR_HEAP_TYPE_SAMPLER;
				descriptorHeapDesc.Access = RHI_DX12_DescriptorHeapAccess::RHI_DX12_DESCRIPTOR_HEAP_ACCESS_CPU;
				descriptorHeapDesc.Count  = 2048;

				m_CPUDescriptorHeap_SAMPLER = new RHI_DX12_DescriptorHeap(this, &descriptorHeapDesc);
			}
			{
				RHI_DX12_DescritorHeapDescriptor descriptorHeapDesc = {};
				descriptorHeapDesc.Name   = "CPUDescriptorHeap_RTV";
				descriptorHeapDesc.Type   = D3D12_DESCRIPTOR_HEAP_TYPE_RTV;
				descriptorHeapDesc.Access = RHI_DX12_DescriptorHeapAccess::RHI_DX12_DESCRIPTOR_HEAP_ACCESS_CPU;
				descriptorHeapDesc.Count  = 1024;

				m_CPUDescriptorHeap_RTV = new RHI_DX12_DescriptorHeap(this, &descriptorHeapDesc);
			}
			{
				RHI_DX12_DescritorHeapDescriptor descriptorHeapDesc = {};
				descriptorHeapDesc.Name   = "CPUDescriptorHeap_DSV";
				descriptorHeapDesc.Type   = D3D12_DESCRIPTOR_HEAP_TYPE_DSV;
				descriptorHeapDesc.Access = RHI_DX12_DescriptorHeapAccess::RHI_DX12_DESCRIPTOR_HEAP_ACCESS_CPU;
				descriptorHeapDesc.Count  = 128;

				m_CPUDescriptorHeap_DSV = new RHI_DX12_DescriptorHeap(this, &descriptorHeapDesc);
			}

			{
				RHI_DX12_DescritorHeapDescriptor descriptorHeapDesc = {};
				descriptorHeapDesc.Name   = "GPUDescriptorHeap_CBV_SRV_UAV";
				descriptorHeapDesc.Type   = D3D12_DESCRIPTOR_HEAP_TYPE_CBV_SRV_UAV;
				descriptorHeapDesc.Access = RHI_DX12_DescriptorHeapAccess::RHI_DX12_DESCRIPTOR_HEAP_ACCESS_GPU;
				descriptorHeapDesc.Count  = 16384;

				m_GPUDescriptorHeap_CBV_SRV_UAV = new RHI_DX12_DescriptorHeap(this, &descriptorHeapDesc);
			}
			{
				RHI_DX12_DescritorHeapDescriptor descriptorHeapDesc = {};
				descriptorHeapDesc.Name   = "GPUDescriptorHeap_SAMPLER";
				descriptorHeapDesc.Type   = D3D12_DESCRIPTOR_HEAP_TYPE_SAMPLER;
				descriptorHeapDesc.Access = RHI_DX12_DescriptorHeapAccess::RHI_DX12_DESCRIPTOR_HEAP_ACCESS_GPU;
				descriptorHeapDesc.Count  = 1024;

				m_GPUDescriptorHeap_SAMPLER = new RHI_DX12_DescriptorHeap(this, &descriptorHeapDesc);
			}
		}
	}
}