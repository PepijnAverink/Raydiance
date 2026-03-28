#pragma once
// Parant class include
#include "./graphics/RHI/object/command/RHI_command_queue.h"

// D3D12 includes
#include <d3d12.h>

// Generic includes
#include <wrl/client.h>

namespace Raydiance
{
	namespace Graphics
	{
		class RHI_DX12_RenderDevice;
		class RHI_DX12_CommandQueue final : public RHI_CommandQueue
		{
		public:
			// Constructor and descructor
			// ======================================
					 RHI_DX12_CommandQueue();
			virtual ~RHI_DX12_CommandQueue();

			[[nodiscard]] const Result Initialize(const RHI_DX12_RenderDevice& _renderDevice, const RHI_CommandQueueDescriptor& _commandQueueDescriptor);

			virtual void SubmitCommandBuffer(RHI_CommandBuffer* _commandBuffer, std::shared_ptr<RHI_FenceCPU> _fence) override;


		private:
			Microsoft::WRL::ComPtr<ID3D12CommandQueue> m_CommandQueueObj = nullptr;
		};
	}
}