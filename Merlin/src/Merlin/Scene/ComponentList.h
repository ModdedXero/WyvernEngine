#pragma once

#include <Merlin/Scene/Scene.h>
#include <Merlin/Scene/Entity.h>

namespace Merlin
{
	template <typename... ComponentTypes>
	struct ComponentList
	{
		ComponentList()
		{
			if (sizeof...(ComponentTypes) == 0)
			{
				All = true;
			}
			else
			{
				int componentIDs[] = { 0, Scene::GetComponentID<ComponentTypes>()... };
				for (int i = 1; i < (sizeof...(ComponentTypes) + 1); i++)
					Components.set(componentIDs[i]);
			}
		}

		struct Iterator
		{
			Iterator(EntityIndex index, ComponentMask components, bool all)
				: index(index), components(components), all(all)
			{}

			Entity* operator*() const
			{
				return Scene::GetEntities()[index];
			}

			bool operator==(const Iterator& other) const
			{
				return index == other.index || index == Scene::GetEntities().size();
			}

			bool operator!=(const Iterator& other) const
			{
				return index != other.index && index != Scene::GetEntities().size();
			}

			Iterator& operator++()
			{
				do
				{
					index++;
				} while (index < Scene::GetEntities().size() && !isValidIndex());
				return *this;
			}

			bool isValidIndex()
			{
				return Scene::IsEntityValid(Scene::GetEntities()[index]->GetID()) &&
					(all || components == (components & Scene::GetEntities()[index]->GetMask()));
			}

			EntityIndex index;
			ComponentMask components;
			bool all;
		};

		const Iterator begin() const
		{
			int firstIndex = 0;
			while (firstIndex < Scene::GetEntities().size() &&
				(Components != (Components & Scene::GetEntities()[firstIndex]->GetMask())
					|| !Scene::IsEntityValid(Scene::GetEntities()[firstIndex]->GetID())))
			{
				firstIndex++;
			}

			return Iterator(firstIndex, Components, All);
		}

		const Iterator end() const
		{
			return Iterator(EntityIndex(Scene::GetEntities().size()), Components, All);
		}

		EntityIndex Index = 0;
		ComponentMask Components = 0;
		bool All = false;
	};
}