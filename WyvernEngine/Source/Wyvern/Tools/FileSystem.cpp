#include "wvpch.h"
#include "FileSystem.h"

namespace Wyvern::Tools
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

	std::string FileSystem::ReadFile() const
	{
		if (IsDirectory())
			return std::string();

		std::ifstream file(m_CurrentPath);
		std::stringstream fileString;

		fileString << file.rdbuf();
		file.close();

		return fileString.str();
	}

	void FileSystem::WriteFile(std::string data) const
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

	void FileSystem::CreateFile() const
	{
		WriteFile("");
	}

	void FileSystem::Rename(const std::string& name)
	{
		std::string path = m_CurrentPath.string();
		size_t index = path.find_last_of("\\");
		path = path.substr(0, path.size() - (path.size() - index));
		std::filesystem::rename(m_CurrentPath, FileSystem(FileSystem(path) / name));
	}

	bool FileSystem::HasDirectoryChildren() const
	{
		Tools::FileSystem temp = *this;
		for (Tools::FileSystem child : temp)
		{
			if (child.IsDirectory()) return true;
		}

		return false;
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

	void FileSystem::CreateFile(const FileSystem& path)
	{
		path.CreateFile();
	}

	void FileSystem::CopyFile(FileSystem original, FileSystem copy)
	{
		if (!std::filesystem::exists(copy))
			std::filesystem::copy_file(original, copy);
	}
}