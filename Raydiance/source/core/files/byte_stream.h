#pragma once
#include "./core/files/file_path.h"
#include "./core/files/byte_stream_exception.h"

#include "./core/files/byte_order.h"
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

		uint32 Read_uint32();
		uint32 Read_uint32_BigEndian();
		uint32 Read_uint32_LittleEndian();

		int32 Read_int32();
		int32 Read_int32_BigEndian();
		int32 Read_int32_LittleEndian();

		uint64 Read_uint64();

		std::string Read_string(size_t _byteCount);

		bool Read_bool();
		uint8 Read_uint8();
		uint16 Read_uint16();
		char Read_char();

		std::vector<uint8> Read_bytes(size_t byteCount);

		// --- Write helpers ---
		void Write(const char* data, std::streamsize size);
		void Write_uint32(uint32 v);
		void Write_uint32(uint32 v, std::streampos offset);
		void Write_uint32_BigEndian(uint32 v);
		void Write_uint32_LittleEndian(uint32 v);

		void Write_uint64(uint64 v);
		void Write_uint64(uint64 v, std::streampos offset);

		void Write_bool(bool _b);
		void Write_char(char v);
		void Write_string(const std::string& _str);
		void Write_float(float _f);

		void Write_uint8(uint8 v);
		void Write_uint8(uint8 v, std::streampos offset);
		void Write_uint16(uint16 v);
		void Write_int16(int16_t v);
		void Write_int8(int8_t v);

		void Write_int32(int32 v);
		void Write_int32_BigEndian(int32 v);
		void Write_int32_LittleEndian(int32 v);

		void Write_file(const FilePath& _filePath);
		void Write_bytes(const void* _data, size_t _size);

	protected:
		std::fstream m_FileStream;
		uint32       m_Size = 0;

		ByteOrder        m_ByteOrder   = ByteOrder::BYTE_ORDER_INVALID;
		ByteStreamState  m_StreamState = ByteStreamState::BYTE_STREAM_STATE_INVALID;
	};
}