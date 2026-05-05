#pragma once
#include "./core/files/file_path.h"

#include "./core/files/byte_stream_state.h"

#include <fstream>
#include <vector>

namespace Raydiance
{
	class ByteStream
	{
	public:
		ByteStream(void);
		ByteStream(const FilePath& _filePath, ByteStreamState _state);

		virtual ~ByteStream();

		template <typename T>
		T ReadCustom()
		{
			T type;
			m_FileStream.read((char*)&type, sizeof(T));
			return type;
		}

		uint64 GetSize();
		uint64 GetPosition();

		std::istream& Read(char* _s, std::streamsize _n);
		std::istream& Seek(std::streampos _pos);
		void Skip(std::streamsize size);


	protected:
		std::fstream m_FileStream;
		uint32       m_Size = 0;

		ByteStreamState  m_StreamState = ByteStreamState::BYTE_STREAM_STATE_INVALID;
	};
}