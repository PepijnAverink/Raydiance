#pragma once
#include "./graphics/RHI/pipeline/graphics/topology/RHI_topology.h"

#include <d3d12.h>

#include "./core/error/logger.h"

namespace Raydiance
{
	namespace Graphics
	{
		inline D3D_PRIMITIVE_TOPOLOGY ResolveDX12Topology(RHI_Topology _topology)
		{
			switch (_topology)
			{
				case RHI_Topology::RHI_TOPOLOGY_INVALID:
					return D3D_PRIMITIVE_TOPOLOGY_UNDEFINED;
				case RHI_Topology::RHI_TOPOLOGY_POINT_LIST:
					return D3D_PRIMITIVE_TOPOLOGY_POINTLIST;
				case RHI_Topology::RHI_TOPOLOGY_LINE_STRIP:
					return D3D_PRIMITIVE_TOPOLOGY_LINESTRIP;
				case RHI_Topology::RHI_TOPOLOGY_LINE_LIST:
					return D3D_PRIMITIVE_TOPOLOGY_LINELIST;
				case RHI_Topology::RHI_TOPOLOGY_TRIANGLE_STRIP:
					return D3D_PRIMITIVE_TOPOLOGY_TRIANGLESTRIP;
				case RHI_Topology::RHI_TOPOLOGY_TRIANGLE_LIST:
					return D3D_PRIMITIVE_TOPOLOGY_TRIANGLELIST;
			}

			Logger::Log("Failed to resolve DX12Topology: " + (uint32)_topology, LogLevel::LOG_LEVEL_ERROR);
			return D3D_PRIMITIVE_TOPOLOGY_UNDEFINED;
		}

		inline D3D12_PRIMITIVE_TOPOLOGY_TYPE ResolveDX12TopologyType(RHI_Topology _topology)
		{
			switch (_topology)
			{
				case RHI_Topology::RHI_TOPOLOGY_INVALID:
					return D3D12_PRIMITIVE_TOPOLOGY_TYPE_UNDEFINED;
				case RHI_Topology::RHI_TOPOLOGY_POINT_LIST:
					return D3D12_PRIMITIVE_TOPOLOGY_TYPE_POINT;
				case RHI_Topology::RHI_TOPOLOGY_LINE_STRIP:
					return D3D12_PRIMITIVE_TOPOLOGY_TYPE_LINE;
				case RHI_Topology::RHI_TOPOLOGY_LINE_LIST:
					return D3D12_PRIMITIVE_TOPOLOGY_TYPE_LINE;
				case RHI_Topology::RHI_TOPOLOGY_TRIANGLE_STRIP:
					return D3D12_PRIMITIVE_TOPOLOGY_TYPE_TRIANGLE;
				case RHI_Topology::RHI_TOPOLOGY_TRIANGLE_LIST:
					return D3D12_PRIMITIVE_TOPOLOGY_TYPE_TRIANGLE;
			}

			Logger::Log("Failed to resolve DX12Topology: " + (uint32)_topology, LogLevel::LOG_LEVEL_ERROR);
			return D3D12_PRIMITIVE_TOPOLOGY_TYPE_UNDEFINED;
		}
	}
}