#pragma once
#include "./graphics/renderer/renderer3D.h"
#include <vector>

class DefaultRenderer : public Raydiance::Graphics::Renderer3D
{
public:
	virtual void OnInitialize(Raydiance::Graphics::RendererBackend* _backend) override;
	virtual void OnTerminate() override;

	virtual void OnResize(const uint32_t _width, const uint32_t _height) override;

	virtual void BeginScene(Raydiance::Graphics::Camera* _camera) override;
	virtual void EndScene() override;

	virtual void DrawMesh(Raydiance::Graphics::Mesh* _mesh, const glm::mat4& transform) override;
	virtual void DrawSubMesh(Raydiance::Graphics::Mesh* _mesh, const uint32_t _subMeshID, const glm::mat4& transform) override;

private:
	Raydiance::Graphics::CommandPool*   m_CommandPool   = nullptr;
	Raydiance::Graphics::CommandBuffer* m_CommandBuffer = nullptr;

	std::shared_ptr<Raydiance::Graphics::RHI_FenceCPU> m_Fence = nullptr;

	Raydiance::Graphics::RenderPass*  m_RenderPass  = nullptr;
	Raydiance::Graphics::InputLayout* m_InputLayout = nullptr;
	Raydiance::Graphics::GraphicsPipeline* m_GraphicsPipeline = nullptr;

	std::vector<Raydiance::Graphics::FrameBuffer*> m_FrameBuffers;

	Raydiance::Graphics::Sampler2D* m_Sampler = nullptr;
	Raydiance::Graphics::Texture2D* m_Texture = nullptr;

	Raydiance::Graphics::DescriptorPool* m_DescriptorPool = nullptr;
	Raydiance::Graphics::DescriptorSet* m_DescriptorSet = nullptr;
};