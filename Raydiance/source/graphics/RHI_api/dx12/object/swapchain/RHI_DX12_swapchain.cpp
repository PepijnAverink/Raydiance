#include "./pch.h"
#include "./graphics/RHI_api/dx12/object/swapchain/RHI_DX12_swapchain.h"


namespace Raydiance
{
	namespace Graphics
	{
		RHI_DX12_Swapchain::RHI_DX12_Swapchain(void)
		{

		}

		RHI_DX12_Swapchain::~RHI_DX12_Swapchain(void)
		{

		}

		const Result RHI_DX12_Swapchain::Initialize(const RHI_DX12_Swapchain& _renderDevice, const RHI_CommandQueue& _commandQueue, const RHI_SwapchainDescriptor& _swapchainDescriptor)
		{
			Result result = RHI_Swapchain::Initialize(_swapchainDescriptor);
			if (CheckError(result) == true)
			{
				// Log error
				return result;
			}

			//m_Format = ResourceFormat::RESOURCE_FORMAT_R8G8B8A8_UNORM;

			DXGI_MODE_DESC backBufferDesc = {};
			backBufferDesc.Width = m_Width;
			backBufferDesc.Height = m_Height;
			backBufferDesc.Format = ResolveDX12ResourceFormat(m_ResourceFormat);

			DXGI_SAMPLE_DESC sampleDesc = {};
			sampleDesc.Count = 1;

			DXGI_SWAP_CHAIN_DESC swapChainDesc = {};
			swapChainDesc.BufferCount = m_BufferCount;
			swapChainDesc.BufferDesc = backBufferDesc;
			swapChainDesc.BufferUsage = DXGI_USAGE_RENDER_TARGET_OUTPUT;
			swapChainDesc.SwapEffect = DXGI_SWAP_EFFECT_FLIP_DISCARD;
			swapChainDesc.OutputWindow = (HWND)_swapchainDescriptor->NativeWindowHandle;
			swapChainDesc.SampleDesc = sampleDesc;
			swapChainDesc.Windowed = true;

			IDXGISwapChain* temp;
			if (_RHI_RenderDevice->GetD3DFactory()->CreateSwapChain(((RHI_DX12_CommandQueue*)_commandQueue)->GetD3DCommandQueue(), &swapChainDesc, &temp) != S_OK)
			{
				Logger::Log("Failed to create DX12Swapchain...", LogLevel::LOG_LEVEL_ERROR);
				return Result::RESULT_ERROR;
			}

			// Set DebugLabel for this D3D12 object
			m_SwapchainObj = static_cast<IDXGISwapChain3*>(temp);
			//m_SwapchainObj->SetPrivateData(WKPDID_D3DDebugObjectName, sizeof(_swapchainDescriptor->Name) - 1, _swapchainDescriptor->Name.c_str());

			// Get current index
			m_BufferIndex = m_SwapchainObj->GetCurrentBackBufferIndex();


			// Create BackBuffer's
			m_RenderTargets = new RHI_Texture2D * [m_BufferCount];
			for (uint32_t i = 0; i < m_BufferCount; i++)
			{
				// Get backbuffer resource
				ID3D12Resource* resource = nullptr;
				if (m_SwapchainObj->GetBuffer(i, IID_PPV_ARGS(&resource)) != S_OK)
				{
					Logger::Log("Failed to retreive resource from DX12Swapchain...", LogLevel::LOG_LEVEL_ERROR);
					return;
				}

				// TextureDescriptor
				RHI_Texture2DDescriptor textureDesc = {};
				textureDesc.Name = "SwapchainImage" + i;
				textureDesc.Width = m_Width;
				textureDesc.Height = m_Height;
				textureDesc.Format = m_ResourceFormat;

				// Create texture
				RHI_DX12_Texture2D* tempTexture = new RHI_DX12_Texture2D();
				tempTexture->Initialize(_RHI_RenderDevice, resource, &textureDesc);

				m_RenderTargets[i] = tempTexture;
			}
			return result;
		}

		void RHI_DX12_Swapchain::Resize(const RHI_CommandQueue& _commandQueue, const uint32 _width, const uint32 _height)
		{

		}

		uint32 RHI_DX12_Swapchain::AquireNewImage(RHI_CommandQueue* _commandQueue, std::shared_ptr<RHI_FenceCPU> _fence)
		{
			m_BufferIndex = m_SwapchainObj->GetCurrentBackBufferIndex();
			// Signal fence
			if (_fence != nullptr)
				((RHI_DX12_CommandQueue*)_commandQueue)->GetD3DCommandQueue()->Signal(((RHI_DX12_FenceCPU*)_fence)->GetD3DFence(), ((RHI_DX12_FenceCPU*)_fence)->GetFenceValue());

			return m_BufferIndex;
		}

		void RHI_DX12_Swapchain::Present(RHI_CommandQueue* _commandQueue)
		{
			m_SwapchainObj->Present(m_VSync, 0);
		}
	}
}