#pragma once

#include <WyvernEditor/Core/EditorWindow.h>

namespace Wyvern::Editor
{
	class HierarchyWindow : public EditorWindow
	{
	public:
		const char* GetWindowTitle() const { return "Hierarchy"; }

		virtual void OnGUI() override;
	private:
		void DrawEntityNode(Entity* ent, bool isChild = false);
		void DrawEntityChildren(Entity* ent);
	};
}