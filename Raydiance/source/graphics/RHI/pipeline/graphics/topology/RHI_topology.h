#pragma once

namespace Raydiance
{
	namespace Graphics
	{
		enum RHI_Topology
		{
			RHI_TOPOLOGY_INVALID	    = 0x00,
			RHI_TOPOLOGY_POINT_LIST     = 0x01,
			RHI_TOPOLOGY_LINE_STRIP     = 0x02,
			RHI_TOPOLOGY_LINE_LIST      = 0x03,
			RHI_TOPOLOGY_TRIANGLE_STRIP = 0x04,
			RHI_TOPOLOGY_TRIANGLE_LIST  = 0x05,
		};
	}
}