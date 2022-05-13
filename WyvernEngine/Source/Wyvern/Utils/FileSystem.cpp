#include "wvpch.h"
#include "FileSystem.h"

namespace Wyvern::Utils
{
	FileSystem::FileSystem()
		: m_CurrentPath("")
	{
		m_IsDirectory = std::filesystem::is_directory(m_CurrentPath);
	}

	FileSystem::FileSystem(std::string path)
		: m_CurrentPath(path)
	{
		m_IsDirectory = std::filesystem::is_directory(m_CurrentPath);
	}


	FileSystem::FileSystem(const char* path)
		: m_CurrentPath(path)
	{
		m_IsDirectory = std::filesystem::is_directory(m_CurrentPath);
	}

	FileSystem::FileSystem(std::filesystem::path path)
		: m_CurrentPath(path)
	{
		m_IsDirectory = std::filesystem::is_directory(m_CurrentPath);
	}

	FileSystem::~FileSystem()
	{
	}

	FileSystem FileSystem::RelativePath(const FileSystem& path, const FileSystem& base)
	{
		FileSystem fs = std::filesystem::relative(path.m_CurrentPath, base.m_CurrentPath);
		fs.m_IsDirectory = path.IsDirectory();
		return fs;
	}

	void FileSystem::CreateDirectory(FileSystem path)
	{
		std::filesystem::create_directory(path);
	}
}