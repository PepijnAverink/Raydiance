#include "./pch.h"
#include "./graphics/RHI_api/dx12/object/swapchain/RHI_DX12_swapchain.h"
#include "./graphics/RHI_api/dx12/RHI_DX12_render_device.h"

#include "./graphics/RHI_api/dx12/object/command/RHI_DX12_command_queue.h"

#include "./graphics/RHI_api/dx12/resource/texture/RHI_DX12_texture2D.h"
#include "./graphics/RHI_api/dx12/resource/RHI_DX12_resource_format.h"

#include "./core/window/window.h"

#include "./graphics/RHI_api/dx12/object/sync/RHI_DX12_FenceCPU.h"

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

		const Result RHI_DX12_Swapchain::Initialize(const RHI_DX12_RenderDevice& _renderDevice, const RHI_CommandQueue& _commandQueue, const RHI_SwapchainDescriptor& _swapchainDescriptor)
		{
			Result result = RHI_Swapchain::Initialize(_swapchainDescriptor);
			if (CheckError(result) == true)
			{
				// Log error
				return result;
			}

			// TODO:: Descriptor for these variables
			m_BufferCount = 2;
			m_ResourceFormat = RHI_ResourceFormat::RHI_RESOURCE_FORMAT_B8G8R8A8_SRGB;

			DXGI_MODE_DESC backBufferDesc = {};
			backBufferDesc.Width = m_Width;
			backBufferDesc.Height = m_Height;
			backBufferDesc.Format = DXGI_FORMAT_R8G8B8A8_UNORM; // TODO:: Dont hard code this
			// ResolveDX12ResourceFormat(m_ResourceFormat);

			DXGI_SAMPLE_DESC sampleDesc = {};
			sampleDesc.Count = 1;

			DXGI_SWAP_CHAIN_DESC swapChainDesc = {};
			swapChainDesc.BufferCount = m_BufferCount;
			swapChainDesc.BufferDesc = backBufferDesc;
			swapChainDesc.BufferUsage = DXGI_USAGE_RENDER_TARGET_OUTPUT;
			swapChainDesc.SwapEffect = DXGI_SWAP_EFFECT_FLIP_DISCARD;
			swapChainDesc.OutputWindow = (HWND)_swapchainDescriptor.Window->GetWindowHandle();
			swapChainDesc.SampleDesc = sampleDesc;
			swapChainDesc.Windowed = true;

			
			IDXGISwapChain* temp;
			if (_renderDevice.GetD3DFactory()->CreateSwapChain(static_cast<const RHI_DX12_CommandQueue&>(_commandQueue).GetD3DCommandQueue().Get(), &swapChainDesc, &temp) != S_OK)
			{
				Logger::Log("Failed to create DX12Swapchain...", LogType::LOG_TYPE_ERROR);
				return Result::RESULT_ERROR;
			}

			// Set DebugLabel for this D3D12 object
			m_SwapchainObj = static_cast<IDXGISwapChain3*>(temp);
			//m_SwapchainObj->SetPrivateData(WKPDID_D3DDebugObjectName, sizeof(_swapchainDescriptor->Name) - 1, _swapchainDescriptor->Name.c_str());

			// Get current index
			m_BufferIndex = m_SwapchainObj->GetCurrentBackBufferIndex();


			// Create BackBuffer's
			//m_RenderTargets = new RHI_Texture2D * [m_BufferCount];
			for (uint32_t i = 0; i < m_BufferCount; i++)
			{
				// Get backbuffer resource
				Microsoft::WRL::ComPtr<ID3D12Resource> resource = nullptr;
				if (m_SwapchainObj->GetBuffer(i, IID_PPV_ARGS(&resource)) != S_OK)
				{
					Logger::Log("Failed to retreive resource from DX12Swapchain...", LogType::LOG_TYPE_ERROR);
					return Result::RESULT_ERROR;
				}

				// TextureDescriptor
				RHI_Texture2DDescriptor textureDesc = {};
				textureDesc.DebugName = "SwapchainImage" + i;
				textureDesc.Width = m_Width;
				textureDesc.Height = m_Height;
				textureDesc.Format = m_ResourceFormat;

				// Create texture
				RHI_DX12_Texture2D* tempTexture = new RHI_DX12_Texture2D(_renderDevice, resource, &textureDesc);
				//tempTexture->Initialize(_RHI_RenderDevice, resource, &textureDesc);

				m_RenderTargets.push_back(tempTexture);
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
				((RHI_DX12_CommandQueue*)_commandQueue)->GetD3DCommandQueue()->Signal(((RHI_DX12_FenceCPU*)_fence.get())->GetD3DFence().Get(), ((RHI_DX12_FenceCPU*)_fence.get())->GetFenceValue());

			return m_BufferIndex;
		}

		void RHI_DX12_Swapchain::Present(RHI_CommandQueue* _commandQueue)
		{
			m_SwapchainObj->Present(m_VSync, 0);
		}
	}
}