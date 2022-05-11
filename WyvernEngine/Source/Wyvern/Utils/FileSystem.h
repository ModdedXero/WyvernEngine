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

		std::string Filename() const { return m_CurrentPath.filename().string(); }
		bool IsDirectory() const { return m_IsDirectory; }

		static FileSystem RelativePath(const FileSystem& path, const FileSystem& base);

		iterator begin() { return iterator(m_CurrentPath); }
		iterator end() { return {}; }

		void operator /=(const FileSystem& rhs)
		{
			m_CurrentPath /= rhs.m_CurrentPath.filename();
		}

		void operator =(const std::filesystem::directory_entry& rhs)
		{
			m_CurrentPath = rhs;
		}

		operator std::string () const
		{
			return m_CurrentPath.string();
		}

	private:
		std::filesystem::path m_CurrentPath;
		bool m_IsDirectory;
	};

	inline std::ostream& operator <<(std::ostream& os, const FileSystem& rhs)
	{
		os << (std::string)rhs;
		return os;
	}
}