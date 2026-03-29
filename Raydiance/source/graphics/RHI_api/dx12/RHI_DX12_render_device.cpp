#include "./pch.h"
#include "./graphics/RHI_api/dx12/RHI_DX12_render_device.h"

#include "./graphics/RHI_api/dx12/RHI_DX12_adapter.h"


#include "./graphics/RHI_api/dx12/object/command/RHI_DX12_command_queue.h"
#include "./graphics/RHI_api/dx12/object/command/RHI_DX12_command_buffer.h"
#include "./graphics/RHI_api/dx12/object/command/RHI_DX12_command_pool.h"
#include "./graphics/RHI_api/dx12/object/swapchain/RHI_DX12_swapchain.h"
#include "./graphics/RHI_api/dx12/object/sync/RHI_DX12_fenceCPU.h"


#include "./graphics/RHI_api/dx12/resource/buffer/RHI_DX12_buffer.h"
#include "./graphics/RHI_api/dx12/resource/sampler/RHI_DX12_Sampler.h"
#include "./graphics/RHI_api/dx12/resource/texture/RHI_DX12_texture2D.h"


// Generic includes


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
			// Object storing the result of all interal functions.
			Result result = Result::RESULT_INVALID;

			// Initialize the base class of the RHI_RenderDevice graphics object class,
			// And error check the result.
			// --------------------------------------------------------------------------
			result = RHI_RenderDevice::Initialize(_renderDeviceDescriptor);
			if (CheckError(result) == true)
			{
				// When result is RESULT_ERROR || RESULT_FATAL.
				Logger::Log("Error while intitializing the base class of the 'RHI_RenderDevice' object.", LogType::LOG_TYPE_ERROR);
				Logger::Log("No further evidence what went wrong, please see earlier logs.", LogType::LOG_TYPE_ERROR);
				return result;
			}

			// ==========================================================================
			// The actual D3D12 initialization follows
			// ==========================================================================

			// Create DXGI-factory object
			UINT createFactoryFlags = (IsDebugModeEnabled() == true) ? DXGI_CREATE_FACTORY_DEBUG : 0;
			CreateDXGIFactory2(createFactoryFlags, IID_PPV_ARGS(m_Factory.GetAddressOf()));

			// Enabling debug mode if set
			if (IsDebugModeEnabled() == true)
			{
				ID3D12Debug* pDx12Debug;
				if (SUCCEEDED(D3D12GetDebugInterface(IID_PPV_ARGS(&pDx12Debug))))
					pDx12Debug->EnableDebugLayer();
			}

			return result;
			return Result::RESULT_GOOD;
		}

		Result RHI_DX12_RenderDevice::GetAdapterCount(uint32& _count) const
		{
			// Get the number of devices
			if (m_Factory == nullptr)
			{
				Logger::Log("IDXGIFactory == NULL, RHI_DX12_RenderDevice probably isn't initialized correctly.", LogType::LOG_TYPE_ERROR);
				return Result::RESULT_ERROR;
			}

			_count = 0;
			IDXGIAdapter* adapter = nullptr;
			for (uint32_t i = 0; DXGI_ERROR_NOT_FOUND != m_Factory->EnumAdapters(i, &adapter); i++)
			{
				adapter->Release();
				_count++;
			}

			return Result::RESULT_GOOD;
		}

		Result RHI_DX12_RenderDevice::GetAdapter(const uint32 _adapterID, std::unique_ptr<RHI_Adapter>& _adapter) const
		{
			// Get the number of devices
			if (m_Factory == nullptr)
			{
				Logger::Log("IDXGIFactory == NULL, RHI_DX12_RenderDevice probably isn't initialized correctly.", LogType::LOG_TYPE_ERROR);
				return Result::RESULT_ERROR;
			}

			// Query the number of adapters present in this device
			uint32 count = 0;
			GetAdapterCount(count);

			// Error checking on the number of presen adapters
			if (count <= _adapterID)
			{
				Logger::Log("The user queried a non-existing adapter, could not retrieve any information for the 'RHI_AdapterInfo' class.", LogType::LOG_TYPE_ERROR);
				return Result::RESULT_ERROR;
			}

			Microsoft::WRL::ComPtr<IDXGIAdapter> adapter = nullptr;
			if (m_Factory->EnumAdapters(_adapterID, adapter.GetAddressOf()) == DXGI_ERROR_NOT_FOUND)
			{
				printf("[Error] Adapter with index %i could not be found.", _adapterID);
				return Result::RESULT_ERROR;
			}

			// Gather info about the specific adapter requested
			_adapter = std::make_unique<RHI_DX12_Adapter>(adapter);
			return Result::RESULT_GOOD;
		}

		Result RHI_DX12_RenderDevice::LinkAdapter(std::unique_ptr<RHI_Adapter> _adapter)
		{
			// Sets the active adapter
			m_Adapter = std::move(_adapter);

			// Cast the adapter to a vulkan specific adapter.
			const RHI_DX12_Adapter* d3d12_adapter = static_cast<const RHI_DX12_Adapter*>(m_Adapter.get());


			// Create the RenderDevice using the adapter specified by the user
			if (D3D12CreateDevice((IDXGIAdapter1*)d3d12_adapter->GetPhysicalDevice().Get(), D3D_FEATURE_LEVEL_11_0, IID_PPV_ARGS(m_Device.GetAddressOf())) != S_OK)
			{
				printf("[Error] Failed to create D3D12Device.");
				return Result::RESULT_ERROR;
			}

			return Result::RESULT_GOOD;
		}

		std::shared_ptr<RHI_CommandPool> RHI_DX12_RenderDevice::CreateCommandPool(const RHI_CommandPoolDescriptor& _commandPoolDescriptor)
		{
			std::shared_ptr<RHI_DX12_CommandPool> commandPool = std::make_shared<RHI_DX12_CommandPool>(this, _commandPoolDescriptor);
			return commandPool;
		}
		std::shared_ptr<RHI_CommandBuffer> RHI_DX12_RenderDevice::CreateCommandBuffer(const RHI_CommandBufferDescriptor& _commandBufferDescriptor)
		{
			std::shared_ptr<RHI_DX12_CommandBuffer> commandBuffer = std::make_shared<RHI_DX12_CommandBuffer>(this, _commandBufferDescriptor);
			return commandBuffer;
		}
		std::shared_ptr<RHI_CommandQueue> RHI_DX12_RenderDevice::CreateCommandQueue(const RHI_CommandQueueDescriptor& _commandQueueDescriptor)
		{
			std::shared_ptr<RHI_DX12_CommandQueue> commandQueue = std::make_shared<RHI_DX12_CommandQueue>();
			Result result = commandQueue->Initialize(*this, _commandQueueDescriptor);

			// Error check
			if (CheckError(result) == true)
			{
				// Log error
				Logger::Log("Initialization of RHI_VK_CommandQueue failed.", LogType::LOG_TYPE_ERROR);
				Logger::Log("No further evidence what went wrong, please see earlier logs.", LogType::LOG_TYPE_ERROR);
				return nullptr;
			}

			return commandQueue;
		}
		std::shared_ptr<RHI_Swapchain> RHI_DX12_RenderDevice::CreateSwapchain(const RHI_CommandQueue& _commandQueue, const RHI_SwapchainDescriptor& _swapchainDescriptor)
		{
			std::shared_ptr<RHI_DX12_Swapchain> swapchain = std::make_shared<RHI_DX12_Swapchain>();
			Result result = swapchain->Initialize(*this, _commandQueue, _swapchainDescriptor);

			// Error check
			if (CheckError(result) == true)
			{
				// Log error
				Logger::Log("Initialization of RHI_DX12_Swapchain failed.", LogType::LOG_TYPE_ERROR);
				Logger::Log("No further evidence what went wrong, please see earlier logs.", LogType::LOG_TYPE_ERROR);
				return nullptr;
			}

			return swapchain;
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
			RHI_DX12_Buffer* buffer = new RHI_DX12_Buffer(this, _bufferDescriptor);
			return buffer;
		}
		RHI_Shader* RHI_DX12_RenderDevice::CreateShader(const RHI_ShaderDescriptor* _shaderDescriptor)
		{
			return nullptr;
		}
		RHI_Sampler* RHI_DX12_RenderDevice::CreateSampler(const RHI_SamplerDescriptor& _sampler2DDescripotr)
		{
			RHI_DX12_Sampler* sampler = new RHI_DX12_Sampler();
			sampler->Initialize(*this, _sampler2DDescripotr);
			return sampler;
		}

		RHI_Texture2D* RHI_DX12_RenderDevice::CreateTexture2D(const RHI_Texture2DDescriptor* _texture2DDescriptor)
		{
			RHI_DX12_Texture2D* texture = new RHI_DX12_Texture2D(this, _texture2DDescriptor);
			return texture;
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
				descriptorHeapDesc.Name = "CPUDescriptorHeap_CBV_SRV_UAV";
				descriptorHeapDesc.Type = D3D12_DESCRIPTOR_HEAP_TYPE_CBV_SRV_UAV;
				descriptorHeapDesc.Access = RHI_DX12_DescriptorHeapAccess::RHI_DX12_DESCRIPTOR_HEAP_ACCESS_CPU;
				descriptorHeapDesc.Count = 8192;

				m_CPUDescriptorHeap_CBV_SRV_UAV = new RHI_DX12_DescriptorHeap(this, &descriptorHeapDesc);
			}
			{
				RHI_DX12_DescritorHeapDescriptor descriptorHeapDesc = {};
				descriptorHeapDesc.Name = "CPUDescriptorHeap_SAMPLER";
				descriptorHeapDesc.Type = D3D12_DESCRIPTOR_HEAP_TYPE_SAMPLER;
				descriptorHeapDesc.Access = RHI_DX12_DescriptorHeapAccess::RHI_DX12_DESCRIPTOR_HEAP_ACCESS_CPU;
				descriptorHeapDesc.Count = 2048;

				m_CPUDescriptorHeap_SAMPLER = new RHI_DX12_DescriptorHeap(this, &descriptorHeapDesc);
			}
			{
				RHI_DX12_DescritorHeapDescriptor descriptorHeapDesc = {};
				descriptorHeapDesc.Name = "CPUDescriptorHeap_RTV";
				descriptorHeapDesc.Type = D3D12_DESCRIPTOR_HEAP_TYPE_RTV;
				descriptorHeapDesc.Access = RHI_DX12_DescriptorHeapAccess::RHI_DX12_DESCRIPTOR_HEAP_ACCESS_CPU;
				descriptorHeapDesc.Count = 1024;

				m_CPUDescriptorHeap_RTV = new RHI_DX12_DescriptorHeap(this, &descriptorHeapDesc);
			}
			{
				RHI_DX12_DescritorHeapDescriptor descriptorHeapDesc = {};
				descriptorHeapDesc.Name = "CPUDescriptorHeap_DSV";
				descriptorHeapDesc.Type = D3D12_DESCRIPTOR_HEAP_TYPE_DSV;
				descriptorHeapDesc.Access = RHI_DX12_DescriptorHeapAccess::RHI_DX12_DESCRIPTOR_HEAP_ACCESS_CPU;
				descriptorHeapDesc.Count = 128;

				m_CPUDescriptorHeap_DSV = new RHI_DX12_DescriptorHeap(this, &descriptorHeapDesc);
			}

			{
				RHI_DX12_DescritorHeapDescriptor descriptorHeapDesc = {};
				descriptorHeapDesc.Name = "GPUDescriptorHeap_CBV_SRV_UAV";
				descriptorHeapDesc.Type = D3D12_DESCRIPTOR_HEAP_TYPE_CBV_SRV_UAV;
				descriptorHeapDesc.Access = RHI_DX12_DescriptorHeapAccess::RHI_DX12_DESCRIPTOR_HEAP_ACCESS_GPU;
				descriptorHeapDesc.Count = 16384;

				m_GPUDescriptorHeap_CBV_SRV_UAV = new RHI_DX12_DescriptorHeap(this, &descriptorHeapDesc);
			}
			{
				RHI_DX12_DescritorHeapDescriptor descriptorHeapDesc = {};
				descriptorHeapDesc.Name = "GPUDescriptorHeap_SAMPLER";
				descriptorHeapDesc.Type = D3D12_DESCRIPTOR_HEAP_TYPE_SAMPLER;
				descriptorHeapDesc.Access = RHI_DX12_DescriptorHeapAccess::RHI_DX12_DESCRIPTOR_HEAP_ACCESS_GPU;
				descriptorHeapDesc.Count = 1024;

				m_GPUDescriptorHeap_SAMPLER = new RHI_DX12_DescriptorHeap(this, &descriptorHeapDesc);
			}
		}
	}
}