#pragma once
// Graphics includes
#include "./graphics/gfx/renderer3D.h"

namespace Sandbox
{
	class DefaultRenderer3D final : public Raydiance::Graphics::Renderer3D
	{
	public:
		 DefaultRenderer3D() = default;
		~DefaultRenderer3D() = default;

		// Initialization and termination
		virtual Raydiance::Result Initialize(const Raydiance::Graphics::Renderer3DDescriptor& _renderer3DDescriptor) override;
		virtual Raydiance::Result Terminate() override;


		// Frame flow
		virtual void BeginFrame()  override;
		virtual void BeginFrame(const Raydiance::Graphics::Camera& _camera) override;

		virtual void EndFrame() override;

	private:
		Raydiance::Graphics::RHI_FenceCPU* m_AquireFence = nullptr;
	};
}