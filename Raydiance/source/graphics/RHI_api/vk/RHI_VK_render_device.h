#pragma once
#include "./graphics/RHI/RHI_render_device.h"
//#include "./graphics/RHI/object/command/command_queue_type.h"

// If running on windows define windows specific VK implementation

#include <vulkan/vulkan.h>

namespace Raydiance
{
	namespace Graphics
	{
		enum class CommandQueueType;
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

			uint32_t GetQueueFamilyID(const CommandQueueType _type) const;

			// Create functions
			// ----------------------------------------------------------------------
			[[nodiscard]] virtual std::shared_ptr<CommandPool>   CreateCommandPool(const CommandPoolDescriptor& _commandPoolDescriptor) override;
			[[nodiscard]] virtual std::shared_ptr<CommandBuffer> CreateCommandBuffer(const CommandBufferDescriptor& _commandBufferDescriptor) override;
			[[nodiscard]] virtual std::shared_ptr<CommandQueue>  CreateCommandQueue(const CommandQueueDescriptor& _commandQueueDescriptor) override;
			[[nodiscard]] virtual std::shared_ptr<RHI_Swapchain> CreateSwapchain(const CommandQueue& _commandQueue, const RHI_SwapchainDescriptor& _swapchainDescriptor) override;
			[[nodiscard]] virtual std::shared_ptr<RHI_FenceCPU>  CreateFenceCPU(const RHI_FenceCPUDescriptor& _fenceDescriptor) override;

			virtual GraphicsPipeline* CreateGraphicsPipeline(const GraphicsPipelineDescriptor* _graphicsPipelineDescriptor) override;
			virtual InputLayout* CreateInputLayout(const InputLayoutDescriptor* _inputLayoutDescriptor) override;
			virtual RenderPass* CreateRenderPass(const RenderPassDescriptor* _renderPassDescriptor) override;
			virtual FrameBuffer* CreateFrameBuffer(const FrameBufferDescriptor* _frameBufferDescriptor) override;

			virtual DescriptorPool* CreateDescriptorPool(const DescriptorPoolDescriptor* _descriptorPoolDescriptor) override;

			virtual Buffer* CreateBuffer(const BufferDescriptor* _bufferDescriptor) override;
			virtual Shader* CreateShader(const ShaderDescriptor* _shaderDescriptor) override;

			virtual Texture2D* CreateTexture2D(const Texture2DDescriptor* _texture2DDescriptor) override;
			virtual Sampler2D* CreateSampler2D(const Sampler2DDescriptor* _sampler2DDescripotr) override;

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