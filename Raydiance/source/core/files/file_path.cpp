#include "./pch.h"
#include "./core/files/file_path.h"

namespace Raydiance
{
	FilePath::FilePath(const char* _filePath)
		: m_FilePath(_filePath)
	{ }


	FilePath::FilePath(const std::string& _filePath)
		: m_FilePath(_filePath)
	{ }
}