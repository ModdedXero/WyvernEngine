#include "ContentBrowserWindow.h"

#include <WyvernBuilder/Core/BuilderLayer.h>

using namespace Wyvern::Tools;

namespace Wyvern
{
	namespace Utils
	{
		static void DrawDirectoryTree(Tools::FileSystem& currentDir, Tools::FileSystem directory)
		{
			for (Tools::FileSystem path : directory)
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
		m_CurrentDirectory = Project::GetAssetsPath();
		m_DirectoryIcon = Texture2D::Create(Project::GetResourcesPath() / "/Icons/ContentBrowser/Directory.png");
		m_FileIcon = Texture2D::Create(Project::GetResourcesPath() / "/Icons/ContentBrowser/File.png");
	}

	void ContentBrowserWindow::OnGUI()
	{
		static float padding = 16.0f;
		static float thumbnailSize = 90.0f;
		float cellSize = thumbnailSize + padding;

		ImGui::Columns(2);

		static float initial_spacing = 150.0f; if (initial_spacing) ImGui::SetColumnWidth(0, initial_spacing), initial_spacing = 0;
		
		ImGuiTreeNodeFlags flags = ImGuiTreeNodeFlags_DefaultOpen | ImGuiTreeNodeFlags_OpenOnArrow;
		bool open = ImGui::TreeNodeEx((void*)Project::GetAssetsPath().Filename().c_str(), flags, Project::GetAssetsPath().Filename().c_str());

		if (ImGui::IsItemClicked())
		{
			m_CurrentDirectory = Project::GetAssetsPath();
		}

		if (open)
		{
			Utils::DrawDirectoryTree(m_CurrentDirectory, Project::GetAssetsPath());
			ImGui::TreePop();
		}

		ImGui::NextColumn();
		ImGui::BeginChild("Content");

		// Right Click Menu (Browser Panel)

		if (ImGui::BeginPopupContextWindow("Empty", ImGuiPopupFlags_NoOpenOverItems | ImGuiPopupFlags_MouseButtonRight))
		{
			if (ImGui::BeginMenu("Scene"))
			{
				if (ImGui::MenuItem("New Scene"))
					Tools::FileSystem(m_CurrentDirectory / "/new_scene.wyvern").CreateFile();

				ImGui::EndMenu();
			}

			if (ImGui::BeginMenu("Renderer"))
			{
				if (ImGui::MenuItem("New Material"))
					Material mat = Material(m_CurrentDirectory);

				ImGui::EndMenu();
			}

			ImGui::EndPopup();
		}

		float panelWidth = ImGui::GetContentRegionAvail().x;
		int columnCount = (int)(panelWidth / cellSize);
		if (columnCount < 1)
			columnCount = 1;

		ImGui::Columns(columnCount, "1", false);

		bool renameModal = false;

		for (FileSystem dir : m_CurrentDirectory)
		{
			FileSystem relative = FileSystem::RelativePath(dir, m_CurrentDirectory);
			std::string filename = relative.RootName();
			
			Ref<Texture2D> icon = dir.IsDirectory() ? m_DirectoryIcon : m_FileIcon;

			ImGui::PushID(filename.c_str());
			ImGui::PushStyleColor(ImGuiCol_Button, ImVec4{ 0,0,0,0 });
			ImGui::ImageButton((ImTextureID)icon->GetID(), { thumbnailSize, thumbnailSize }, { 0, 1 }, { 1,0 });
			ImGui::PopStyleColor();

			// Right Click Menu (Files and Folders)

			if (ImGui::IsItemHovered() && ImGui::IsItemClicked(ImGuiMouseButton_Right))
			{
				SelectContext(dir);
			}

			if (ImGui::BeginPopupContextWindow("Files", ImGuiPopupFlags_MouseButtonRight | ImGuiPopupFlags_NoOpenOverExistingPopup))
			{
				if (ImGui::MenuItem("Rename"))
					renameModal = true;

				ImGui::EndPopup();
			}

			// Drag and Drop FileSystem source

			const FileSystem* sourcePath = new FileSystem(dir);
			EditorGUIInternal::DragDropSource(DragDropTypes::FileSystem, sourcePath, sizeof(FileSystem));

			if (ImGui::IsItemHovered() && ImGui::IsItemClicked(ImGuiMouseButton_Left))
			{
				if (!dir.IsDirectory())
				{
					SelectContext(dir);
				}
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

		if (renameModal)
			ImGui::OpenPopup("RENAME");

		if (ImGui::BeginPopupModal("RENAME", NULL, ImGuiWindowFlags_AlwaysAutoResize))
		{
			std::string text("Rename file " + m_SelectedContext.Filename());
			ImGui::Text(text.c_str());
			ImGui::Separator();

			EditorGUI::TextControl("Rename: ", m_SelectedFileName);

			if (ImGui::Button("Rename", ImVec2(120, 0)))
			{
				m_SelectedContext.Rename(m_SelectedFileName);
				ImGui::CloseCurrentPopup();
			}

			if (ImGui::Button("Cancel", ImVec2(120, 0)))
				ImGui::CloseCurrentPopup();

			ImGui::EndPopup();
		}

		ImGui::EndChild();
	}

	void ContentBrowserWindow::SelectContext(Tools::FileSystem& file)
	{
		if (file.IsExtension(".material"))
		{
			Material* object = new Material(file);
			BuilderLayer::SetSelectedContext(object);
		}

		m_SelectedContext = file;
		m_SelectedFileName = file.Filename();
	}
}