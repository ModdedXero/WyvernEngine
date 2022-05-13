#include "wvpch.h"
#include "FileSystem.h"

namespace Wyvern::Utils
{
	FileSystem::FileSystem()
		: m_CurrentPath("")
	{
	}

	FileSystem::FileSystem(std::string path)
		: m_CurrentPath(path)
	{
	}


	FileSystem::FileSystem(const char* path)
		: m_CurrentPath(path)
	{
	}

	FileSystem::FileSystem(std::filesystem::path path)
		: m_CurrentPath(path)
	{
	}

	FileSystem::~FileSystem()
	{
	}

	std::string FileSystem::ReadFile()
	{
		if (IsDirectory())
			return std::string();

		std::ifstream file(m_CurrentPath);
		std::stringstream fileString;

		fileString << file.rdbuf();
		file.close();

		return fileString.str();
	}

	void FileSystem::WriteFile(std::string data)
	{
		if (IsDirectory())
		{
			DEBUG_CORE("Cannot write to a directory");
			return;
		}

		std::ofstream out(m_CurrentPath);
		out << data;
		out.close();
	}

	FileSystem FileSystem::RelativePath(const FileSystem& path, const FileSystem& base)
	{
		FileSystem fs = std::filesystem::relative(path.m_CurrentPath, base.m_CurrentPath);
		return fs;
	}

	void FileSystem::CreateDirectory(FileSystem path)
	{
		std::filesystem::create_directory(path);
	}
}