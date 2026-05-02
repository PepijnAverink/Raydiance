#pragma once
// Core includes
#include "./core/container/types.h"


// Generic includes
#include <exception>


namespace Raydiance
{
	// Exception type for errors related to byte stream operations.
	class ByteStreamException : public std::exception
	{
	public:
		// Error codes describiing the type of failure.
		enum
		{
			None		  = 0x00, // No error was detected
			NoFilePath	  = 0x01, // File path was not provided
			FileOpenError = 0x02, // Failed to open the file
		};


		// Creates an exception with no specific error code.
		ByteStreamException(void);
		ByteStreamException(uint32_t _code);

		[[nodiscard]] 
		virtual const char* what(void) const throw();

		[[nodiscard]] 
		inline uint32_t code() const noexcept
		{
			return m_ExceptionCode;
		}

	protected:
		uint32_t m_ExceptionCode = None;
	};
}