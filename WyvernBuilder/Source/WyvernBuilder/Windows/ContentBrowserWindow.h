#pragma once

#include <Wyvern.h>
#include <WyvernEditor.h>

using namespace Wyvern::Editor;

namespace Wyvern
{
	class ContentBrowserWindow : public EditorWindow
	{
	public:
		const char* GetWindowTitle() const { return "Content Browser"; }

		virtual void OnAttach() override;
		virtual void OnGUI() override;

	private:
		Tools::FileSystem m_CurrentDirectory;
		Tools::FileSystem m_SelectedContext;

		Ref<Texture2D> m_DirectoryIcon;
		Ref<Texture2D> m_FileIcon;

	private:
		void SelectContext(Tools::FileSystem& file);
	};
}