#pragma once

namespace Merlin
{
	template <const char* N, typename T>
	struct TypePair
	{
		using type = T;

		static TypePair GetPair(std::integral_constant<const char*, N>)
		{
			return {};
		}
	};

	template <typename ...T>
	struct TypeMap : public T...
	{
		using T::GetPair...;

		template <const char* N>
		using FindType = typename decltype(
				GetPair(std::integral_constant<const char*, N>{}))::type;
	};

	class ApplicationDomain
	{
	public:
		static void RegisterType();
	private:

	};
}