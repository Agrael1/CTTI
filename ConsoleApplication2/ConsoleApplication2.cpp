#include "Header.h"
#include /**/ <iostream>
#include "Type1.h"

int main()
{
    //Type3 a(5, 2);
    //constexpr auto x = a.type();
    Type4<int, int> a;
    auto x = ver::codex::xcodex["class Type3"]();
    auto y = ver::codex::xcodex["class Type2<class Type3>"]();

    

    std::cout << x;
}
