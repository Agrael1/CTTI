#pragma once
#include "TypeName.h"

namespace ver
{
	class Unknown
	{
	public:
		template<class C>
		constexpr bool isDerivedFrom()
		{
			return isDerivedFrom(TypeName <C>::value);
		}
	public:
		virtual ~Unknown() = default;
		constexpr virtual std::string_view getTypeId()const = 0;
		constexpr virtual bool isDerivedFrom(std::string_view type)const { return xtype == type; }
	private:
		static inline constexpr std::string_view xtype = TypeName<Unknown>::value;
	};
}