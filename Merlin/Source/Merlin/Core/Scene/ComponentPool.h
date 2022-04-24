#pragma once

#include "Scene.h"

namespace Merlin
{
	struct ComponentPool
	{
		ComponentPool(size_t componentSize, const char* componentType, const char* componentBaseType, int componentID)
		{
			ComponentSize = componentSize;
			ComponentType = componentType;
			ComponentBaseType = componentBaseType;
			ComponentID = componentID;
			Data = new char[ComponentSize * MaxEntities];
		}

		~ComponentPool()
		{
			delete[] Data;
			delete ComponentType;
		}

		inline void* Get(size_t index)
		{
			return Data + index * ComponentSize;
		}

		size_t ComponentSize = 0;
		const char* ComponentType = nullptr;
		const char* ComponentBaseType = nullptr;
		int ComponentID = 0;
		char* Data = nullptr;
	};
}