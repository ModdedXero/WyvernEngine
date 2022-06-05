#pragma once

#include <string>

namespace Wyvern
{
	class WyvernObject
	{
	public:
		virtual std::string _ObjectType() const = 0;
		virtual void _DrawProperties() {}

		template <typename T>
		bool _IsObjectType()
		{
			return std::string(typeid(T).name()) == this->_ObjectType();
		}

	public:
		template <typename T>
		static T* Cast(WyvernObject* object)
		{
			if (object && object->_IsObjectType<T>())
				return static_cast<T*>(object);
			else
				return nullptr;
		}
	};
}