#pragma once
#include "./core/container/types.h"

namespace Raydiance
{
	enum class ByteOrder : uint8
	{
		BYTE_ORDER_INVALID		 = 0x00,
		BYTE_ORDER_BIG_ENDIAN    = 0x01,
		BYTE_ORDER_LITTLE_ENDIAN = 0x02,
	};
}