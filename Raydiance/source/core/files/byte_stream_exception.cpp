#include "./pch.h"
#include "./core/files/byte_stream_exception.h"

namespace Raydiance
{
	ByteStreamException::ByteStreamException(void)
		: m_ExceptionCode(-1)
	{ }


	ByteStreamException::ByteStreamException(uint32_t _code)
		: m_ExceptionCode(_code)
	{ }


	const char* ByteStreamException::what(void) const throw()
	{
		switch (this->m_ExceptionCode)
		{
		case NoFilePath:
			return "No input FilePath.";
		case FileOpenError:
			return "Error while opening the file.";
		}
		return "Unknown exception.";
	}
}