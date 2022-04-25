#pragma once

#include <Merlin/Core/Scene/Component.h>

namespace Merlin
{
	class ApplicationDomain
	{
	public:
		template <typename T>
		static void RegisterComponentType(const char* name);
		static void DeregisterComponentType(const char* name);

		static std::unordered_map<const char*, Component*(*)()> ComponentTypes;
	private:
		template <typename T>
		Component* CreateComponentInstance() { return new T(); }
	};

	template<typename T>
	inline void ApplicationDomain::RegisterComponentType(const char* name)
	{
		s_ComponentTypes[name] = &CreateComponentInstance<T>;
	}
}