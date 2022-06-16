#include "wvpch.h"
#include "Object.h"

namespace Wyvern
{
	Object::Object()
		: m_UUID(UUID()), m_ObjectType(typeid(*this).name())
	{
	}

	Object::Object(UUID uuid)
		: m_UUID(uuid), m_ObjectType(typeid(*this).name())
	{
	}
}