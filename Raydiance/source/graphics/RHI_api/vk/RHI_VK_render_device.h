#pragma once
#include "./graphics/RHI/RHI_render_device.h"
#include "./graphics/RHI/object/command/RHI_command_queue_type.h"

// If running on windows define windows specific VK implementation

#include <vulkan/vulkan.h>

namespace Raydiance
{
	namespace Graphics
	{
		class RHI_VK_RenderDevice final : public RHI_RenderDevice
		{
		public:
			// Public constructor and desctructor
					 RHI_VK_RenderDevice(void);
			virtual ~RHI_VK_RenderDevice(void);


			virtual Result Initialize(const RHI_RenderDeviceDescriptor& _renderDeviceDescriptor) override;

			// Adapter functions
			// ----------------------------------------------------------------------
			[[nodiscard]] virtual Result GetAdapterCount(uint32& _count) const override;
			[[nodiscard]] virtual Result GetAdapter(const uint32 _adapterID, std::unique_ptr<RHI_Adapter>& _adapter) const override;

			[[nodiscard]] virtual Result LinkAdapter(std::unique_ptr<RHI_Adapter> _adapter) override;

			inline VkInstance GetVKInstance() const { return m_Instance; }
			inline VkSurfaceKHR GetVKSurface() const { return m_Surface; }

			inline VkDevice GetDevice() const { return m_Device; }

			inline uint32_t GetPresentQueueID() const { return m_PresentQueueID; }
			inline uint32_t GetGraphicsQueueID() const { return m_GraphicsQueueID; }

			uint32_t GetQueueFamilyID(const RHI_CommandQueueType _type) const;

			// Create functions
			// ----------------------------------------------------------------------
			[[nodiscard]] virtual std::shared_ptr<RHI_CommandPool>   CreateCommandPool(const RHI_CommandPoolDescriptor& _commandPoolDescriptor) override;
			[[nodiscard]] virtual std::shared_ptr<RHI_CommandBuffer> CreateCommandBuffer(const RHI_CommandBufferDescriptor& _commandBufferDescriptor) override;
			[[nodiscard]] virtual std::shared_ptr<RHI_CommandQueue>  CreateCommandQueue(const RHI_CommandQueueDescriptor& _commandQueueDescriptor) override;
			[[nodiscard]] virtual std::shared_ptr<RHI_Swapchain> CreateSwapchain(const RHI_CommandQueue& _commandQueue, const RHI_SwapchainDescriptor& _swapchainDescriptor) override;
			[[nodiscard]] virtual std::shared_ptr<RHI_FenceCPU>  CreateFenceCPU(const RHI_FenceCPUDescriptor& _fenceDescriptor) override;

			virtual RHI_GraphicsPipeline* CreateGraphicsPipeline(const RHI_GraphicsPipelineDescriptor* _graphicsPipelineDescriptor) override;
			virtual RHI_InputLayout* CreateInputLayout(const RHI_InputLayoutDescriptor* _inputLayoutDescriptor) override;
			virtual RHI_RenderPass* CreateRenderPass(const RHI_RenderPassDescriptor* _renderPassDescriptor) override;
			virtual RHI_FrameBuffer* CreateFrameBuffer(const RHI_FrameBufferDescriptor* _frameBufferDescriptor) override;

			virtual RHI_DescriptorPool* CreateDescriptorPool(const RHI_DescriptorPoolDescriptor* _descriptorPoolDescriptor) override;

			virtual RHI_Buffer* CreateBuffer(const RHI_BufferDescriptor* _bufferDescriptor) override;
			virtual RHI_Shader* CreateShader(const RHI_ShaderDescriptor* _shaderDescriptor) override;

			virtual RHI_Texture2D* CreateTexture2D(const RHI_Texture2DDescriptor* _texture2DDescriptor) override;
			virtual RHI_Sampler2D* CreateSampler2D(const RHI_Sampler2DDescriptor* _sampler2DDescripotr) override;

		private:
			bool CheckValidationLayerSupport();
			void GetVKPhysicalDevice();

			// Per application state is stored in the VK_Instance object
			// Used to initialize vulkan, should be deleted after everything else is freed
			VkInstance m_Instance = VK_NULL_HANDLE;

			VkDebugUtilsMessengerEXT m_DebugMessenger;

			VkSurfaceKHR m_Surface;

			VkDevice m_Device;

			uint32_t m_PresentQueueID = 0;
			uint32_t m_GraphicsQueueID = 0;
		};
	}
}