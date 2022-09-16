#pragma once
#include <concepts>
#include <string_view>
#include <unordered_map>
#include <memory>
#include "Unknown.h"

//seal from C++17
#ifdef __cpp_concepts
#define CXX20M(...) __VA_ARGS__
#else
#define CXX20M(a)
#endif // __cpp_concepts



namespace ver
{
	template<class __Implemented, class __Parent = Unknown> CXX20M(requires std::derived_from<__Parent,Unknown>)
	class implements : public __Parent
	{
	public:
		template<class...Args>
		constexpr implements(Args&&...args)
			:__Parent(std::forward<Args>(args)...)
		{}
	public:
		static constexpr auto type() { return xtype; }
		constexpr virtual std::string_view getTypeId()const override {return xtype;}
		constexpr virtual bool isDerivedFrom(std::string_view type)const { return xtype == type || __Parent::isDerivedFrom(type); }
	public:
		static std::unique_ptr<Unknown> make_self() { return std::make_unique<__Implemented>(); }
	private:
		static inline constexpr std::string_view xtype = TypeName<__Implemented>::value;
	};

	struct codex
	{
		using create_func = std::unique_ptr<Unknown>(*)();

		static void add_impl(std::string_view c, create_func func)
		{
			xcodex.try_emplace(c, func);
		}
		static inline std::unordered_map<std::string_view, create_func> xcodex{};
	};

	template<class T>
	struct add_factory
	{
		constexpr add_factory() { add(); }
		constexpr static void add() {
			codex::add_impl(T::type(), T::make_self);
		}
	};
}