#include "wvpch.h"
#include "UIWizard.h"

#include <Wyvern/Core/Components/Button.h>
#include <Wyvern/Renderer/CameraRenderer.h>
#include <Wyvern/Core/Input.h>
#include <Wyvern/Core/Scene/Entity.h>
#include <Wyvern/Core/Scene/EntityList.h>

#include "GLFW/glfw3.h"

using namespace Wyvern::Events;

namespace Wyvern::UI
{
	void UIWizard::OnEvent(Event& event)
	{
		EventDispatcher dispatcher(event);

		dispatcher.Distpatch<MouseMovedEvent>(BIND_EVENT_FN(UIWizard::OnMouseMoveEvent));
		dispatcher.Distpatch<MouseButtonPressedEvent>(BIND_EVENT_FN(UIWizard::OnMouseClickEvent));
	}

	bool UIWizard::OnMouseMoveEvent(MouseMovedEvent& e)
	{
		for (Entity* ent : EntityList<Button>())
		{
			Button* button = ent->GetComponent<Button>();
			Vector2 mousePos = Vector2(e.GetXPos(), e.GetYPos());
			Vector2 buttonScale = ent->GetTransform()->scale;
			Vector2 buttonPos = ent->GetTransform()->position;

			Vector2 buttonTopLeft = Renderer::CameraRenderer::WorldToScreenPoint(Vector3(buttonPos.x - buttonScale.x, buttonPos.y + buttonScale.y, 1.0f));
			Vector2 buttonTopRight = Renderer::CameraRenderer::WorldToScreenPoint(Vector3(buttonPos.x + buttonScale.x, buttonPos.y + buttonScale.y, 1.0f));
			Vector2 buttonBottomLeft = Renderer::CameraRenderer::WorldToScreenPoint(Vector3(buttonPos.x - buttonScale.x, buttonPos.y - buttonScale.y, 1.0f));

			if (mousePos.x > buttonTopLeft.x && mousePos.x < buttonTopRight.x
				&& mousePos.y < buttonBottomLeft.y && mousePos.y > buttonTopLeft.y)
			{
				if (!button->m_IsHovering)
				{
					button->m_IsHovering = true;
					if (button->OnHoverEnter != nullptr)
						(button->OnHoverEnter)();
				}
			}
			else
			{
				if (button->m_IsHovering)
				{
					button->m_IsHovering = false;
					if (button->OnHoverExit != nullptr)
						(button->OnHoverExit)();
				}
			}
		}

		return true;
	}

	bool UIWizard::OnMouseClickEvent(MouseButtonPressedEvent& e)
	{
		for (Entity* ent : EntityList<Button>())
		{
			Button* button = ent->GetComponent<Button>();

			if (e.GetKey() == MouseCode::MOUSE_BUTTON_LEFT)
			{
				if (e.GetState() == GLFW_PRESS && !button->m_IsClicked)
				{
					if (button->m_IsHovering)
					{
						button->m_IsClicked = true;
						if (button->OnClick != nullptr)
							(button->OnClick)();
					}
				}
				else if (e.GetState() == GLFW_RELEASE && button->m_IsClicked)
				{
					button->m_IsClicked = false;
				}
			}
		}

		return true;
	}
}