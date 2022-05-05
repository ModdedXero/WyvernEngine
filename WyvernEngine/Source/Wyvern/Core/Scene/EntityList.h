#pragma once

#include "Scene.h"
#include "Entity.h"

namespace Wyvern
{
	template <typename... ComponentTypes>
	struct EntityList
	{
		EntityList(Ref<Scene> scene, bool baseClass = false)
		{
			CurrentScene = scene;

			if (sizeof...(ComponentTypes) == 0)
			{
				All = true;
			}
			else
			{
				int componentIDs[] = { 0, CurrentScene->FindComponentID<ComponentTypes>(baseClass)... };
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

			EntitySize = (SceneIndex)CurrentScene->m_Entities.size();
		}

		struct Iterator
		{
			Iterator(Ref<Scene> scene, SceneIndex index, size_t size, ComponentMask components, bool all)
				: currentScene (scene), index(index), entSize(size), components(components), all(all)
			{}

			Entity* operator*() const
			{
				return currentScene->m_Entities[index];
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
				return Scene::IsEntityValid(currentScene->m_Entities[index]) &&
					(all || components == (components & currentScene->m_Entities[index]->m_Components));
			}

			Ref<Scene> currentScene;
			SceneIndex index;
			size_t entSize;
			ComponentMask components;
			bool all;
		};

		const Iterator begin() const
		{
			SceneIndex firstIndex = Invalid ? EntitySize : 0;
			while (firstIndex < EntitySize &&
				(Components != (Components & CurrentScene->m_Entities[firstIndex]->m_Components)
					|| !Scene::IsEntityValid(CurrentScene->m_Entities[firstIndex])))
			{
				firstIndex++;
			}

			return Iterator(CurrentScene, firstIndex, EntitySize, Components, All);
		}

		const Iterator end() const
		{
			return Iterator(CurrentScene, SceneIndex(EntitySize), EntitySize, Components, All);
		}

		Ref<Scene> CurrentScene;
		SceneIndex EntitySize = 0;
		SceneIndex Index = 0;
		ComponentMask Components = 0;
		bool All = false;
		bool Invalid = false;
	};
}