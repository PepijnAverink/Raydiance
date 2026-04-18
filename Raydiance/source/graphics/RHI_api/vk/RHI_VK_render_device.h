#pragma once
#include "./graphics/RHI/RHI_render_device.h"
#include "./graphics/RHI_api/vk/object/command/RHI_VK_command_queue_family.h"

#define VK_USE_PLATFORM_WIN32_KHR
#include <vulkan/vulkan.h>

namespace Raydiance
{
	namespace Graphics
	{
		class RHI_VK_RenderDevice final : public RHI_RenderDevice
		{
		public:
			RHI_VK_RenderDevice();
			virtual ~RHI_VK_RenderDevice();

			virtual Result Initialize(const RHI_RenderDeviceDescriptor* _renderDeviceDescriptor) override;

			// Adapter functions
			// ----------------------------------------------------------------------
			virtual Result GetAdapterCount(uint32& _count) const override;
			virtual Result GetAdapter(uint32 _index, RHI_Adapter** _adapter) const override;

			virtual Result LinkAdapter(RHI_Adapter* _adapter) override;


			// Swapchain functions
			// ----------------------------------------------------------------------
			virtual Result CheckSwapchainResourceFormatSupport(RHI_ResourceFormat _format, bool& _supported) const override;


			// Native create functions
			// ----------------------------------------------------------------------
			virtual RHI_CommandQueue*  RHI_CreateCommandQueue(const RHI_CommandQueueDescriptor* _commandQueueDescriptor) override;
			virtual RHI_CommandBuffer* RHI_CreateCommandBuffer(const RHI_CommandBufferDescriptor* _commandBufferDescriptor) override;
			virtual RHI_CommandPool*   RHI_CreateCommandPool(const RHI_CommandPoolDescriptor* _commandPoolDescriptor) override;

			virtual RHI_Swapchain* RHI_CreateSwapchain(RHI_CommandQueue* _commandQueue, const RHI_SwapchainDescriptor* _swapchainDescriptor) override;
			virtual RHI_FenceCPU*  RHI_CreateFenceCPU(const RHI_FenceCPUDescriptor* _FenceDescriptor) override;

			virtual RHI_Texture2D* RHI_CreateTexture2D(const RHI_Texture2DDescriptor* _texture2DDescriptor) override;
			virtual RHI_Shader* RHI_CreateShader(const RHI_ShaderDescriptor* _shaderDescriptor) override;
			virtual RHI_Buffer* RHI_CreateBuffer(const RHI_BufferDescriptor* _bufferDescriptor) override;
			virtual RHI_Sampler* RHI_CreateSampler(const RHI_SamplerDescriptor* _samplerDescriptor) override;

			virtual RHI_RenderPass* RHI_CreateRenderPass(const RHI_RenderPassDescriptor* _renderPassDescriptor) override;
			virtual RHI_FrameBuffer* RHI_CreateFrameBuffer(const RHI_FrameBufferDescriptor* _frameBufferDescriptor) override;

			virtual RHI_DescriptorPool* RHI_CreateDescriptorPool(const RHI_DescriptorPoolDescriptor* _descriptorPoolDescriptor) override;

			virtual RHI_InputLayout* RHI_CreateInputLayout(const RHI_InputLayoutDescriptor* _inputLayoutDescriptor) override;
			virtual RHI_GraphicsPipeline* RHI_CreateGraphicsPipeline(const RHI_GraphicsPipelineDescriptor* _graphicsPipelineDescriptor) override;
			virtual RHI_ComputePipeline* RHI_CreateComputePipeline(const RHI_ComputePipelineDescriptor* _computePipelineDescriptor) override;

			virtual RHI_Pipeline* RHI_CreatePipeline(const RHI_ComputePipelineDescriptor* _computePipelineDescriptor) override;
			virtual RHI_Pipeline* RHI_CreatePipeline(const RHI_GraphicsPipelineDescriptor* _graphicsPipelineDescriptor) override;

			RHI_Texture2D* CreateTexture2DFromVkImage(VkImage _image, const RHI_Texture2DDescriptor* _texture2DDescriptor);

			// Query the Vulkan Queue families allocated at startup
			// --------------------------------------------------------------------------
			const Result QueryCommandQueueIndex(RHI_CommandQueueType _type, uint32& _index) const;

			// Vulkan getter functions
			// --------------------------------------------------------------------------
			inline VkDevice GetVKDevice() const { return m_Device; }
			inline VkInstance GetVKInstance() const { return m_Instance; }

			inline VkSurfaceKHR GetVKSurface() const { return m_Surface; }

			static PFN_vkSetDebugUtilsObjectNameEXT    vkSetDebugUtilsObjectNameEXT;
			static PFN_vkQueueBeginDebugUtilsLabelEXT  vkQueueBeginDebugUtilsLabelEXT;
			static PFN_vkQueueEndDebugUtilsLabelEXT    vkQueueEndDebugUtilsLabelEXT;
			static PFN_vkQueueInsertDebugUtilsLabelEXT vkQueueInsertDebugUtilsLabelEXT;
			static PFN_vkCmdBeginDebugUtilsLabelEXT    vkCmdBeginDebugUtilsLabelEXT;
			static PFN_vkCmdEndDebugUtilsLabelEXT      vkCmdEndDebugUtilsLabelEXT;
			static PFN_vkCmdInsertDebugUtilsLabelEXT   vkCmdInsertDebugUtilsLabelEXT;

			static PFN_vkGetBufferDeviceAddressKHR vkGetBufferDeviceAddressKHR;

			static PFN_vkGetAccelerationStructureBuildSizesKHR vkGetAccelerationStructureBuildSizesKHR;
			static PFN_vkCreateAccelerationStructureKHR vkCreateAccelerationStructureKHR;
			static PFN_vkDestroyAccelerationStructureKHR vkDestroyAccelerationStructureKHR;

			static PFN_vkCmdBuildAccelerationStructuresKHR vkCmdBuildAccelerationStructuresKHR;
			static PFN_vkGetAccelerationStructureDeviceAddressKHR vkGetAccelerationStructureDeviceAddressKHR;
			static PFN_vkCreateRayTracingPipelinesKHR vkCreateRayTracingPipelinesKHR;

			static PFN_vkGetRayTracingShaderGroupHandlesKHR vkGetRayTracingShaderGroupHandlesKHR;
			static PFN_vkCmdTraceRaysKHR vkCmdTraceRaysKHR;

		private:
			bool CheckValidationLayerSupport();

			VkInstance m_Instance  = VK_NULL_HANDLE;
			VkDebugUtilsMessengerEXT m_DebugMessenger;

			VkDevice  m_Device     = nullptr;

			VkSurfaceKHR   m_Surface = VK_NULL_HANDLE;

			std::vector<RHI_VK_CommandQueueFamily> m_CommandQueueFamilies;
		};
	}
}