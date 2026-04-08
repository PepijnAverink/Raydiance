#pragma once
// Descriptor include
#include "./graphics/gfx/renderer3D_descriptor.h"


// Core includes
#include "./core/error/result.h"


// Graphics includes
#include "./graphics/gfx/frame_data.h"
#include "./graphics/gfx/camera/camera.h"
#include "./graphics/gfx/render_backend.h"


namespace Raydiance
{
	namespace Graphics
	{
		class Renderer3D
		{
		public:
			// Initialization and termination
			Result Initialize(const Renderer3DDescriptor& _renderer3DDescriptor);
			Result Terminate();


			// Frame flow
			void BeginFrame();
			//void BeginFrame(const Camera& _camera);

			void EndFrame();


			// Build renderlist
			// void SubmitMesh();

		protected:
			uint32 m_FramesInFlight	   = 0;
			uint32 m_CurrentFrameIndex = 0;

			std::vector<FrameData> m_FrameData;

			RHI_FenceCPU* m_AquireFence = nullptr;
		};
	}
}