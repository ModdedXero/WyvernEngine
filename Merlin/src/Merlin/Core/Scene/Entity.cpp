#include "mlpch.h"
#include "Entity.h"

namespace Merlin
{
    void Entity::AddChildEntity(Entity* ent)
    {
        m_Children.push_back(ent);
        ent->m_Parent = this;
    }
    
    void Entity::RemoveChildEntity(Entity* ent)
    {
        for (int i = 0; i < m_Children.size(); i++)
        {
            if (m_Children[i] == ent)
                m_Children.erase(m_Children.begin() + i);
        }
    }
}