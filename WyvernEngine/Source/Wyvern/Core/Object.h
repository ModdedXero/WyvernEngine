#pragma once

#include "UUID.h"
#include "Serializable.h"

#include <Wyvern/Core/Scene/Scene.h>

#include <string>

namespace Wyvern
{
	class Object
	{
	public:
		Object();
		Object(UUID uuid);

		template <typename T>
		Object(T* obj);
		template <typename T>
		Object(UUID uuid, T* obj);

		virtual void _DrawProperties() {}
		virtual void _SerializeObject(SerializeInfo& serial) {}

		const UUID GetUUID() const { return m_UUID; }
		const std::string GetObjectType() const { return m_ObjectType; }

	public:
		template <typename T>
		static T* Cast(Object* object)
		{
			if (object && object->IsObjectType<T>())
				return static_cast<T*>(object);
			else
				return nullptr;
		}

	private:
		UUID m_UUID;
		std::string m_ObjectType;

	private:
		template <typename T>
		inline bool IsObjectType()
		{
			return std::string(typeid(T).name()) == std::string(typeid(*this).name());
		}

		operator bool() const
		{
			return Scene::IsEntityValid(Scene::GetActiveScene(), m_UUID);
		}

		bool operator ==(const Object& rhs) const
		{
			return m_UUID == rhs.m_UUID;
		}

		bool operator !=(const Object& rhs) const
		{
			return m_UUID != rhs.m_UUID;
		}
	};

	template <typename T, typename ...Args>
	class SerialObject : public Object, public Serializable<T, Args...>
	{
	public:
		SerialObject()
			: Object(&T())
		{}

		SerialObject(UUID uuid)
			: Object(uuid, &T())
		{}

		virtual void _SerializeObject(SerializeInfo& serial) override
		{
			_Serialize(serial);
		}
	};

	template<typename T>
	inline Object::Object(T* obj)
		: m_UUID(UUID()), m_ObjectType(typeid(T).name())
	{
	}

	template<typename T>
	inline Object::Object(UUID uuid, T* obj)
		: m_UUID(uuid), m_ObjectType(typeid(T).name())
	{
	}
}