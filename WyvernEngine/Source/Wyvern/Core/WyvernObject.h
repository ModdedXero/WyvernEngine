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
	};
}