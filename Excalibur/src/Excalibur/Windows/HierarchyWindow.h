#pragma once

#include <Excalibur/Core/EditorWindow.h>

namespace Merlin::Editor
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