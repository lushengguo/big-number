#include "Infinit_bit.hpp"
#include <iostream>
using namespace std;
using namespace DIY;
int main()
{
    InfinitBit bits;
    auto agent = bits.first_bit();
    for (int i = 0; i < 100; i++)
    {
        if (i % 2 == 0)
            agent.set();
        else
            agent.clear();
        bits.advance(agent);
    }

    bits.print();
}