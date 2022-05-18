#include "ContentBrowserWindow.h"

using namespace Wyvern::Utils;

namespace Wyvern
{
	namespace Utils
	{
		static void DrawDirectoryTree(Utils::FileSystem& currentDir, Utils::FileSystem directory)
		{
			for (Utils::FileSystem path : directory)
			{
				if (!path.IsDirectory()) continue;
				bool hasChildren = path.HasDirectoryChildren();

				std::string pathID = path;

				ImGuiTreeNodeFlags flags = ImGuiTreeNodeFlags_SpanAvailWidth;
				flags |= (hasChildren) ? ImGuiTreeNodeFlags_OpenOnArrow : ImGuiTreeNodeFlags_Leaf;
				bool open = ImGui::TreeNodeEx((void*)pathID.c_str(), flags, path.Filename().c_str());

				if (ImGui::IsItemClicked())
				{
					currentDir = path;
				}

				if (open)
				{
					if (hasChildren) DrawDirectoryTree(currentDir, path);
					ImGui::TreePop();
				}
			}
		}
	}

	void ContentBrowserWindow::OnAttach()
	{
		m_CurrentDirectory = Application::GetAssetsPath();
		m_DirectoryIcon = Texture2D::Create(Application::GetResourcesPath() / "/Icons/ContentBrowser/Directory.png");
		m_FileIcon = Texture2D::Create(Application::GetResourcesPath() / "/Icons/ContentBrowser/File.png");
	}

	void ContentBrowserWindow::OnGUI()
	{
		static float padding = 16.0f;
		static float thumbnailSize = 90.0f;
		float cellSize = thumbnailSize + padding;

		ImGui::Columns(2);

		static float initial_spacing = 150.0f; if (initial_spacing) ImGui::SetColumnWidth(0, initial_spacing), initial_spacing = 0;
		
		ImGuiTreeNodeFlags flags = ImGuiTreeNodeFlags_DefaultOpen | ImGuiTreeNodeFlags_OpenOnArrow;
		bool open = ImGui::TreeNodeEx((void*)Application::GetAssetsPath().Filename().c_str(), flags, Application::GetAssetsPath().Filename().c_str());

		if (ImGui::IsItemClicked())
		{
			m_CurrentDirectory = Application::GetAssetsPath();
		}

		if (open)
		{
			Utils::DrawDirectoryTree(m_CurrentDirectory, Application::GetAssetsPath());
			ImGui::TreePop();
		}

		ImGui::NextColumn();
		ImGui::BeginChild("Content");

		float panelWidth = ImGui::GetContentRegionAvail().x;
		int columnCount = (int)(panelWidth / cellSize);
		if (columnCount < 1)
			columnCount = 1;

		ImGui::Columns(columnCount, "1", false);

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

		ImGui::EndChild();

		//ImGui::Columns(1);

		//ImGui::SliderFloat("Thumbnail Size", &thumbnailSize, 16, 512);
		//ImGui::SliderFloat("Padding", &padding, 0, 32);
	}
}