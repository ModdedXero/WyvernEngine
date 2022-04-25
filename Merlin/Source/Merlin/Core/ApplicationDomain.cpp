#include "mlpch.h"
#include "ApplicationDomain.h"

namespace Merlin
{
    std::unordered_map<const char*, Component* (*)()> s_ComponentTypes;

    void ApplicationDomain::DeregisterComponentType(const char* name)
    {
        s_ComponentTypes.erase(name);
    }
}