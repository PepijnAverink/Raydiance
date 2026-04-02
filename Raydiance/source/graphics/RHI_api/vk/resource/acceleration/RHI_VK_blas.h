#pragma once
#include "./graphics/RHI/resource/acceleration/RHI_blas.h"
#include "./graphics/RHI_api/vk/resource/buffer/RHI_VK_buffer.h"

#include <vulkan/vulkan.h>

namespace Raydiance
{
	namespace Graphics
	{
		class RHI_VK_RenderDevice;
		class RHI_VK_BLAS final : public RHI_BLAS
		{
		public:
			RHI_VK_BLAS(RHI_VK_RenderDevice* _RHI_RenderDevice, const RHI_BLASDescriptor* _blasDescriptor);
			virtual ~RHI_VK_BLAS();

			inline RHI_VK_Buffer* GetVKScratchBuffer() const { return m_BuildScratchBuffer; }

			inline VkQueryPool GetVKQueryPool() const { return m_QueryPool; }

			inline VkDeviceAddress GetVKAccelerationStructureAddress() const { return m_AccelerationStructureAddress; }
			inline const std::vector<VkAccelerationStructureBuildRangeInfoKHR>& GetVKRanges() const { return m_Ranges; }
			inline const std::vector<VkAccelerationStructureGeometryKHR>& GetVKGeometryList() const { return m_GeometryList; }

			inline VkAccelerationStructureKHR GetVKAccelerationStructure() const { return m_AccelerationStructure; }

		private:
			RHI_VK_Buffer* m_BuildScratchBuffer;
			RHI_VK_Buffer* m_UpdateScratchBuffer;

			std::vector<VkAccelerationStructureBuildRangeInfoKHR> m_Ranges;
			std::vector<VkAccelerationStructureGeometryKHR>       m_GeometryList;

			VkDeviceAddress	 m_AccelerationStructureAddress;
			RHI_VK_Buffer*   m_AccelerationStructureBuffer;
			VkAccelerationStructureKHR m_AccelerationStructure;

			VkQueryPool m_QueryPool = VK_NULL_HANDLE;

		};
	}
}