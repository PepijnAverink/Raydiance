#pragma once
#include "./core/container/types.h"

#include <iostream>

namespace Raydiance
{
	enum class ByteStreamState : uint8
	{
		BYTE_STREAM_STATE_INVALID = 0x00,
		BYTE_STREAM_STATE_READ    = 0x01,
		BYTE_STREAM_STATE_WRITE   = 0x02,
	};


	inline uint32 ResolveStreamState(ByteStreamState _state)
	{
		if (_state == ByteStreamState::BYTE_STREAM_STATE_READ)
			return std::ios::in;
		if (_state == ByteStreamState::BYTE_STREAM_STATE_WRITE)
			return std::ios::out;

		return 0;
	}
}