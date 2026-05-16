#include "./pch.h"
#include "./core/files/byte_stream.h"

namespace Raydiance
{
	ByteStream::ByteStream(void)
	{
		ByteStreamException e = ByteStreamException::NoFilePath;
		throw e;
	}

	ByteStream::ByteStream(const FilePath& _filePath, ByteStreamState _streamState)
	{
		// Initial declaration
		m_StreamState = _streamState;
		m_ByteOrder = ByteOrder::BYTE_ORDER_LITTLE_ENDIAN;

		// Open stream
		m_FileStream.open(_filePath.GetPath(), std::ios::binary | ResolveStreamState(_streamState));

		// Check stream
		if (m_FileStream.is_open() == false || m_FileStream.good() == false)
		{
			ByteStreamException e = ByteStreamException::FileOpenError;
			throw e;
		}

		// Additional operand
		GetSize();
		m_FileStream.seekg(0, std::ios::beg);
	}

	ByteStream::~ByteStream()
	{
		if (m_FileStream.is_open() == true)
			m_FileStream.close();
	}

	uint64 ByteStream::GetSize()
	{
		if (m_StreamState == ByteStreamState::BYTE_STREAM_STATE_WRITE)
		{
			std::streampos begin = m_FileStream.tellg();
			return begin;
		}

		std::streampos begin = m_FileStream.tellg();  // Save the current position

		// Move the file pointer to the end
		m_FileStream.seekg(0, std::ios::end);
		std::streamsize size = m_FileStream.tellg() - begin;  // Calculate the size of the file
		m_Size = static_cast<uint32>(size);  // Cast to uint32 if needed (make sure it fits)

		return m_Size;
	}

	uint64 ByteStream::GetPosition()
	{
		return  m_FileStream.tellg();
	}

	std::istream& ByteStream::Read(char* _s, std::streamsize _n)
	{
		return m_FileStream.read(_s, _n);
	}

	std::istream& ByteStream::Seek(std::streampos _pos)
	{
		return this->m_FileStream.seekg(_pos);
	}

	void ByteStream::Skip(std::streamsize size)
	{
		std::streampos currentPos = m_FileStream.tellp();
		m_FileStream.seekp(currentPos + size);
	}

	// ------------------------------------------------------------
	// Reading
	// ------------------------------------------------------------

	uint32 ByteStream::Read_uint32()
	{
		uint32 v;
		m_FileStream.read(reinterpret_cast<char*>(&v), sizeof(v));
		return v;
	}

	uint32 ByteStream::Read_uint32_BigEndian()
	{
		uint32 v = Read_uint32();
		return ((v & 0x000000FF) << 24) |
			((v & 0x0000FF00) << 8) |
			((v & 0x00FF0000) >> 8) |
			((v & 0xFF000000) >> 24);
	}

	uint32 ByteStream::Read_uint32_LittleEndian()
	{
		return Read_uint32();
	}

	int32 ByteStream::Read_int32()
	{
		int32 v;
		m_FileStream.read(reinterpret_cast<char*>(&v), sizeof(v));
		return v;
	}

	int32 ByteStream::Read_int32_BigEndian()
	{
		uint32 v = Read_uint32_BigEndian();
		return static_cast<int32>(v);
	}

	int32 ByteStream::Read_int32_LittleEndian()
	{
		return Read_int32();
	}

	uint64 ByteStream::Read_uint64()
	{
		uint64 v;
		m_FileStream.read(reinterpret_cast<char*>(&v), sizeof(v));
		return v;
	}

	std::string ByteStream::Read_string(size_t _byteCount)
	{
		std::string result;
		result.resize(_byteCount);

		m_FileStream.read(result.data(), static_cast<std::streamsize>(_byteCount));

		// In case fewer bytes were read (EOF or error)
		const std::streamsize bytesRead = m_FileStream.gcount();
		result.resize(static_cast<size_t>(bytesRead));

		return result;
	}

	bool ByteStream::Read_bool()
	{
		bool b;
		m_FileStream.read(reinterpret_cast<char*>(&b), sizeof(b));
		return b;
	}

	uint8 ByteStream::Read_uint8()
	{
		uint8 i;
		m_FileStream.read(reinterpret_cast<char*>(&i), sizeof(i));
		return i;
	}

	uint16 ByteStream::Read_uint16()
	{
		uint16 i;
		m_FileStream.read(reinterpret_cast<char*>(&i), sizeof(i));
		return i;
	}

	char ByteStream::Read_char()
	{
		char c;
		m_FileStream.read(reinterpret_cast<char*>(&c), sizeof(c));
		return c;
	}

