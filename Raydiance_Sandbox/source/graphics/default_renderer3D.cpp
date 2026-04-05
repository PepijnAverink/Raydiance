#include "stdafx.h"
#include "./graphics/default_renderer3D.h"


namespace Sandbox
{
	Raydiance::Result DefaultRenderer3D::Initialize(const Raydiance::Graphics::Renderer3DDescriptor& _renderer3DDescriptor)
	{
		m_AquireFence;

		return Raydiance::Result::RESULT_GOOD;
	}


	Raydiance::Result DefaultRenderer3D::Terminate()
	{
		return Raydiance::Result::RESULT_GOOD;
	}


	void DefaultRenderer3D::BeginFrame()
	{
		//m_CurrentFrameIndex = Raydiance::Graphics::RenderBackend::AquireNewFrame();
	}


	void DefaultRenderer3D::BeginFrame(const Raydiance::Graphics::Camera& _camera)
	{

	}


	void DefaultRenderer3D::EndFrame()
	{

	}
}