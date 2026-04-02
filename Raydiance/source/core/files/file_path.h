#pragma once
#include <string>

// TODO:: Look into using string_view here

namespace Raydiance
{
	class FilePath
	{
	public:
		// Default constructor and destructor of the filepath object
		FilePath(void) = default;
		virtual ~FilePath(void) = default;

		// Constructors
		FilePath(const char* _filePath);
		FilePath(const std::string& _filePath);

		// Direct inline setter for the filepath
		inline const void SetPath(const std::string& _filePath)
		{
			m_FilePath = _filePath;
		}

		// Direct inline getter for the filepath
		inline const std::string GetPath(void) const
		{
			return m_FilePath;
		}

		inline const std::string GetDirectory(void) const
		{
			size_t pos = m_FilePath.find_last_of("/\\"); // handles both \ and /
			return (pos != std::string::npos) ? m_FilePath.substr(0, pos + 1) : "";
		}

		inline bool Is_Empty() const { return m_FilePath.empty(); }

	protected:
		std::string m_FilePath = "";
	};
}