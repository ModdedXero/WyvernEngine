#pragma once

#include <filesystem>

namespace Wyvern::Utils
{
	class FileSystem
	{
		using iterator = std::filesystem::directory_iterator;
	public:
		FileSystem();
		FileSystem(std::string path);
		FileSystem(const char* path);
		FileSystem(std::filesystem::path path);
		~FileSystem();

		std::string ReadFile();
		void WriteFile(std::string data);

		std::string Filename() const { return m_CurrentPath.filename().string(); }
		bool IsDirectory() const { return std::filesystem::is_directory(m_CurrentPath);; }

		static FileSystem RelativePath(const FileSystem& path, const FileSystem& base);
		static void CreateDirectory(FileSystem path);
		static void CopyFile(FileSystem original, FileSystem copy);

		iterator begin() { return iterator(m_CurrentPath); }
		iterator end() { return {}; }

		FileSystem operator /=(const FileSystem& rhs)
		{
			return m_CurrentPath /= rhs.m_CurrentPath.filename();
		}

		void operator =(const std::filesystem::directory_entry& rhs)
		{
			m_CurrentPath = rhs;
		}

		FileSystem operator /(const FileSystem& rhs)
		{
			return m_CurrentPath / rhs.m_CurrentPath.filename();
		}

		operator std::filesystem::path() const
		{
			return m_CurrentPath;
		}

		operator std::string() const
		{
			return m_CurrentPath.string();
		}

	private:
		std::filesystem::path m_CurrentPath;
	};

	inline std::ostream& operator <<(std::ostream& os, const FileSystem& rhs)
	{
		os << (std::string)rhs;
		return os;
	}
}