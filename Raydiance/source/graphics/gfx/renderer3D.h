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
			virtual Result Initialize(const Renderer3DDescriptor& _renderer3DDescriptor);
			virtual Result Terminate();


			// Frame flow
			virtual void BeginFrame() = 0;
			virtual void BeginFrame(const Camera& _camera) = 0;

			virtual void EndFrame() = 0;


			// Build renderlist
			//virtual void SubmitMesh();

		protected:
			uint32 m_FramesInFlight	   = 0;
			uint32 m_CurrentFrameIndex = 0;

			std::vector<FrameData> m_FrameData;
		};
	}
}