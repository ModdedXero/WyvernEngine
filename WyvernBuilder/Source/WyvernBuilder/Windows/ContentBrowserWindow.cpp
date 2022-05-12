#include "ContentBrowserWindow.h"

using namespace Wyvern::Utils;

namespace Wyvern
{
	void ContentBrowserWindow::OnAttach()
	{
		m_CurrentDirectory = std::string(Application::Get().GetProjectPath()) + "/" + Application::Get().GetSpecification().ProjectName + "/Assets";

		m_DirectoryIcon = Texture2D::Create("../Assets/Icons/ContentBrowser/Directory.png");
		m_FileIcon = Texture2D::Create("../Assets/Icons/ContentBrowser/File.png");
	}

	void ContentBrowserWindow::OnGUI()
	{
		static float padding = 16.0f;
		static float thumbnailSize = 90.0f;
		float cellSize = thumbnailSize + padding;

		float panelWidth = ImGui::GetContentRegionAvail().x;
		int columnCount = (int)(panelWidth / cellSize);
		if (columnCount < 1)
			columnCount = 1;

		ImGui::Columns(columnCount, 0, false);

		for (FileSystem dir : m_CurrentDirectory)
		{
			FileSystem relative = FileSystem::RelativePath(dir, m_CurrentDirectory);
			std::string filename = relative.Filename();
			
			Ref<Texture2D> icon = dir.IsDirectory() ? m_DirectoryIcon : m_FileIcon;

			ImGui::PushID(filename.c_str());
			ImGui::PushStyleColor(ImGuiCol_Button, ImVec4{ 0,0,0,0 });
			ImGui::ImageButton((ImTextureID)icon->GetID(), { thumbnailSize, thumbnailSize }, { 0, 1 }, { 1,0 });
			ImGui::PopStyleColor();


			if (ImGui::BeginDragDropSource())
			{
				const FileSystem* sourcePath = new FileSystem(dir);
				ImGui::SetDragDropPayload("CONTENT_BROWSER_ITEM", sourcePath, sizeof(FileSystem), ImGuiCond_Once);
				ImGui::EndDragDropSource();
			}

			if (ImGui::IsItemHovered() && ImGui::IsMouseDoubleClicked(ImGuiMouseButton_Left))
			{
				if (dir.IsDirectory())
				{
					m_CurrentDirectory /= relative;
				}
			}
			ImGui::TextWrapped(filename.c_str());
			ImGui::PopID();

			ImGui::NextColumn();
		}

		//for (auto& dir : std::filesystem::directory_iterator(m_CurrentDirectory))
		//{
		//	auto relPath = std::filesystem::relative(dir.path(), s_AssetsPath);
		//	std::string fileString = relPath.filename().string();

		//	Ref<Texture2D> icon = dir.is_directory() ? m_DirectoryIcon : m_FileIcon;

		//	ImGui::PushID(fileString.c_str());
		//	ImGui::PushStyleColor(ImGuiCol_Button, ImVec4{ 0,0,0,0 });
		//	ImGui::ImageButton((ImTextureID)icon->GetID(), { thumbnailSize, thumbnailSize }, { 0, 1 }, { 1,0 });
		//	ImGui::PopStyleColor();

		//	if (ImGui::BeginDragDropSource())
		//	{
		//		const std::filesystem::path* itemPath = new std::filesystem::path(dir.path());
		//		ImGui::SetDragDropPayload("CONTENT_BROWSER_ITEM", itemPath, sizeof(std::filesystem::path), ImGuiCond_Once);
		//		ImGui::EndDragDropSource();
		//	}

		//	if (ImGui::IsItemHovered() && ImGui::IsMouseDoubleClicked(ImGuiMouseButton_Left))
		//	{
		//		if (dir.is_directory())
		//			m_CurrentDirectory /= relPath.filename();
		//	}
		//	ImGui::TextWrapped(fileString.c_str());
		//	ImGui::PopID();

		//	ImGui::NextColumn();
		//}

		ImGui::Columns(1);

		ImGui::SliderFloat("Thumbnail Size", &thumbnailSize, 16, 512);
		ImGui::SliderFloat("Padding", &padding, 0, 32);
	}
}