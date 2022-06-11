#pragma once

#include "Scene.h"
#include "Component.h"

#include <Wyvern/Core/Application/ApplicationDomain.h>

namespace Wyvern
{
	template <typename T, typename ...Args>
	class NativeScriptComponent : public NativeComponentBase, public Serializable<T, Args...>
	{
	public:
		virtual void _SerializeObject(SerializeInfo& serial) override
		{
			_Serialize(serial);
		}

	private:
		static inline ComponentBase* __RegisterComponent(Wyvern::Ref<Wyvern::Scene> scene, unsigned long long entity) { return Scene::AddComponent<T>(scene, entity); }
		static inline bool __IsRegistered = ApplicationDomain::RegisterComponent<T>(__RegisterComponent);
	};
}