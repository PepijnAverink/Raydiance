#pragma once
#include "./graphics/renderer/renderer3D.h"
#include <vector>

class DefaultRenderer : public Raydiance::Graphics::Renderer3D
{
public:
	virtual ~DefaultRenderer();

	virtual void OnInitialize(Raydiance::Graphics::RendererBackend* _backend) override;
	virtual void OnTerminate() override;

	virtual void OnResize(const uint32_t _width, const uint32_t _height) override;

	virtual void BeginScene(Raydiance::Graphics::Camera* _camera) override;
	virtual void EndScene() override;

	virtual void DrawMesh(Raydiance::Graphics::Mesh* _mesh, const glm::mat4& transform) override;
	virtual void DrawSubMesh(Raydiance::Graphics::Mesh* _mesh, const uint32_t _subMeshID, const glm::mat4& transform) override;

private:
	std::shared_ptr<Raydiance::Graphics::RHI_CommandPool>   m_CommandPool   = nullptr;
	std::shared_ptr<Raydiance::Graphics::RHI_CommandBuffer> m_CommandBuffer = nullptr;

	std::shared_ptr<Raydiance::Graphics::RHI_FenceCPU> m_Fence = nullptr;

	Raydiance::Graphics::RHI_RenderPass*  m_RenderPass  = nullptr;
	Raydiance::Graphics::RHI_InputLayout* m_InputLayout = nullptr;
	Raydiance::Graphics::RHI_GraphicsPipeline* m_GraphicsPipeline = nullptr;

	std::vector<Raydiance::Graphics::RHI_FrameBuffer*> m_FrameBuffers;

	Raydiance::Graphics::RHI_Sampler2D* m_Sampler = nullptr;
	Raydiance::Graphics::RHI_Texture2D* m_Texture = nullptr;

	Raydiance::Graphics::RHI_DescriptorPool* m_DescriptorPool = nullptr;
	Raydiance::Graphics::RHI_DescriptorSet* m_DescriptorSet = nullptr;
};