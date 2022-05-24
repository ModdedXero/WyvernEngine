#pragma once

#include <filesystem>
#include <iostream>

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
		std::string Extension() const { return m_CurrentPath.extension().string(); }
		bool IsExtension(const char* extension) const { return m_CurrentPath.extension() == extension; }
		bool IsDirectory() const { return std::filesystem::is_directory(m_CurrentPath);; }
		bool HasDirectoryChildren() const;

		std::string ToString() const { return m_CurrentPath.string(); }

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
		
		bool operator ==(const FileSystem& rhs) const
		{
			return m_CurrentPath == rhs.m_CurrentPath;
		}

		FileSystem operator /(const FileSystem& rhs) const
		{
			std::string path = m_CurrentPath.string() + rhs.m_CurrentPath.string();
			return FileSystem(path);
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