	std::vector<uint8> ByteStream::Read_bytes(size_t byteCount)
	{
		std::vector<uint8> buffer(byteCount);

		m_FileStream.read(reinterpret_cast<char*>(buffer.data()),
			static_cast<std::streamsize>(byteCount));

		// Resize to match actual bytes read (EOF-safe)
		buffer.resize(static_cast<size_t>(m_FileStream.gcount()));

		return buffer;
	}

	// ------------------------------------------------------------
	// Writing
	// ------------------------------------------------------------
	void ByteStream::Write(const char* data, std::streamsize size)
	{
		m_FileStream.write(data, size);
	}

	void ByteStream::Write_bool(bool v)
	{
		// Write the bool as a single byte (0 or 1)
		uint8_t b = v ? 1 : 0;
		m_FileStream.write(reinterpret_cast<const char*>(&b), sizeof(b));
	}

	void ByteStream::Write_char(char v)
	{
		m_FileStream.write(reinterpret_cast<const char*>(&v), sizeof(v));
	}

	void ByteStream::Write_string(const std::string& _str)
	{
		// Write length first (uint32_t is typical)
		uint32_t length = static_cast<uint32_t>(_str.size());

		// Write raw string bytes (no null terminator)
		m_FileStream.write(_str.data(), length);
	}

	void ByteStream::Write_float(float _f)
	{
		m_FileStream.write(reinterpret_cast<const char*>(&_f), sizeof(_f));
	}

	void ByteStream::Write_uint8(uint8 v)
	{
		m_FileStream.write(reinterpret_cast<const char*>(&v), sizeof(v));
	}

	void ByteStream::Write_uint8(uint8 v, std::streampos offset)
	{
		std::streampos currentPos = m_FileStream.tellp();

		m_FileStream.seekp(offset);
		m_FileStream.write(reinterpret_cast<const char*>(&v), sizeof(v));
		m_FileStream.seekp(currentPos);
	}

	void ByteStream::Write_uint16(uint16 v)
	{
		m_FileStream.write(reinterpret_cast<const char*>(&v), sizeof(v));
	}

	void ByteStream::Write_int16(int16_t v)
	{
		m_FileStream.write(reinterpret_cast<const char*>(&v), sizeof(v));
	}

	void ByteStream::Write_int8(int8_t v)
	{
		m_FileStream.write(reinterpret_cast<const char*>(&v), sizeof(v));
	}

	void ByteStream::Write_uint32(uint32 v)
	{
		m_FileStream.write(reinterpret_cast<const char*>(&v), sizeof(v));
	}

	void ByteStream::Write_uint32(uint32 v, std::streampos offset)
	{
		std::streampos currentPos = m_FileStream.tellp();

		m_FileStream.seekp(offset);
		m_FileStream.write(reinterpret_cast<const char*>(&v), sizeof(v));
		m_FileStream.seekp(currentPos);
	}

	void ByteStream::Write_uint64(uint64 v)
	{
		m_FileStream.write(reinterpret_cast<const char*>(&v), sizeof(v));
	}

	void ByteStream::Write_uint64(uint64 v, std::streampos offset)
	{
		std::streampos currentPos = m_FileStream.tellp();

		m_FileStream.seekp(offset);
		m_FileStream.write(reinterpret_cast<const char*>(&v), sizeof(v));
		m_FileStream.seekp(currentPos);
	}

	void ByteStream::Write_uint32_BigEndian(uint32 v)
	{
		uint32 be =
			((v & 0x000000FF) << 24) |
			((v & 0x0000FF00) << 8) |
			((v & 0x00FF0000) >> 8) |
			((v & 0xFF000000) >> 24);

		Write_uint32(be);
	}

	void ByteStream::Write_uint32_LittleEndian(uint32 v)
	{
		Write_uint32(v);
	}

	void ByteStream::Write_int32(int32 v)
	{
		m_FileStream.write(reinterpret_cast<const char*>(&v), sizeof(v));
	}

	void ByteStream::Write_int32_BigEndian(int32 v)
	{
		Write_uint32_BigEndian(static_cast<uint32>(v));
	}

	void ByteStream::Write_int32_LittleEndian(int32 v)
	{
		Write_int32(v);
	}

	void ByteStream::Write_file(const FilePath& _filePath)
	{
		std::ifstream src(_filePath.GetPath());
		m_FileStream << src.rdbuf();
	}

	void ByteStream::Write_bytes(const void* _data, size_t _size)
	{
		m_FileStream.write(reinterpret_cast<const char*>(_data), _size);
	}
}