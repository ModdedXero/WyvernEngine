#pragma once

#include "Scene.h"
#include "Entity.h"

namespace Wyvern
{
	template <typename... ComponentTypes>
	struct EntityList
	{
		EntityList(bool baseClass = false)
		{
			if (sizeof...(ComponentTypes) == 0)
			{
				All = true;
			}
			else
			{
				int componentIDs[] = { 0, Scene::GetActiveScene()->FindComponentID<ComponentTypes>(baseClass)... };
				for (int i = 1; i < (sizeof...(ComponentTypes) + 1); i++)
				{
					if (componentIDs[i] == -1)
					{
						Invalid = true;
						break;
					}
					Components.set(componentIDs[i]);
				}
			}

			EntitySize = (EntityIndex)Scene::GetActiveScene()->m_Entities.size();
		}

		struct Iterator
		{
			Iterator(EntityIndex index, size_t size, ComponentMask components, bool all)
				: index(index), entSize(size), components(components), all(all)
			{}

			Entity* operator*() const
			{
				return Scene::GetActiveScene()->m_Entities[index];
			}

			bool operator==(const Iterator& other) const
			{
				return index == other.index || index == entSize;
			}

			bool operator!=(const Iterator& other) const
			{
				return index != other.index && index != entSize;
			}

			Iterator& operator++()
			{
				do
				{
					index++;
				} while (index < entSize && !isValidIndex());
				return *this;
			}

			bool isValidIndex()
			{
				return Scene::IsEntityValid(Scene::GetActiveScene()->m_Entities[index]) &&
					(all || components == (components & Scene::GetActiveScene()->m_Entities[index]->GetMask()));
			}

			size_t entSize;
			EntityIndex index;
			ComponentMask components;
			bool all;
		};

		const Iterator begin() const
		{
			EntityIndex firstIndex = Invalid ? EntitySize : 0;
			while (firstIndex < EntitySize &&
				(Components != (Components & Scene::GetActiveScene()->m_Entities[firstIndex]->GetMask())
					|| !Scene::IsEntityValid(Scene::GetActiveScene()->m_Entities[firstIndex])))
			{
				firstIndex++;
			}

			return Iterator(firstIndex, EntitySize, Components, All);
		}

		const Iterator end() const
		{
			return Iterator(EntityIndex(EntitySize), EntitySize, Components, All);
		}

		EntityIndex EntitySize = 0;
		EntityIndex Index = 0;
		ComponentMask Components = 0;
		bool All = false;
		bool Invalid = false;
	};
}