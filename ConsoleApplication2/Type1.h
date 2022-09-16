#pragma once
#include "Implements.h"
#include "Unknown.h"


class Type1 : public ver::implements <Type1, Unknown>
{
	static inline ver::add_factory< Type1 > a;
};

template<class T>
class Type2 :public ver::implements <Type2<T>, Type1>
{
public:
	Type2() :x(9) {}
	Type2(int y) { x = y; }
	int x;
private:
	static inline ver::add_factory<Type2<T>> a;
};

template<class T, class C>
class Type4 : public ver::implements <Type4<T, C>, Type2<int>>
{
public:
	using base = ver::implements <Type4<T, C>, Type2<int>>;
	using base::implements;
	static inline ver::add_factory<Type4<T, C>> a;
};

class Type3 : public ver::implements<Type3, Type2<Type3>>
{
public:
	using base = ver::implements<Type3, Type2<Type3>>;
	using base::implements;
private:
	static inline ver::add_factory<Type3> a;
};


