#pragma once
#include <Merlin.h>

namespace Merlin
{
	class EditorCamera : public Entity
	{
	public:
		virtual void OnAttach() override;
		virtual void OnUpdate(Timestep ts) override;
		virtual void OnEvent(Events::Event& e) override;
	private:
		Camera* m_Camera;
	};
}