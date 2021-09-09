#include "big_integer.hpp"
#include <assert.h>
#include <iostream>
using namespace std;
using namespace DIY;
int main()
{
    BigInteger integer(123456);
    integer.debug_view();
    integer.multi(-1);
    integer.debug_view();
    cout << integer.to_string() << endl;
    BigInteger integer2(-654321);
    integer2.debug_view();
    integer.add(integer2);
    cout << integer.to_string() << endl;
    // integer.debug_view();
    // assert(integer.to_string() == "777777");
}