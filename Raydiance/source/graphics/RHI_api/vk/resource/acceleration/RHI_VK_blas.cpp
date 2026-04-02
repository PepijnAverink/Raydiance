#include "./pch.h"
#include "./graphics/RHI_api/vk/resource/acceleration/RHI_vk_blas.h"
#include "./graphics/RHI_api/vk/resource/acceleration/RHI_vk_as_build_flags.h"
#include "./graphics/RHI_api/vk/resource/buffer/RHI_vk_buffer.h"

#include <./graphics/RHI_api/vk/RHI_vk_render_device.h>

namespace Raydiance
{
	namespace Graphics
	{
		RHI_VK_BLAS::RHI_VK_BLAS(RHI_VK_RenderDevice* _RHI_RenderDevice, const RHI_BLASDescriptor* _blasDescriptor)
			: RHI_BLAS(_blasDescriptor)
		{
			std::vector<uint32_t> primitive_count;
			for (uint32_t i = 0; i < _blasDescriptor->Instances.size(); i++)
			{
				RHI_BLASInstance instance = _blasDescriptor->Instances[i];
				bool indexed = (instance.IndexBuffer != nullptr);

				VkBufferDeviceAddressInfo info{};
				info.sType = VK_STRUCTURE_TYPE_BUFFER_DEVICE_ADDRESS_INFO;
				info.buffer = ((RHI_VK_Buffer*)instance.VertexBuffer)->GetVKBuffer();

				VkDeviceAddress vertexBufferAddress = vkGetBufferDeviceAddress(_RHI_RenderDevice->GetVKDevice(), &info);

				VkDeviceAddress indexBufferAddress;
				if (indexed == true)
				{
					info.buffer = ((RHI_VK_Buffer*)instance.IndexBuffer)->GetVKBuffer();
					indexBufferAddress = vkGetBufferDeviceAddress(_RHI_RenderDevice->GetVKDevice(), &info);
				}

				VkAccelerationStructureGeometryTrianglesDataKHR triangles{};
				triangles.sType = VK_STRUCTURE_TYPE_ACCELERATION_STRUCTURE_GEOMETRY_TRIANGLES_DATA_KHR;
				triangles.vertexFormat = VK_FORMAT_R32G32B32_SFLOAT;  // vec3 vertex position data.
				triangles.vertexData.deviceAddress = vertexBufferAddress;
				triangles.vertexStride = instance.VertexBuffer->GetStride();
				triangles.maxVertex = (instance.VertexBuffer->GetSize() / instance.VertexBuffer->GetStride()) - 1;
				triangles.indexType = VK_INDEX_TYPE_NONE_KHR;

				if (indexed == true)
				{
					triangles.indexType = ((RHI_VK_Buffer*)instance.IndexBuffer)->GetVKIndexFormat();
					triangles.indexData.deviceAddress = indexBufferAddress;
				}

				VkAccelerationStructureGeometryKHR geometry{};
				geometry.sType = VK_STRUCTURE_TYPE_ACCELERATION_STRUCTURE_GEOMETRY_KHR;
				geometry.geometryType = VK_GEOMETRY_TYPE_TRIANGLES_KHR;
				geometry.geometry.triangles = triangles;
				geometry.flags = VK_GEOMETRY_OPAQUE_BIT_KHR;

				m_GeometryList.push_back(geometry);

				if (indexed)
					primitive_count.push_back(instance.IndexBuffer->GetSize() / (instance.IndexBuffer->GetStride() * 3));
				else
					primitive_count.push_back(instance.VertexBuffer->GetSize() / (instance.VertexBuffer->GetStride() * 3));


				VkAccelerationStructureBuildRangeInfoKHR range;
				range.firstVertex = 0;
				range.primitiveCount = primitive_count[i];
				range.primitiveOffset = 0;
				range.transformOffset = 0;

				m_Ranges.push_back(range);
			}

			VkAccelerationStructureBuildGeometryInfoKHR buildInfo{};
			buildInfo.sType = VK_STRUCTURE_TYPE_ACCELERATION_STRUCTURE_BUILD_GEOMETRY_INFO_KHR;
			buildInfo.type = VK_ACCELERATION_STRUCTURE_TYPE_BOTTOM_LEVEL_KHR;
			buildInfo.mode = VK_BUILD_ACCELERATION_STRUCTURE_MODE_BUILD_KHR;
			buildInfo.geometryCount = m_GeometryList.size();
			buildInfo.pGeometries = m_GeometryList.data();
			buildInfo.ppGeometries = NULL;
			buildInfo.flags = ResolveVKBuildFlags(_blasDescriptor->Flags);

			VkAccelerationStructureBuildSizesInfoKHR resultSize{};
			resultSize.sType = VK_STRUCTURE_TYPE_ACCELERATION_STRUCTURE_BUILD_SIZES_INFO_KHR;
			((RHI_VK_RenderDevice*)RHI_RenderDevice::Get())->vkGetAccelerationStructureBuildSizesKHR(_RHI_RenderDevice->GetVKDevice(), VK_ACCELERATION_STRUCTURE_BUILD_TYPE_DEVICE_KHR, &buildInfo, primitive_count.data(), &resultSize);
			m_ScratchSize = resultSize.buildScratchSize;

			RHI_BufferDescriptor bufferDesc = {};
			bufferDesc.Name = "BuildBuffer";
			bufferDesc.MemoryType = Graphics::RHI_ResourceMemoryType::RHI_RESOURCE_MEMORY_TYPE_GPU;
			bufferDesc.Size  = resultSize.buildScratchSize;
			bufferDesc.Flags = Graphics::RHI_BufferUsageFlags::RHI_BUFFER_USAGE_FLAGS_UNORDERED_ACCESS;

			m_BuildScratchBuffer = (RHI_VK_Buffer*)_RHI_RenderDevice->RHI_CreateBuffer(&bufferDesc);

			if (m_AllowUpdate == true)
			{
				bufferDesc.Size = resultSize.updateScratchSize;
				m_UpdateScratchBuffer = (RHI_VK_Buffer*)_RHI_RenderDevice->RHI_CreateBuffer(&bufferDesc);
			}

			bufferDesc.Size = resultSize.accelerationStructureSize;
			bufferDesc.Flags = Graphics::RHI_BufferUsageFlags::RHI_BUFFER_USAGE_FLAGS_ACCELERATION_STRUCTURE;
			m_AccelerationStructureBuffer = (RHI_VK_Buffer*)_RHI_RenderDevice->RHI_CreateBuffer(&bufferDesc);


			VkAccelerationStructureCreateInfoKHR createInfo{};
			createInfo.sType = VK_STRUCTURE_TYPE_ACCELERATION_STRUCTURE_CREATE_INFO_KHR;
			createInfo.type = VK_ACCELERATION_STRUCTURE_TYPE_BOTTOM_LEVEL_KHR;
			createInfo.buffer = m_AccelerationStructureBuffer->GetVKBuffer();
			createInfo.offset = 0;
			createInfo.size = resultSize.accelerationStructureSize;

			if (((RHI_VK_RenderDevice*)RHI_RenderDevice::Get())->vkCreateAccelerationStructureKHR(_RHI_RenderDevice->GetVKDevice(), &createInfo, nullptr, &m_AccelerationStructure) != VK_SUCCESS)
				Logger::Log("VK_ERROR - Failed to create AccelerationStructure.", LogLevel::LOG_LEVEL_ERROR);


			VkAccelerationStructureDeviceAddressInfoKHR info1{};
			info1.sType = VK_STRUCTURE_TYPE_ACCELERATION_STRUCTURE_DEVICE_ADDRESS_INFO_KHR;
			info1.accelerationStructure = m_AccelerationStructure;

			((RHI_VK_RenderDevice*)RHI_RenderDevice::Get())->vkGetAccelerationStructureDeviceAddressKHR(_RHI_RenderDevice->GetVKDevice(), &info1);

			VkAccelerationStructureDeviceAddressInfoKHR addressACInfo{};
			addressACInfo.sType = VK_STRUCTURE_TYPE_ACCELERATION_STRUCTURE_DEVICE_ADDRESS_INFO_KHR;
			addressACInfo.accelerationStructure = m_AccelerationStructure;

			m_AccelerationStructureAddress = ((RHI_VK_RenderDevice*)RHI_RenderDevice::Get())->vkGetAccelerationStructureDeviceAddressKHR(_RHI_RenderDevice->GetVKDevice(), &addressACInfo);
			//if (m_AllowCompaction == true) 
			//{
			//	VkQueryPoolCreateInfo qpci{ VK_STRUCTURE_TYPE_QUERY_POOL_CREATE_INFO };
			//	qpci.queryCount = 1;
			//	qpci.queryType  = VK_QUERY_TYPE_ACCELERATION_STRUCTURE_COMPACTED_SIZE_KHR;
			//
			//	vkCreateQueryPool(_RHI_RenderDevice->GetDevice(), &qpci, nullptr, &m_QueryPool);
			//}
		}

		RHI_VK_BLAS::~RHI_VK_BLAS()
		{
			delete m_BuildScratchBuffer;
			delete m_UpdateScratchBuffer;
			delete m_AccelerationStructureBuffer;

			((RHI_VK_RenderDevice*)RHI_RenderDevice::Get())->vkDestroyAccelerationStructureKHR(((RHI_VK_RenderDevice*)RHI_RenderDevice::Get())->GetVKDevice(), m_AccelerationStructure, nullptr);
		}
	}
}