#pragma once

#include <map>
#include <memory>

namespace Wyvern
{
	class Scene;
	struct Component;

	class ApplicationDomain
	{
	public:
		using CreateComponentFn = Component*(*)(Ref<Scene> scene, unsigned long long entity);

	public:
		ApplicationDomain() = delete;

		static bool RegisterComponent(std::string name, CreateComponentFn func);
		static Component* CreateComponent(std::string name, Ref<Scene> scene, unsigned long long entity);

		static std::map<std::string, CreateComponentFn> GetComponents() { return s_Components; }

	private:
		static inline std::map<std::string, CreateComponentFn> s_Components;
	};
}