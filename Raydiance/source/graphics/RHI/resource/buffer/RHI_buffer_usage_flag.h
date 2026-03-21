#pragma once
// Core includes
#include "./core/error/logger.h"
#include "./core/container/types.h"


namespace Raydiance
{
	namespace Graphics
	{
		enum class RHI_BufferUsageFlag : uint32
		{
			RHI_BUFFER_USAGE_FLAG_INVALID		   = 0x00,
			RHI_BUFFER_USAGE_FLAG_VERTEX_BUFFER    = 0x01,
			RHI_BUFFER_USAGE_FLAG_INDEX_BUFFER	   = 0x02,
			RHI_BUFFER_USAGE_FLAG_UNIFORM_BUFFER   = 0x04,
			RHI_BUFFER_USAGE_FLAG_STAGING_BUFFER   = 0x08,
			RHI_BUFFER_USAGE_FLAG_UNORDERED_ACCESS = 0x10,
		};


		[[nodiscard]]
		inline constexpr const std::string& RHI_BufferUsageFlagToString(const RHI_BufferUsageFlag _flag) noexcept
		{
			switch (_flag)
			{
				case RHI_BufferUsageFlag::RHI_BUFFER_USAGE_FLAG_INVALID:
					return "RHI_BUFFER_USAGE_FLAG_INVALID";
				case RHI_BufferUsageFlag::RHI_BUFFER_USAGE_FLAG_VERTEX_BUFFER:
					return "RHI_BUFFER_USAGE_FLAG_VERTEX_BUFFER";
				case RHI_BufferUsageFlag::RHI_BUFFER_USAGE_FLAG_INDEX_BUFFER:
					return "RHI_BUFFER_USAGE_FLAG_INDEX_BUFFER";
				case RHI_BufferUsageFlag::RHI_BUFFER_USAGE_FLAG_UNIFORM_BUFFER:
					return "RHI_BUFFER_USAGE_FLAG_UNIFORM_BUFFER";
				case RHI_BufferUsageFlag::RHI_BUFFER_USAGE_FLAG_STAGING_BUFFER:
					return "RHI_BUFFER_USAGE_FLAG_STAGING_BUFFER";
				case RHI_BufferUsageFlag::RHI_BUFFER_USAGE_FLAG_UNORDERED_ACCESS:
					return "RHI_BUFFER_USAGE_FLAG_UNORDERED_ACCESS";
				default:
					// Error checking and logging
					Logger::Log("No string found for 'RHI_BufferUsageFlag': " + (uint8)_flag, LogType::LOG_TYPE_ERROR);
					return "RHI_BUFFER_USAGE_FLAG_INVALID";
			}
		}


		[[nodiscard]]
		inline constexpr const std::string& RHI_BufferUsageFlagsToString(const uint32 _flags) noexcept
		{
			// Early out
			if (_flags == 0)
				return "RHI_BUFFER_USAGE_FLAG_INVALID";

			std::string result;
			auto append_flag = [&](RHI_BufferUsageFlag flag)
				{
					if (_flags & static_cast<uint32>(flag))
					{
						if (!result.empty())
						{
							result += " | ";
						}
						result += RHI_BufferUsageFlagToString(flag);
					}
				};

			// Check for all the flags
			append_flag(RHI_BufferUsageFlag::RHI_BUFFER_USAGE_FLAG_VERTEX_BUFFER);
			append_flag(RHI_BufferUsageFlag::RHI_BUFFER_USAGE_FLAG_INDEX_BUFFER);
			append_flag(RHI_BufferUsageFlag::RHI_BUFFER_USAGE_FLAG_UNIFORM_BUFFER);
			append_flag(RHI_BufferUsageFlag::RHI_BUFFER_USAGE_FLAG_STAGING_BUFFER);
			append_flag(RHI_BufferUsageFlag::RHI_BUFFER_USAGE_FLAG_UNORDERED_ACCESS);

			// Error checking
			if (result.empty())
			{
				Logger::Log("No valid flags found in 'RHI_BufferUsageFlags': " + std::to_string(_flags), LogType::LOG_TYPE_ERROR);
				return "RHI_BUFFER_USAGE_FLAG_INVALID";
			}

			return result;
		}
	}
}