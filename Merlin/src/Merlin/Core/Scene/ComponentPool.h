#pragma once

#include "Scene.h"

namespace Merlin
{
	struct ComponentPool
	{
		ComponentPool(size_t componentSize, const char* componentType, int componentID)
		{
			ComponentSize = componentSize;
			ComponentType = componentType;
			ComponentID = componentID;
			Data = new char[ComponentSize * MaxEntities];
		}

		~ComponentPool()
		{
			delete[] Data;
		}

		inline void* Get(size_t index)
		{
			return Data + index * ComponentSize;
		}

		size_t ComponentSize{ 0 };
		const char* ComponentType{ nullptr };
		int ComponentID{ 0 };
		char* Data{ nullptr };
	};
}