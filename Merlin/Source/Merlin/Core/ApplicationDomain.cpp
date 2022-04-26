#include "mlpch.h"
#include "ApplicationDomain.h"

namespace Merlin
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

    std::shared_ptr<Component> ApplicationDomain::CreateComponent(std::string name)
    {
        if (auto it = s_Components.find(name); it != s_Components.end())
        {
            return it->second();
        }

        return nullptr;
    }

}