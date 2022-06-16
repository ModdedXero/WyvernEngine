#pragma once

#include <Wyvern/Core/Scene/SerializeInfo.h>

#include <string>
#include <tuple>
#include <vector>

namespace Wyvern
{
	template <typename T, typename ...Args>
	class Serializable
	{
	public:
		Serializable()
		{
			size_t sizes[] = { 0, sizeof(Args)... };
			char* ptr = (char*)this + sizeof(Serializable);

			size_t index = 0;
			for (uint32_t i = 0; i < (sizeof...(Args)); i++)
			{
				m_Variables.push_back((void*)(ptr + sizes[i] + index));
				index += sizes[i];
			}
		}

		void _Serialize(SerializeInfo& serial)
		{
			serial.out << YAML::Key << typeid(T).name() << YAML::BeginMap;
			_SerializeData<0, Args...>(serial);
			serial.out << YAML::EndMap;
		}

		template <typename ...Vars>
		friend YAML::Emitter& operator <<(YAML::Emitter&, Serializable<Vars...>&);
		template <typename ...Vars>
		friend YAML::Node& operator >>(YAML::Node&, Serializable<Vars...>&);

	private:
		std::vector<void*> m_Variables;

	private:
		template <size_t I = 0, typename ...Tuple>
		inline typename std::enable_if < I < sizeof...(Args), void>::type
			_SerializeData(SerializeInfo& serial)
		{
			using CastType = std::tuple_element_t<I, std::tuple<Args...>>;

			if (I < m_Variables.size())
			{
				CastType* variable = (CastType*)m_Variables[I];
				if (serial.IsSerialize())
				{
					serial.out << YAML::Key << std::string(typeid(CastType).name() + std::to_string(I))
						<< YAML::Value << *variable;
				}
				else
				{
					if (serial.in[std::string(typeid(CastType).name() + std::to_string(I)).c_str()])
						serial.in[std::string(typeid(CastType).name() + std::to_string(I)).c_str()] >> *variable;
				}

				_SerializeData<I + 1, Args...>(serial);
			}
		}

		template <size_t I = 0, typename ...Tuple>
		inline typename std::enable_if<I == sizeof...(Args), void>::type
			_SerializeData(SerializeInfo& serial)
		{
		}
	};

	template <typename ...Args>
	inline YAML::Emitter& operator <<(YAML::Emitter& lhs, Serializable<Args...>& rhs)
	{
		SerializeInfo info(true);

		rhs._Serialize(info);

		lhs << info.out;
		return lhs;
	}

	template <typename ...Args>
	inline YAML::Node& operator >>(YAML::Node& lhs, Serializable<Args...>& rhs)
	{
		SerializeInfo info(false);
		info.in = lhs;
		rhs._Serialize(info);
		return lhs;
	}

	template <typename T>
	inline void operator >>(YAML::Node& lhs, T& rhs)
	{
		rhs = lhs.as<T>();
	}
}