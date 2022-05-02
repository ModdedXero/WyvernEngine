#pragma once

#include <map>
#include <memory>

namespace Wyvern
{
	struct Component;

	class ApplicationDomain
	{
	public:
		using CreateComponentFn = Component*(*)(unsigned long long ent);

	public:
		ApplicationDomain() = delete;

		static bool RegisterComponent(std::string name, CreateComponentFn func);
		static Component* CreateComponent(std::string name, unsigned long long ent);

		static std::map<std::string, CreateComponentFn> GetComponents() { return s_Components; }

	private:
		static inline std::map<std::string, CreateComponentFn> s_Components;
	};
}