#pragma once
#include <concepts>
#include <string_view>
#include <unordered_map>
#include <memory>
#include "Unknown.h"

namespace ver
{
	template<typename T>
	struct TypeName {
		constexpr static const char* fullname_internal() {
#if defined(__clang__) || defined(__GNUC__)
			return __PRETTY_FUNCTION__;
#elif defined(_MSC_VER)
			return __FUNCSIG__;
#else
#error "Unsupported compiler"
#endif
		}
	public:
		constexpr static std::string_view name() {
			constexpr auto xvoid = std::string_view(TypeName<void>::fullname_internal());
			constexpr auto postfix = xvoid.length() - xvoid.rfind(">::");

			auto line = std::string_view(fullname_internal());
			line.remove_suffix(postfix);
			line = line.substr(line.find("TypeName<") + 9);
			if (line.ends_with(' ')) //trailing space MSVC
				line.remove_suffix(1);
			return line;
		}

		using type = T;
		constexpr static std::string_view value = name();
	};

	template<class __Implemented, class ... __Parents>
	class implements : public __Parents...
	{
	public:
		template<class...Args> requires (sizeof...(__Parents) > 0)
		implements(Args&&...args)
			:__Parents(std::forward<Args>(args))...
		{}
		implements()
			: __Parents()...
		{}
	public:
		static constexpr auto calculate_type() { return TypeName<__Implemented>::name(); }
		static constexpr auto type() { return xtype; }
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