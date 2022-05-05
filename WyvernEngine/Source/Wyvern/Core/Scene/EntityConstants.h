#pragma once

#include <bitset>

namespace Wyvern
{
	const size_t MaxEntities = 50000;

	const size_t MaxComponents = 32;
	typedef std::bitset<MaxComponents> ComponentMask;

	typedef unsigned int SceneIndex;
	typedef unsigned int SceneVersion;
	typedef unsigned long long SceneID;
}