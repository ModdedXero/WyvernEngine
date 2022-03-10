#pragma once

#include "Scene.h"
#include "Entity.h"

#include "mlpch.h"

namespace Merlin
{
	template <typename... ComponentTypes>
	struct EntityList
	{
		EntityList()
		{
			if (sizeof...(ComponentTypes) == 0)
			{
				All = true;
			}
			else
			{
				int componentIDs[] = { 0, Scene::FindComponentID<ComponentTypes>()... };
				ML_LOG_INFO(sizeof(componentIDs));
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

			EntitySize = Scene::s_Entities.size();
		}

		struct Iterator
		{
			Iterator(EntityIndex index, size_t size, ComponentMask components, bool all)
				: index(index), entitySize(size), components(components), all(all)
			{}

			Entity* operator*() const
			{
				return Scene::s_Entities[index];
			}

			bool operator==(const Iterator& other) const
			{
				return index == other.index || index == entitySize;
			}

			bool operator!=(const Iterator& other) const
			{
				return index != other.index && index != entitySize;
			}

			Iterator& operator++()
			{
				do
				{
					index++;
				} while (index < entitySize && !isValidIndex());
				return *this;
			}

			bool isValidIndex()
			{
				return Scene::IsEntityValid(Scene::s_Entities[index]->GetID()) &&
					(all || components == (components & Scene::s_Entities[index]->GetMask()));
			}

			size_t entitySize;
			EntityIndex index;
			ComponentMask components;
			bool all;
		};

		const Iterator begin() const
		{
			int firstIndex = Invalid ? EntitySize : 0;
			while (firstIndex < EntitySize &&
				(Components != (Components & Scene::s_Entities[firstIndex]->GetMask())
					|| !Scene::IsEntityValid(Scene::s_Entities[firstIndex]->GetID())))
			{
				firstIndex++;
			}

			return Iterator(firstIndex, EntitySize, Components, All);
		}

		const Iterator end() const
		{
			return Iterator(EntityIndex(EntitySize), EntitySize, Components, All);
		}

		size_t EntitySize = 0;
		EntityIndex Index = 0;
		ComponentMask Components = 0;
		bool All = false;
		bool Invalid = false;
	};
}