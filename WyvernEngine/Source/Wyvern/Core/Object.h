#pragma once

#include "UUID.h"

#include <string>

namespace Wyvern
{
	class Object
	{
	public:
		UUID uuid = UUID();

	public:
		virtual void _DrawProperties() {}

		template <typename T>
		bool _IsObjectType()
		{
			return std::string(typeid(T).name()) == std::string(typeid(*this).name());
		}

	public:
		template <typename T>
		static T* Cast(Object* object)
		{
			if (object && object->_IsObjectType<T>())
				return static_cast<T*>(object);
			else
				return nullptr;
		}
	};
}