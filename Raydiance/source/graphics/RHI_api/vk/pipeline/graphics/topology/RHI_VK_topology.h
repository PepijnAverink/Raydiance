#pragma once
#include "./graphics/RHI/pipeline/graphics/topology/RHI_topology.h"
#include "./core/error/logger.h"

#include <vulkan/vulkan.h>

namespace Raydiance
{
	namespace Graphics
	{
		inline VkPrimitiveTopology ResolveVKTopology(RHI_Topology _topology)
		{
			switch (_topology)
			{
				case RHI_Topology::RHI_TOPOLOGY_POINT_LIST:
					return VK_PRIMITIVE_TOPOLOGY_POINT_LIST;
				case RHI_Topology::RHI_TOPOLOGY_LINE_STRIP:
					return VK_PRIMITIVE_TOPOLOGY_LINE_STRIP;
				case RHI_Topology::RHI_TOPOLOGY_LINE_LIST:
					return VK_PRIMITIVE_TOPOLOGY_LINE_LIST;
				case RHI_Topology::RHI_TOPOLOGY_TRIANGLE_STRIP:
					return VK_PRIMITIVE_TOPOLOGY_TRIANGLE_STRIP;
				case RHI_Topology::RHI_TOPOLOGY_TRIANGLE_LIST:
					return VK_PRIMITIVE_TOPOLOGY_TRIANGLE_LIST;
			}

			Logger::Log("Failed to resolve VKTopology: " + (uint8)_topology, LogLevel::LOG_LEVEL_ERROR);
			return VK_PRIMITIVE_TOPOLOGY_TRIANGLE_LIST;
		}
	}
}