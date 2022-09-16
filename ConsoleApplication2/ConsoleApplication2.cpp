#include "Header.h"
#include /**/ <iostream>
#include "Type1.h"
#include <cassert>

int main()
{
    static_assert(Type1::type() == "class Type1");
    assert(Type1::type() == "class Type1");

    Type1 a;
    assert(a.isDerivedFrom("class Type1"));

    Type3 a1(5);
    assert(a1.isDerivedFrom("class Type1"));

    assert(!a1.isDerivedFrom("class Unknown"));
    assert(a1.isDerivedFrom("class ver::Unknown"));

    //constexpr auto x = a.type();
    auto x = ver::codex::xcodex["class Type3"]();
    assert(x->isDerivedFrom("class ver::Unknown"));
    assert(x->isDerivedFrom("class Type3"));

    auto y = ver::codex::xcodex["class Type2<class Type3>"]();
    assert(y->isDerivedFrom("class ver::Unknown"));
    assert(!y->isDerivedFrom("class Type3"));
    assert(y->isDerivedFrom("class Type2<class Type3>"));
    
    assert(!y->isDerivedFrom<class A>());

    std::cout << "all done";
}
