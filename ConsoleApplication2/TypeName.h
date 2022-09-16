#pragma once
#include <string_view>

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
}
