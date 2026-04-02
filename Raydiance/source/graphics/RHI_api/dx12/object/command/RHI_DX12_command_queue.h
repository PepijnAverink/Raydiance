#pragma once
// Graphics includes
#include "./graphics/RHI/object/command/RHI_command_queue.h"

// D3D12 includes
#include <d3d12.h>

namespace Raydiance
{
	namespace Graphics
	{
		class RHI_DX12_RenderDevice;
		class RHI_DX12_CommandQueue final : public RHI_CommandQueue
		{
		public:
			RHI_DX12_CommandQueue();
			virtual ~RHI_DX12_CommandQueue();

			const Result Initialize(RHI_DX12_RenderDevice* _renderDevice, const RHI_CommandQueueDescriptor* _commandQueueDescriptor);

			virtual void Execute(RHI_CommandBuffer* _commandBuffer, RHI_FenceCPU* _fence = nullptr) override;

			virtual void InsertDebugLabel(const std::string& _name, float* _color) override;
			virtual void BeginDebugLabel(const std::string& _name, float* _color) override;
			virtual void EndDebugLabel() override;

			// Getters
			inline ID3D12CommandQueue* GetD3DCommandQueue() const { return m_CommandQueueObj; }

		private:
			ID3D12CommandQueue* m_CommandQueueObj;
		};
	}
}