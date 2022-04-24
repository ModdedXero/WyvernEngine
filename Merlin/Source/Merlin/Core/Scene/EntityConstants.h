#pragma once

#include <bitset>

namespace Merlin
{
	const size_t MaxEntities = 50000;

	const size_t MaxComponents = 32;
	typedef std::bitset<MaxComponents> ComponentMask;

	typedef unsigned int EntityIndex;
	typedef unsigned int EntityVersion;
	typedef unsigned long long EntityID;
}