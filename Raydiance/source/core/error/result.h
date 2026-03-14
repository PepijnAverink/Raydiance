#pragma once
#include "./core/container/types.h"

namespace Raydiance
{
	enum class Result : uint8
	{
		RESULT_INVALID = 0x00,
		RESULT_GOOD    = 0x01,
		RESULT_WARNING = 0x02,
		RESULT_ERROR   = 0b011, // 0b011
		RESULT_FATAL   = 0b111, // 0b111
	};

	inline bool CheckError(Result _result)
	{
		return ((uint8)_result & (uint8)Result::RESULT_ERROR) == (uint8)Result::RESULT_ERROR;
	}
}