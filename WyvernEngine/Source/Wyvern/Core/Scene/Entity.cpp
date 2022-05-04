#include "wvpch.h"
#include "Entity.h"

#include "Scene.h"

namespace Wyvern
{
    void Entity::DestroyEntity()
    {
        return Scene::DestoryEntity(this);
    }

    void Entity::AddChildEntity(Entity* entity)
    {
        m_Children.push_back(entity);
        entity->m_Parent = this;
    }
    
    void Entity::RemoveChildEntity(Entity* entity)
    {
        for (int i = 0; i < m_Children.size(); i++)
        {
            if (m_Children[i] == entity)
                m_Children.erase(m_Children.begin() + i);
        }
    }
}