#pragma once
// Parant class include
#include "./graphics/RHI/object/sync/RHI_FenceCPU.h"


// DirectX12 includes
#include <d3d12.h>


namespace Raydiance
{
	namespace Graphics
	{
		class RHI_DX12_RenderDevice;
		class RHI_DX12_FenceCPU final : public RHI_FenceCPU
		{
		public:
			// Constructor and descructor
			// ======================================
					 RHI_DX12_FenceCPU(void);
			virtual ~RHI_DX12_FenceCPU(void);

			[[nodiscard]] const Result Initialize(const RHI_DX12_RenderDevice& _renderDevice, const RHI_FenceCPUDescriptor& _fenceDescriptor);

			// TODO:: MAYBEEEE not [[nodiscard]]???
			[[nodiscard]] virtual const Result Wait(void) override;

		private:
		};
	}
}