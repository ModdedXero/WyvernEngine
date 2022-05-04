#include "wvpch.h"
#include "ApplicationDomain.h"

namespace Wyvern
{
    bool ApplicationDomain::RegisterComponent(std::string name, CreateComponentFn func)
    {
        if (auto it = s_Components.find(name); it == s_Components.end())
        {
            s_Components[name] = func;
            return true;
        }

        return false;
    }

    Component* ApplicationDomain::CreateComponent(std::string name, unsigned long long entity)
    {
        if (auto it = s_Components.find(name); it != s_Components.end())
        {
            return it->second(entity);
        }

        return nullptr;
    }

}