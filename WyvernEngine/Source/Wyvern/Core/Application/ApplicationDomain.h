#pragma once

#include <map>
#include <memory>

namespace Wyvern
{
	class Scene;
	struct ComponentBase;

	class ApplicationDomain
	{
	public:
		using CreateComponentFn = ComponentBase*(*)(Ref<Scene> scene, unsigned long long entity);

	public:
		ApplicationDomain() = delete;

		template <typename T>
		static bool RegisterComponent(CreateComponentFn func);
		static inline ComponentBase* CreateComponent(std::string name, Ref<Scene> scene, unsigned long long entity)
		{
			if (auto it = s_Components.find(name); it != s_Components.end())
			{
				return it->second(scene, entity);
			}

			return nullptr;
		}

		static std::map<std::string, CreateComponentFn> GetComponents() { return s_Components; }

	private:
		static inline std::map<std::string, CreateComponentFn> s_Components;
	};

	template<typename T>
	inline bool ApplicationDomain::RegisterComponent(CreateComponentFn func)
	{
		std::string name(typeid(T).name());
		if (auto it = s_Components.find(name); it == s_Components.end())
		{
			s_Components[name] = func;
			return true;
		}

		return false;
	}
}